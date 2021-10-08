start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\5_LCA3_scenarioA.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp05_LCA3_scenarioA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "5_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 1
start "GPP 2" "5_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 2
start "GPP 3" "5_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 3
