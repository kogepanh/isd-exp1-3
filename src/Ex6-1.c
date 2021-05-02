typedef volatile unsigned short hword;
#define VRAM 0x06000000

void draw_point(hword, hword, hword);

int main(void) {
  hword *ptr;
  hword color;
  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;

  hword y;
  hword x;
  hword xa;
  hword ya;
  hword xb;
  hword yb;

  xa = ((525) + (3)) % 59;
  ya = (525) * (3) % 39 + 41;
  xb = (1028) % 59 + 181;
  yb = (1032) % 39 + 81;

  color = 0x7FE0;
  for (y = 0; y < 160; y++) {
    for (x = 0; x < 240; x++) {
      draw_point(x, y, color);
    }
  }

  color = 0x001F;
  for (y = ya; y <= yb; y++) {
    for (x = xa; x <= xb; x++) {
      draw_point(x, y, color);
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
