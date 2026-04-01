#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
cmake -S . -B build
cmake --build build -j
echo "Готово. Запуск: ./build/nosmoke (из этой же папки)"
