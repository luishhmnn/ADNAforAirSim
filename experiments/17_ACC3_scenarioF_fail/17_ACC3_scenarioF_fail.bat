start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\17_ACC3_scenarioF_fail.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp017_ACC3_scenarioF_fail"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "17_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "17_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "17_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3
