#!/bin/bash

# Stop on error
set -e

echo "Starting build script..."

# Add Homebrew bin to PATH just in case
export PATH="/opt/homebrew/bin:/usr/local/bin:$PATH"

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="."
IMG_FOLDER="img"

# Attempt to auto-detect Qt installation path on macOS (Homebrew)
if [ "$(uname)" = "Darwin" ]; then
    if [ -d "/opt/homebrew/opt/qt" ]; then
        echo "Found Qt at /opt/homebrew/opt/qt"
        export CMAKE_PREFIX_PATH="/opt/homebrew/opt/qt:$CMAKE_PREFIX_PATH"
    elif [ -d "/usr/local/opt/qt" ]; then
        echo "Found Qt at /usr/local/opt/qt"
        export CMAKE_PREFIX_PATH="/usr/local/opt/qt:$CMAKE_PREFIX_PATH"
    else
        echo "Warning: Qt installation not found in standard Homebrew locations."
    fi
fi

if [ ! -d "$BUILD_FOLDER" ]; then
  echo "Creating build directory: $BUILD_FOLDER"
  mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER" || exit

echo "Running CMake..."
cmake -G "$BUILD_TYPE" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "../$SOURCE_FOLDER"

echo "Building..."
cmake --build .

if [ ! -d "$IMG_FOLDER" ]; then
  mkdir "$IMG_FOLDER"
fi

echo "Copying resources..."
cp "../$IMG_FOLDER/grustnii-smail.png" "$IMG_FOLDER/"

cd ..
echo "Build complete."

