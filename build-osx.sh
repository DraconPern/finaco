#!/bin/bash
set -xe

if [ "$1" == "Release" ]
then
  TYPE=Release
else
  TYPE=Debug
fi

BUILD_DIR=`pwd`
DEVSPACE=`pwd`
export MACOSX_DEPLOYMENT_TARGET=10.9

./build.sh $1

cd $BUILD_DIR/build-$TYPE
hdiutil create -volname finaco -srcfolder $BUILD_DIR/build-$TYPE/finaco.app -ov -format UDZO finaco.dmg
