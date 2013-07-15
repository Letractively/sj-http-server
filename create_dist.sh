#!/bin/bash

rm -rf dist
mkdir -p dist/{lib,work}
mkdir -p dist/work/{logs,image-gallery}

cp LICENSE.txt dist
cp server/sj-http-server dist
cp server/run.sh dist
cp server/sjlog.xml dist
cp server/sj-http-server.xml dist

cp -r www dist
cp httplib/lib*.so* dist/lib
cp weblib/lib*.so* dist/lib
cp image-gallery/lib*.so* dist/lib
cp fortune-teller/lib*.so* dist/lib
cp logger/lib*.so* dist/lib

