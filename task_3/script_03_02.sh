#!/bin/bash

echo "PID = $$"

for s in {1..31}; do
    [ $s -eq $(kill -l CHLD) ] && continue  # SIGCHLD
    trap "echo signal $(kill -l $s) catched" $s
done

while true; do
    sleep 1
done
