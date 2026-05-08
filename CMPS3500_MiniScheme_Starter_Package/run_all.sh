#!/usr/bin/env bash
set -euo pipefail

# NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga #
# ASGT: CHECKPOINT                                    #
# ORGN: CSUB - CMPS 3500                              #
# FILE: ExpressionHandler.java                        #
# DATE: 05/01/2026                                    #

# variable cmd is set to the first argument passed
cmd="${1:-}"

unknown_case="$*"

case "$cmd" in
  list-cases)

    echo "Public Core Cases:"
    find tests/public challenges/public \
        -type f \( -name 'core*.scm' -o -name 'let*.scm' -o -name 'addon*.scm' \
                -o -name 'bool*.scm' -o -name 'lambda*.scm' -o -name 'recursion*.scm' \
                -o -name 'sample_case.scm' \) 2>/dev/null \
                | xargs -n 1 basename \
                | sort \
                | sed -z 's/\n/, /g; s/, $/\n/; s/^/  /' \
                || true

    echo "Public Error Cases:"
    find tests/public challenges/public \
        -type f \( -name 'error*.scm' -o -name 'syntax*.scm' \) 2>/dev/null \
                | xargs -n 1 basename \
                | sort \
                | sed -z 's/\n/, /g; s/, $/\n/; s/^/  /' \
                || true

    ;;
  run-case)

    # check for no implementation selection
    if [ ! "${2:-}" ]; then
        echo "Error: Please choose an implementation (oop/procedural)"
        exit 1
    fi

    impl="${2:-}"

    # check for emtpy file path
    if [ ! "${3:-}" ]; then
        echo "Error: Please enter file path"
        exit 1
    fi

    file="${3:-}"

    # Stop the script if file is not found
    if [ ! -f "$file" ]; then
        echo "Error: File '${file}' not found"
        exit 1
    fi

    # ----------------- start of procedural case -----------------
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
          echo "Error: ${result}" # "result" stores the error message
        fi

        # print this output if there was no error
        if [ ! "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: OK"
          echo "Result: ${result}"
          echo "Type: ${type}"
        fi

    fi
    # ----------------- end of procedural case -----------------


    #  ----------------- start of oop case -----------------
    if [ "$2" == "oop" ]; then

        # compile interpreter program if not found
        if [ ! -f "./oop/Main" ]; then
            javac ./oop/*.java
        fi

        # process interpreter's output
        mapfile -t lines < <( java -cp oop Main "$file")
        result="${lines[0]:-}"
        type="${lines[1]:-}"

        # print error output
        if [ "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: ERROR"
          echo "Error: ${result}" # "result" stores the error message
        fi

        # print this output if there was no error
        if [ ! "$type" == "ERROR" ]; then
          echo "Implementation: ${impl}"
          echo "Case: ${file}"
          echo "Status: OK"
          echo "Result: ${result}"
          echo "Type: ${type}"
        fi

    fi
    # ----------------- end of oop case -----------------

    ;;
  compare-case)

    # check for emtpy file path
    if [ ! "${2:-}" ]; then
        echo "Error: Please enter file path"
        exit 1
    fi

    file="${2:-}"

    # Stop the script if file is not found
    if [ ! -f "$file" ]; then
        echo "Error: File '${file}' not found"
        exit 1
    fi

    echo ""
    echo "Case: ${file}"
    echo ""

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
        echo "procedural: ERROR -> ${result1}"
    fi

    # -------------------------- JAVA program -----------------------------
    # compile interpreter program if not found
    if [ ! -f "./oop/Main" ]; then
        javac ./oop/*.java
    fi

    # process interpreter's output
    mapfile -t lines < <(java -cp oop Main "$file")
    result2="${lines[0]:-}"
    type2="${lines[1]:-}"

    # print this output if there was no error
    if [ ! "$type2" == "ERROR" ]; then
        echo "oop:        OK -> ${result2} : ${type2}"
    fi

    # print error output
    if [ "$type2" == "ERROR" ]; then
        echo "oop:        ERROR -> ${result2}"
    fi
    
    # Print "skipped functional" message
    echo "functional: SKIPPED "
    echo ""
    ;;
  *)
    # Handle Unknown Input
    echo "Error: Unknown command ${unknown_case@Q}. Valid commands are: list-cases, compare-case"
    exit 1
    ;;
esac