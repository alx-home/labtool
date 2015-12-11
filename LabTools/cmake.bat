cd build/exe/Release
del CMakeCache.txt
cmake -G "MinGW Makefiles" -DFINAL=true -DCMAKE_BUILD_TYPE=Release ../../../ -DCMAKE_EXECUTABLE_INSTALL_DIR=C:/Users/AnalyseVid‚oMarche/Dropbox/LabTools
cd ../../../
pause