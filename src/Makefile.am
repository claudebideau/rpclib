AM_CFLAGS = -Wall -D__USE_GNU -I./include
AM_CPPFLAGS = -Wall -D__USE_GNU -I./include

# AM_LDFLAGS  = -lrt
# AM_LDFLAGS += -lxmlrpc_server++ -lxmlrpc_server_abyss++ 
AM_LDFLAGS = -Wl,-Map,./rpclib.map

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile

lib_LTLIBRARIES = librpclib.la

librpclib_la_SOURCES =	inireader.cpp \
	rttrace.cpp \
	trace.cpp \
    rpc/rttraceRpc.cpp \
    rpc/traceRpc.cpp \
	include/inireader.h \
	include/rttrace.h \
	include/trace.h \
    include/rpc/xmlrpc_method.h



