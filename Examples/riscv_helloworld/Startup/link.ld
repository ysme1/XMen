OUTPUT_ARCH( "riscv" )

ENTRY(_start)

ROM_BASE = 0x0;
ROM_SIZE = 0x0;

RAM_BASE = 0x0;
RAM_SIZE = 0x0;

MEMORY
{
  rom   (rxa!w)  : ORIGIN = ROM_BASE, LENGTH = ROM_SIZE
  ram   (wxa!r)  : ORIGIN = RAM_BASE, LENGTH = RAM_SIZE
}

SECTIONS
{
	.text : {
		PROVIDE(_text_start = .);
		*(.text .text.*)
		PROVIDE(_text_end = .);
	} >rom

  .data : {
		PROVIDE(_data_start = .);
		*(.data .data.*)
		PROVIDE(_data_end = .);
	} >ram

  .bss :{
		PROVIDE(_bss_start = .);
		*(.bss .bss.*)
		PROVIDE(_bss_end = .);
	} >ram
}

