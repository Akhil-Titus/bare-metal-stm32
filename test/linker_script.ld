MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    /* Interrupt Vector Table */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    /* Code and Read-Only Data */
    .text :
    {
        . = ALIGN(4);
        *(.text)       /* Code */
        *(.rodata)     /* Read-only data */
        
        . = ALIGN(4);
        _etext = .;    /* End of text section */
    } >FLASH

    /* Initialized Data */
    _sidata = LOADADDR(.data);
    .data : AT (_sidata)
    {
        . = ALIGN(4);
        _sdata = .;   /* Start of .data in SRAM */
        
        *(.data)      /* Initialized data */
        
        . = ALIGN(4);
        _edata = .;   /* End of .data */
    } >SRAM

    /* Uninitialized Data */
    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;  /* Start of .bss (alias for _sbss) */
        _sbss = .;

        *(.bss)        /* Uninitialized data */

        . = ALIGN(4);
        __bss_end__ = .;    /* End of .bss (alias for _ebss) */
        _ebss = .;
    } >SRAM
}

/* Provide aliases for compatibility */
PROVIDE(__data_start__ = _sdata);
PROVIDE(__data_end__ = _edata);
