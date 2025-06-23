#!/bin/bash

ETH0="$(ip link | awk -F: '$0 !~ "lo|vir|wl|^[^0-9]"{print $2;getline}')"
ip link add br0 type bridge
ip link set br0 up
ip link set $(ETH0) master br0
ip tuntap add tap0 mode tap user `whoami`
ip link set tap0 up
ip link set tap0 master br0
dhclient -v br0

ip link set $(ETH0) nomaster
ip link set tap0 nomaster
ip link set tap0 down
ip link delete br0 type bridge
ip link delete tap0.
dhclient -v $(ETH0)