dnl Copyright (C) 2014 FABLAB-LANNION


AC_INIT([rpclib],[0.1],[claude.bideau@gmail.com])

dnl -------------------------------------------------------------
dnl insert --enable-generic to build and test xmlrpc manager
dnl -------------------------------------------------------------


dnl AC_ARG_ENABLE([generic],
dnl [  --enable-generic    enable generic building on local target, default: no],
dnl [case "${enableval}" in
dnl     yes) debug=true; AC_MSG_NOTICE([----->GENERATE GENERIC TOOL]) ;;
dnl     no)  debug=false ;;
dnl     *) AC_MSG_ERROR([bad value ${enableval} for --enable-generic]) ;;
dnl esac],[generic=false])
dnl 
dnl AM_CONDITIONAL([GENERIC], [test x"$generic" = x"true"])

dnl -------------------------------------------------------------
dnl insert --with-beaglebone to target beaglebone board
dnl -------------------------------------------------------------
AC_ARG_WITH([beaglebone],
	[AS_HELP_STRING([--with-beaglebone], [target BEAGLEBONE code instead of generic ] @@)],
	[],
	[with_beaglebone=no])

AS_IF([test "x$with_beaglebone" != xno],
	[
	AM_CONDITIONAL(WITH_BEAGLEBONE, true)
	AC_DEFINE(WITH_BEAGLEBONE,[],[Use BEAGLEBONE])
	], [
	AC_DEFINE(WITH_BEAGLEBONE,[],[Use BEAGLEBONE])
	AM_CONDITIONAL(WITH_BEAGLEBONE, false)
	])

dnl -------------------------------------------------------------
dnl insert --enable-debug for debug purpose 
dnl -------------------------------------------------------------

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

dnl -------------------------------------------------------------

AC_CONFIG_HEADER(config.h)
AC_CONFIG_AUX_DIR(auxdir)
dnl AC_CONFIG_SRCDIR(src/main.c)

if test -z $DEBUG; then
    CFLAGS = -Wall -g3 -O0
    CPPFLAGS = -Wall -g3 -O0
fi

if test -z $CFLAGS; then
    CFLAGS='-Wall -O3'
    CPPFLAGS='-Wall -O3'
fi

AC_ENABLE_SHARED
AC_PROG_CC
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

AC_CHECK_FUNCS([bzero gettimeofday inet_ntoa memset socket strchr strdup])
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h unistd.h])

dnl DX_HTML_FEATURE(ON)
dnl DX_CHM_FEATURE(OFF)
dnl DX_CHI_FEATURE(OFF)
dnl DX_MAN_FEATURE(ON)
dnl DX_RTF_FEATURE(OFF)
dnl DX_XML_FEATURE(OFF)
dnl DX_PDF_FEATURE(ON)
dnl DX_PS_FEATURE(OFF)

AM_INIT_AUTOMAKE(rpclib_test1, 0.1)


AC_OUTPUT([ Makefile src/Makefile test/Makefile])
