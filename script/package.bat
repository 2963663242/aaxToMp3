chcp 65001
set WORKSPACE=%~dp0..
set BUILD_AUDIBLE=%WORKSPACE%\build
set BUILD_RELEASE=%WORKSPACE%\build\x64\Release
set SCRIPT_DIR=%WORKSPACE%\script
set PACKAGE_DIR=%WORKSPACE%\package
set PACKAGE_BIN=%PACKAGE_DIR%\bin
set PACKAGE_LIB=%PACKAGE_DIR%\lib
set PACKAGE_INCLUDE=%PACKAGE_DIR%\include
set PACKAGE_DOC=%PACKAGE_DIR%\doc
set PACKAGE_PDB=%PACKAGE_DIR%\pdb
set LIBFILE=%BUILD_RELEASE%\libAudibleConverter.dll
set DEMOFILE=%BUILD_RELEASE%\AudibleConverter.exe
set HEADER_FILE=%WORKSPACE%\src\libAudibleConverter\IAudibleConvert.h
set DOC_DIR=%WORKSPACE%\doc
call %SCRIPT_DIR%\compile.bat

if not exist %PACKAGE_DIR% (
	mkdir "%PACKAGE_DIR%"
	rem %PACKAGE_DIR%不存在，重新创建
)

if not exist %PACKAGE_BIN% (
	mkdir "%PACKAGE_BIN%"
	rem %PACKAGE_BIN%不存在，重新创建
)

if not exist %PACKAGE_LIB% (
	mkdir "%PACKAGE_LIB%"
	rem %PACKAGE_LIB%不存在，重新创建
)

if not exist %PACKAGE_INCLUDE% (
	mkdir "%PACKAGE_INCLUDE%"
	rem %PACKAGE_INCLUDE%不存在，重新创建
)

if not exist %PACKAGE_DOC% (
	mkdir "%PACKAGE_DOC%"
	rem %PACKAGE_DOC%不存在，重新创建
)

if not exist %PACKAGE_PDB% (
	mkdir "%PACKAGE_PDB%"
	rem %PACKAGE_PDB%不存在，重新创建
)


rem *******************将%LIBFILE%和%DEMOFILE%复制到%PACKAGE_BIN%
xcopy %LIBFILE% %PACKAGE_BIN% /Y
xcopy %DEMOFILE% %PACKAGE_BIN% /Y


set BIN_DIR_NAME=bin
set PLUGINS_DIR_NAME=plugins
rem *******************将 %BUILD_RELEASE%\%BIN_DIR_NAME% 和 %BUILD_RELEASE%\%PLUGINS_DIR_NAME% 复制到 %PACKAGE_BIN%
xcopy %BUILD_RELEASE%\%BIN_DIR_NAME% %PACKAGE_BIN%\%BIN_DIR_NAME% /E /Y /I
xcopy %BUILD_RELEASE%\%PLUGINS_DIR_NAME% %PACKAGE_BIN%\%PLUGINS_DIR_NAME% /E /Y /I


rem *******************将 %HEADER_FILE% 复制到 %PACKAGE_INCLUDE%
xcopy %HEADER_FILE% %PACKAGE_INCLUDE% /Y

rem *******************将 %DOC_DIR% 的所有文档复制到 %PACKAGE_DOC%
xcopy %DOC_DIR%\* %PACKAGE_DOC% /E /Y

rem *******************将 所有lib文件复制到 %PACKAGE_LIB%
xcopy %BUILD_RELEASE%\*.lib %PACKAGE_LIB%  /Y

rem *******************将 所有pdb文件复制到 %PACKAGE_LIB%
xcopy %BUILD_RELEASE%\*.pdb %PACKAGE_PDB%  /Y

