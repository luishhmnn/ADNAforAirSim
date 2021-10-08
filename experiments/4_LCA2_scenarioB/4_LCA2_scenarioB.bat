start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\4_LCA2_scenarioB.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp04_LCA2_scenarioB"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "4_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "4_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "4_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3
