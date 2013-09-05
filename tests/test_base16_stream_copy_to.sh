#!/bin/bash
#
# Unicode and ASCII (byte stream) conversion library base16 stream copy to testing script
#
# Copyright (c) 2008-2013, Joachim Metz <joachim.metz@gmail.com>
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

test_base16_stream_copy_to()
{ 
	rm -rf tmp;
	mkdir tmp;

	echo "Testing base16 stream copy to function";

	${TEST_RUNNER} ./${UNA_TEST_BASE16_STREAM_COPY_FROM};

	RESULT=$?;

	rm -rf tmp;

	echo "";

	return ${RESULT};
}

UNA_TEST_BASE16_STREAM_COPY_FROM="una_test_base16_stream_copy_to";

if ! test -x ${UNA_TEST_BASE16_STREAM_COPY_FROM};
then
	UNA_TEST_BASE16_STREAM_COPY_FROM="una_test_base16_stream_copy_to.exe";
fi

if ! test -x ${UNA_TEST_BASE16_STREAM_COPY_FROM};
then
	echo "Missing executable: ${UNA_TEST_BASE16_STREAM_COPY_FROM}";

	exit ${EXIT_FAILURE};
fi

TEST_RUNNER="tests/test_runner.sh";

if ! test -x ${TEST_RUNNER};
then
	TEST_RUNNER="./test_runner.sh";
fi

if ! test -x ${TEST_RUNNER};
then
	echo "Missing test runner: ${TEST_RUNNER}";

	exit ${EXIT_FAILURE};
fi

if ! test_base16_stream_copy_to;
then
	exit ${EXIT_FAILURE};
fi

exit ${EXIT_SUCCESS};

