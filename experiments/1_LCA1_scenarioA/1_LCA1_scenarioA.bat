start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\1_LCA1_scenarioA.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp01_LCA1_scenarioA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "1_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "1_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "1_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

