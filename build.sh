#!/usr/bin/env bash

CURRENT_DIR=`pwd $(dirname "$0")`
cd ${CURRENT_DIR}/src/main/native
g++ -std=c++11 \
        -fPIC \
        -I "${JAVA_HOME}/include" \
        -I "${JAVA_HOME}/include/linux" \
        -shared -o "libpmdevice.so" \
        com_intel_pmdevice.cpp \
        -lmemkind

mkdir -p ${CURRENT_DIR}/src/main/resources/lib/linux64
mv libpmdevice.so ${CURRENT_DIR}/src/main/resources/lib/linux64
cd ${CURRENT_DIR}/
mvn clean package
