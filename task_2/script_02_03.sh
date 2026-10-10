#!/bin/bash

CONFIG="$1"
shift
while getopts "a:" opt; do
    case "$opt" in
        a) ALG="$OPTARG" ;;
    esac
done

if [ -z "$CONFIG" ] || [ -z "$ALG" ]; then
    echo "Использование: $0 <config> -a <gzip|bzip2|xz>"
    exit 1
fi

source "$CONFIG"

case "$ALG" in
    gzip)  EXT=tar.gz;  TAR_OPT=z ;;
    bzip2) EXT=tar.bz2; TAR_OPT=j ;;
    xz)    EXT=tar.xz;  TAR_OPT=J ;;
    *) echo "Неизвестный алгоритм: $ALG (gzip|bzip2|xz)"; exit 1 ;;
esac

mkdir -p "$DST_DIR"

ARCHIVE="${DST_DIR}/backup_$(date +%Y%m%d_%H%M%S).${EXT}"
tar -c${TAR_OPT}f "$ARCHIVE" -C "$(dirname "$SRC_DIR")" "$(basename "$SRC_DIR")"
echo "Создан архив: $ARCHIVE"

COUNT=$(ls -1 "${DST_DIR}"/backup_* 2>/dev/null | wc -l)
if [ "$COUNT" -gt "$MAX_BACKUPS" ]; then
    EXCESS=$((COUNT - MAX_BACKUPS))
    if [ "$POLICY" = "oldest" ]; then
        ls -1t "${DST_DIR}"/backup_* | tail -n "$EXCESS" | xargs rm -f
    else
        ls -1t "${DST_DIR}"/backup_* | head -n "$EXCESS" | xargs rm -f
    fi
    echo "Удалено лишних архивов: $EXCESS (policy=$POLICY)"
fi
