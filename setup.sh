#!/usr/bin/env bash

readonly dir=build-debug
rm -rf ${dir}
mkdir ${dir}
cd ${dir}

conan install ..
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MODULE_PATH=${PWD} ..
