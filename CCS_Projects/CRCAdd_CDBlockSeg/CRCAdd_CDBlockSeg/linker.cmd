-x
-stack 0x10000
-heap 0x8000

MEMORY
{

  VECTORS: origin = 0x00800000 length = 0x00000400
  /*Local addresses*/
  LL2MEM: origin = 0x00800400 length = 0x0007FC00

  /* M3 RAM */
  MSMCSRAM: origin = 0x0C000000 length = 0x00400000

  /*DDR3 */
  DDR3: origin = 0x80000000 length = 0x80000000
}
 
SECTIONS
{
  .csl_vect: > VECTORS

  /* Boot Memory Sections */
  .boot: > LL2MEM

  /* Text Memory Sections */
  .text: > LL2MEM

  /* Data Memory Sections */
  .data: > DDR3
  
  .fasttext:  >       LL2MEM
  .cinit:     >       LL2MEM
  .stack:     >       LL2MEM
  .bss:       >       LL2MEM
  .const:     >       LL2MEM
  .far:       >       LL2MEM
  .switch:    >       LL2MEM
  .sysmem:    >       LL2MEM
  .cio:       >       LL2MEM
  .heap       >       LL2MEM
  
  .fardata    > LL2MEM
  .neardata   > LL2MEM
  .rodata     > LL2MEM

  myDDRdata   > DDR3


}
