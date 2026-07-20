#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Run like: $0 prog"
    exit 1
fi

prog="$1"
if [ "$(basename -- "$1")" = "$1" ]; then
    prog="./"$1
fi

for test_name in example minimal params many_players many_games delete_null \
    normal_move golden_move golden_possible areas tree border; do

    if ! timeout 2s valgrind --leak-check=full -q "$prog" "$test_name"; then
        echo "Test $test_name fail"
        exit 1
    fi

    echo "Test $test_name OK"
done

function run_wo_valgrind() {
    if ! timeout 600s "$prog" "$1"; then
        echo "Test $1 fail"
        exit 1
    fi
    echo "Test $1 OK"
}

# Limit virtual memory to 8gb so that malloc actually returns NULL when there is
# no memory.
ulimit -v 8000000
run_wo_valgrind middle_board
run_wo_valgrind big_board

timeout 13s "$prog" memory_alloc
ret_val=$?
if [ $ret_val -ne 13 ]; then
    echo "Test memory_alloc fail"
    exit 1
fi
echo "Test memory_alloc OK"
