#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -device rtl8139 -netdev socket,id=mynet0,listen=:1234