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
  hword xa;
  hword ya;
  hword xb;
  // hword yb;

  xa = ((525) + (3)) % 59;
  ya = (525) * (3) % 39 + 41;
  xb = (1028) % 59 + 181;
  // yb = (1032) % 39 + 81;

  color1 = 0x7FE0;
  color2 = 0x001F;

  for (y = 0; y < 160; y++) {
    for (x = 0; x < 240; x++) {
      draw_point(x, y, color1);
    }
  }

  // hword sum = 1;
  hword a = 1;
  y = ya;
  for (x = xa; x <= xb; x++) {
    a = a * (x - xa);
    a = a + (y - ya);
    if (a < (x - xa)) {
      y = y;
    } else {
      y = y + 1;
      a = a - (y - ya);
    }
    draw_point(x, y, color2);
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
