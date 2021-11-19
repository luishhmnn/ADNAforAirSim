set "DNAPATH=%~dp0DNA"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:4 1

