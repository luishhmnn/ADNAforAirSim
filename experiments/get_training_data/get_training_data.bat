start "AirSim CityEnviron" "..\..\AirSimServer\CityEnviron\WindowsNoEditor\CityEnviron.exe" --settings "%~dp0\airsim_settings.json"

start "ADNAforAirSim" "..\..\Client\build\x64\Debug\ADNAAirSimClient.exe"

set "DNAPATH=%~dp0get_training_data"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% 1
