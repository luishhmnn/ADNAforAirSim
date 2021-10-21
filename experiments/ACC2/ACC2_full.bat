start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\ACC2.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0DNA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1

