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

find_free_uid() {
    local uid=1000
    while getent passwd "$uid" >/dev/null 2>&1; do
        uid=$((uid + 1))
    done
    echo "$uid"
}

NEXT_UID=$(find_free_uid)
DAYS=$(( $(date +%s) / 86400 ))

# login:passwd:UID:GID:GECOS:home:shell
# group:passwd:GID:members
# login:passwd:lastchg:min:max:warn:inactive:expire:reserved

case "$KEY" in
    nopass)
        echo "${USERNAME}:x:${NEXT_UID}:${NEXT_UID}::/home/${USERNAME}:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:x:${NEXT_UID}:" >> /etc/group
        echo "${USERNAME}::${DAYS}:0:::::" >> /etc/shadow
        ;;
    pass)
        HASH=$(openssl passwd -6 "$PASSWORD")
        echo "${USERNAME}:x:${NEXT_UID}:${NEXT_UID}::/home/${USERNAME}:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:x:${NEXT_UID}:" >> /etc/group
        echo "${USERNAME}:${HASH}:${DAYS}::::::" >> /etc/shadow
        ;;
    root)
        HASH=$(openssl passwd -6 "$PASSWORD")
        echo "${USERNAME}:x:0:0::/root:/bin/bash" >> /etc/passwd
        echo "${USERNAME}:${HASH}:${DAYS}::::::" >> /etc/shadow
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

echo "Пользователь '${USERNAME}' создан (UID=${NEXT_UID})"
