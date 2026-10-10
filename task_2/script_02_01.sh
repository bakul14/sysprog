#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Использование: $0 <username>"
    exit 1
fi

last -n 3 "$1"
