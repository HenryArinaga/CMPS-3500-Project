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

    if [ "$2" == "procedural" ]; then

        if [ ! -f "./procedural/cpp_interpreter" ]; then
            g++ ./procedural/*.cpp -o ./procedural/cpp_interpreter
        fi

        mapfile -t lines < <(./procedural/cpp_interpreter "$file") # run: cpp_interpreter <path to file_name.scm>
        result="${lines[0]:-}"
        type="${lines[1]:-}"

        if [ "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: ERROR"
          echo "Error: ${result}"
        fi

        if [ ! "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: OK"
          echo "Result: ${result}"
          echo "Type: ${type}"
        fi

        #implement error messages (later)
        #echo "Error: NOT_IMPLEMENTED"

    fi

    if [ "$2" == "oop" ]; then
        echo "Implementation: ${impl}"
        echo "Case: ${file}"
        echo "Status: Work in progress"
        echo "Result: Work in progress"
        echo "Type: Work in progress"
    fi
    ;;
  *)
    echo "Usage: ./run_all.sh {list-cases|run-case <implementation> <file>|compare-case <file>}"
    exit 1
    ;;
esac