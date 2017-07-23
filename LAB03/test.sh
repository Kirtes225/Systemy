#!/bin/bash
gcc -std=c11 primeThread.c -lpthread -o thr
gcc -std=c11 primeProcess.c -o prc

thrTime="$(time ( ./thr 9 3 5 2 ) 2>&1 1>/dev/null )"
prcTime="$(time ( ./prc 9 3 5 2 ) 2>&1 1>/dev/null )"
echo "Watki: $thrTime"
echo "Procesy: $prcTime"
