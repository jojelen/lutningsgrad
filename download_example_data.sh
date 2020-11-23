#!/bin/bash

if [ ! -d data/mnist ]; then
    mkdir -p data/mnist;
fi

getFile() {
    if [ ! -f "data/mnist/$1" ]; then
        wget -P data/mnist http://yann.lecun.com/exdb/mnist/$1
    fi
    gzip -f -d data/mnist/$1
}

getFile "train-images-idx3-ubyte.gz"
getFile "train-labels-idx1-ubyte.gz"
getFile "t10k-images-idx3-ubyte.gz"
getFile "t10k-labels-idx1-ubyte.gz"

