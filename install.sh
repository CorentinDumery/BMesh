#!/bin/bash

# exit when any command fails
set -e
# keep track of the last executed command
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command filed with exit code $?."' EXIT

# Create extern lib folder
mkdir -p extern
cd extern

# Install gsl 2.5 as an extern lib
wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.5.tar.gz
tar -zxvf gsl-2.5.tar.gz
cd gsl-2.5
mkdir -p ../gsl
./configure --prefix=$PWD/../gsl
make
make install
cd ..
rm -rf gsl-2.5.tar.gz gsl-2.5

# Install libQGLViewer 2.7.1 as an extern lib
wget http://www.libqglviewer.com/src/libQGLViewer-2.7.1.tar.gz
tar -xzf libQGLViewer-2.7.1.tar.gz
cd libQGLViewer-2.7.1/QGLViewer
qmake
make
cd ../..
rm -rf libQGLViewer-2.7.1.tar.gz

echo "Installation done !"
exit 1
