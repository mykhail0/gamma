#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Run like: $0 prog dir"
    exit
fi

prog="$1"
if [ "$(basename -- "$1")" = "$1" ]; then
    prog="./"$1
fi

for f in "$2"/*.in; do
    base="$(basename -- "$f" .in)"

    out="$(mktemp)"
    err="$(mktemp)"

    valgrind --leak-check=full -q "$prog" <"$f" >"$out" 2>"$err"
    ret_val=$?
    if [ $ret_val -ne 0 ]; then
        echo "Test $base fail"
        echo "Output files: $out $err"
        break
    fi

    if ! diff --color=auto "${2}/${base}.out" "$out"; then
        echo "Test $base fail: .out diff"
        echo "Output files: $out $err"
        break
    fi

    if ! diff --color=auto "${2}/${base}.err" "$err"; then
        echo "Test $base fail: .err diff"
        echo "Output files: $out $err"
        break
    fi
    rm "$out" "$err"

    echo "Test $base OK"
done
