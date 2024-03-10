#!/bin/bash

source config.sh

# Remove the CMake build directory.
if [ -d "$SP_BUILD_DIR" ]
then
    echo "removing '$SP_BUILD_DIR'"
    rm -rf "$SP_BUILD_DIR"
fi
