#!/bin/bash

cd debug || exit 1
for n in $(seq 1 109); do
    cmake -D CMAKE_BUILD_TYPE=Debug -D N="$n" ..
    make gamma_malloc
    if ! valgrind --leak-check=full -q ./gamma_malloc <../tests/simple.in >/dev/null; then
        echo "fail $n"
        break
    fi
done
