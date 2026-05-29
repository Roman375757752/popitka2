#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
cmake -S . -B build
cmake --build build -j --clean-first
cp -f build/nosmoke nosmoke_linux
chmod +x nosmoke_linux build/nosmoke
if strings nosmoke_linux | grep -q "BUILD_ID=20260529-gamefix"; then
  echo "OK: новый nosmoke_linux (с исправлениями)"
else
  echo "ВНИМАНИЕ: в бинарнике нет метки сборки — проверьте компиляцию"
fi
echo "Запуск: ./run.sh   (не старый бинарник из кэша)"
