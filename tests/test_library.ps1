# Tests library functions and types.
#
# Version: 20230410

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$LibraryTests = "base16_stream base32_stream base64_stream byte_stream codepage_koi8_r codepage_koi8_u codepage_mac_arabic codepage_mac_celtic codepage_mac_centraleurroman codepage_mac_croatian codepage_mac_cyrillic codepage_mac_dingbats codepage_mac_farsi codepage_mac_gaelic codepage_mac_greek codepage_mac_icelandic codepage_mac_inuit codepage_mac_roman codepage_mac_romanian codepage_mac_russian codepage_mac_symbol codepage_mac_thai codepage_mac_turkish codepage_mac_ukrainian codepage_windows_874 codepage_windows_932 codepage_windows_936 codepage_windows_949 codepage_windows_950 codepage_windows_1250 codepage_windows_1251 codepage_windows_1252 codepage_windows_1253 codepage_windows_1254 codepage_windows_1255 codepage_windows_1256 codepage_windows_1257 codepage_windows_1258 error support unicode_character url_stream utf16_stream utf16_string utf32_stream utf32_string utf7_stream utf8_stream utf8_string"
$LibraryTestsWithInput = ""
$OptionSets = ""

$InputGlob = "*"

Function GetTestExecutablesDirectory
{
	$TestExecutablesDirectory = ""

	ForEach (${VSDirectory} in ("msvscpp", "vs2008", "vs2010", "vs2012", "vs2013", "vs2015", "vs2017", "vs2019", "vs2022"))
	{
		ForEach (${VSConfiguration} in ("Release", "VSDebug"))
		{
			ForEach (${VSPlatform} in ("Win32", "x64"))
			{
				$TestExecutablesDirectory = "..\${VSDirectory}\${VSConfiguration}\${VSPlatform}"

				If (Test-Path ${TestExecutablesDirectory})
				{
					Return ${TestExecutablesDirectory}
				}
			}
			$TestExecutablesDirectory = "..\${VSDirectory}\${VSConfiguration}"

			If (Test-Path ${TestExecutablesDirectory})
			{
				Return ${TestExecutablesDirectory}
			}
		}
	}
	Return ${TestExecutablesDirectory}
}

Function ReadIgnoreList
{
	param( [string]$TestProfileDirectory )

	$IgnoreFile = "${TestProfileDirectory}\ignore"
	$IgnoreList = ""

	If (Test-Path -Path ${IgnoreFile} -PathType "Leaf")
	{
		$IgnoreList = Get-Content -Path ${IgnoreFile} | Where {$_ -notmatch '^#.*'}
	}
	Return $IgnoreList
}

Function RunTest
{
	param( [string]$TestType )

	$TestDescription = "Testing: ${TestName}"
	$TestExecutable = "${TestExecutablesDirectory}\una_test_${TestName}.exe"

	If (-Not (Test-Path -Path ${TestExecutable} -PathType "Leaf"))
	{
		Write-Host "${TestDescription} (" -nonewline
		Write-Host "SKIP" -foreground Cyan -nonewline
		Write-Host ")"

		Return ${ExitIgnore}
	}
	$Output = Invoke-Expression ${TestExecutable}
	$Result = ${LastExitCode}

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	Write-Host "${TestDescription} (" -nonewline

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host "FAIL" -foreground Red -nonewline
	}
	Else
	{
		Write-Host "PASS" -foreground Green -nonewline
	}
	Write-Host ")"

	Return ${Result}
}

Function RunTestWithInput
{
	param( [string]$TestType )

	$TestDescription = "Testing: ${TestName}"
	$TestExecutable = "${TestExecutablesDirectory}\una_test_${TestName}.exe"

	If (-Not (Test-Path -Path ${TestExecutable} -PathType "Leaf"))
	{
		Write-Host "${TestDescription} (" -nonewline
		Write-Host "SKIP" -foreground Cyan -nonewline
		Write-Host ")"

		Return ${ExitIgnore}
	}
	$TestProfileDirectory = "input\.libuna"

	If (-Not (Test-Path -Path ${TestProfileDirectory} -PathType "Container"))
	{
		New-Item -ItemType "directory" -Path ${TestProfileDirectory}
	}
	$IgnoreList = ReadIgnoreList ${TestProfileDirectory}

	$Result = ${ExitSuccess}

	ForEach ($TestSetInputDirectory in Get-ChildItem -Path "input" -Exclude ".*")
	{
		If (-Not (Test-Path -Path ${TestSetInputDirectory} -PathType "Container"))
		{
			Continue
		}
		If (${TestSetInputDirectory} -Contains ${IgnoreList})
		{
			Continue
		}
		$TestSetName = ${TestSetInputDirectory}.Name

		If (Test-Path -Path "${TestProfileDirectory}\${TestSetName}\files" -PathType "Leaf")
		{
			$InputFiles = Get-Content -Path "${TestProfileDirectory}\${TestSetName}\files" | Where {$_ -ne ""}
		}
		Else
		{
			$InputFiles = Get-ChildItem -Path ${TestSetInputDirectory} -Include ${InputGlob}
		}
		ForEach ($InputFile in ${InputFiles})
		{
			$TestedWithOptions = $False

			ForEach ($OptionSet in ${OptionSets} -split " ")
			{
				$InputFileName = ${InputFile}.Name
				$TestDataOptionFile = "${TestProfileDirectory}\${TestSetName}\${InputFileName}.${OptionSet}"

				If (-Not (Test-Path -Path "${TestDataOptionFile}" -PathType "Leaf"))
				{
					Continue
				}
				$InputOptions = Get-content -Path "${TestDataOptionFile}" -First 1

				$Output = Invoke-Expression "${TestExecutable} ${InputOptions} ${InputFile}"
				$Result = $LastExitCode

				If (${Result} -ne ${ExitSuccess})
				{
					Break
				}
				$TestedWithOptions = $True
			}
			If ((${Result} -eq ${ExitSuccess}) -And (-Not (${TestedWithOptions})))
			{
				$Output = Invoke-Expression "${TestExecutable} ${InputFile}"
				$Result = ${LastExitCode}
			}
			If (${Result} -ne ${ExitSuccess})
			{
				Break
			}
		}
		If (${Result} -ne ${ExitSuccess})
		{
			Break
		}
	}
	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host ${Output} -foreground Red
	}
	Write-Host "${TestDescription} (" -nonewline

	If (${Result} -ne ${ExitSuccess})
	{
		Write-Host "FAIL" -foreground Red -nonewline
	}
	Else
	{
		Write-Host "PASS" -foreground Green -nonewline
	}
	Write-Host ")"

	Return ${Result}
}

$TestExecutablesDirectory = GetTestExecutablesDirectory

If (-Not (Test-Path ${TestExecutablesDirectory}))
{
	Write-Host "Missing test executables directory." -foreground Red

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
	$Result = RunTest ${TestName}

	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

Foreach (${TestName} in ${LibraryTestsWithInput} -split " ")
{
	# Split will return an array of a single empty string when LibraryTestsWithInput is empty.
	If (-Not (${TestName}))
	{
		Continue
	}
	If (Test-Path -Path "input" -PathType "Container")
	{
		$Result = RunTestWithInput ${TestName}
	}
	Else
	{
		$Result = RunTest ${TestName}
	}
	If ((${Result} -ne ${ExitSuccess}) -And (${Result} -ne ${ExitIgnore}))
	{
		Break
	}
}

Exit ${Result}

