start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\11_ACC2_scenarioF.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp011_ACC2_scenarioF"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "11_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "11_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "11_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3


