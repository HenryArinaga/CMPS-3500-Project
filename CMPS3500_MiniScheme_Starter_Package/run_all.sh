#!/usr/bin/env bash
set -euo pipefail

# variable cmd is set to the first argument passed
cmd="${1:-}"
case "$cmd" in
  list-cases)
    find tests/public challenges/public -type f \( -name '*.scm' -o -name '*.txt' \) 2>/dev/null | sort || true
    ;;
  run-case)
    impl="${2:-}"
    file="${3:-}"
    # if impl=procedural:
    if [ $impl -eq "procedural" ]; then
    # run: ./cplusplus <file>
    output=$(./"program-name" "$file")
    echo "Implementation: ${impl}"
    echo "Case: ${file}"
    # Status is always OK for now
    echo "Status: OK"
    echo "Result: ${output}"
    # CHANGE TYPE, maybe use a variable.
    echo "Type: it-varies"
    #echo "Error: NOT_IMPLEMENTED"
    ;;
  compare-case)
    file="${2:-}"
    echo "Case: ${file}"
    echo
    echo "procedural: ERROR -> NOT_IMPLEMENTED"
    echo "oop:        ERROR -> NOT_IMPLEMENTED"
    #echo "functional: ERROR -> NOT_IMPLEMENTED"
    ;;
  *)
    echo "Usage: ./run_all.sh {list-cases|run-case <implementation> <file>|compare-case <file>}"
    exit 1
    ;;
esac
