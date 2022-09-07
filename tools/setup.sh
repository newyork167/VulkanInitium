# Install basic stuff
brew install cmake python3 ninja

git clone https://github.com/KhronosGroup/MoltenVK.git ../external
pushd ../external/MoltenVK
./fetchDependencies --macos
popd
