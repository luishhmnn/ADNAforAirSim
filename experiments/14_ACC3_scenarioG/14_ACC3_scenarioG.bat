start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\14_ACC3_scenarioG.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp014_ACC3_scenarioG"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "14_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "14_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "14_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3
