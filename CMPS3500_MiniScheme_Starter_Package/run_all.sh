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
    #if [ $impl -eq "procedural" ]; then
    if [ "$2" == "procedural" ]; then

        output=$(./procedural/cpp_interpreter "$file") # run: cpp_interpreter <file_name.scm>

        echo "Implementation: ${impl}"
        echo "Case: ${file}"
        echo "Status: OK"        # <------- Status is always OK for now
        echo "Result: ${output}"
        #echo "Type: -----"   # <----- CHANGE TYPE, maybe use a variable.
        
        #implement error messages (later)
        #echo "Error: NOT_IMPLEMENTED"  
    fi
    ;;
  *)
    echo "Usage: ./run_all.sh {list-cases|run-case <implementation> <file>|compare-case <file>}"
    exit 1
    ;;
esac