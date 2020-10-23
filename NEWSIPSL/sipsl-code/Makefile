all:	bin/_SIPSL

bin/_SIPSL:	bin/SEAMFAIL.o bin/test.o bin/CALL_OSET.o bin/MESSAGE.o bin/VALO.o bin/DOA.o bin/ENGINE.o bin/SPIN.o bin/SIPUTIL.o bin/CS_HEADERS.o bin/SIPENGINE.o bin/TRNSPRT.o bin/SUDP.o bin/ACTION.o bin/TRNSCT_SM.o bin/DAO.o bin/SL_CC.o bin/COMAP.o bin/ALARM.o bin/ALO.o
	g++ -O -s -m64 -o bin/_SIPSL bin/SEAMFAIL.o bin/test.o bin/CALL_OSET.o bin/MESSAGE.o bin/VALO.o bin/DOA.o bin/ENGINE.o bin/SPIN.o bin/SIPUTIL.o bin/CS_HEADERS.o bin/SIPENGINE.o bin/TRNSPRT.o bin/SUDP.o bin/ACTION.o bin/TRNSCT_SM.o bin/DAO.o bin/SL_CC.o bin/COMAP.o bin/ALARM.o bin/ALO.o -lpthread

bin/SIPUTIL.o:  src/SIPUTIL.cpp
	g++ -O -s -m64  -c   -o bin/SIPUTIL.o src/SIPUTIL.cpp -I hdr  -std=gnu++0x

bin/SEAMFAIL.o:	src/SEAMFAIL.cpp
	g++ -O -s -m64   -c   -o bin/SEAMFAIL.o src/SEAMFAIL.cpp -I hdr  -std=gnu++0x


bin/test.o:	src/test.cpp
	g++ -O -s -m64   -c   -o bin/test.o src/test.cpp -I hdr  -std=gnu++0x

bin/CALL_OSET.o:	src/CALL_OSET.cpp
	g++ -O -s -m64   -c   -o bin/CALL_OSET.o src/CALL_OSET.cpp -I hdr  -std=gnu++0x

bin/MESSAGE.o:	src/MESSAGE.cpp
	g++ -O -s -m64   -c   -o bin/MESSAGE.o src/MESSAGE.cpp -I hdr  -std=gnu++0x

bin/VALO.o:	src/VALO.cpp
	g++ -O -s -m64   -c   -o bin/VALO.o src/VALO.cpp -I hdr  -std=gnu++0x

bin/DOA.o:	src/DOA.cpp
	g++ -O -s -m64   -c   -o bin/DOA.o src/DOA.cpp -I hdr  -std=gnu++0x

bin/ENGINE.o:	src/ENGINE.cpp
	g++ -O -s -m64   -c   -o bin/ENGINE.o src/ENGINE.cpp -I hdr  -std=gnu++0x

bin/SPIN.o:	src/SPIN.cpp
	g++ -O -s -m64   -c   -o bin/SPIN.o src/SPIN.cpp -I hdr  -std=gnu++0x

bin/bin/SIPUTIL.o:	src/SIPUTIL.cpp
	g++ -O -s -m64   -c   -o bin/SIPUTIL.o src/SIPUTIL.cpp -I hdr  -std=gnu++0x

bin/CS_HEADERS.o:	src/CS_HEADERS.cpp
	g++ -O -s -m64   -c   -o bin/CS_HEADERS.o src/CS_HEADERS.cpp -I hdr  -std=gnu++0x

bin/SIPENGINE.o:	src/SIPENGINE.cpp
	g++ -O -s -m64   -c   -o bin/SIPENGINE.o src/SIPENGINE.cpp -I hdr  -std=gnu++0x

bin/TRNSPRT.o:	src/TRNSPRT.cpp
	g++ -O -s -m64   -c   -o bin/TRNSPRT.o src/TRNSPRT.cpp -I hdr  -std=gnu++0x

bin/ACTION.o:	src/ACTION.cpp
	g++ -O -s -m64   -c   -o bin/ACTION.o src/ACTION.cpp -I hdr  -std=gnu++0x

bin/TRNSCT_SM.o:	src/TRNSCT_SM.cpp
	g++ -O -s -m64   -c   -o bin/TRNSCT_SM.o src/TRNSCT_SM.cpp -I hdr  -std=gnu++0x

bin/DAO.o:	src/DAO.cpp
	g++ -O -s -m64   -c   -o bin/DAO.o src/DAO.cpp -I hdr  -std=gnu++0x

bin/SL_CC.o:	src/SL_CC.cpp
	g++ -O -s -m64   -c   -o bin/SL_CC.o src/SL_CC.cpp -I hdr  -std=gnu++0x

bin/COMAP.o:	src/COMAP.cpp
	g++ -O -s -m64   -c   -o bin/COMAP.o src/COMAP.cpp -I hdr  -std=gnu++0x

bin/ALARM.o:	src/ALARM.cpp
	g++ -O -s -m64   -c   -o bin/ALARM.o src/ALARM.cpp -I hdr  -std=gnu++0x

bin/ALO.o:	src/ALO.cpp
	g++ -O -s -m64   -c   -o bin/ALO.o src/ALO.cpp -I hdr  -std=gnu++0x

bin/SUDP.o:	src/SUDP.cpp
	g++ -O -s -m64   -c   -o bin/SUDP.o src/SUDP.cpp -I hdr  -std=gnu++0x
