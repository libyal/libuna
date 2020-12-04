#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libuna/.libs/libuna.1.dylib && test -f ./pyuna/.libs/pyuna.so;
then
	install_name_tool -change /usr/local/lib/libuna.1.dylib ${PWD}/libuna/.libs/libuna.1.dylib ./pyuna/.libs/pyuna.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

