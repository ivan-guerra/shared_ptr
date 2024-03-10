#!/bin/bash

# Root directory.
SP_PROJECT_PATH="$(dirname "$(pwd)")"

# Scripts directory.
export SP_SCRIPTS_PATH="${SP_PROJECT_PATH}/scripts"

# CMake build files and cache.
export SP_BUILD_DIR="${SP_PROJECT_PATH}/build"
