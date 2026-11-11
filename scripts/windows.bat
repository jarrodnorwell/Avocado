cmake . -G "Visual Studio 18 2026" -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM="3.5" -B build
cmake --build build --config Release

mkdir build\windows
robocopy assets\data build\windows\data /E
robocopy build\Release build\windows /E