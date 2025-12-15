MEMORY
{
    FLASH (rx)              : ORIGIN = 0x08000000, LENGTH = 2048K
    RAM_SHARED (xrw)        : ORIGIN = 0, LENGTH = 0
    RAM (xrw)               : ORIGIN = 0x20000000, LENGTH = 128K    /* DTCM - Fast, zero wait-state */
    AXI_SRAM (xrw)          : ORIGIN = 0x24000000, LENGTH = 512K
    SRAM1 (xrw)             : ORIGIN = 0x30000000, LENGTH = 128K
    SRAM2 (xrw)             : ORIGIN = 0x30020000, LENGTH = 128K
    SRAM3 (xrw)             : ORIGIN = 0x30040000, LENGTH = 32K
    SRAM4 (xrw)             : ORIGIN = 0x38000000, LENGTH = 64K
}
