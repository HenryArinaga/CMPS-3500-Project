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

    # start of procedural case
    if [ "$2" == "procedural" ]; then

        # compile interpreter program if not found
        if [ ! -f "./procedural/cpp_interpreter" ]; then
            g++ ./procedural/*.cpp -o ./procedural/cpp_interpreter
        fi

        # process interpreter's output
        mapfile -t lines < <(./procedural/cpp_interpreter "$file")
        result="${lines[0]:-}"
        type="${lines[1]:-}"

        # print error output
        if [ "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: ERROR"
          echo "Error: ${result}" # "result" stores the detailed error message
        fi

        # print this output if there was no error
        if [ ! "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: OK"
          echo "Result: ${result}"
          echo "Type: ${type}"
        fi

    fi # end of procedural case

# --------------------------------------------------
    # # start of oop case
    # if [ "$2" == "oop" ]; then

    #     # compile interpreter program if not found
    #     if [ ! -f "./oop/Main" ]; then
    #         javac *.java
    #     fi

    #     # process interpreter's output
    #     mapfile -t lines < <(./oop/Main "$file")
    #     result="${lines[0]:-}"
    #     type="${lines[1]:-}"

    #     # print error output
    #     if [ "$type" == "ERROR" ]; then
    #       echo "Implementation: ${impl}"
    #       echo "Case: ${file}"
    #       echo "Status: ERROR"
    #       echo "Error: ${result}" # "result" stores the detailed error message
    #     fi

    #     # print this output if there was no error
    #     if [ ! "$type" == "ERROR" ]; then
    #       echo "Implementation: ${impl}"
    #       echo "Case: ${file}"
    #       echo "Status: OK"
    #       echo "Result: ${result}"
    #       echo "Type: ${type}"
    #     fi

    # fi # end of procedural case

# --------------------------------------------------
    ;;
  compare-case)
    file="${2:-}"

    # ------------------------- C++ program -----------------------------
    # compile interpreter program if not found
    if [ ! -f "./procedural/cpp_interpreter" ]; then
        g++ ./procedural/*.cpp -o ./procedural/cpp_interpreter
    fi

    # process interpreter's output
    mapfile -t lines < <(./procedural/cpp_interpreter "$file"| tr -d '\r')
    result1="${lines[0]:-}"
    type1="${lines[1]:-}"

    # print this output if there was no error
    if [ ! "$type1" == "ERROR" ]; then
        echo "procedural: OK -> ${result1} : ${type1}"
    fi

    # print error output
    if [ "$type1" == "ERROR" ]; then
        echo "ERROR -> ${result1}"
    fi

    # -------------------------- JAVA program -----------------------------
    # # compile interpreter program if not found
    # if [ ! -f "./oop/Main" ]; then
    #     javac *.java
    # fi

    # # process interpreter's output
    # mapfile -t lines < <(./oop/Main "$file")
    # result2="${lines[0]:-}"
    # type2="${lines[1]:-}"

    # # print this output if there was no error
    # if [ ! "$type2" == "ERROR" ]; then
    #     echo "procedural: OK -> ${result2} : ${type2}"
    # fi

    # # print error output
    # if [ "$type2" == "ERROR" ]; then
    #     echo "ERROR -> ${result2}"
    # fi
    
    echo "functional: SKIPPED "
    ;;
  *)
    echo "Usage: ./run_all.sh {list-cases|run-case <implementation> <file>|compare-case <file>}"
    exit 1
    ;;
esac