nosmoke — что на флешке
======================

Папки:
  platform/   — SDL-вход, рендер, заглушки
  Data/       — код игры
  Graphics/   — картинки
  Audio/      — звук
  .github/    — опционально CI

Файл nosmoke_linux — уже собранный бинарник под Linux (если есть).
Если не запускается на другой версии Ubuntu — собери заново (ниже).

ЗАВИСИМОСТИ (один раз в Ubuntu)
-------------------------------
sudo apt update
sudo apt install -y libsdl2-2.0-0 libsdl2-image-2.0-0

Для сборки из исходников ещё:
sudo apt install -y build-essential cmake pkg-config libsdl2-dev libsdl2-image-dev

ЗАПУСК ГОТОВОГО БИНАРНИКА
-------------------------
Распакуй/скопируй всю папку nosmoke_usb_linux на ПК.
В терминале зайди В ЭТУ ПАПКУ (рядом должны лежать Graphics и Audio):

  chmod +x nosmoke_linux run.sh
  ./run.sh

Или вручную:
  ./nosmoke_linux

СБОРКА ЗАНОВО (если бинарник не подошёл)
---------------------------------------
  chmod +x build.sh
  ./build.sh
  ./build/nosmoke

Важно: запускать из каталога, где лежат Graphics и Audio — иначе будет чёрный экран.
