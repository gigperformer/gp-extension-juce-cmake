#!/bin/sh

BUILD_CONFIGURATION="Release" # could be "Debug" as well
SOURCE_DIR=$(pwd)
BUILD_DIR="${SOURCE_DIR}/build/${BUILD_CONFIGURATION}"

if ! test -d "${BUILD_DIR}"; then
   mkdir -p "${BUILD_DIR}"
fi

cd "${BUILD_DIR}" || exit
cmake "${SOURCE_DIR}"
cmake --build . --config ${BUILD_CONFIGURATION} --parallel
cmake --install . --config ${BUILD_CONFIGURATION}
