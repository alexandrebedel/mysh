#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Debug ..
make

echo "Surveillance des changements dans les fichiers source..."
inotifywait -rmq -e modify,create,delete --format '%w%f' ../src/** ../include | while read file; do
    echo "Modification détectée : $file"
    cmake .. && make
done
