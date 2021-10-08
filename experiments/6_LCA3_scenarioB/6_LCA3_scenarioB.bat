start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\6_LCA3_scenarioB.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp06_LCA3_scenarioB"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "6_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 1
start "GPP 2" "6_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 2
start "GPP 3" "6_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 3
