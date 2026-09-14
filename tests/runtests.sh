#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libuna/.libs/libuna.1.dylib" ] && [ -f ./pyuna/.libs/pyuna.so ]
then
    install_name_tool -change /usr/local/lib/libuna.1.dylib "${PWD}/libuna/.libs/libuna.1.dylib" ./pyuna/.libs/pyuna.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

