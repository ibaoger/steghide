#!/bin/bash

## Ubuntu 16
aptitude install libmhash-dev -y
aptitude install libmcrypt-dev -y
aptitude install libjpeg-dev -y
aptitude install zlib1g zlib1g-dev -y
aptitude install gettext -y
aptitude install build-essential -y
aptitude install libtool-bin -y
./configure
make
make check


## Mac OSX (failed)
# brew install mhash
# brew install mcrypt
# brew install jpeg
# brew install zlib
# brew install gettext
# brew link gettext --force

# ./configure CPPFLAGS='-I/usr/local/Cellar/gettext/0.19.8.1/include'
# make # error of libtools
# make check

# brew unlink gettext