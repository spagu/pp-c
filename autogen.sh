#!/usr/local/bin/bash

make clean

$(type glibtoolize >/dev/null 2>&1) && LIBTOOLIZE=${LIBTOOLIZE:-glibtoolize}
aclocal 
${LIBTOOLIZE:-libtoolize} --automake --force 
autoheader --force 
automake --foreign --add-missing --force 
autoconf --force
autoreconf --install --force 
./configure