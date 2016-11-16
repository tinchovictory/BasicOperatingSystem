#include <pci.h>
#include <sysIO.h>

#include <naiveConsole.h>
#define RTL_VENDOR_ID 0x10EC
#define RTL_DEVICE_ID 0x8139

#define PCI_CONFIG_ADDRESS  0x0CF8
#define PCI_CONFIG_DATA 0x0CFC


/*Activo DMA*/
void activeDMA(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
 
    /* create configuration address */
//    address    10000000000000000000000000000000b
/*               /\     /\      /\   /\ /\    /\
               E    Res    Bus    Dev  F  Reg   0
*/


    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
 
    /* write out the address */
    sysOutLong (PCI_CONFIG_ADDRESS, address);

    /*write the command register*/
    sysOutLong (PCI_CONFIG_DATA, 0x107);
}

void activeRTLdma(){
    activeDMA(0,4,0,4);
}


/************************************/
// BAR0 - RTL = C001
// BUS - RTL = 0
// SLOT - RTL = 4
// FUNC - RTL = 0
// CMDreg - RTL = 4
/************************************/

uint16_t pciConfigReadWord (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;
 
    /* create configuration address */
//    address    10000000000000000000000000000000b
/*               /\     /\      /\   /\ /\    /\
               E    Res    Bus    Dev  F  Reg   0
*/

    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
 
    /* write out the address */
    sysOutLong (PCI_CONFIG_ADDRESS, address);
    /* read in the data */
    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
    tmp = (uint16_t)((sysInLong (PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
 }


uint16_t pciCheckOffset(uint8_t bus, uint8_t slot, int vendorID, int deviceID, int offset){
    if(pciConfigReadWord(bus,slot,0,0) == vendorID && pciConfigReadWord(bus, slot, 0, 2) == deviceID){
        //ncPrintHex(pciConfigReadWord(bus, slot, 0, offset));
        return pciConfigReadWord(bus, slot, 0, offset);
    }
    return 0;
 }

 void searchRTL(){
    for(int bus = 0; bus<256; bus++){
        for(int slot = 0; slot < 32; slot ++){
            uint16_t offset = pciCheckOffset(bus, slot, RTL_VENDOR_ID, RTL_DEVICE_ID, 18);
            if(offset != 0){
                ncPrintHex(offset);
            }
            offset = pciCheckOffset(bus, slot, RTL_VENDOR_ID, RTL_DEVICE_ID, 16);
            if(offset != 0){
                ncPrintHex(bus);
                ncNewline();
                ncPrintHex(slot);
                ncNewline();
                ncPrintHex(offset);
            }


            offset = pciCheckOffset(bus, slot, RTL_VENDOR_ID, RTL_DEVICE_ID, 4);
            if(offset != 0){
                ncPrintHex(offset);
            }


        }
    }
    ncNewline();
    ncNewline();
    ncPrintHex(pciCheckOffset(0, 4, RTL_VENDOR_ID, RTL_DEVICE_ID, 4));

    activeDMA(0,4,0,4);
    ncNewline();
    ncNewline();
    ncPrintHex(pciCheckOffset(0, 4, RTL_VENDOR_ID, RTL_DEVICE_ID, 4));
 }