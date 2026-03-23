#!/bin/bash

set -ex

puzzle="53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79"
expected="534678912672195348198342567859761423426853791713924856961537284287419635345286179"

output=$(./sudoku-solver "$puzzle")
if ! echo "$output" | grep -q "$expected"; then
    echo "Test failed: expected solution was not found"
    exit 1
fi

invalid="11..............................................................................."
if ./sudoku-solver "$invalid" >/dev/null 2>&1; then
    echo "Test failed: contradictory board should be rejected as invalid input"
    exit 1
fi

limited_output=$(./sudoku-solver "$puzzle" 1)
if ! echo "$limited_output" | grep -Fq "Found 1 solution(s)."; then
    echo "Test failed: max_solutions limit did not work"
    exit 1
fi

echo "All tests passed"
