#!/bin/bash

KEY="$1"
USERNAME="$2"
PASSWORD="$3"

if [ -z "$KEY" ] || [ -z "$USERNAME" ]; then
    echo "Использование: $0 <nopass|pass|root> <username> [password]"
    exit 1
fi

if [ "$EUID" -ne 0 ]; then
    echo "Нужны права root"
    exit 1
fi

# следующий свободный UID
NEW_UID=$(($(tail -1 /etc/passwd | cut -d: -f3) + 1))
DAYS=$(( $(date +%s) / 86400 ))

case "$KEY" in
    nopass)
        echo "${USERNAME}:x:${NEW_UID}:${NEW_UID}::/home/${USERNAME}:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:x:${NEW_UID}:" >> /etc/group
        echo "${USERNAME}::${DAYS}:0:99999:7:::" >> /etc/shadow
        ;;
    pass)
        HASH=$(openssl passwd -6 "$PASSWORD")
        echo "${USERNAME}:x:${NEW_UID}:${NEW_UID}::/home/${USERNAME}:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:x:${NEW_UID}:" >> /etc/group
        echo "${USERNAME}:${HASH}:${DAYS}:0:99999:7:::" >> /etc/shadow
        ;;
    root)
        HASH=$(openssl passwd -6 "$PASSWORD")
        echo "${USERNAME}:x:0:0::/root:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:${HASH}:${DAYS}:0:99999:7:::" >> /etc/shadow
        ;;
    *)
        echo "Неизвестный ключ: $KEY (nopass|pass|root)"
        exit 1
        ;;
esac

if [ "$KEY" = "root" ]; then
    mkdir -p "/root"
else
    mkdir -p "/home/${USERNAME}"
fi

echo "Пользователь '${USERNAME}' создан (ключ=${KEY}, UID=${NEW_UID})"
