start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\18_ACC3_scenarioF_fail_hlp10.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp018_ACC3_scenarioF_fail_hlp10"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "18_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /H:10 /L:4 1
start "GPP 2" "18_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /H:10 /L:4 2
start "GPP 3" "18_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /H:10 /L:4 3
