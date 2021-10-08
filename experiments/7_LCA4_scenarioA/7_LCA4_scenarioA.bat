start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\7_LCA4_scenarioA.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp07_LCA4_scenarioA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "7_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 1

