start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\8_LCA4_scenarioB.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp08_LCA4_scenarioB"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "8_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "8_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "8_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

