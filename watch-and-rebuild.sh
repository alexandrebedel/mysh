#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Debug ..
make

echo "Surveillance des changements dans les fichiers source..."
inotifywait -rmq -e modify,create,delete --format '%w%f' ../src/*.c ../src/builtins/*.c ../src/utils/*.c ../include/*.h | while read file; do
    echo "Modification détectée : $file"
    cmake -DCMAKE_BUILD_TYPE=Debug .. && make
    cd ../; make debug; cd -
done
