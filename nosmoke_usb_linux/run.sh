#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
if [[ -f build/nosmoke ]]; then
  exec ./build/nosmoke
elif [[ -f nosmoke_linux ]]; then
  chmod +x nosmoke_linux 2>/dev/null || true
  exec ./nosmoke_linux
else
  echo "Нет бинарника. Сначала: chmod +x build.sh && ./build.sh"
  exit 1
fi
