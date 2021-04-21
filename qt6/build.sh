#!/bin/bash

if [ -z "$1" ]; then
    BDIR=$(pwd)/lib/qt6
else
    BDIR=$1
fi

mkdir -pv $BDIR/src
mkdir -pv $BDIR/build
mkdir -pv $BDIR/bin

cd $BDIR/src

if [[ ! -d ".git" ]]; then
    git clone https://code.qt.io/qt/qt5.git .
fi

git remote update origin
git checkout --detach v6.1.0-beta3
perl init-repository
git submodule update

cd ../build
../src/configure -prefix $BDIR/bin -make tests -skip qtscxml
cmake --build . --parallel 4 && cmake --install .
