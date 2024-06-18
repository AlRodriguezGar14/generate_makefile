#!/bin/bash

REPO_URL="https://github.com/AlRodriguezGar14/generate_makefile.git"
EXECUTABLE="setMakefile"
DIR="/tmp/makefile_generator_alrodriguezgar14"

echo "Installing Makefile generator"
git clone $REPO_URL $DIR
cd $DIR
make

rm /usr/local/bin/$EXECUTABLE
mv $EXECUTABLE /usr/local/bin
cd ..
rm -rf $DIR

echo "Makefile generator installed"
