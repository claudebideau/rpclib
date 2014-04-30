#!/bin/bash
# $Id$
# $Date$
# $Rev$
# $Author$
#
# script for build XMLRPC library on local and beaglebone platform


function cross_compile_env {
    CC_LIB_PATH=""
    CFLAGS="-I${CC_LIB_PATH}/include"
    CXXFLAGS="-I${CC_LIB_PATH}/include"
    CC="powerpc-wrs-linux-gnu-ppc_e500mc-glibc_small-gcc"
    LDFLAGS="-L${CC_LIB_PATH}/lib"

    printf "NEW PATH = ${PATH}\n"

}


# xmlrpc-c library need to use gennmtab to be build locally
function build_local_xmlrpc {
    INSTALL_PATH=${PACKAGE_DIR}/../build/${LOCAL_PLT}
    # build localy the xml-rpc due to non compatibility with cross compile environment
    if [ -d ${LOCAL_BUILD_PATH} ]; then
        printf " Folder ${LOCAL_BUILD_PATH} exist \n CLEANUP\n=======================\n"
        rm -rf ${LOCAL_BUILD_PATH}
    fi
    mkdir -pv ${LOCAL_BUILD_PATH}
    mkdir -pv ${INSTALL_PATH}
    cd ${LOCAL_BUILD_PATH}
    printf " Untar\n"
    tar xfz ${PACKAGE_DIR}/${XMLRPC_NAME}.tgz
    mv stable ${XMLRPC_NAME}
    cd ${XMLRPC_NAME}
    printf " configure\n"
    ./configure  --disable-curl-client --prefix=${INSTALL_PATH} 
    #~ CFLAGS="-I." \
        #~ CPPFLAGS="-I."
    cd lib/expat/gennmtab/
    make clean && make gennmtab
    cp gennmtab ${LOCAL_BUILD_PATH}
    cd ../../..
    make CADD=-fPIC
    find . -name "*.so" -print
    make install    
    cd ${CDIR}
}


function build_cross_compile_xmlrpc {
    INSTALL_PATH=${PACKAGE_DIR}/../build/beaglebone
    # build localy the xml-rpc due to non compatibility with cross compile environment
    if [ -d ${CROSS_BUILD_PATH} ]; then
        printf " Folder ${BCEM_BUILD_PATH} exist \n CLEANUP\n=======================\n"
        rm -rf ${CROSS_BUILD_PATH}
    fi
    mkdir -pv ${CROSS_BUILD_PATH}
    mkdir -pv ${INSTALL_PATH}
    cd ${CROSS_BUILD_PATH}

    printf " Untar\n"
    tar xfz ${PACKAGE_DIR}/${XMLRPC_NAME}.tgz
    mv stable ${XMLRPC_NAME}
    cd ${CROSS_BUILD_PATH}/${XMLRPC_NAME}

    # start configure

    printf " LDFLAGS=\"-L${CC_LIB_PATH}/lib\" CC=\"powerpc-wrs-linux-gnu-ppc_e500mc-glibc_small-gcc\" ./configure  --host=powerpc-wrs-linux-gnu\n"


    ./configure --host=powerpc-wrs-linux --build=i686-pc-linux-gnu  --disable-curl-client LDFLAGS="-L${CC_LIB_PATH}/lib" \
        CC="powerpc-wrs-linux-gnu-ppc_e500mc-glibc_small-gcc" \
        CFLAGS="-I${CC_LIB_PATH}/include" \
        CPPFLAGS="-I${CC_LIB_PATH}/include" --disable-cplusplus --prefix=${INSTALL_PATH}
        
    
    make clean
    cd lib/expat/gennmtab/
    make clean && make gennmtab
    cd ${BCEM_BUILD_PATH}/${XMLRPC_NAME}
    cp ${LOCAL_BUILD_PATH}/gennmtab lib/expat/gennmtab/
    make CADD=-fPIC
    #~ cp ${PLATFORM_BUILD_PATH}/gennmtab lib/expat/gennmtab/
    #~ touch lib/expat/gennmtab/gennmtab
    find . -name "*.so" -print
    make install
    

}

#---------------------- help ----------------------
#
# Procedure help()
#
# Objet : display the help
#
help()
{
   #clear
   printf "\nNAME\n\n"
   printf "     %s - Compile xmlrpc library \n\n" $0 
   printf "SYNOPSYS\n\n"
   printf "     %s [-h :help] [-l] [-b]\n"
   printf "\nDESCRIPTION\n\n"
   printf "\nOPTIONS\n\n"
   printf "     -l    : build the xmlrpc library for local target\n"
   printf "     -b    : build the xmlrpc library for beagleBone target\n"
   printf "\nEXAMPLE\n\n"
   printf "\nEXIT STATUS\n\n"
   printf "     0 Successful completion\n"
   printf "\nIDENTIFICATION\n\n"
   printf "$0 : "                  
   printf "$RELEASED_VERSION\n";  

   return
}

#~ printf "LOCAL_BUILD_PATH = ${LOCAL_BUILD_PATH}"
main=$0
CDIR=`pwd`
XMLRPC_NAME="xmlrpc-c-stable"

LOCAL_PLT=`uname -m`
LOCAL_BUILD_PATH=${CDIR}/${LOCAL_PLT}
CROSS_BUILD_PATH="${CDIR}/CROSS"

if [[ "${main}" == "./build.sh" ]]; then
    NO_ARGS=0 
    E_OPTERROR=85
    PACKAGE_DIR=${CDIR}

    if [ $# -eq "$NO_ARGS" ]    # Script invoked with no command-line args?
    then
      help
      exit $E_OPTERROR          # Exit and explain usage.
                                # Usage: scriptname -options
                                # Note: dash (-) necessary
    fi  
    while getopts "lb" Option
    do
      case $Option in
        h     ) help; exit 0;;
        l     ) printf "BUILD XML-RPC LIBRARY\n===========================\n"; build_local_xmlrpc ;;
        b     ) printf "BUILD XML-RPC LIBRARY for beagleBone\n==================\n"; cross_compile_env; build_cross_compile_xmlrpc ;;
        *     ) printf "Unimplemented option chosen.\n"; help; exit 1;;   # Default.
      esac
    done
fi
