#!/bin/bash
SCRIPTPATH="$(cd "$(dirname "$0")" && pwd)"
set -e
wget -O bzImage "https://raw.githubusercontent.com/yuawn/Linux-Kernel-Exploitation/master/bzImage"

rm -rf initramfs
mkdir -p initramfs/{bin,sbin,etc,proc,sys,usr/bin,usr/sbin}

gcc $SCRIPTPATH/main.c $SCRIPTPATH/../utils.c -o initramfs/init -O2 -pthread -lm -static

chmod +x initramfs/init

cd initramfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.img
cd ..

qemu-system-x86_64 \
    -kernel bzImage \
    -cpu host,kvm=on,topoext=on -enable-kvm -cpu host,kvm=on,topoext=on \
    -initrd initramfs.img \
    -append "console=ttyS0 init=/init" \
    -nographic 