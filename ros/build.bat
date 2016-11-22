set PYTHON_ROOT=E:\WARE\PYTHON27
set PATH=%~dp0;%PYTHON_ROOT%;%PATH%;C:\Program Files (x86)\CMake\bin
set PYTHONPATH=%PYTHONPATH%;F:\PROJECTS\infusion\ros-android\ros\install_isolated\lib\site-packages

python ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBoost_USE_STATIC_LIBS=1 -DBUILD_SHARED_LIBS=1 --only-pkg-with-deps=roscpp_tutorials  --from-pkg=roscpp --cmake-args -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=F:\PROJECTS\infusion\ros-android\toolchain.cmake