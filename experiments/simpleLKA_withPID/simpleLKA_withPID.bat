start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\simpleLKA_withPID.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0simpleLKA_withPID"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

