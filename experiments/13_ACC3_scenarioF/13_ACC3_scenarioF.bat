start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\13_ACC3_scenarioF.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp013_ACC3_scenarioF"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "13_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "13_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2

