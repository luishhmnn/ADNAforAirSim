
set "DNAPATH=%~dp0complexLCA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1
start "GPP 2" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 2
start "GPP 3" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 3
start "GPP 4" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 4
start "GPP 5" "%~dp0\..\..\GeneralPurposeProcessor\GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 5

