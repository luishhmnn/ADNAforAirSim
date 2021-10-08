set "DNAPATH=%~dp099_ANN"
set "DNAPATH=%DNAPATH:\=\\%"
start "GPP 1" "99_GeneralPurposeProcessor.exe" /DNA:%DNAPATH% /L:1 1