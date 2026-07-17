#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Run like: $0 prog"
    exit
fi

prog="$1"
if [ "$(basename -- "$1")" = "$1" ]; then
    prog="./"$1
fi

for test_name in example minimal params many_players many_games delete_null \
    normal_move golden_move golden_possible areas tree border; do

    if ! valgrind --leak-check=full -q "$prog" "$test_name"; then
        echo "Test $test_name fail"
        exit
    fi

    echo "Test $test_name OK"
done

function run_wo_valgrind() {
    if ! "$prog" "$1"; then
        echo "Test $1 fail"
        exit
    fi
    echo "Test $1 OK"
}

# Limit virtual memory to 8gb so that malloc actually returns NULL when there is
# no memory.
ulimit -v 8000000
run_wo_valgrind middle_board
run_wo_valgrind big_board

"$prog" memory_alloc
ret_val=$?
if [ $ret_val -ne 13 ]; then
    echo "Test memory_alloc fail"
    exit
fi
echo "Test memory_alloc OK"
