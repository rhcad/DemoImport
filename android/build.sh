#!/bin/sh
# Type './build.sh' to make Android native libraries.
# Type './build.sh -B' to rebuild the native libraries.
# Type `./build.sh -swig` to re-generate JNI classes too.
# Type `./build.sh APP_ABI=x86` to build for the x86 Emulator.
#

if [ ! -f ../../vgcore/android/build.sh ] ; then
    git clone https://github.com/rhcad/vgcore ../../vgcore
fi
if [ ! -f ../../vgandroid/build.sh ] ; then
    git clone https://github.com/rhcad/vgandroid ../../vgandroid
fi

cd ../../vgandroid; sh build.sh $1 $2; cd ../DemoImport/android
cd DemoImport/jni; sh build.sh $1 $2; cd ../..
