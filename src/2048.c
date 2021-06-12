/**
 * 2048 ゲーム
 *
 * <操作方法>
 *  ゲーム開始：           Aボタン
 *  上下左右のスワイプ：    上下左右の矢印キー
 *  ゲームをやり直したい時： SELECTボタン
 */

// 関数
#include "2048.h"

// メイン関数
int main(void) {
  // おまじない
  hword *ptr = (hword *)INIT;
  *ptr = 0x0F03;

  // 2048をプレイ
  while (1) {
    play_2048();
  }

  while (1)
    ;

  return 0;
}

// 割り算
hword div(hword a, hword b) {
  hword ans;
  for (ans = 0; a >= b; ans++) {
    a -= b;
  }
  return ans;
}

// 割り算の余り
hword mod(hword a, hword b) {
  while (a >= b) {
    a -= b;
  }
  return a;
}

// 「2048」をプレイ
void play_2048() {
  // 画面塗りつぶし
  draw_window(GRAY);

  // 初期盤面を描画
  draw_board();

  // 初期配置を決定（Aボタンの入力待ち）
  init_board();

  // キーの入力判定
  while (1) {
    if ((*key & KEY_UP) == KEY_NULL) {
      swipe(0);
      while ((*key & KEY_UP) != KEY_UP)
        ;
    } else if ((*key & KEY_LEFT) == KEY_NULL) {
      swipe(1);
      while ((*key & KEY_LEFT) != KEY_LEFT)
        ;
    } else if ((*key & KEY_DOWN) == KEY_NULL) {
      swipe(2);
      while ((*key & KEY_DOWN) != KEY_DOWN)
        ;
    } else if ((*key & KEY_RIGHT) == KEY_NULL) {
      swipe(3);
      while ((*key & KEY_RIGHT) != KEY_RIGHT)
        ;
    } else if ((*key & KEY_SELECT) == KEY_NULL) {
      break;
    }

    rand_i++;
    if (rand_i == 159) {
      rand_i = 0;
    }
  }
}

// 点を描画
void draw_point(hword x, hword y, hword color) {
  hword *ptr = (hword *)VRAM;
  ptr += (x + y * WINDOW_X);
  *ptr = color;
}

// 横線の描画
void draw_line_x(hword x, hword y, hword length, hword color) {
  hword i;
  for (i = 0; i < length; i++) {
    draw_point(x + i, y, color);
  }
}

// 縦線の描画
void draw_line_y(hword x, hword y, hword length, hword color) {
  hword i;
  for (i = 0; i < length; i++) {
    draw_point(x, y + i, color);
  }
}

// 画面の塗りつぶし
void draw_window(hword color) {
  hword x;
  hword y;
  for (y = 0; y < WINDOW_Y; y++) {
    for (x = 0; x < WINDOW_X; x++) {
      draw_point(x, y, color);
    }
  }
}

// 四角形の描画
void draw_square(hword x1, hword y1, hword x2, hword y2, hword color) {
  if (x2 < x1) {
    hword tmp = x2;
    x2 = x1;
    x1 = tmp;
  }

  if (y2 < y1) {
    hword tmp = y2;
    y2 = y1;
    y1 = tmp;
  }

  hword x;
  hword y;
  for (y = y1; y < y2; y++) {
    for (x = x1; x < x2; x++) {
      draw_point(x, y, color);
    }
  }
}

// マスの背景描画
void draw_box_bg(hword xn, hword yn, hword color) {
  hword x1 = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + 1;
  hword y1 = 80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + 1;
  hword x2 = x1 + BOX_SIZE - 2;
  hword y2 = y1 + BOX_SIZE - 2;
  draw_square(x1, y1, x2, y2, color);
}

// マスの枠線描画
void draw_box_line(hword xn, hword yn, hword color) {
  hword x1 = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn);
  hword y1 = 80 - (BOX_SIZE * 2) + (BOX_SIZE * yn);

  hword i;
  for (i = 0; i <= BOX_SIZE; i++) {
    draw_point(x1 + i, y1, color);
    draw_point(x1 + i, y1 + BOX_SIZE, color);
    draw_point(x1, y1 + i, color);
    draw_point(x1 + BOX_SIZE, y1 + i, color);
  }
}

// 初期盤面の描画
void draw_board() {
  hword x;
  hword y;
  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      draw_box_bg(x, y, WHITE);
      draw_box_line(x, y, BLUE);
    }
  }
}

// 初期数字の配置
void init_board() {
  hword x, y;
  for (y = 0; y < 4; y++) {
    for (x = 0; x < 4; x++) {
      board[y][x] = 0;
      board_flag[y][x] = 0;
      board_red_flag[y][x] = 0;
    }
  }

  hword i = 0;
  while (1) {
    if ((*key & KEY_A) == KEY_NULL) {
      hword a = div(i, 16);
      hword b = mod(i, 16);
      if (a == b) {
        if (b != 15) {
          b++;
        } else {
          b = 0;
        }
      }

      board[mod(a, 4)][div(a, 4)] = 2;
      board[mod(b, 4)][div(b, 4)] = 2;
      draw_box_2(div(a, 4), mod(a, 4), BLACK);
      draw_box_2(div(b, 4), mod(b, 4), BLACK);

      return;
    }

    i++;
    if (i == 256) {
      i = 0;
    }
  }
}

void draw_number(hword j, hword i, hword number, hword color) {
  switch (number) {
    case 2: {
      draw_box_2(j, i, color);
      break;
    }
    case 4: {
      draw_box_4(j, i, color);
      break;
    }
    case 8: {
      draw_box_8(j, i, color);
      break;
    }
    case 16: {
      draw_box_16(j, i, color);
      break;
    }
    case 32: {
      draw_box_32(j, i, color);
      break;
    }
    case 64: {
      draw_box_64(j, i, color);
      break;
    }
    case 128: {
      draw_box_128(j, i, color);
      break;
    }
    case 256: {
      draw_box_256(j, i, color);
      break;
    }
    case 512: {
      draw_box_512(j, i, color);
      break;
    }
    case 1024: {
      draw_box_1024(j, i, color);
      break;
    }
    case 2048: {
      draw_box_2048(j, i, color);
      break;
    }
    case 4096: {
      draw_box_4096(j, i, color);
      break;
    }
    default: {
      break;
    }
  }
}

void draw_all_number() {
  hword i, j;
  hword turn_flag = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (board_flag[i][j] == 1) {
        draw_box_bg(j, i, WHITE);
        draw_number(j, i, board[i][j], BLACK);
        turn_flag = 1;
      }
    }
  }

  if (turn_flag == 1) {
    clean_board_red();
    generate_number();
  }

  clean_board_flag();
}

void swipe(hword direction) {
  hword i;
  for (i = 0; i < 4; i++) {
    merge_number(direction, i);
    move_number(direction, i);
  }
  draw_all_number();
}

void merge_number(hword direction, hword n) {
  hword i, j;
  switch (direction) {
    case 0: {
      for (i = 0; i < 3; i++) {
        if (board[i][n] != 0) {
          for (j = i + 1; j < 4; j++) {
            if (board[i][n] != board[j][n] && board[j][n] != 0) {
              break;
            }
            if (board[i][n] == board[j][n]) {
              board[i][n] *= 2;
              board_flag[i][n] = 1;
              board[j][n] = 0;
              board_flag[j][n] = 1;
              break;
            }
          }
        }
      }
      break;
    }
    case 1: {
      for (i = 0; i < 3; i++) {
        if (board[n][i] != 0) {
          for (j = i + 1; j < 4; j++) {
            if (board[n][i] != board[n][j] && board[n][j] != 0) {
              break;
            }
            if (board[n][i] == board[n][j]) {
              board[n][i] *= 2;
              board_flag[n][i] = 1;
              board[n][j] = 0;
              board_flag[n][j] = 1;
              break;
            }
          }
        }
      }
      break;
    }
    // case 2: {
    //   for (i = 3; i >= 1; i--) {
    //     if (board[i][n] != 0) {
    //       for (j = i - 1; j >= 0; j--) {
    //         if (board[i][n] != board[j][n] && board[j][n] != 0) {
    //           break;
    //         }
    //         if (board[i][n] == board[j][n]) {
    //           board[i][n] *= 2;
    //           board_flag[i][n] = 1;
    //           board[j][n] = 0;
    //           board_flag[j][n] = 1;
    //           break;
    //         }
    //       }
    //     }
    //   }
    //   break;
    // }
    // case 3: {
    //   for (i = 3; i >= 1; i--) {
    //     if (board[n][i] != 0) {
    //       for (j = i - 1; j >= 0; j--) {
    //         if (board[n][i] != board[n][j] && board[n][j] != 0) {
    //           break;
    //         }
    //         if (board[n][i] == board[n][j]) {
    //           board[n][i] *= 2;
    //           board_flag[n][i] = 1;
    //           board[n][j] = 0;
    //           board_flag[n][j] = 1;
    //           break;
    //         }
    //       }
    //     }
    //   }
    //   break;
    // }
    default:
      break;
  }
}

void move_number(hword direction, hword n) {
  hword i, j;
  switch (direction) {
    case 0: {
      for (i = 0; i < 3; i++) {
        if (board[i][n] == 0) {
          for (j = i + 1; j < 4; j++) {
            if (board[j][n] != 0) {
              board[i][n] = board[j][n];
              board_flag[i][n] = 1;
              board[j][n] = 0;
              board_flag[j][n] = 1;
              break;
            }
          }
        }
      }
      break;
    }
    case 1: {
      for (i = 0; i < 3; i++) {
        if (board[n][i] == 0) {
          for (j = i + 1; j < 4; j++) {
            if (board[n][j] != 0) {
              board[n][i] = board[n][j];
              board_flag[n][i] = 1;
              board[n][j] = 0;
              board_flag[n][j] = 1;
              break;
            }
          }
        }
      }
      break;
    }
    // case 2: {
    //   for (i = 3; i >= 1; i--) {
    //     if (board[i][n] == 0) {
    //       for (j = i - 1; j >= 0; j--) {
    //         if (board[j][n] != 0) {
    //           board[i][n] = board[j][n];
    //           board_flag[i][n] = 1;
    //           board[j][n] = 0;
    //           board_flag[j][n] = 1;
    //           break;
    //         }
    //       }
    //     }
    //   }
    //   break;
    // }
    // case 3: {
    //   for (i = 3; i >= 1; i--) {
    //     if (board[n][i] == 0) {
    //       for (j = i - 1; j >= 0; j--) {
    //         if (board[n][j] != 0) {
    //           board[n][i] = board[n][j];
    //           board_flag[n][i] = 1;
    //           board[n][j] = 0;
    //           board_flag[n][j] = 1;
    //           break;
    //         }
    //       }
    //     }
    //   }
    //   break;
    // }
    default: {
      break;
    }
  }
}

void clean_board_flag() {
  hword i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      board_flag[i][j] = 0;
    }
  }
}

void clean_board_red() {
  hword i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (board_red_flag[i][j] == 1) {
        draw_number(j, i, board[i][j], BLACK);
        board_red_flag[i][j] = 0;
        return;
      }
    }
  }
}

void generate_number() {
  hword b = mod(rand_i, 16);
  hword a;
  for (a = 0; a < 16; a++) {
    hword c = mod((a + b), 16);
    if (board[mod(c, 4)][div(c, 4)] == 0) {
      if (rand_i > 100) {
        board[mod(c, 4)][div(c, 4)] = 4;
        draw_box_4(div(c, 4), mod(c, 4), RED);
      } else {
        board[mod(c, 4)][div(c, 4)] = 2;
        draw_box_2(div(c, 4), mod(c, 4), RED);
      }
      board_red_flag[mod(c, 4)][div(c, 4)] = 1;
      break;
    }
  }
}

// ####################################################

void draw_number_0(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE * 2 - 1, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_1(hword x, hword y, hword color) {
  draw_line_y(x + div(NUMBER_SQ_SIZE, 2), y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_2(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE, color);
}

void draw_number_3(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_4(hword x, hword y, hword color) {
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_5(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE,
              color);
}

void draw_number_6(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE * 2 - 1, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE,
              color);
}

void draw_number_7(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_8(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE * 2 - 1, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

void draw_number_9(hword x, hword y, hword color) {
  draw_line_x(x, y, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + NUMBER_SQ_SIZE - 1, NUMBER_SQ_SIZE, color);
  draw_line_x(x, y + (NUMBER_SQ_SIZE - 1) * 2, NUMBER_SQ_SIZE, color);
  draw_line_y(x, y, NUMBER_SQ_SIZE, color);
  draw_line_y(x + NUMBER_SQ_SIZE - 1, y, NUMBER_SQ_SIZE * 2 - 1, color);
}

// ####################################################

void draw_box_2(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_2(x, y, color);
}

void draw_box_4(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_4(x, y, color);
}

void draw_box_8(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_8(x, y, color);
}

void draw_box_16(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 1);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_1(x, y, color);
  draw_number_6(x + (NUMBER_SQ_SIZE + 2), y, color);
}

void draw_box_32(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 1);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_3(x, y, color);
  draw_number_2(x + (NUMBER_SQ_SIZE + 2), y, color);
}

void draw_box_64(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 1);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_6(x, y, color);
  draw_number_4(x + (NUMBER_SQ_SIZE + 2), y, color);
}

void draw_box_128(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 2) - div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_1(x, y, color);
  draw_number_2(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_8(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
}

void draw_box_256(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 2) - div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_2(x, y, color);
  draw_number_5(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_6(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
}

void draw_box_512(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + div(BOX_SIZE, 2) -
            (NUMBER_SQ_SIZE + 2) - div(NUMBER_SQ_SIZE, 2);
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_5(x, y, color);
  draw_number_1(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_2(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
}

void draw_box_1024(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + 3;
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_1(x, y, color);
  draw_number_0(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_2(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
  draw_number_4(x + (NUMBER_SQ_SIZE + 2) * 3, y, color);
}

void draw_box_2048(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + 3;
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_2(x, y, color);
  draw_number_0(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_4(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
  draw_number_8(x + (NUMBER_SQ_SIZE + 2) * 3, y, color);
}

void draw_box_4096(hword xn, hword yn, hword color) {
  hword x = 120 - (BOX_SIZE * 2) + (BOX_SIZE * xn) + 3;
  hword y =
      80 - (BOX_SIZE * 2) + (BOX_SIZE * yn) + div(BOX_SIZE, 2) - NUMBER_SQ_SIZE;
  draw_number_4(x, y, color);
  draw_number_0(x + (NUMBER_SQ_SIZE + 2), y, color);
  draw_number_9(x + (NUMBER_SQ_SIZE + 2) * 2, y, color);
  draw_number_6(x + (NUMBER_SQ_SIZE + 2) * 3, y, color);
}
