start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\16_LCA4_scenarioA_fail.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp016_LCA4_scenarioA_fail"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "16_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "16_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "16_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

