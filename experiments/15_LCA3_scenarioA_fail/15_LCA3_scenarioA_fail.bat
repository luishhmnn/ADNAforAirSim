start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\15_LCA3_scenarioA_fail.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp015_LCA3_scenarioA_fail"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "15_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 1
start "GPP 2" "15_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 2
start "GPP 3" "15_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 3
