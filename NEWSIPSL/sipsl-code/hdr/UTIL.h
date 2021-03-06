//**********************************************************************************
//**********************************************************************************
//**********************************************************************************
// SIPSL Sip Service Layer
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
//Per far funzionare devi provisionare!!!
//lancia sipsl
//SIPSL A 127.0.0.1 9000 9001 (active mateadrress mateport)
//lancia su un'altra finestra sotto test-tools
//java sendU3 grog
//poi provisiona:
//PD-SIPSL
//0%i%127.0.0.1:5061%service@127.0.0.1:5061
//send
//controllare host file con sipsl.ddns.net (?)


#ifndef UTIL_H
#define UTIL_H

extern double PERFARRAY[4][50];

#define CALL_REALM 1
#define MESSAGE_REALM 2
#define SIPSL_REALM CALL_REALM

//Processing type
#define STAND_ALONE 0
#define CALL_DISTRIBUTOR 1
#define CALL_PROCESSOR 2

#define SPARC

#define OSX

//set SIPSL to work with Vodafone bb
// SIPSL run on linux behind Vodafone router
// Vodafone router modifies URI putting the local address of the server:
// REGISTER sip:192.168.1.9:5060 SIP/2.0^M
// this can be avoided by changing the sip default, but then the 200OK is not sent back correctly (to be investigated)
//
// V1 changes to set up the call
//#define VODAFONEBB

using namespace std;

#define WINDOWS
#ifdef WINDOWS
typedef time_t __time_t;
#endif

typedef long long int lli;

typedef struct {
	struct timeval tv;
	struct timezone tz;
} SysTime;

#define ECHOMAX 2048
#define GENSTRINGLEN 128

class ThreadWrapper {
    public:
        pthread_t thread;
        //pthread_mutex_t mutex;
        ThreadWrapper();
};

//Tuning
//COMAPS: number of comaps
//COMAPS: number of gloabl message tables
//MAXTHREADS: threads initialized in ENGINE
//SIPENGINETH: SIPENGINE activated threads
//SL_CCTH: SL_CC activated threads
//ARR: dimension of the buffer
//ARR_SHORT: dimension of the overload buffer
//SPINC_MOD: number of locks in the buffer
//DOA_CLEANUP: seconds every loop of the DOA
//TIMER_DOA: milliseconds before a call_oset is set to DELETED
//TIMER_DOA / 2 : milliseconds before a DELETED call_oset if purged

//#define NOLOGATALL

#define SPINSTL

#ifndef SPARC
#define ADDRESSPACE 8
#else
#define ADDRESSPACE 8
#endif

//#define VODAFONEBB

#ifdef SPARC

#define GETDATA "service@10.10.10.249:5062"
//#define GETDATA "service@10.21.99.81:5062"

//The call_oset and valo do not reinject the message
//but recall the sl_co->call
#define NONESTEDPW

//Invert the get call_oset lock and release comap lok
//should core if inverted
//test shows that it is incorrect... don't uncomment
//#define WRONGLOCKMGMT

//uses two loks for call_oset server side and client side
//if WRONGLOCKMGMT is commented then this one blocks the SIPSL
//leave commented
//#define SV_CL_MUTEX

//Use the gobalmessagetable
//#define USEMESSAGEMAP

//The state machine will send the message directly to transport
#define USEFASTSEND

//The try is sent by SL_CC
#define QUICKTRY

//use map instead of calculating the modulus
#define USEMAPMODUL
#define MAPMODULHYBRID

//send reply and request are always with numeric IP
#define IPNUMERIC

//#define USETRYLOCK

//Sudp threads
// its x 2
#define SUDPTH 3

//Max engine threads
//128
#define MAXTHREADS 6
#define MAXMAPS 6

//128
#define SIPENGINETH 4
//64
#define SIPENGINMAPS 4

//64
#define TRNSPRTTH 3
//32
#define TRNSPRTMAPS 3

//128
#define SL_CCTH 7
//32
#define SL_CCMAPS 7

// end threds

#define CALLPROCESSOR 3
#define LOADBALANCER 2
#define STANDALONE 1


//#define ENGINEMAPS 5
#define ALARMTH 1
#define ALARMMAPS 1
#define ALARMENGINE
#define TRYMAXLOCKALARM 9
#define INHIBITALARM

//number of maps for message module when using MAPMODULHYBRID
#define PREMODMAP 10
#define COMAPS 300
#define COMAPS_DIG 3
#define MESSAGEMAPS 100

#define ARR 4000
#define ARR_SHORT 30
#define SPINC_MOD 50

//intervallo attesa loop secs
#define DOA_CLEANUP 10
//time before object moves to deleted
#define TIMER_DOA 5000000
//COMAPS must be divisble by DOATH
#define DOATH 2

//DATA TABLES
#define TBL_ROUTE 0
#define TBL_NAT 1
#define TBL_REGISTER 2
#define TBL_SIPSL_PROC 10
#define TBL_SUBSCRIBER_PROC 11
#define TABLES 12


//uncomment for profiling
//#define PROFILING
//#define PROFILELOCK
//#define PROFILELOCKCALC

#define CHECKDOA

#define NOWARNINGS

//define this to full log (old method)
//#define LOGLEVL1
#ifdef LOGLEVL1
#define LOGMIN
#define PROFILELOCK

#define LOGSIPHIGH
#define LOGSIPLOW
#define LOGINF
#define LOGDEV
//#define LOGMEM
#define DEBCODEALARM1
#define LOGINFMESSAGE_MIN
#define LOGINFCALLOSET
#endif

//#define LOGLEVL2
#ifdef LOGLEVL2
#define LOGINFMESSAGE
#define LOGLOK

//#define LOGINCOMAP_H

#define LOGINFSUDP
//#define LOGMIN
//#define LOGNTW
//#define SELFCHECK
//#define DEBCODE
//#define MESSAGEUSAGE
#endif

#define SHOWFLOWLOG
#ifdef SHOWFLOWLOG
#undef NOWARNINGS
#define LOGMIN
#define LOGDEV
#define LOGSIPHIGH
#define LOGPTR
#define LOGALO
#endif

//willgo getDoa everytime a call to call_oset is done
//needed to check is call_oset is deleted

//SEAMLESS FAILOVER
//hearbeat
#define HEARTBEATPULSE 5

#else
//#define GETDATA "service@10.21.99.79:5062"
//#define GETDATA "service@10.21.99.81:5062"

//The call_oset and valo do not reinject the message
//but recall the sl_co->call
#define NONESTEDPW

//Invert the get call_oset lock and release comap lok
//should core if inverted
//test shows that it is incorrect... don't uncomment
//#define WRONGLOCKMGMT

//uses two loks for call_oset server side and client side
//if WRONGLOCKMGMT is commented then this one blocks the SIPSL
//leave commented
//#define SV_CL_MUTEX

//Use the gobalmessagetable
//#define USEMESSAGEMAP

//The state machine will send the message directly to transport
#define USEFASTSEND

//The try is sent by SL_CC
#define QUICKTRY

//use map instead of calculating the modulus
#define USEMAPMODUL
#define MAPMODULHYBRID

//#define USETRYLOCK

//Sudp threads
// its x 2
#define SUDPTH 1

//Max engine threads
//128
#define MAXTHREADS 8
#define MAXMAPS 8
#define MAXTH_Q 1


//128
#define SIPENGINETH 3
//64
#define SIPENGINMAPS 3
#define SIPENGINTH_Q 1


//64
#define TRNSPRTTH 2
//32
#define TRNSPRTMAPS 2
#define TRNSPRTTH_Q 1


//128
#define SL_CCTH 6
//32
#define SL_CCMAPS 6
#define SL_CCTH_Q 1


//#define ENGINEMAPS 5
#define ALARMTH 1
#define ALARMMAPS 1
#define ALARMENGINE
#define TRYMAXLOCKALARM 9
#define INHIBITALARM

//number of maps for message module when using MAPMODULHYBRID
#define PREMODMAP 20
#define COMAPS 600
#define COMAPS_DIG 3
#define MESSAGEMAPS 100

#define ARR 4000
#define ARR_SHORT 30
#define SPINC_MOD 50

//intervallo attesa loop secs
#define DOA_CLEANUP 10
//time before object moves to deleted
#define TIMER_DOA 5000000
//COMAPS must be divisble by DOATH
#define DOATH 2

#define PROFILING
#define PROFILELOCK
#define PROFILELOCKCALC
#define TUNEPERF

#define CHECKDOA

#define NOWARNINGS

#define LOGLEVL1
#ifdef LOGLEVL1
#define LOGMIN
#define PROFILELOCK

#define LOGSIPHIGH
#define LOGSIPLOW
#define LOGINF
#define LOGDEV
#define LOGMEM
#define DEBCODEALARM1
#define LOGINFMESSAGE_MIN
#define LOGINFCALLOSET
#endif

#define LOGLEVL2
#ifdef LOGLEVL2
#define LOGINFMESSAGE
//#define LOGLOK

//#define LOGINCOMAP_H

#define LOGINFSUDP
//#define LOGMIN
//#define LOGNTW
//#define SELFCHECK
#define DEBCODE
//#define MESSAGEUSAGE
#endif

#define SHOWFLOWLOG
#ifdef SHOWFLOWLOG
#undef NOWARNINGS
#define LOGMIN
#define LOGDEV
#define LOGSIPHIGH
#define LOGPTR
#define LOGINFMESSAGE
#endif

//willgo getDoa everytime a call to call_oset is done
//needed to check is call_oset is deleted


//#define GETDATA "service@127.0.0.1:5062"
//
////The call_oset and valo do not reinject the message
////but recall the sl_co->call
//#define NONESTEDPW
//
////Invert the get call_oset lock and release comap lok
////should core if inverted
////test shows that it is incorrect... don't uncomment
////#define WRONGLOCKMGMT
//
////uses two loks for call_oset server side and client side
////if WRONGLOCKMGMT is commented then this one blocks the SIPSL
////leave commented
////#define SV_CL_MUTEX
//
////Use the gobalmessagetable
////#define USEMESSAGEMAP
//
////The state machine will send the message directly to transport
//#define USEFASTSEND
//
////The try is sent by SL_CC
//#define QUICKTRY
//
////use map instead of calculating the modulus
//#define USEMAPMODUL
//
////#define USETRYLOCK
//
////Sudp threads
////24
//#define SUDPTH 4
//
////Max engine threads
////128
//#define MAXTHREADS 16
//
////128
//#define SIPENGINETH 4
////64
//#define SIPENGINMAPS 2
//
////64
//#define TRNSPRTTH 4
////32
//#define TRNSPRTMAPS 2
//
////128
//#define SL_CCTH 16
////32
//#define SL_CCMAPS 4
//
////#define ENGINEMAPS 5
//#define ALARMTH 4
//#define ALARMMAPS 1
//#define ALARMENGINE
//#define TRYMAXLOCKALARM 9
//#define INHIBITALARM
//
//#define COMAPS 400
//#define COMAPS_DIG 3
//#define MESSAGEMAPS 100
//
//#define ARR 4000
//#define ARR_SHORT 30
//#define SPINC_MOD 50
//
//#define DOA_CLEANUP 3
//#define TIMER_DOA 5000000
//
//#define PROFILING
//#define PROFILELOCK
//
//#define CHECKDOA
//
////#define LOGLEVL1
//#ifdef LOGLEVL1
//#define LOGMIN
//#define PROFILELOCK
//
//#define LOGSIPHIGH
//#define LOGSIPLOW
//#define LOGINF
//#define LOGDEV
//#define LOGMEM
//#define DEBCODEALARM1
//#define LOGINFMESSAGE_MIN
//#define LOGINFCALLOSET
//#endif
//
////#define LOGLEVL2
//#ifdef LOGLEVL2
//#define LOGINFMESSAGE
////#define LOGLOK
//
////#define LOGINCOMAP_H
//
////#define LOGINFSUDP
////#define LOGMIN
////#define LOGNTW
////#define SELFCHECK
////#define DEBCODE
////#define MESSAGEUSAGE
//#endif
//
////willgo getDoa everytime a call to call_oset is done
////needed to check is call_oset is deleted


#endif
//end if SPARC

//struct timeval tv;
//time_t nowtime;
//struct tm *nowtm;
//char tmbuf[64], buf[64];
//
//gettimeofday(&tv, NULL);
//nowtime = tv.tv_sec;
//nowtm = localtime(&nowtime);
//strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
//snprintf(buf, sizeof buf, "%s.%06d", tmbuf, tv.tv_usec);
////Mandatory

#define TIME_S {SysTime mytime; gettimeofday(&mytime.tv, &mytime.tz);\
		char _bu2[64];\
           time_t t;\
           struct tm *tmp;\
           t = time(NULL);\
           tmp = localtime(&t);\
           strftime(_bu2, sizeof _bu2 , "%Y-%m-%d %H:%M:%S", tmp);\
           sprintf(bu2,"%s.%06ld",_bu2,mytime.tv.tv_usec);\
       	   }

//BASE logger
#define BDEBUG(m1, m2) {stringstream xx ; \
		char bu2[200];\
		cout.precision(20);\
		TIME_S\
		xx <<"+++ "<< m1 << "\n" << "[" << pthread_self() <<" " << bu2 <<"]" <<  __FILE__ << " " <<__LINE__ << "\n[" << m2 << "]\n---\n"; \
		cout << xx.str();cout.flush();}
//**********************************************************
#undef DEBASSERT
#define DEBASSERT(m1)  {BDEBUG("DEBASSERT",m1);assert(0);}
#ifndef NOWARNINGS
#undef DEBWARNING
#define DEBWARNING(m1,m2)  BDEBUG("******************************\n   WARNING   \n******************************\n"<<m1,m2)
#else
#undef DEBWARNING
#define DEBWARNING(m1,m2)
#endif

//#define DEBASSERT(m1) {cout << "\n\nDEBASSERT [" << pthread_self() << "] "<< __FILE__ << " " << __LINE__<< " ******" << m1 << "*****" << endl<<endl<< endl; cout.flush();assert(0);}
//**********************************************************
#define WAITTIME { timespec sleep_time; \
	sleep_time.tv_sec = 20;\
	sleep_time.tv_nsec = 0;\
	nanosleep(&sleep_time,NULL);}


#define GETTIME(mytime) gettimeofday(&mytime.tv, &mytime.tz);

//HANDLER - Reference to Pointer
#define MKHANDMESSAGE(pointer,reference) \
		MESSAGE* pointer;\
		MESSAGE*& reference = pointer;

#define MESSAGEH MESSAGE*&

#ifndef LOGPTR
#undef NEWPTR
#define NEWPTR(type, m1, m2,mess) type m1 = 0x0;\
	m1 = new (nothrow) m2;\
	if (m1 == 0x0) { DEBASSERT("Alloc failed")}
//no embedded declaration
#undef  NEWPTR2
#define NEWPTR2(m1, m2, mess) m1 = 0x0;\
	m1 = new (nothrow) m2;\
	if (m1 == 0x0) { DEBASSERT("Alloc failed")}
#undef DELPTR
#define DELPTR(m1, mess) \
		delete m1;
#undef DELPTRARR
#define DELPTRARR(m1, mess) \
		delete[] m1;
#else
#define NEWPTR(type, m1, m2,mess) type m1 = 0x0;\
	try {\
		m1 = new m2;\
		DEBOUT("NEW ", mess <<"]["<<m1)\
		if (m1 == 0x0){\
			DEBASSERT("NEWPTR failed")\
		}\
	}\
	catch (bad_alloc &b){\
		DEBOUT("NEW BAD ALLOC",b.what())\
		DEBASSERT("BAD ALLOC")\
	}
	//**********************************************************
//no embedded declaration
#define NEWPTR2(m1, m2,mess) m1 = 0x0;\
	try {\
		m1 = new m2;\
		DEBOUT("NEW ", mess <<"]["<<m1)\
		if (m1 == 0x0){\
			DEBASSERT("NEWPTR failed")\
		}\
	}\
	catch (bad_alloc &b){\
		DEBOUT("NEW BAD ALLOC",b.what())\
		DEBASSERT("BAD ALLOC")\
	}

	//**********************************************************
#define DELPTR(m1, mess) \
		DEBOUT("DELPTR",mess<<"]["<<m1)\
		delete m1;
#define DELPTRARR(m1, mess) \
		DEBOUT("DELPTRARR",mess<<"]["<<m1)\
		delete[] m1;
#endif

//******************************************************************************

#undef TRYCATCH
#define TRYCATCH(m) try { m; } catch (exception& e) { DEBOUT("TRYCATCH", e.what()) DEBASSERT("Exception")}
#undef PURGEMESSAGE

#ifdef USEMESSAGEMAP
#define PURGEMESSAGE(m1)  { \
	if (m1 == MainMessage){DEBASSERT("Purging MainMessage")}\
	if (m1->getLock()) {DEBASSERT("Purging a locked message")}\
	map<const MESSAGE*, MESSAGE*>::iterator p; \
	int i = getModulus(m1);\
	GETLOCK(&messTableMtx[i],"&messTableMtx"<<i,30);\
	p = globalMessTable[i].find(m1);\
	if (p !=globalMessTable[i].end()) {\
		globalMessTable[i].erase(m1);\
		DELPTR(m1,"MESSAGE");\
		m1 = MainMessage; \
	}\
	RELLOCK(&messTableMtx[i],"&messTableMtx"<<i);}
#define CREATEMESSAGE(m1, m2, gen, dest) MESSAGE* m1=0x0; {char bu[512];\
				SysTime inTime;\
				GETTIME(inTime);\
				NEWPTR2(m1, MESSAGE(m2, gen, inTime),"MESSAGE");\
				m1->setDestEntity(dest);\
				int i= m1->fillIn();\
				DEBDEV("New MESSAGE"," " << i);\
				long long int num = ((long long int) inTime.tv.tv_sec)*1000000+(long long int)inTime.tv.tv_usec;\
				sprintf(bu, "%x%llu",(unsigned int)m1,num);\
				string key(bu);\
				m1->setKey(key);\
				int j = getModulus(m1);\
				GETLOCK(&messTableMtx[j],"&messTableMtx"<<j,30);\
				globalMessTable[j].insert(pair<const MESSAGE*, MESSAGE*>(m1, m1));\
				RELLOCK(&messTableMtx[j],"&messTableMtx"<<j);}

#define CREATENEWMESSAGE_EXT(__mess, __echob, __sock, __echoAddr, __sode) {char bu[512];\
				SysTime inTime;\
				GETTIME(inTime);\
				NEWPTR2(__mess, MESSAGE(__echob, __sode, inTime, __sock, __echoAddr),"MESSAGE");\
				DEBY \
				if (__mess != 0x0 ) {long long int num = ((long long int) inTime.tv.tv_sec)*1000000+(long long int)inTime.tv.tv_usec;\
				sprintf(bu, "%x%llu",(unsigned int)__mess,num);\
				string key(bu);\
				__mess->setKey(key);\
				int i = getModulus(__mess);\
				GETLOCK(&messTableMtx[i],"&messTableMtx"<<i,30);\
				globalMessTable[i].insert(pair<const MESSAGE*, MESSAGE*>(__mess, __mess));\
				RELLOCK(&messTableMtx[i],"&messTableMtx"<<i);}}
#else
#define PURGEMESSAGE(m1)  DELPTR(m1,"MESSAGE")
#define CREATEMESSAGE(m1, m2, gen, dest) MESSAGE* m1=NULL; {char bu[512];\
				SysTime inTime;\
				GETTIME(inTime);\
				NEWPTR2(m1, MESSAGE(m2, gen, inTime),"MESSAGE");\
				m1->setDestEntity(dest);\
				int i= m1->fillIn();\
				DEBDEV("New MESSAGE"," " << i);\
				long long int num = ((long long int) inTime.tv.tv_sec)*1000000+(long long int)inTime.tv.tv_usec;\
				sprintf(bu, "%x%llu",m1,num);\
				string key(bu);\
				m1->setKey(key);}

#define CREATENEWMESSAGE_EXT(__mess, __echob, __sock, __echoAddr, __sode) {char bu[512];\
				SysTime inTime;\
				GETTIME(inTime);\
				NEWPTR2(__mess, MESSAGE(__echob, __sode, inTime, __sock, __echoAddr),"MESSAGE");\
				DEBY \
				if (__mess != 0x0 ) {long long int num = ((long long int) inTime.tv.tv_sec)*1000000+(long long int)inTime.tv.tv_usec;\
				sprintf(bu, "%x%llu",__mess,num);\
				string key(bu);\
				__mess->setKey(key);}}

#endif

//**********************************************************
#ifdef LOGALO
#define DEBALO(m1,m2) DEBOUT("DEBALO " << m1, m2)
#else
#define DEBALO(m1,m2)
#endif
#ifdef LOGSIPLOW
#define LOGSIPHIGH

	//**********************************************************
#undef DEBSIP
#define DEBSIP(m1,m2)  {BDEBUG("DEBSIP",m2)}
	//**********************************************************
#else
#define DEBSIP(m1,m2)
#define DEBMESSAGE(m1,m2)
#define DEBMESSAGESHORT(m1,m2)
#endif
#ifdef LOGSIPHIGH
#undef DEBMESSAGE
#define DEBMESSAGE(m1,m2) {BDEBUG("DEBMESS",m1 << "\n" << "**************** MESSAGE CONTENT ***************************\n[" <<m2->getKey() << "] Gen [" <<m2->getGenEntity() << "] Dest ["<<m2->getDestEntity() <<"]\n["<< m2->getOriginalString() << "]\n*********************************************************\n")}
//**********************************************************
#undef DEBMESSAGESHORT
#define DEBMESSAGESHORT(m1,m2) {stringstream xx ; xx << "DEBMESS [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "\n" << "**************** MESSAGE EXTRACTS ***************************\n[" << m2 << "]\n[" <<m2->getKey() << "]\n["<< m2->getFirstLine() << "]\n*********************************************************\n"; cout << xx.str();cout.flush();}
#endif
//**********************************************************
//**********************************************************
#ifdef LOGNTW
//1 288 696 804 323 901
//1.288.696.804.323.901
#undef PRTIME
#define PRTIME {SysTime mytime; gettimeofday(&mytime.tv, &mytime.tz);\
		long long int num = ((long long int) mytime.tv.tv_sec)*1000000+(long long int)mytime.tv.tv_usec;\
		char bu[128];\
		sprintf(bu, "%llu",num);\
		string time(bu);\
		stringstream xx ; xx << "TIME [" << time.substr(0,1) << "." << time.substr(1,3) << "." << time.substr(4,3)<< "-" << time.substr(7,3)<< "-" << time.substr(10,3)<< "." << time.substr(13,3)<<"]\n"; cout << xx.str();cout.flush();}
#undef PRTIME_F
#define PRTIME_F(m) {\
		char bu[128];\
		sprintf(bu, "%llu",m);\
		string time(bu);\
		stringstream xx ; xx << "TIME [" << time.substr(0,1) << "." << time.substr(1,3) << "." << time.substr(4,3)<< "-" << time.substr(7,3)<< "-" << time.substr(10,3)<< "." << time.substr(13,3)<<"]\n"; cout << xx.str();cout.flush();}
#undef DEBNTW
#define DEBNTW(m1,m2)  {stringstream xx ; xx << "DEBINF [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
#else
#define DEBNTW(m1,m2)
#define PRTIME
#define PRTIME_F(m)
#endif
//**********************************************************
//**********************************************************
#define DEBCOMAP_H(m1,m2)
#ifdef LOGINCOMAP_H
#undef DEBCOMAP_H
#define DEBCOMAP_H(m1,m2) BDEBUG("DEBCOMAP_H", m1 << "[" << m2)
#endif
#define DEBCOMAP_L(m1,m2)
#ifdef LOGINCOMAP_L
#undef DEBCOMAP_L
#define DEBCOMAP_L BDEBUG("DEBCOMAP_H", m1 << "[" << m2)
#endif

#define DEBINFSUDP(m1,m2)
#ifdef LOGINFSUDP
#undef DEBINFSUDP
#define DEBINFSUDP(m1,m2) BDEBUG("DEBINFSUDP", m1 << "[" << m2)
//#define DEBINF(m1,m2)  {stringstream xx ; xx << "DEBINF [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
#endif

//**********************************************************
//**********************************************************
#define DEBINFMESSAGE(m1,m2)
#define DEBINFMESSAGE_MIN(m1,m2)
#ifdef LOGINFMESSAGE
#define LOGINFMESSAGE_MIN
	//**********************************************************
#undef DEBINFMESSAGE
#undef DEBINFMESSAGE_MIN
#define DEBINFMESSAGE(m1,m2) BDEBUG("DEBINFMESSAGE", m1 << "[" << m2)
#define DEBINFMESSAGE_MIN(m1,m2) BDEBUG("DEBINFMESSAGE_MIN", m1 << "[" << m2)
#endif
#ifdef LOGINFMESSAGE_MIN
#undef DEBINFMESSAGE_MIN
#define DEBINFMESSAGE_MIN(m1,m2) BDEBUG("DEBINFMESSAGE_MIN", m1 << "[" << m2)
#endif

//**********************************************************
//**********************************************************
#define DEBINFCALLOSET(m1,m2)
#ifdef LOGINFCALLOSET
	//**********************************************************
#undef DEBINFCALLOSET
#define DEBINFCALLOSET(m1,m2) BDEBUG("DEBINFCALLOSET", m1 << "[" << m2)
//#define DEBINF(m1,m2)  {stringstream xx ; xx << "DEBINF [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
#endif

//**********************************************************
//**********************************************************
#ifdef LOGINF
	//**********************************************************
#undef DEBINF
#define DEBINF(m1,m2) BDEBUG("DEBINF", m1 << "[" << m2)
//#define DEBINF(m1,m2)  {stringstream xx ; xx << "DEBINF [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
	//**********************************************************
#undef DEBOUT_UTIL
#define DEBOUT_UTIL(m1,m2)  {stringstream xx ; xx << "DEBOUT_UTIL [" << pthread_self() << "]"<<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
	//**********************************************************
#else
#define DEBOUT(m1,m2)
#define DEBOUT_UTIL(m1,m2)
#define DEBINF(m1,m2)
#endif
//**********************************************************
//**********************************************************


//**********************************************************
//**********************************************************
#ifdef LOGMIN
	//**********************************************************
#undef DEBERROR
#define DEBERROR(m1)  {stringstream xx ; xx << "**** RUNTIME ERROR **** " << __FILE__ <<" " <<__LINE__<< "[" << m1 << "]\n";cout << xx.str();cout.flush();}
	//**********************************************************
//**********************************************************
#undef DEBOUT
//#define DEBOUT(m1,m2)  {stringstream xx ; xx << "DEBOUT [" << pthread_self() << "]" <<  __FILE__ <<" " <<__LINE__<< " "<< m1 << "[" << m2 << "]\n"; cout << xx.str();cout.flush();}
#define DEBOUT(m1,m2) BDEBUG("DEBOUT", m1 << "[" << m2 << "]")
#else
#define DEBERROR(m)
#endif
//**********************************************************
//**********************************************************

//**********************************************************
//**********************************************************
#ifdef LOGDEV
#undef DEBDEV
#define DEBDEV(m1,m2) BDEBUG("DEBDEV", m1 << "[" << m2)
#undef DEBY
#define DEBY  BDEBUG("DEBY", "")
#undef PRINTTIME
#define PRINTTIME(starttime,endtime){char bu[1024];sprintf(bu, "init %lld end %lld diff %lld",(lli)starttime.tv.tv_sec*1000000+(lli)starttime.tv.tv_usec, (lli)endtime.tv.tv_sec*1000000+(lli)bbb.tv.tv_usec, (lli)endtime.tv.tv_sec*1000000+(lli)bbb.tv.tv_usec - (lli)starttime.tv.tv_sec*1000000-(lli)starttime.tv.tv_usec );DEBOUT("TIME INTERVAL", bu )}
#undef PRINTTIMESHORT
#define PRINTTIMESHORT(m,starttime){char bu[1024];sprintf(bu, "time %lld",(lli)starttime.tv.tv_sec*1000000+(lli)starttime.tv.tv_usec);DEBOUT(m, bu )}
#else
#define DEBY
#define DEBDEV(m1,m2)
#define PRINTTIME(starttime,endtime)
#define PRINTTIMESHORT(m,starttime)
#endif
//**********************************************************
//**********************************************************

//**********************************************************
//**********************************************************
#ifdef LOGMEM
	//**********************************************************

#define DEBMEM(m1,m2) BDEBUG("DEBMEM", m1 << "[" << m2)

#undef DUMPMESSTABLE
#define DUMPMESSTABLE {map<const MESSAGE*, MESSAGE *>::iterator p;\
	for(int i = 0; i < COMAPS;i++){\
	pthread_mutex_lock(&messTableMtx[i]);\
	DEBOUT("GLOBALMESSAGETABLE",i << "]["<<&globalMessTable[i] << "]["<<globalMessTable[i].size())\
	for (p=globalMessTable[i].begin() ; p != globalMessTable[i].end() ; p ++){\
		DEBOUT("***********MESSAGE in table ", i<<"]["<<(MESSAGE*)p->second)\
	}\
	pthread_mutex_unlock(&messTableMtx[i]);}}
	//**********************************************************


#else
#define DEBMEM(m1,m2)
#define DUMPMESSTABLE
#endif
//**********************************************************
//**********************************************************

//**********************************************************
//**********************************************************
#undef GETLOCK
#define GETLOCK(m,message,i) \
		pthread_mutex_lock(m);
#undef RELLOCK
#define RELLOCK(m,message) \
		pthread_mutex_unlock(m);
#undef TRYLOCK
#define TRYLOCK(m,message,r)\
		r = pthread_mutex_trylock(m);
#ifdef LOGLOK
#undef GETLOCK
#define GETLOCK(m,message,i) \
		DEBOUT("Reaching lock " << message, m)\
		pthread_mutex_lock(m);\
		DEBOUT("Acquired lock " << message, m)
#undef RELLOCK
#define RELLOCK(m,message) \
		DEBOUT("Releasing lock " << message, m)\
		pthread_mutex_unlock(m);
#undef TRYLOCK
#define TRYLOCK(m,message,r)\
		DEBOUT("Trying lock " << message, m)\
		r = pthread_mutex_trylock(m);\
		DEBOUT("Trying lock result "<< r , m)
#endif
#ifdef PROFILELOCKCALC
#undef GETLOCK
#define GETLOCK(m,message,i) \
    {TIMEDEF SETNOW pthread_mutex_lock(m); CALCPERF("Wait on lock " << message,i)}
#undef RELLOCK
#define RELLOCK(m,message) \
		pthread_mutex_unlock(m);
#undef TRYLOCK
#define TRYLOCK(m,message,r)\
		r = pthread_mutex_trylock(m);
#endif
#ifdef PROFILELOCK
#undef GETLOCK
#define GETLOCK(m,message,i) \
    {TIMEDEF SETNOW pthread_mutex_lock(m); PRINTDIFFMIN("Wait on lock " << message,10)}
#undef RELLOCK
#define RELLOCK(m,message) \
		pthread_mutex_unlock(m);
#undef TRYLOCK
#define TRYLOCK(m,message,r)\
		r = pthread_mutex_trylock(m);
#endif
#ifdef PROFILELOCKVERB
#undef GETLOCK
#define GETLOCK(m,message) \
    {TIMEDEF SETNOW pthread_mutex_lock(m); PRINTDIFFMIN("Got lock - Wait on lock " << message,10)}
#undef RELLOCK
#define RELLOCK(m,message) \
		DEBOUT("Releasing lock " << message, m)\
		pthread_mutex_unlock(m);
#undef TRYLOCK
#define TRYLOCK(m,message,r)\
		r = pthread_mutex_trylock(m);
#endif
//**********************************************************
//**********************************************************
//**********************************************************
//**********************************************************
//**********************************************************
//**********************************************************
// new logging done per source file
// debug info
#define LOGSUDP
#define LOGSUDP_2
#define LOGSUDP_3
#define LOGSIPENGINE
#define LOGSIPENGINE_2
#define LOGSIPENGINE_3
#define LOGSL_CC
#define LOGSL_CC_2
#define LOGSL_CC_3
#define LOGSIPUTIL
#define LOGSIPUTIL_2
#define LOGSIPUTIL_3
#define LOGACTION
#define LOGACTION_2
#define LOGACTION_3
#define LOGCALL_OSET
#define LOGCALL_OSET_2
#define LOGCALL_OSET_3
#define LOGOMAP
#define LOGCOMAP_2
#define LOGCOMAP_3

#ifdef LOGSUDP
#define DBSUDP(m1, m2) BDEBUG(m1,m2)
#else
#define DBSUDP(m1, m2)
#endif
//low
#ifdef LOGSUDP_2
#define DBSUDP_2(m1, m2) BDEBUG(m1,m2)
#else
#define DBSUDP_2(m1, m2)
#endif
//iperlow
#ifdef LOGSUDP_3
#define DBSUDP_3(m1, m2) BDEBUG(m1,m2)
#else
#define DBSUDP_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGSIPENGINE
#define DEBUGSIPENGINE(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPENGINE(m1, m2)
#endif
//low
#ifdef LOGSIPENGINE_2
#define DEBUGSIPENGINE_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPENGINE_2(m1, m2)
#endif
//iperlow
#ifdef LOGSIPENGINE_3
#define DEBUGSIPENGINE_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPENGINE_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGSL_CC
#define DEBUGSL_CC(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSL_CC(m1, m2)
#endif
//low
#ifdef LOGSL_CC_2
#define DEBUGSL_CC_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSL_CC_2(m1, m2)
#endif
//iperlow
#ifdef LOGSL_CC_3
#define DEBUGSL_CC_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSL_CC_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGSIPUTIL
#define DEBUGSIPUTIL(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPUTIL(m1, m2)
#endif
//low
#ifdef LOGSIPUTIL_2
#define DEBUGSIPUTIL_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPUTIL_2(m1, m2)
#endif
//iperlow
#ifdef LOGSIPUTIL_3
#define DEBUGSIPUTIL_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGSIPUTIL_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGACTION
#define DEBUGACTION(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGACTION(m1, m2)
#endif
//low
#ifdef LOGACTION_2
#define DEBUGACTION_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGACTION_2(m1, m2)
#endif
//iperlow
#ifdef LOGACTION_3
#define DEBUGACTION_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGACTION_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGCALL_OSET
#define DEBUGCALL_OSET(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCALL_OSET(m1, m2)
#endif
//low
#ifdef LOGCALL_OSET_2
#define DEBUGCALL_OSET_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCALL_OSET_2(m1, m2)
#endif
//iperlow
#ifdef LOGCALL_OSET_3
#define DEBUGCALL_OSET_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCALL_OSET_3(m1, m2)
#endif
//**********************************************************
//**********************************************************
#ifdef LOGCOMAP
#define LOGCOMAP_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCOMAP(m1, m2)
#endif
//low
#ifdef LOGCOMAP_2
#define DEBUGCOMAP_2(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCOMAP_2(m1, m2)
#endif
//iperlow
#ifdef LOGCOMAP_3
#define DEBUGCOMAP_3(m1, m2) BDEBUG(m1,m2)
#else
#define DEBUGCOMAP_3(m1, m2)
#endif

//**********************************************************
//**********************************************************
//**********************************************************
//PERFORMANCE
#ifdef PROFILING
//#define PROFILE(m) DEBOUT("PROFILING",m)
#define PROFILE(m)
#define TIMEDEF SysTime mytime1111;
#define SETNOW gettimeofday(&mytime1111.tv, &mytime1111.tz);;
#define PRINTDIFF(m) {SysTime mytime2222; gettimeofday(&mytime2222.tv, &mytime2222.tz);\
		long long int num = ((long long int) ( mytime2222.tv.tv_sec - mytime1111.tv.tv_sec))*1000000+((long long int)(mytime2222.tv.tv_usec - mytime1111.tv.tv_usec));\
                gettimeofday(&mytime1111.tv, &mytime1111.tz);\
                BDEBUG("PROFILE DIFFERENCE ", m << "]["<<num)}
#define PRINTDIFF_A(m,m2) {SysTime mytime2222; gettimeofday(&mytime2222.tv, &mytime2222.tz);\
		long long int num = ((long long int) ( mytime2222.tv.tv_sec - mytime1111.tv.tv_sec))*1000000+((long long int)(mytime2222.tv.tv_usec - mytime1111.tv.tv_usec));\
                gettimeofday(&mytime1111.tv, &mytime1111.tz);\
                BDEBUG("PROFILE DIFFERENCE ", m << "]["<<num)\
				if (num > m2){ DEBASSERT("TIME EXCEEDED" << m << "]["<<num)}}
#define PRINTDIFFMIN(m,min) {SysTime mytime2222; gettimeofday(&mytime2222.tv, &mytime2222.tz);\
		long long int num = ((long long int) ( mytime2222.tv.tv_sec - mytime1111.tv.tv_sec))*1000000+((long long int)(mytime2222.tv.tv_usec - mytime1111.tv.tv_usec));\
                gettimeofday(&mytime1111.tv, &mytime1111.tz);\
		if (num >= min ){ BDEBUG("PROFILE DIFFERENCE ", m << "][#"<<num<<"#")\
			if (num > 10000) BDEBUG("Waited too long","")}}

#define CALCPERF(mess,n) {SysTime mytime2222; gettimeofday(&mytime2222.tv, &mytime2222.tz);\
		long long int num = ((long long int) ( mytime2222.tv.tv_sec - mytime1111.tv.tv_sec))*1000000+((long long int)(mytime2222.tv.tv_usec - mytime1111.tv.tv_usec));\
                gettimeofday(&mytime1111.tv, &mytime1111.tz);\
                if (PERFARRAY[0][n] <  num){ \
                	PERFARRAY[0][n]  = num;}\
                if (PERFARRAY[1][n] > num) {\
                	PERFARRAY[1][n]  = num;}\
                PERFARRAY[3][n] = (PERFARRAY[2][n] * PERFARRAY[3][n] + num ) / (PERFARRAY[2][n] + 1);\
                PERFARRAY[2][n] ++; BDEBUG("CALCPERF ",mess <<" Avg["<<PERFARRAY[3][n]<<"] Min["<<PERFARRAY[1][n]<<"] Max["<<PERFARRAY[0][n])}


#else
#define PROFILE(m)
#define TIMEDEF
#define SETNOW
#define PRINTDIFF(m)
#define CALCPERF(m1,m2)
#endif
//**********************************************************
//**********************************************************

inline int getModulus(void* pointer) {

	//Addresses are all multiple of ADDRESSPACE
	//DEBOUT("MESSAGE pointer modulus",(long long unsigned int)pointer)
	int i = (int)((long long unsigned int)pointer % (MESSAGEMAPS*ADDRESSPACE));
	DEBOUT("MESSAGE pointer modulus",pointer<<"]["<<i/ADDRESSPACE)
	return i/ADDRESSPACE;

}
inline string b2S(bool _b){
    if (_b)
        return "true";
    else
        return "false";
}
inline int getPreModulus(const char* st) {
	int k = strlen(st) - 1;
	if (k > 100){
		k = 100;
	}
	long long int tot=0;
	for (int i = 0; i < k ; i++){
		tot =  (long long int) st[i] + tot;
	}
	return tot % PREMODMAP;
}

#endif //UTIL_H
