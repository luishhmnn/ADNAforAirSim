start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\2_LCA1_scenarioB.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp02_LCA1_scenarioB"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "2_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "2_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "2_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

