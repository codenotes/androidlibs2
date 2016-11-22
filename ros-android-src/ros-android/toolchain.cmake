SET(CMAKE_SYSTEM_NAME Linux)
SET(ANDROID 1)
SET(CMAKE_HOST_UNIX 0)

# specify the cross compiler
SET(CMAKE_C_COMPILER   F:/DOWNLOAD/android-ndk-r10e/toolchains/arm-linux-androideabi-4.9/prebuilt/windows/bin/arm-linux-androideabi-gcc.exe)
SET(CMAKE_CXX_COMPILER   F:/DOWNLOAD/android-ndk-r10e/toolchains/arm-linux-androideabi-4.9/prebuilt/windows/bin/arm-linux-androideabi-g++.exe)

set (CMAKE_C_FLAGS "-If:/download/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/include -If:/download/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi/include    -If:/download/android-ndk-r10e/platforms/android-19/arch-arm/usr/include -LF:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm/usr/lib --sysroot=F:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm -fPIE" CACHE STRING "" FORCE)

set (CMAKE_CXX_FLAGS  "-If:/download/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/include -If:/download/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi/include    -If:/download/android-ndk-r10e/platforms/android-19/arch-arm/usr/include -LF:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm/usr/lib --sysroot=F:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm -fPIE" CACHE STRING "" FORCE)

#set (CMAKE_EXE_LINKER_FLAGS  "-LF:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm/usr/lib --sysroot=F:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm")
#set (CMAKE_MODULE_LINKER_FLAGS  "-LF:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm/usr/lib --sysroot=F:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm")
#set (CMAKE_SHARED_LINKER_FLAGS  "-LF:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm/usr/lib --sysroot=F:/DOWNLOAD/android-ndk-r10e/platforms/android-14/arch-arm  -lsupc++ -lgnustl_static -LF:/DOWNLOAD/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi -Wl,--no-undefined"  CACHE STRING "" FORCE)

set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER>  <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES> -lsupc++ -lgnustl_static -LF:/DOWNLOAD/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi -Wl,--no-undefined -fPIE -pie")

set(CMAKE_CXX_CREATE_SHARED_LIBRARY
      "<CMAKE_CXX_COMPILER> <CMAKE_SHARED_LIBRARY_CXX_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS> <SONAME_FLAG><TARGET_SONAME> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> -lsupc++ -lgnustl_static -LF:/DOWNLOAD/android-ndk-r10e/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi -Wl,--no-undefined -fPIE")