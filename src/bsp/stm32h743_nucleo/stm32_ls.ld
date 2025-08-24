ENTRY(Reset_Handler)

MEMORY
{
  ITCMRAM (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K   /*0x0001 0000*/
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 2048K /*0x0820 0000*/
  DTCMRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K  /*0x2002 0000*/
  SRAM (xrw)     : ORIGIN = 0x24000000, LENGTH = 512K  /*0x2408 0000*/
  /*SRAM1 (xrw)  : ORIGIN = 0x30000000, LENGTH = 128K  /*0x3002 0000*/
  /*SRAM2 (xrw)  : ORIGIN = 0x30020000, LENGTH = 128K  /*0x3004 0000*/
  /*SRAM3 (xrw)  : ORIGIN = 0x30040000, LENGTH = 32K   /*0x3004 8000*/
  SRAM123 (xrw)  : ORIGIN = 0x30000000, LENGTH = 288K  /*0x3004 8000*/
  SRAM4 (xrw)    : ORIGIN = 0x38000000, LENGTH = 64K   /*0x3801 0000*/
}

SECTIONS
{
	.text : 
	{
		*(.isr-vector)
		*(.text)
		*(.text.*)
		*(.init)
		*(.fini)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		_etext = .;
	}> FLASH
	_la_data = LOADADDR(.data);
	.data :
	{
		_sdata = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = .;
	}> SRAM AT> FLASH

	.bss :
	{
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;
		. = ALIGN(4);
		end = .;
		__end__ = .;
	}> SRAM
}

