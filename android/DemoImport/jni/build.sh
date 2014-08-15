#!/bin/sh
# Type './build.sh' to make Android native libraries.
# Type './build.sh -B' to rebuild the native libraries.
# Type `./build.sh -swig` to re-generate JNI classes too.
#
if [ "$1"x = "-swig"x ] || [ ! -f glyph_java_wrap.cpp ] ; then # Make JNI classes
    mkdir -p ../src/DemoImport/core
    rm -rf ../src/DemoImport/core/*.*

    swig -c++ -java -package DemoImport.core -D__ANDROID__ \
        -outdir ../src/DemoImport/core \
        -o glyph_java_wrap.cpp \
        -I../../../../vgcore/core/include \
        -I../../../core \
          ../../../core/glyph.i
        python replacejstr.py
fi
if [ "$1"x = "-swig"x ] ; then
    ndk-build $2
else
    ndk-build $1 $2
fi
