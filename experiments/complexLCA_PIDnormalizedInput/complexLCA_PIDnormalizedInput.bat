start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\complexLCA_PIDnormalizedInput.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0complexLCA_PIDnormalizedInput"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3
start "GPP 4" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 4
start "GPP 5" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 5

