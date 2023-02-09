set WORKSPACE=%~dp0..
set BUILD_AUDIBLE=%WORKSPACE%\build

if not exist %WORKSPACE% (
	mkdir "%BUILD_AUDIBLE%"
)

cmake -S "%WORKSPACE%" -B "%BUILD_AUDIBLE%" -G "Visual Studio 16 2019" -A x64
cmake --build "%BUILD_AUDIBLE%" --config Release
