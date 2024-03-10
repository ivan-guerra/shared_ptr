#!/bin/bash

source config.sh

Main()
{
    # Create the build directory if it does not already exist.
    mkdir -pv "$SP_BUILD_DIR"

    # Set the build type according to the first program arg if any. Default is release.
    BUILD_TYPE="Release"
    if [ -n  "$1" ]
    then
        BUILD_TYPE=$1
    fi

    pushd "$SP_BUILD_DIR" > /dev/null || exit 1
    cmake ../ \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_INSTALL_PREFIX="$SP_BIN_DIR" \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" && \
        make -j"$(nproc)" all

    # Exit if any of the above commands fails.
    if [ $? -ne 0 ];
    then
        exit 1
    fi
    popd > /dev/null || exit 1
}

Main "$1"
