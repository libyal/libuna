#!/bin/bash
#
# unaexport testing script
#
# Copyright (c) 2008-2012, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

INPUT="input";
TMP="tmp";

GREP="grep";
LS="ls";
ICONV="iconv";
SED="sed";
TR="tr";
WC="wc";

test_unaexport()
{ 
	INPUT_FILE=$1;

	SUM=`${UNAEXPORT} -d md5 ${INPUT_FILE} | ${GREP} "MD5" | ${SED} 's/^[^:]*[:][\t][\t]*//'`;

	RESULT=$?;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		SUM_CHECK=`${ICONV} ${INPUT_FILE} | ${SED} 's/[ ][ ]*[^ ][^ ]*$//'`;

		if test ${SUM} != ${SUM_CHECK};
		then
			RESULT=${EXIT_FAILURE};
		fi
	fi

	echo "";

	echo -n "Testing unaexport of input: ${INPUT_FILE} ";

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

UNAEXPORT="../unatools/unaexport";

if ! test -x ${UNAEXPORT};
then
	UNAEXPORT="../unatools/unaexport.exe";
fi

if ! test -x ${UNAEXPORT};
then
	echo "Missing executable: ${UNAEXPORT}";

	exit ${EXIT_FAILURE};
fi

if ! test -d ${INPUT};
then
	echo "No ${INPUT} directory found, to test unaexport create ${INPUT} directory and place test files in directory.";

	exit ${EXIT_IGNORE};
fi

EXIT_RESULT=${EXIT_IGNORE};

CODEPAGES="ascii iso-8859-1 iso-8859-2 iso-8859-3 iso-8859-4 iso-8859-5 iso-8859-6 iso-8859-7 iso-8859-8 iso-8859-9 iso-8859-10 iso-8859-11 iso-8859-13 iso-8859-14 iso-8859-15 iso-8859-16 koi8-r koi8-u windows-874 windows-1250 windows-1251 windows-1252 windows-1253 windows-1254 windows-1255 windows-1256 windows-1257 windows-1258";

INPUT_ENCODINGS="byte_stream";

OUTPUT_ENCODINGS="utf7 utf8 utf16be utf16le utf32be utf32le";

if test -d ${INPUT};
then
	RESULT=`${LS} ${INPUT}/* | ${TR} ' ' '\n' | ${WC} -l`;

	if test ${RESULT} -eq 0;
	then
		echo "No files found in ${INPUT} directory, to test unaexport place test files in directory.";
	else
		for FILENAME in `${LS} ${INPUT}/* | ${TR} ' ' '\n'`;
		do
			if ! test_unaexport "${FILENAME}";
			then
				exit ${EXIT_FAILURE};
			fi
		done

		EXIT_RESULT=${EXIT_SUCCESS};
	fi
fi

exit ${EXIT_RESULT};

