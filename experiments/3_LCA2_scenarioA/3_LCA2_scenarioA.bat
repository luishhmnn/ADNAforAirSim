start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\3_LCA2_scenarioA.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp03_LCA2_scenarioA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "3_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "3_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "3_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

