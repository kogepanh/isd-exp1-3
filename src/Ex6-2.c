typedef volatile unsigned short hword;
#define VRAM 0x06000000

void draw_point(hword, hword, hword);

int main(void) {
  hword *ptr;
  hword color1;
  hword color2;
  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;

  hword y;
  hword x;
  hword xe = (525) * (3) % 19 + 101;
  hword ye = (1028) % 19 + 61;
  hword r = (1032) % 9 + 29;

  color1 = 0x7FE0;
  color2 = 0x001F;

  for (y = 0; y < 160; y++) {
    for (x = 0; x < 240; x++) {
      if (r * r >= (xe - x) * (xe - x) + (ye - y) * (ye - y)) {
        draw_point(x, y, color2);
      } else {
        draw_point(x, y, color1);
      }
    }
  }

  while (1)
    ;
  return (0);
}

void draw_point(hword x, hword y, hword color) {
  hword *ptr = (hword *)VRAM;
  ptr += (x + y * 240);
  *ptr = color;
}
