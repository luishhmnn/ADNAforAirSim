start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\settings.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0car"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

