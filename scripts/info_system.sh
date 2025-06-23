#!/bin/bash

echo "=== ОС и Ядро ==="
echo "Имя хоста: $(hostname)"
echo "Операционная система: $(lsb_release -ds 2>/dev/null || cat /etc/*release 2>/dev/null | head -n1 || uname -om)"
echo "Версия ядра: $(uname -r)"
echo "Архитектура: $(uname -m)"

echo -e "\n=== Процессор ==="
echo "Модель процессора: $(grep 'model name' /proc/cpuinfo | head -n1 | cut -d: -f2 | sed 's/^[ \t]*//')"
echo "Количество ядер: $(grep -c '^processor' /proc/cpuinfo)"
echo "Количество потоков: $(nproc)"

echo -e "\n=== Память ==="
echo "Объем памяти: $(free -h | awk '/^Mem:/{print $2}')"

echo -e "\n=== Сводка по железу (lshw коротко) ==="
if command -v lshw &> /dev/null; then
    sudo lshw -short 2>/dev/null | head -n10
else
    echo "lshw не установлен. Установите его командой: sudo apt install lshw"
fi
