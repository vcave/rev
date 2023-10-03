#!/bin/bash

#Build the test
make clean && make
REV_SST_CONFIG=${REV_SST_CONFIG:-./rev-dcmp.py}
REV_EXE=dcmp.exe

# Check that the exec was built...
if [ -f ${REV_EXE} ]; then
  REV_EXE=${REV_EXE} sst --add-lib-path=../../build/src/ ${REV_SST_CONFIG}
else
  echo "Test DCMP: File ${REV_EXE} not found - likely build failed"
  exit 1
fi
