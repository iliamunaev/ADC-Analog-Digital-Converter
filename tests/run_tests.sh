#!/bin/bash

# Set executable name
EXEC="./ADC"

# Ensure the executable exists
if [ ! -f "$EXEC" ]; then
    echo "Executable $EXEC not found! Compiling now..."
    make
    if [ ! -f "$EXEC" ]; then
        echo "Error: Compilation failed. Fix errors before testing."
        exit 1
    fi
fi

echo "Running ADC Program Tests..."
echo "----------------------------"

# Define test cases
declare -a TEST_CASES=(
    "3 8 0 5"     # Expected Output: 00000011
    "6 8 0 10"    # Expected Output: 00011001
    "0 4 0 5"     # Expected Output: 0000
    "5 4 0 5"     # Expected Output: 1111
    "10 16 0 100" # Expected Output: 0011001000110000
)

# Expected outputs for valid cases
declare -a EXPECTED_OUTPUTS=(
    "00000011"
    "00011001"
    "0000"
    "1111"
    "0011001000110000"
)

# Invalid test cases (should return "Error")
declare -a INVALID_TESTS=(
    "-3 8 0 5"
    "3 -8 0 5"
    "3 8 5 0"
    "3 40 0 5"
)

# Expected error message for invalid tests
ERROR_MESSAGE="Error"

# Loop through valid test cases
for i in "${!TEST_CASES[@]}"; do
    TEST="${TEST_CASES[i]}"
    EXPECTED="${EXPECTED_OUTPUTS[i]}"

    echo -n "Test: ./ADC $TEST -> "

    OUTPUT=$($EXEC $TEST 2>&1 | tail -n1)  # Capture last line of output (binary)

    # Compare only the last 'bit_res' bits
    if [[ "$OUTPUT" == *"$EXPECTED"* ]]; then
        echo "✅ PASSED"
    else
        echo "❌ FAILED"
        echo "Expected: $EXPECTED"
        echo "Got:      $OUTPUT"
    fi
done

# Loop through invalid test cases
for TEST in "${INVALID_TESTS[@]}"; do
    echo -n "Test: ./ADC $TEST (Invalid Input) -> "

    OUTPUT=$($EXEC $TEST 2>&1)

    if [[ "$OUTPUT" == *"$ERROR_MESSAGE"* ]]; then
        echo "✅ PASSED"
    else
        echo "❌ FAILED"
        echo "Expected: $ERROR_MESSAGE"
        echo "Got:      $OUTPUT"
    fi
done

# Test "exit" command
echo -n "Test: ./ADC exit -> "
EXIT_OUTPUT=$($EXEC exit 2>&1)
if [[ "$EXIT_OUTPUT" == *"exit success"* ]]; then
    echo "✅ PASSED"
else
    echo "❌ FAILED"
fi

echo "----------------------------"
echo "Testing Complete."
