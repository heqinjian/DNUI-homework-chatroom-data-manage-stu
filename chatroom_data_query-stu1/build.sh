#!/bin/bash
set -x
SOURCE_DIR=`pwd`
rm -rf ${SOURCE_DIR}/build/*
cd ${SOURCE_DIR}/build &&
   cmake .. &&
   make
