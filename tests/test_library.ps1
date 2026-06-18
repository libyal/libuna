# Tests library functions and types.

$LibraryTests = "base16_stream base32_stream base64_stream byte_stream codepage_koi8_r codepage_koi8_u codepage_mac_arabic codepage_mac_celtic codepage_mac_centraleurroman codepage_mac_croatian codepage_mac_cyrillic codepage_mac_dingbats codepage_mac_farsi codepage_mac_gaelic codepage_mac_greek codepage_mac_icelandic codepage_mac_inuit codepage_mac_roman codepage_mac_romanian codepage_mac_russian codepage_mac_symbol codepage_mac_thai codepage_mac_turkish codepage_mac_ukrainian codepage_windows_874 codepage_windows_932 codepage_windows_936 codepage_windows_949 codepage_windows_950 codepage_windows_1250 codepage_windows_1251 codepage_windows_1252 codepage_windows_1253 codepage_windows_1254 codepage_windows_1255 codepage_windows_1256 codepage_windows_1257 codepage_windows_1258 error support unicode_character url_stream utf16_stream utf16_string utf32_stream utf32_string utf7_stream utf8_stream utf8_string"
$LibraryTestsWithInput = ""
$OptionSets = "" -split " "

. .\test_functions.ps1

$TestExecutablesDirectory = GetTestExecutablesDirectory

If (-Not (Test-Path ${TestExecutablesDirectory}))
{
	Write-Error "Missing test executables directory"

	Exit ${ExitFailure}
}

$Result = ${ExitIgnore}

Foreach (${TestName} in ${LibraryTests} -split " ")
{
	# Split will return an array of a single empty string when LibraryTests is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	$Result = RunTestBinary ${TestExecutablesDirectory} "una_test_${TestName}"

	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

$TestInputs = GenerateTestInputs "libuna" ${OptionSets}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# Split will return an array of a single empty string when LibraryTestsWithInput is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	ForEach ($TestInput in ${TestInputs})
	{
		$Result = RunTestBinaryWithInput ${TestExecutablesDirectory} "una_test_${TestName}" ${TestInput}

		If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
		{
			Break
		}
	}
	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

Exit ${Result}
