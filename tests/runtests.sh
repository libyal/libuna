#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libuna/.libs/libuna.1.dylib && test -f ./pyuna/.libs/pyuna.so
then
	install_name_tool -change /usr/local/lib/libuna.1.dylib ${PWD}/libuna/.libs/libuna.1.dylib ./pyuna/.libs/pyuna.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

