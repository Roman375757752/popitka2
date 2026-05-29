#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
BIN=""
if [[ -f build/nosmoke ]]; then
  BIN=build/nosmoke
elif [[ -f nosmoke_linux ]]; then
  BIN=nosmoke_linux
fi
if [[ -z "$BIN" ]]; then
  echo "Нет бинарника. Сначала: chmod +x build.sh && ./build.sh"
  exit 1
fi
if ! strings "$BIN" | grep -q "BUILD_ID=20260529-gamefix"; then
  echo "ОШИБКА: $BIN — СТАРАЯ сборка (будет вылет на «Новая игра»)."
  echo "Соберите заново:"
  echo "  chmod +x build.sh run.sh"
  echo "  ./build.sh"
  echo "  (или: bash build.sh)"
  exit 1
fi
exec ./"$BIN"
