#!/bin/bash

set -e

export PATH="/opt/homebrew/bin:/usr/local/bin:$PATH"

if command -v ninja &> /dev/null; then
    BUILD_TYPE="Ninja"
    BUILD_SUFFIX="ninja"
else
    BUILD_TYPE="Unix Makefiles"
    BUILD_SUFFIX="make"
fi

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="."
if [ "$(uname)" = "Darwin" ]; then
    export PATH="/opt/homebrew/bin:$PATH"
    if [ -d "/opt/homebrew/opt/qt" ]; then
        export CMAKE_PREFIX_PATH="/opt/homebrew/opt/qt:$CMAKE_PREFIX_PATH"
    fi
fi

if [ ! -d "$BUILD_FOLDER" ]; then
  mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER" || exit

cmake -G "$BUILD_TYPE" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "../$SOURCE_FOLDER"

cmake --build .
