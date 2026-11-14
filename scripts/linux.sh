cmake . -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM="3.5" -B build
cmake --build build --config Release

rm -r build/linux
mkdir -p build/linux/usr/share/avocado
cp -r assets/data build/linux/usr/share/avocado

wget -ncv https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x ./linuxdeploy-x86_64.AppImage
mv ./linuxdeploy-x86_64.AppImage build/linuxdeploy-x86_64.AppImage

APPIMAGE_EXTRACT_AND_RUN=1 ./build/linuxdeploy-x86_64.AppImage \
    --appdir=./build/linux \
    --create-desktop-file \
    --executable=./build/Avocado \
    --icon-file=./assets/Avocado.png \
    --output=appimage

mv ./*.AppImage build