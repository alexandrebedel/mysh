#!/bin/bash

ls ..
# Crée un dossier build si nécessaire
# mkdir -p build
# cd build

# Première compilation
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Surveiller les fichiers pour les changements
echo "Surveillance des changements dans les fichiers source..."
inotifywait -rmq -e modify,create,delete --format '%w%f' ../src/** ../include | while read file; do
    echo "Modification détectée : $file"
    cmake .. && make
done
