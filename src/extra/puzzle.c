typedef volatile unsigned short hword;

#define VRAM 0x06000000
#define KEY 0x04000130
#define KEY_A 0x0001
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_LEFT 0x0020
#define KEY_RIGHT 0x0010
#define KEY_START 0x0008
#define WHITE 0x7FFF
#define GRAY 0x5294

void drawL(hword, hword, hword status[], hword, hword);
void drawM1(hword, hword, hword status[], hword, hword);
void drawM2(hword, hword, hword status[], hword, hword);
void drawS(hword, hword, hword status[], hword, hword);
void clear(hword, hword, hword status[], hword, hword);
void memory(hword status[], hword, hword, hword);
void cursor(hword, hword, hword, hword, hword);
hword moveCP(hword status[], hword, hword, hword, hword);
hword moveI(hword status[], hword, hword, hword, hword);
hword moveJ(hword status[], hword, hword, hword, hword);
void update(hword memory2[]);
void repaint(hword memory2[]);
void message();

//プログラム
int main(void) {
  hword *ptr;
  hword key;

  hword x[5][4];
  hword y[5][4];
  hword status[20];
  hword xa = 61;
  hword ya = 6;
  hword size[5][2];
  hword memory2[120 * 150];
  hword cp;
  hword i;
  hword j;

  size[0][0] = 60;
  size[0][1] = 60;
  size[1][0] = 30;
  size[1][1] = 60;
  size[2][0] = 60;
  size[2][1] = 30;
  size[3][0] = 30;
  size[3][1] = 30;
  size[4][0] = 30;
  size[4][1] = 30;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      x[j][i] = xa;
    }
    xa += size[3][0];
  }

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 4; j++) {
      y[i][j] = ya;
    }
    ya += size[3][1];
  }

  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;

  drawL(x[0][1], y[0][1], status, 0, 1);
  drawM1(x[0][0], y[0][0], status, 0, 0);
  drawM1(x[0][3], y[0][3], status, 0, 3);
  drawM1(x[2][0], y[2][0], status, 2, 0);
  drawM1(x[2][3], y[2][3], status, 2, 3);
  drawM2(x[2][1], y[2][1], status, 2, 1);
  drawS(x[3][1], y[3][1], status, 3, 1);
  drawS(x[3][2], y[3][2], status, 3, 2);
  drawS(x[4][0], y[4][0], status, 4, 0);
  drawS(x[4][3], y[4][3], status, 4, 3);

  memory(status, 4, 1, 4);
  memory(status, 4, 2, 4);

  ptr = (hword *)VRAM + 57 + 240 * 2;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 126 - 2 * i; j++) {
      *ptr = 0x0110;
      ptr++;
    }
    for (j = 0; j < 156 - 2 * i; j++) {
      *ptr = 0x0110;
      ptr += 240;
    }
    for (j = 0; j < 126 - 2 * i; j++) {
      if (32 - i < j && j < 93 - i) {
        ptr--;
        continue;
      }
      *ptr = 0x0110;
      ptr--;
    }
    for (j = 0; j < 156 - 2 * i; j++) {
      *ptr = 0x0110;
      ptr -= 240;
    }
    ptr = ptr + 241;
  }

  update(memory2);

  cp = 0;
  i = 0;
  j = 0;
  hword cp0;
  hword i0;
  hword j0;

  while (1) {
    cp0 = cp;
    i0 = i;
    j0 = j;
    cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], WHITE);
    key = *(hword *)KEY;
    if (((key & KEY_UP) != KEY_UP) && i > 0) {
      repaint(memory2);
      cp = moveCP(status, cp0, i0, j0, KEY_UP);
      i = moveI(status, cp0, i0, j0, KEY_UP);
      j = moveJ(status, cp0, i0, j0, KEY_UP);
      cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], WHITE);
    } else if (((key & KEY_DOWN) != KEY_DOWN) && i < 4) {
      repaint(memory2);
      cp = moveCP(status, cp0, i0, j0, KEY_DOWN);
      i = moveI(status, cp0, i0, j0, KEY_DOWN);
      j = moveJ(status, cp0, i0, j0, KEY_DOWN);
      cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], WHITE);
    } else if (((key & KEY_LEFT) != KEY_LEFT) && j > 0) {
      repaint(memory2);
      cp = moveCP(status, cp0, i0, j0, KEY_LEFT);
      i = moveI(status, cp0, i0, j0, KEY_LEFT);
      j = moveJ(status, cp0, i0, j0, KEY_LEFT);
      cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], WHITE);
    } else if (((key & KEY_RIGHT) != KEY_RIGHT) && j < 3) {
      repaint(memory2);
      cp = moveCP(status, cp0, i0, j0, KEY_RIGHT);
      i = moveI(status, cp0, i0, j0, KEY_RIGHT);
      j = moveJ(status, cp0, i0, j0, KEY_RIGHT);
      cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], WHITE);
    }

    if (((key & KEY_A) != KEY_A) && status[cp] != 4) {
      cursor(x[i][j], y[i][j], size[status[cp]][0], size[status[cp]][1], GRAY);
      while (1) {
        key = *(hword *)KEY;
        if ((key & KEY_UP) != KEY_UP) {
          if (i > 0) {
            repaint(memory2);
            if (status[cp] == 0) {
              if (status[cp - 4 * 1] == 4 && status[cp - 4 * 1 + 1] == 4) {
                clear(x[i + 1][j], y[i + 1][j], status, i + 1, j);
                clear(x[i + 1][j + 1], y[i + 1][j + 1], status, i + 1, j + 1);
                cp -= 4 * 1;
                i--;
                drawL(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 1) {
              if (status[cp - 4 * 1] == 4) {
                clear(x[i + 1][j], y[i + 1][j], status, i + 1, j);
                cp -= 4 * 1;
                i--;
                drawM1(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 2) {
              if (status[cp - 4 * 1] == 4 && status[cp - 4 * 1 + 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i][j + 1], y[i][j + 1], status, i, j + 1);
                cp -= 4 * 1;
                i--;
                drawM2(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 3) {
              if (status[cp - 4 * 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp -= 4 * 1;
                i--;
                drawS(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            }
          }
          break;
        } else if ((key & KEY_DOWN) != KEY_DOWN) {
          if (i < 4) {
            repaint(memory2);
            if (status[cp] == 0 && i < 3) {
              if (status[cp + 4 * 2] == 4 && status[cp + 4 * 2 + 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i][j + 1], y[i][j + 1], status, i, j + 1);
                cp += 4 * 1;
                i++;
                drawL(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 1 && i < 3) {
              if (status[cp + 4 * 2] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp += 4 * 1;
                i++;
                drawM1(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 2) {
              if (status[cp + 4 * 1] == 4 && status[cp + 4 * 1 + 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i][j + 1], y[i][j + 1], status, i, j + 1);
                cp += 4 * 1;
                i++;
                drawM2(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 3) {
              if (status[cp + 4 * 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp += 4 * 1;
                i++;
                drawS(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            }
          }
          break;
        } else if ((key & KEY_LEFT) != KEY_LEFT) {
          if (j > 0) {
            repaint(memory2);
            if (status[cp] == 0) {
              if (status[cp - 1] == 4 && status[cp - 1 + 4 * 1] == 4) {
                clear(x[i][j + 1], y[i][j + 1], status, i, j + 1);
                clear(x[i + 1][j + 1], y[i + 1][j + 1], status, i + 1, j + 1);
                cp--;
                j--;
                drawL(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 1) {
              if (status[cp - 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i + 1][j], y[i + 1][j], status, i + 1, j);
                cp--;
                j--;
                drawM1(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 2) {
              if (status[cp - 1] == 4) {
                clear(x[i][j + 1], y[i][j + 1], status, i, j + 1);
                cp--;
                j--;
                drawM2(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 3) {
              if (status[cp - 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp--;
                j--;
                drawS(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            }
          }
          break;
        } else if (((key & KEY_RIGHT) != KEY_RIGHT)) {
          if (j < 3) {
            repaint(memory2);
            if (status[cp] == 0 && j < 2) {
              if (status[cp + 2] == 4 && status[cp + 2 + 4 * 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i + 1][j], y[i + 1][j], status, i + 1, j);
                cp++;
                j++;
                drawL(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 1) {
              if (status[cp + 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                clear(x[i + 1][j], y[i + 1][j], status, i + 1, j);
                cp++;
                j++;
                drawM1(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 2 && j < 2) {
              if (status[cp + 2] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp++;
                j++;
                drawM2(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            } else if (status[cp] == 3) {
              if (status[cp + 1] == 4) {
                clear(x[i][j], y[i][j], status, i, j);
                cp++;
                j++;
                drawS(x[i][j], y[i][j], status, i, j);
                update(memory2);
              }
            }
          }
          break;
        }
      }
    }
    if (status[3 * 4 + 1] == 0) {
      break;
    }
  }

  while (1) {
    message();
  }
  return 0;
}

void drawL(hword x, hword y, hword *status, hword i, hword j) {
  hword *ptr;
  hword color = 0x001F;
  hword width = 58;
  hword height = 58;
  hword k;
  hword l;

  ptr = (hword *)VRAM + (x + 1) + 240 * (y + 1);

  for (k = 0; k < height; k++) {
    for (l = 0; l < width; l++) {
      *(ptr + l) = color;
    }
    ptr += 240;
  }

  memory(status, i, j, 0);
}

void drawM1(hword x, hword y, hword *status, hword i, hword j) {
  hword *ptr;
  hword color = 0x7C00;
  hword width = 28;
  hword height = 58;
  hword k;
  hword l;

  ptr = (hword *)VRAM + (x + 1) + 240 * (y + 1);

  for (k = 0; k < height; k++) {
    for (l = 0; l < width; l++) {
      *(ptr + l) = color;
    }
    ptr += 240;
  }

  memory(status, i, j, 1);
}

void drawM2(hword x, hword y, hword *status, hword i, hword j) {
  hword *ptr;
  hword color = 0x03E0;
  hword width = 58;
  hword height = 28;
  hword k;
  hword l;

  ptr = (hword *)VRAM + (x + 1) + 240 * (y + 1);

  for (k = 0; k < height; k++) {
    for (l = 0; l < width; l++) {
      *(ptr + l) = color;
    }
    ptr += 240;
  }

  memory(status, i, j, 2);
}

void drawS(hword x, hword y, hword *status, hword i, hword j) {
  hword *ptr;
  hword color = 0x03FF;
  hword width = 28;
  hword height = 28;
  hword k;
  hword l;

  ptr = (hword *)VRAM + (x + 1) + 240 * (y + 1);

  for (k = 0; k < height; k++) {
    for (l = 0; l < width; l++) {
      *(ptr + l) = color;
    }
    ptr += 240;
  }

  memory(status, i, j, 3);
}

void clear(hword x, hword y, hword *status, hword i, hword j) {
  hword *ptr;
  hword color;
  hword size;
  hword k;
  hword l;

  ptr = (hword *)VRAM + x + 240 * y;
  color = 0x0000;
  size = 30;

  for (k = 0; k < size; k++) {
    for (l = 0; l < size; l++) {
      *(ptr + l) = color;
    }
    ptr += 240;
  }

  memory(status, i, j, 4);
}

void memory(hword *status, hword i, hword j, hword n) {
  if (0 <= n && n <= 4) {
    status[4 * i + j] = n;
    if (n == 0) {
      status[4 * i + j + 1] = 10;
      status[4 * (i + 1) + j] = 20;
      status[4 * (i + 1) + j + 1] = 30;
    } else if (n == 1) {
      status[4 * (i + 1) + j] = 11;
    } else if (n == 2) {
      status[4 * i + j + 1] = 12;
    }
  }
}

void cursor(hword x, hword y, hword width, hword height, hword color) {
  hword *ptr;
  hword i;
  hword j;

  ptr = (hword *)VRAM + x + 240 * y;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < width - 2 * i; j++) {
      *(ptr + i + 240 * i + j) = color;
    }
    for (j = 0; j < height - 2 * i; j++) {
      *(ptr + i + 240 * i + 240 * j) = color;
    }
    for (j = 0; j < width - 2 * i; j++) {
      *(ptr + i + 240 * (height - 1 - i) + j) = color;
    }
    for (j = 0; j < height - 2 * i; j++) {
      *(ptr + (width - 1) - i + 240 * i + 240 * j) = color;
    }
  }
}

hword moveCP(hword *status, hword cp, hword i, hword j, hword key) {
  hword cp0 = cp;

  if (key == KEY_UP) {
    if (status[cp - 4 * 1] == 20 || status[cp - 4 * 1] == 11) {
      cp0 -= 4 * 2;
    } else if (status[cp - 4 * 1] == 30) {
      cp0 = cp0 - 4 * 2 - 1;
    } else if (status[cp - 4 * 1] == 2 || status[cp - 4 * 1] == 3 ||
               status[cp - 4 * 1] == 4) {
      cp0 -= 4 * 1;
    } else if (status[cp - 4 * 1] == 12) {
      cp0 = cp0 - 4 * 1 - 1;
    }
  } else if (key == KEY_DOWN) {
    if ((status[cp] == 0 || status[cp] == 1) && i < 3) {
      cp0 += 4 * 2;
    } else if (status[cp] == 2 || status[cp] == 3 || status[cp] == 4) {
      cp0 += 4 * 1;
    }
    if (status[cp0] == 10 || status[cp0] == 12) {
      cp0--;
    }
  } else if (key == KEY_LEFT) {
    if (status[cp - 1] == 10) {
      cp0 -= 2;
    } else if (status[cp - 1] == 30) {
      cp0 = cp0 - 4 * 1 - 2;
    } else if (status[cp - 1] == 1 || status[cp - 1] == 3 ||
               status[cp - 1] == 4) {
      cp0--;
    } else if (status[cp - 1] == 11) {
      cp0 = cp0 - 4 * 1 - 1;
    } else if (status[cp - 1] == 12) {
      cp0 -= 2;
    }
  } else if (key == KEY_RIGHT) {
    if ((status[cp] == 0 || status[cp] == 2) && j < 2) {
      cp0 += 2;
    } else if (status[cp] == 1 || status[cp] == 3 || status[cp] == 4) {
      cp0++;
    }
    if (status[cp0] == 20 || status[cp0] == 11) {
      cp0 -= 4 * 1;
    }
  }
  return cp0;
}

hword moveI(hword *status, hword cp, hword i, hword j, hword key) {
  hword i0 = i;

  if (key == KEY_UP) {
    if (status[cp - 4 * 1] == 20 || status[cp - 4 * 1] == 30 ||
        status[cp - 4 * 1] == 11) {
      i0 -= 2;
    } else if (status[cp - 4 * 1] == 2 || status[cp - 4 * 1] == 12 ||
               status[cp - 4 * 1] == 3 || status[cp - 4 * 1] == 4) {
      i0--;
    }
  } else if (key == KEY_DOWN) {
    if ((status[cp] == 0 || status[cp] == 1) && i < 3) {
      i0 += 2;
    } else if (status[cp] == 2 || status[cp] == 3 || status[cp] == 4) {
      i0++;
    }
  } else if (key == KEY_LEFT) {
    if (status[cp - 1] == 10) {
    } else if (status[cp - 1] == 30) {
      i0--;
    } else if (status[cp - 1] == 1 || status[cp - 1] == 3 ||
               status[cp - 1] == 4) {
    } else if (status[cp - 1] == 11) {
      i0--;
    } else if (status[cp - 1] == 12) {
    }
  } else if (key == KEY_RIGHT) {
    if (((status[cp] == 1 || status[cp] == 3 || status[cp] == 4) &&
         (status[cp + 1] == 20 || status[cp + 1] == 11)) ||
        (j < 2 && (status[cp] == 0 || status[cp] == 2) &&
         (status[cp + 2] == 20 || status[cp + 2] == 11))) {
      i0--;
    }
  }
  return i0;
}

hword moveJ(hword *status, hword cp, hword i, hword j, hword key) {
  hword j0 = j;

  if (key == KEY_UP) {
    if (status[cp - 4 * 1] == 20) {
    } else if (status[cp - 4 * 1] == 30) {
      j0--;
    } else if (status[cp - 4 * 1] == 11) {
    } else if (status[cp - 4 * 1] == 2) {
    } else if (status[cp - 4 * 1] == 12) {
      j0--;
    } else if (status[cp - 4 * 1] == 3 || status[cp - 4 * 1] == 4) {
    }
  } else if (key == KEY_DOWN) {
    if (((status[cp] == 2 || status[cp] == 3 || status[cp] == 4) &&
         (status[cp + 4 * 1] == 10 || status[cp + 4 * 1] == 12)) ||
        ((status[cp] == 0 || status[cp] == 1) &&
         (status[cp + 4 * 2] == 10 || status[cp + 4 * 2] == 12))) {
      j0--;
    }
  } else if (key == KEY_LEFT) {
    if (status[cp - 1] == 10) {
      j0 -= 2;
    } else if (status[cp - 1] == 30) {
      j0 -= 2;
    } else if (status[cp - 1] == 1 || status[cp - 1] == 3 ||
               status[cp - 1] == 4) {
      j0--;
    } else if (status[cp - 1] == 11) {
      j0--;
    } else if (status[cp - 1] == 12) {
      j0 -= 2;
    }
  } else if (key == KEY_RIGHT) {
    if ((status[cp] == 0 || status[cp] == 2) && j < 2) {
      j0 += 2;
    } else if (status[cp] == 1 || status[cp] == 3 || status[cp] == 4) {
      j0++;
    }
  }
  return j0;
}

void update(hword *memory2) {
  hword *ptr;
  hword i;
  hword j;

  ptr = (hword *)VRAM + 61 + 240 * 6;
  for (i = 0; i < 150; i++) {
    for (j = 0; j < 120; j++) {
      memory2[j + (120 * i)] = *(ptr + j + (240 * i));
    }
  }
}

void repaint(hword *memory2) {
  hword *ptr;
  hword i;
  hword j;

  ptr = (hword *)VRAM + 61 + 240 * 6;
  for (i = 0; i < 150; i++) {
    for (j = 0; j < 120; j++) {
      *(ptr + j + (240 * i)) = memory2[j + (120 * i)];
    }
  }
}

void message() {
  hword *ptr;
  hword i;
  hword j;

  ptr = (hword *)VRAM + 5 + 240 * 2;
  for (i = 0; i < 12; i++) {
    for (j = 0; j < 48; j++) {
      if ((i == 0 || i == 1) &&
          !(j == 0 || j == 1 || (5 < j && j < 10) || (11 < j && j < 20) ||
            (27 < j && j < 32) || (35 < j && j < 40) || j == 46 || j == 47)) {
        *(ptr + j) = WHITE;
      } else if ((i == 2 || i == 3) &&
                 !((1 < j && j < 6) || j == 8 || j == 9 || (11 < j && j < 20) ||
                   (21 < j && j < 30) || (31 < j && j < 36) || j == 38 ||
                   j == 39 || (41 < j && j < 46))) {
        *(ptr + j) = WHITE;
      } else if ((i == 4 || i == 5) &&
                 !((1 < j && j < 10) || (11 < j && j < 20) ||
                   (25 < j && j < 30) || (31 < j && j < 36) || j == 38 ||
                   j == 39 || (41 < j && j < 46))) {
        *(ptr + j) = WHITE;
      } else if ((i == 6 || i == 7) &&
                 !((1 < j && j < 10) || (11 < j && j < 20) ||
                   (21 < j && j < 30) || j == 38 || j == 39 || j == 46 ||
                   j == 47)) {
        *(ptr + j) = WHITE;
      } else if ((i == 8 || i == 9) &&
                 !((1 < j && j < 6) || j == 8 || j == 9 || (11 < j && j < 20) ||
                   (21 < j && j < 30) || (31 < j && j < 36) || j == 38 ||
                   j == 39 || (41 < j && j < 46))) {
        *(ptr + j) = WHITE;
      } else if ((i == 10 || i == 11) &&
                 !(j == 0 || j == 1 || (5 < j && j < 10) || j == 18 ||
                   j == 19 || j == 28 || j == 29 || (31 < j && j < 36) ||
                   j == 38 || j == 39 || (41 < j && j < 46))) {
        *(ptr + j) = WHITE;
      }
    }
    ptr += 240;
  }
}
