start "AirSim CityEnviron" "D:\Program Files\AirSim\LandscapeMountains_v1.5.0\WindowsNoEditor\LandscapeMountains.exe" --settings "%~dp0\ACC2_mountain.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0DNA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3

