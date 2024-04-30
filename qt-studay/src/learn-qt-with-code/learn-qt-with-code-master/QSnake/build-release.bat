mkdir build
cd build

rem build parent folder
cmake -G "Visual Studio 15 2017" -A x64  -DCMAKE_PREFIX_PATH=C:\Qt\Qt5.12.10\5.12.10\msvc2017_64 ..
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.com" QSnake.sln  /Build "Release|x64"