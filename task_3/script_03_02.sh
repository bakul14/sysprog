#!/bin/bash

echo "PID = $$"

max=$(kill -l RTMAX)
for ((s = 1; s <= max; s++)); do
    if [ $s -eq $(kill -l CHLD) ]; then  # SIGCHLD
        continue
    fi
    trap "echo signal $s $(kill -l $s) catched" $s
done

callback_sigint() {
    echo "CALLBACK: signal 2 SIGINT catched"
}

trap callback_sigint SIGINT

while true; do
    sleep 0.1
done
