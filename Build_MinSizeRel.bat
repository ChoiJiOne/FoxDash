@ECHO OFF

SET MODE=MinSizeRel
SET SCRIPT=Script\\Build.bat
SET ADMIN_OPTION=%1

%SCRIPT% %MODE% %ADMIN_OPTION%