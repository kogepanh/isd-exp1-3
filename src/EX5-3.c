typedef volatile unsigned short hword;
#define VRAM 0x06000000

void draw_point(hword, hword, hword);

int main(void) {
  hword *ptr;
  hword color;
  hword x;
  hword y;

  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;
  color = 0x7FE0;

  for (y = 0; y < 160; y++) {
    for (x = 0; x < 240; x++) {
      draw_point(x, y, color);
    }
  }

  x = ((525) + (3)) % 59 + 60;
  y = (525) * (3) % 39 + 81;
  draw_point(x, y, 0x001F);

  while (1)
    ;
  return (0);
}

void draw_point(hword x, hword y, hword color) {
  hword *ptr = (hword *)VRAM;
  ptr += (x + y * 240);
  *ptr = color;
}
