#!/bin/bash
# Tests library functions and types.
#
# Version: 20200705

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

LIBRARY_TESTS="base16_stream base32_stream base64_stream byte_stream codepage_koi8_r codepage_koi8_u codepage_mac_arabic codepage_mac_celtic codepage_mac_centraleurroman codepage_mac_croatian codepage_mac_cyrillic codepage_mac_dingbats codepage_mac_farsi codepage_mac_gaelic codepage_mac_greek codepage_mac_icelandic codepage_mac_inuit codepage_mac_roman codepage_mac_romanian codepage_mac_russian codepage_mac_symbol codepage_mac_ukrainian codepage_windows_874 codepage_windows_932 codepage_windows_936 codepage_windows_949 codepage_windows_950 codepage_windows_1250 codepage_windows_1251 codepage_windows_1252 codepage_windows_1253 codepage_windows_1254 codepage_windows_1255 codepage_windows_1256 codepage_windows_1257 codepage_windows_1258 error support unicode_character url_stream utf16_stream utf16_string utf32_stream utf32_string utf7_stream utf8_stream utf8_string";
LIBRARY_TESTS_WITH_INPUT="";
OPTION_SETS="";

INPUT_GLOB="*";

run_test()
{
	local TEST_NAME=$1;

	local TEST_DESCRIPTION="Testing: ${TEST_NAME}";
	local TEST_EXECUTABLE="./una_test_${TEST_NAME}";

	if ! test -x "${TEST_EXECUTABLE}";
	then
		TEST_EXECUTABLE="${TEST_EXECUTABLE}.exe";
	fi

	# TODO: add support for TEST_PROFILE and OPTION_SETS?
	run_test_with_arguments "${TEST_DESCRIPTION}" "${TEST_EXECUTABLE}";
	local RESULT=$?;

	return ${RESULT};
}

run_test_with_input()
{
	local TEST_NAME=$1;

	local TEST_DESCRIPTION="Testing: ${TEST_NAME}";
	local TEST_EXECUTABLE="./una_test_${TEST_NAME}";

	if ! test -x "${TEST_EXECUTABLE}";
	then
		TEST_EXECUTABLE="${TEST_EXECUTABLE}.exe";
	fi

	if ! test -d "input";
	then
		echo "Test input directory not found.";

		return ${EXIT_IGNORE};
	fi
	local RESULT=`ls input/* | tr ' ' '\n' | wc -l`;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		echo "No files or directories found in the test input directory";

		return ${EXIT_IGNORE};
	fi

	local TEST_PROFILE_DIRECTORY=$(get_test_profile_directory "input" "libuna");

	local IGNORE_LIST=$(read_ignore_list "${TEST_PROFILE_DIRECTORY}");

	RESULT=${EXIT_SUCCESS};

	for TEST_SET_INPUT_DIRECTORY in input/*;
	do
		if ! test -d "${TEST_SET_INPUT_DIRECTORY}";
		then
			continue;
		fi
		if check_for_directory_in_ignore_list "${TEST_SET_INPUT_DIRECTORY}" "${IGNORE_LIST}";
		then
			continue;
		fi

		local TEST_SET_DIRECTORY=$(get_test_set_directory "${TEST_PROFILE_DIRECTORY}" "${TEST_SET_INPUT_DIRECTORY}");

		local OLDIFS=${IFS};

		# IFS="\n" is not supported by all platforms.
		IFS="
";

		if test -f "${TEST_SET_DIRECTORY}/files";
		then
			for INPUT_FILE in `cat ${TEST_SET_DIRECTORY}/files | sed "s?^?${TEST_SET_INPUT_DIRECTORY}/?"`;
			do
				if test "${OSTYPE}" = "msys";
				then
					# A test executable built with MinGW expects a Windows path.
					INPUT_FILE=`echo ${INPUT_FILE} | sed 's?/?\\\\?g'`;
				fi
				run_test_on_input_file_with_options "${TEST_SET_DIRECTORY}" "${TEST_DESCRIPTION}" "default" "${OPTION_SETS}" "${TEST_EXECUTABLE}" "${INPUT_FILE}";
				RESULT=$?;

				if test ${RESULT} -ne ${EXIT_SUCCESS};
				then
					break;
				fi
			done
		else
			for INPUT_FILE in `ls -1d ${TEST_SET_INPUT_DIRECTORY}/${INPUT_GLOB}`;
			do
				if test "${OSTYPE}" = "msys";
				then
					# A test executable built with MinGW expects a Windows path.
					INPUT_FILE=`echo ${INPUT_FILE} | sed 's?/?\\\\?g'`;
				fi
				run_test_on_input_file_with_options "${TEST_SET_DIRECTORY}" "${TEST_DESCRIPTION}" "default" "${OPTION_SETS}" "${TEST_EXECUTABLE}" "${INPUT_FILE}";
				RESULT=$?;

				if test ${RESULT} -ne ${EXIT_SUCCESS};
				then
					break;
				fi
			done
		fi
		IFS=${OLDIFS};

		if test ${RESULT} -ne ${EXIT_SUCCESS};
		then
			break;
		fi
	done

	return ${RESULT};
}

if test -n "${SKIP_LIBRARY_TESTS}";
then
	exit ${EXIT_IGNORE};
fi

TEST_RUNNER="tests/test_runner.sh";

if ! test -f "${TEST_RUNNER}";
then
	TEST_RUNNER="./test_runner.sh";
fi

if ! test -f "${TEST_RUNNER}";
then
	echo "Missing test runner: ${TEST_RUNNER}";

	exit ${EXIT_FAILURE};
fi

source ${TEST_RUNNER};

RESULT=${EXIT_IGNORE};

for TEST_NAME in ${LIBRARY_TESTS};
do
	run_test "${TEST_NAME}";
	RESULT=$?;

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		break;
	fi
done

if test ${RESULT} -ne ${EXIT_SUCCESS} && test ${RESULT} -ne ${EXIT_IGNORE};
then
	exit ${RESULT};
fi

for TEST_NAME in ${LIBRARY_TESTS_WITH_INPUT};
do
	if test -d "input";
	then
		run_test_with_input "${TEST_NAME}";
		RESULT=$?;
	else
		run_test "${TEST_NAME}";
		RESULT=$?;
	fi

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		break;
	fi
done

exit ${RESULT};

