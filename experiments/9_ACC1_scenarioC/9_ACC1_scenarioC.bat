start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\9_ACC1_scenarioC.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp09_ACC1_scenarioC"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "9_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "9_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "9_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

