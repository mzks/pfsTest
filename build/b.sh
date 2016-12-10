#!/bin/zsh
ls | grep -v -E 'sh$' | xargs rm -r
cmake ../source
make
make install
