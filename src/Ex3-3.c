typedef volatile unsigned short hword;
#define VRAM 0x06000000

int main(void) {
  hword *ptr;
  hword color;

  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;

  color = 0x07FFF;
  ptr = (hword *)VRAM;

  *ptr = color;

  ptr = (hword *)0x06000004;
  *ptr = color;

  ptr = (hword *)0x06000008;
  *ptr = color;

  ptr = (hword *)0x0600000C;
  *ptr = color;

  while (1)
    ;
  return (0);
}
