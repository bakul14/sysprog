#!/bin/bash

log() {
    echo "[$(date +%T)] $1"
}

sleep 100 &
child_pid=$!
log "child started, PID = $child_pid"

sleep 5

kill -TERM $child_pid
log "sent SIGTERM to $child_pid"

wait $child_pid
log "child exited, status = $?"
