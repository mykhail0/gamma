#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Run like: $0 path/to/gamma_test path/to/gamma path/to/tests/dir"
    exit 1
fi

function prepend_dot {
    prog="$1"
    if [ "$(basename -- "$1")" = "$1" ]; then
        prog="./"$1
    fi
    echo "$prog"
}

prog="$(prepend_dot "$2")"
test_prog="$(prepend_dot "$1")"

echo "Testing game engine"
if ! ./test_game_engine.sh "$test_prog"; then
    echo "Game engine tests failed"
    exit 1
fi
echo "Game engine tests OK"

echo "Testing batch mode"
for f in "$3"/*.in; do
    base="$(basename -- "$f" .in)"

    out="$(mktemp)"
    err="$(mktemp)"

    timeout 2s valgrind --leak-check=full -q "$prog" <"$f" >"$out" 2>"$err"
    ret_val=$?
    if [ $ret_val -ne 0 ]; then
        echo "Test $base fail"
        echo "Out: $out"
        echo "Err: $err"
        exit 1
    fi

    if ! diff --color=auto "${3}/${base}.out" "$out"; then
        echo "Test $base fail: .out diff"
        echo "Out: $out"
        echo "Err: $err"
        exit 1
    fi

    if ! diff --color=auto "${3}/${base}.err" "$err"; then
        echo "Test $base fail: .err diff"
        echo "Out: $out"
        echo "Err: $err"
        exit 1
    fi
    rm "$out" "$err"

    echo "Test $base OK"
done

echo "Batch mode OK"

echo "Testing interactive mode"

broken="${3}/broken.input"
err="$(mktemp)"
out="$(cat "$broken" | timeout 2s valgrind --leak-check=full -q "$prog" 2>"$err")"
ret_val=$?

echo "Testing broken.input"
if [ "$out" ]; then
    echo "Expected no standard output"
    echo "Err: $err"
    echo "Output: $out"
    echo "Exit code: $ret_val"
    exit 1
fi
if [ $ret_val -ne 1 ]; then
    echo "Expected exit code of 1"
    echo "Err: $err"
    echo "Exit code: $ret_val"
    exit 1
fi
if ! diff --color=auto "${3}/broken.err" "$err"; then
    echo "Expected different error output"
    echo "Err: $err"
    exit 1
fi
echo "Test broken.input OK"
echo "Interactive mode OK"
