#!/bin/bash

BIN=../floacon

source fp-constants.sh

test_binary64_to_binary32() {
    VALUE=${1}
    RESULT=${2}
    echo "test_binary64_to_binary32 ${VALUE} ${RES}"
    ${BIN} ${1} ${BINARY64_PRECISION} ${BINARY64_EXPONENT} ${BINARY32_PRECISION} ${BINARY32_EXPONENT} >log.txt
    echo ${RESULT} >result.txt
    RES=$(diff log.txt result.txt)
    echo "Result: " $RES
    if [[ ${RES} != "" ]]; then
        echo "Fail"
    fi
}

run() {
    while read -f $from $to; do
        test_binary64_to_binary32 $from $to
    done <inputs.txt
}

run
