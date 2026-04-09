#!/bin/bash

set -e

make
sudo rmmod hello 2>/dev/null/ || true
sudo insmod hello.ko
dmesg | tail -n 20
