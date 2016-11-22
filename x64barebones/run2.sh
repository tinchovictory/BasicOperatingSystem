#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -no-kvm-irqchip -device rtl8139,netdev=mynet0,mac=DE:AD:C0:FF:EE:11 -netdev socket,id=mynet0,connect=:1234
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -no-kvm-irqchip -device rtl8139,mac=DE:AD:C0:FF:EE:11 -netdev socket,id=mynet0,mcast=DE.AD.C0.FF.EE.11:1234
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -no-kvm-irqchip -net nic,model=rtl8139,vlan=1,macaddr=52:54:00:12:34:56 -net socket,mcast=230.0.0.1:1234