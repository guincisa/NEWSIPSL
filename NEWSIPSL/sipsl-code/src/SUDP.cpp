//**********************************************************************************
//**********************************************************************************
//**********************************************************************************
// SIPCSL Sip Core And Service Layer
// Copyright (C) 2011 Guglielmo Incisa di Camerana
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//**********************************************************************************
//**********************************************************************************
//**********************************************************************************
#include <algorithm>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <iostream>
#include <map>
#include <memory>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>



#include "UTIL.h"

#ifndef CS_HEADERS_H
#include "CS_HEADERS.h"
#endif
#ifndef MESSAGE_H
#include "MESSAGE.h"
#endif
#ifndef SPIN_H
#include "SPIN.h"
#endif
#ifndef ENGINE_H
#include "ENGINE.h"
#endif
#ifndef SIPENGINE_H
#include "SIPENGINE.h"
#endif
#ifndef SL_CC_H
#include "SL_CC.h"
#endif
#ifndef ACTION_H
#include "ACTION.h"
#endif
#ifndef DOA_H
#include "DOA.h"
#endif
#ifndef SUDP_H
#include "SUDP.h"
#endif
#ifndef CALL_OSET_H
#include "CALL_OSET.h"
#endif
#ifndef COMAP_H
#include "COMAP.h"
#endif
#ifndef ALO_H
#include "ALO.h"
#endif
#ifndef VALO_H
#include "VALO.h"
#endif
#ifndef SIP_PROPERTIES_H
#include "SIP_PROPERTIES.h"
#endif
#ifndef ALARM_H
#include "ALARM.h"
#endif
#ifndef SIPUTIL_H
#include "SIPUTIL.h"
#endif
#ifndef TRNSPRT_H
#include "TRNSPRT.h"
#endif
#ifndef DAO_H
#include "DAO.h"
#endif


static SIPUTIL SipUtil;

// *****************************************************************************************
// Socket listener thread
// *****************************************************************************************
// *****************************************************************************************
extern "C" void* SUPDSTACK (void*);

void * SUDPSTACK(void *_tgtObject) {

	DBSUDP_3("SUDPSTACK thread id",pthread_self())
	DBSUDP_3("SUDPSTACK start","")

    SUDPtuple *tgtObject = (SUDPtuple *)_tgtObject;

    tgtObject->st->listen(tgtObject->thid);

    DBSUDP_3("SUDPSTACK started","")

    return (NULL);
}
// *****************************************************************************************
// Set DAO
// *****************************************************************************************
// *****************************************************************************************
void SUDP::setDAO(DAO* _dao) {
    dao = _dao;
}
// *****************************************************************************************
// Return processing type
// *****************************************************************************************
// *****************************************************************************************
int SUDP::getProcessingType(void){
	return processingType;
}
// *****************************************************************************************
// SUDP
// Initialize Stack
// *****************************************************************************************
// *****************************************************************************************
//void SUDP::init(int _port, ENGINE *_engine, DOA* _doa, string _domain, ALMGR* _alarm, bool singleThread){
void SUDP::init(int _port, TRNSPRT* _engine, string _domain, ALMGR* _alarm, bool singleThread){

	DBSUDP_3("SUDP init",_domain)

    domain = _domain;

    echoServPort = _port;

    transport = _engine;

    cliAddrLen = sizeof(echoClntAddr);

    alarm = _alarm;

    //doa = _doa;

    if ( singleThread ){
    	threadNum = 1;
    }else {
        threadNum = SUDPTH;
    }

    /* Create socket for sending datagrams */
	for (int i = 0 ; i <threadNum ; i++){
		if ((sock_se[i] = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
			DEBASSERT("socket() failed)")
			return;
		}
	}
    /* Create socket for receiving datagrams */
	if ((sock_re = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		DEBASSERT("socket() failed)")
		return;
	}

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    //Init mutex
#ifdef USEMESSAGEMAP
    for (int i = 0; i < MESSAGEMAPS;i++){
    	pthread_mutex_init(&messTableMtx[i],NULL);
    }
#endif
#ifdef USEMAPMODUL
#ifndef MAPMODULHYBRID
	pthread_mutex_init(&modulusMapMtx,NULL);
	modulusIter = 0;
#else
	for (int zi = 0 ; zi < PREMODMAP ; zi ++){
		pthread_mutex_init(&(modulusMapMtx[zi]),NULL);
		modulusIter[zi] = 0;
	}
#endif
#endif

    /* Bind to the local address */
	// moved to start
//	if (bind(sock_re, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
//		DEBERROR("bind() failed)");
//	}

	//DEFINE LOCAL ADDRESS for VIA
	char hostname[1024];
	char str[INET_ADDRSTRLEN];
	hostname[1023]='\0';
	gethostname(hostname,1023);

	struct addrinfo _hints, *info;
	memset(&_hints, 0, sizeof _hints);
	_hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
	_hints.ai_socktype = SOCK_DGRAM;

	char ss[GENSTRINGLEN];
	sprintf(ss,"%d",echoServPort);
	localport = ss;

	if (getaddrinfo(hostname, ss, &_hints, &info) != 0) {
	    DEBASSERT("getaddrinfo")
	}
	inet_ntop(AF_INET, &((struct sockaddr_in *) info->ai_addr)->sin_addr, str, INET_ADDRSTRLEN);
	localip = str;
	DBSUDP("local ip address",localip<<"]["<<localport)
	// END DEFINE LOCAL ADDRESS
#ifdef VODAFONEBB
	localip = "sipsl.ddns.net";
#endif
	//sipengine->linkSUDP(this);

	DBSUDP_3("SUDP init done","")

    return;
}

// *****************************************************************************************
// Start Stack
// *****************************************************************************************
// *****************************************************************************************
void SUDP::start(int _processingType) {

	processingType = _processingType;

    // allocate thread and starts

#ifdef OSX
	if (bind((int)sock_re, (const struct sockaddr *) &echoServAddr, (socklen_t) sizeof(echoServAddr)) < 0) {
		//bind(int, const struct sockaddr *, socklen_t) __DARWIN_ALIAS(bind);
        DEBERROR("bind() failed)");
	}
#else
    if (bind(sock_re, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0) {
        DEBERROR("bind() failed)");
    }
#endif

	DBSUDP_3("SUDP::start threads",threadNum)
	SUDPtuple *t1[threadNum*2];

	for (int i = 0 ; i <(2*threadNum) ; i++){
	    NEWPTR2(listenerThread[i], ThreadWrapper,"ThreadWrapper"<<i)

	    NEWPTR2(t1[i], SUDPtuple,"SUDPtuple")
	    t1[i]->st = this;
	    t1[i]->thid = i;

	    pthread_create(&(listenerThread[i]->thread), NULL, SUDPSTACK, (void *) t1[i] );

	}

    return;
}

// *****************************************************************************************
// Listen to network
// *****************************************************************************************
void SUDP::listen(int _socknum) {

	//processing type
	// If router then I can receive
	//  [network] -> SUDP
	//  [C_PROC] -> SUDP
	// we distinguish in transport

    TIMEDEF

	DBSUDP_3("SUDP::listen","listen " << _socknum)
    char echoBuffer[ECHOMAX];

    sockaddr_inX _echoClntAddr;
    unsigned int _cliAddrLen;

    for (;;){
        /* Block until receive message from a client */
        memset(&echoBuffer, 0x0, ECHOMAX);
        int recvMsgSize;
        int _sok;
        if ( _socknum < threadNum ){
        	_sok = sock_se[_socknum];
        }
        else {
        	_sok = sock_re;
        }
        if ((recvMsgSize = recvfrom(_sok, echoBuffer, ECHOMAX, 0,
            (struct sockaddr *) &_echoClntAddr, (socklen_t*)&_cliAddrLen)) < 0) {
            DEBERROR("SUDP::listen() recvfrom() failed")
        }else if ( recvMsgSize < 1){
        	DEBERROR("SUDP::listen() abnormal message")
        }else {
        	SETNOW
            PROFILE("SUDP:Message arrived from socket")
            //Message handling
            MESSAGE* message=0x0;

            CREATENEWMESSAGE_EXT(message, echoBuffer, _sok, _echoClntAddr, SODE_NTWPOINT)
            if (message != 0x0 ){
            	DBSUDP_3("New message from buffer ", message)
				DBSUDP("SINPORT",echoClntAddr.sin_port)
				DBSUDP("SINPORT",ntohs(echoClntAddr.sin_port))

				//problem if not sip...?
                message->fillIn();

                DEBOUT("MODULUS DEBUG",message->getModulus())

                //engine->p_w((void*)message);
                transport->upCall(message);
                PRINTDIFF("SUDP listen")
            }else {
                DEBERROR("SUDP::listen() could not allocate memory for incoming message")
            }
            CALCPERF("SUDP::listen() Message sent to SIPENGINE",1)
        }
    }
}
// *****************************************************************************************
// getters
// *****************************************************************************************
// *****************************************************************************************
string SUDP::getDomain(void) {
    return domain;
}
int SUDP::getPort(void){
	return echoServPort;
}
ALMGR* SUDP::getAlmgr(void){
	return alarm;
}
//void SUDP::sendRequest(MESSAGE* _message){
//	DEBINFSUDP("void SUDP::sendRequest(MESSAGE* _message)",_message)
//
//    struct sockaddr_in si_part;
//    struct hostent *host;
//    memset((char *) &si_part, 0, sizeof(si_part));
//
//    DEBMESSAGE("SUDP::sendRequest sending Message ", _message)
//
//    pair<string,int> _pair = _message->getUri("REQUEST");
//    const char* _hostchar = _pair.first.c_str();
//    host = gethostbyname(_hostchar);
//    if (host == NULL){
//    	DEBASSERT("host = gethostbyname(_hostchar); is null "<< _hostchar)
//    }
//
//    si_part.sin_family = AF_INET;
//    si_part.sin_port = htons(_pair.second);
//    //core qui
//    si_part.sin_addr = *( struct in_addr*)( host -> h_addr_list[0]);
//
//    int i = _message->getModulus() % threadNum;
//
//    sendto(sock_se[i], _message->getMessageBuffer(), strlen(_message->getMessageBuffer()) , 0, (struct sockaddr *)&si_part, sizeof(si_part));
//    if (!_message->getLock()){
//        PURGEMESSAGE(_message)
//    }
//
//    return;
//}
void SUDP::sendRawMessage(string* message, string address, int port){

	struct sockaddr_in si_part;
	si_part.sin_family = AF_INET;
	si_part.sin_port = port;

	inet_aton(address.c_str(), &si_part.sin_addr);

	//heart beat messages always sent to socket 0
	sendto(sock_se[0], message->c_str(), message->length(), 0, (struct sockaddr *)&si_part, sizeof(si_part));
	DEBY

}
void SUDP::sendRequest(MESSAGE* _message){
	DBSUDP_3("void SUDP::sendRequest(MESSAGE* _message)",_message)

    TIMEDEF
    SETNOW

#ifdef IPNUMERIC

    pair<string,string> _pair;
    if(_message->hasRoute()){
    	_pair = _message->getRoute();
    	DBSUDP("hasroute",_pair.first<<"]["<<_pair.second)
    }
    else if (_message->natTraversal()){
    	_pair = _message->getNatAddress();
    	DBSUDP("hasNat",_pair.first<<"]["<<_pair.second)
    }
    else{
#ifdef VODAFONEBB
    	//get the called user id
    	DBSUDP("getHeadTo",_message->getHeadTo())
		DBSUDP("getHeadToName",_message->getHeadToName())

		//non arriva
		//riprova 5060

		_pair = brkin2string(dao->getData(TBL_REGISTER,_message->getHeadToName()), ":");
    	DBSUDP("Use REGISTER table",_pair.first<<"]["<<_pair.second)

#else
    	_pair = _message->getRequestUriProtocol();
    	DBSUDP("use request",_pair.first<<"]["<<_pair.second)
#endif
    }
    DBSUDP("sending to",_pair.first<<"]["<<_pair.second)
    const char* _hostchar = _pair.first.c_str();

	struct sockaddr_in si_part;
	si_part.sin_family = AF_INET;
	si_part.sin_port = htons(atoi(_pair.second.c_str()));

	inet_aton(_hostchar, &si_part.sin_addr);

    int i = _message->getModulus() % threadNum;

	sendto(sock_se[i], _message->getMessageBuffer(),strlen(_message->getMessageBuffer()) , 0, (struct sockaddr *)&si_part, sizeof(si_part));
    if (!_message->getLock()){
        PURGEMESSAGE(_message)
    }
	PRINTDIFF("IPNUMERIC SUDP::sendRequest")

    return;


#else

    pair<string,string> _pair;
    if(_message->hasRoute()){
    	_pair = _message->getRoute();
        DEBOUT("hasroute",_pair.first<<"]["<<_pair.second)
    }
    else if (_message->natTraversal()){
    	_pair = _message->getNatAddress();
        DEBOUT("hasNat",_pair.first<<"]["<<_pair.second)
    }
    else{
    	_pair = _message->getRequestUriProtocol();
    	DEBOUT("use request",_pair.first<<"]["<<_pair.second)
    }
    DEBOUT("sending to",_pair.first<<"]["<<_pair.second)
    const char* _hostchar = _pair.first.c_str();

    struct addrinfo hints,*servinfo;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICHOST;

	int res = getaddrinfo(_hostchar,_pair.second.c_str(),&hints, &servinfo);

	if (res != 0){
		DEBASSERT("getaddrinfo")
	}

    int i = _message->getModulus() % threadNum;

    //CHECK ERROR HERE
    sendto(sock_se[i], _message->getMessageBuffer(), strlen(_message->getMessageBuffer()) , 0, servinfo->ai_addr, servinfo->ai_addrlen);
    if (!_message->getLock()){
        PURGEMESSAGE(_message)
    }
    freeaddrinfo(servinfo);
	PRINTDIFF("NON IPNUMERIC SUDP::sendRequest")

    return;
#endif
}

void SUDP::sendReply(MESSAGE* _message){
	DBSUDP_3("void SUDP::sendReply(MESSAGE* _message)",_message)

	TIMEDEF
	SETNOW

#ifdef IPNUMERIC

	string receivedProp = _message->getProperty("Via:","received");
	const char* _hostchar;
	char cstr[256];
	string reportPro;
	DBSUDP("receivedProp",receivedProp)
	if (receivedProp.length() != 0){
		reportPro = _message->getProperty("Via:","rport");
		strcpy(cstr, receivedProp.c_str());
	}else{
		DBSUDP("_message->getViaUriHost()",_message->getViaUriHost())
		strcpy(cstr, _message->getViaUriHost().c_str());
	}
	_hostchar = cstr;
	DBSUDP("PORT",_message->getEchoClntAddr().sin_port)
	DBSUDP("ReplyHost",_hostchar)
	DBSUDP("reportPro",reportPro)
	//DEBOUT("PORT",_message->getEchoClntAddr().sin_port);

	DBSUDP("reply message", _message->getMessageBuffer())

	struct sockaddr_in si_part;
	si_part.sin_family = AF_INET;
	si_part.sin_port = _message->getEchoClntAddr().sin_port;

	inet_aton(_hostchar, &si_part.sin_addr);
	sendto(sock_re, _message->getMessageBuffer(),strlen(_message->getMessageBuffer()) , 0, (struct sockaddr *)&si_part, sizeof(si_part));

    if (!_message->getLock()){
        PURGEMESSAGE(_message)
    }
	PRINTDIFF("IPNUMERIC SUDP::sendReply")


	return;

#else

    //Reply uses topmost Via header

	DEBSUP_3("SUDP::sendReply sending Message ", _message)
    struct addrinfo hints,*servinfo;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICHOST;

//    string receivedProp = _message->getProperty("Via:","received");
//    if (receivedProp.length() != 0){
//        string reportPro = _message->getProperty("Via:","rport");
//        const char* _hostchar = receivedProp.c_str();
//        int res = getaddrinfo(_hostchar,reportPro.c_str(),&hints, &servinfo);
//        if (res != 0){
//        	DEBASSERT("getaddrinfo")
//        }
//
//    }else{
//        const char* _hostchar = _message->getViaUriHost().c_str();
//        int res = getaddrinfo(_hostchar,_message->getViaUriProtocol().c_str(),&hints, &servinfo);
//        if (res != 0){
//        	DEBASSERT("getaddrinfo")
//        }
//    }
	const char* _hostchar = inet_ntoa(_message->getEchoClntAddr().sin_addr);
	char xx[GENSTRINGLEN];
	sprintf(xx,"%d",ntohs((_message->getEchoClntAddr()).sin_port));

	DEBSUP("sendReply to", _hostchar <<"]["<<xx)
	int res = getaddrinfo(_hostchar,xx,&hints, &servinfo);
	if (res != 0){
		DEBASSERT("getaddrinfo")
	}

    //CHECK ERROR HERE
    sendto(sock_re,  _message->getMessageBuffer(), strlen(_message->getMessageBuffer()) , 0, servinfo->ai_addr, servinfo->ai_addrlen);
    if (!_message->getLock()){
        PURGEMESSAGE(_message)
    }
    freeaddrinfo(servinfo);
	PRINTDIFF("NON IPNUMERIC SUDP::sendReply")
    return;

#endif
}
string SUDP::getLocalIp(void){
	return localip;
}
string SUDP::getLocalPort(void){
	return localport;
}
int SUDP::getRealm(void){
	return realm;
}

//void SUDP::sendReply(MESSAGE* _message){
//	DEBINFSUDP("void SUDP::sendReply(MESSAGE* _message)",_message)
//
//    //Reply uses topmost Via header
//
//    struct sockaddr_in si_part;
//    struct hostent *host;
//    memset((char *) &si_part, 0, sizeof(si_part));
//
//    DEBMESSAGE("SUDP::sendReply sending Message ", _message)
//
//
//    const char* _hostchar = _message->getViaUriHost().c_str();
//    host = gethostbyname(_hostchar);
//    if (host == NULL){
//    	DEBASSERT("host = gethostbyname(_hostchar); is null "<< _hostchar)
//    }
//
//    si_part.sin_family = AF_INET;
//    //core qui
//    si_part.sin_addr = *( struct in_addr*)( host -> h_addr_list[0]);
//    si_part.sin_port = htons(_message->getViaUriPort());
//
//    sendto(sock_re,  _message->getMessageBuffer(), strlen(_message->getMessageBuffer()) , 0, (struct sockaddr *)&si_part, sizeof(si_part));
//    if (!_message->getLock()){
//        PURGEMESSAGE(_message)
//    }
//    return;
//}
