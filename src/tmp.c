#include "othello.h"

int main(void) {
  // おまじない
  hword *ptr = (hword *)INIT;
  *ptr = 0x0F03;

  // オセロゲーム
  play_othello();

  while (1)
    ;

  return 0;
}

void play_othello() {
  // 初期盤面を描画
  init_board();

  // 操作
  while (1) {
    if ((*key & KEY_RIGHT) == KEY_NULL) {
      move_player(1, 0);
      while ((*key & KEY_RIGHT) != KEY_RIGHT)
        ;
    } else if ((*key & KEY_LEFT) == KEY_NULL) {
      move_player(-1, 0);
      while ((*key & KEY_LEFT) != KEY_LEFT)
        ;
    } else if ((*key & KEY_UP) == KEY_NULL) {
      move_player(0, -1);
      while ((*key & KEY_UP) != KEY_UP)
        ;
    } else if ((*key & KEY_DOWN) == KEY_NULL) {
      move_player(0, 1);
      while ((*key & KEY_DOWN) != KEY_DOWN)
        ;
    } else if ((*key & KEY_A) == KEY_NULL) {
      while ((*key & KEY_A) != KEY_A)
        ;
    }
  }
}

// 割り算（分母が変数の場合でも使用可）
hword div(hword a, hword b) {
  hword ans;
  for (ans = 0; a >= b; ans++) {
    a -= b;
  }
  return ans;
}

// コマを置く
void put_piece(hword x, hword y, short turn) {
  hword color;
  if (turn == 1) {
    color = BLACK;
  } else {
    color = WHITE;
  }

  board[y][x] = turn;
  draw_piece(x, y, color);
}

// プレイヤーの場所を移動
void move_player(short x, short y) {
  if (0 <= player_A.x + x && player_A.x + x <= 7 && 0 <= player_A.y + y &&
      player_A.y + y <= 7) {
    draw_player(player_A.x, player_A.y, BLACK);
    player_A.x += x;
    player_A.y += y;
    draw_player(player_A.x, player_A.y, RED);
  }
}

// 初期盤面の描画
void init_board() {
  // 画面塗りつぶし
  draw_window(GRAY);

  // 盤面の描画
  hword x, y;
  for (y = 0; y < BOX_COUNT; y++) {
    for (x = 0; x < BOX_COUNT; x++) {
      draw_box_bg(x, y, GREEN);
      draw_player(x, y, BLACK);
    }
  }

  // コマの初期設定
  init_piece();

  // プレイヤー位置の初期描画
  init_player();
  draw_player(player_A.x, player_A.y, RED);
}

// 4つの初期コマを設定
void init_piece() {
  put_piece(3, 3, 1);
  put_piece(4, 4, 1);
  put_piece(3, 4, -1);
  put_piece(4, 3, -1);
}

// プレイヤー情報の初期設定
void init_player() {
  player_A.turn = YOUR_TURN;
  player_B.turn = YOUR_TURN * -1;
}

// マスの背景描画
void draw_box_bg(hword xn, hword yn, hword color) {
  hword x1 =
      div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * xn);
  hword y1 =
      div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * yn);
  hword x2 = x1 + BOX_SIZE;
  hword y2 = y1 + BOX_SIZE;
  draw_square(x1, x2, y1, y2, color);
}

// マスの枠線描画
void draw_player(hword xn, hword yn, hword color) {
  hword x1 =
      div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * xn);
  hword y1 =
      div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * yn);

  hword i;
  for (i = 0; i <= BOX_SIZE; i++) {
    draw_point(x1 + i, y1, color);
    draw_point(x1 + i, y1 + BOX_SIZE, color);
    draw_point(x1, y1 + i, color);
    draw_point(x1 + BOX_SIZE, y1 + i, color);
  }
}

// マスにコマを描画
void draw_piece(hword xn, hword yn, hword color) {
  hword xc = div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) +
             (BOX_SIZE * xn) + div(BOX_SIZE, 2);
  hword yc = div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) +
             (BOX_SIZE * yn) + div(BOX_SIZE, 2);
  draw_circle(xc, yc, div(BOX_SIZE, 2), color);
}

// 円の描画
void draw_circle(hword xc, hword yc, hword r, hword color) {
  hword x1 = xc - r;
  hword x2 = xc + r;
  hword y1 = yc - r;
  hword y2 = yc + r;

  hword x;
  hword y;
  for (y = y1; y < y2; y++) {
    for (x = x1; x < x2; x++) {
      if (r * r > (xc - x) * (xc - x) + (yc - y) * (yc - y)) {
        draw_point(x, y, color);
      }
    }
  }
}

// 四角形の描画
void draw_square(hword x1, hword x2, hword y1, hword y2, hword color) {
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

// 点を描画
void draw_point(hword x, hword y, hword color) {
  hword *ptr = (hword *)VRAM;
  ptr += (x + y * WINDOW_X);
  *ptr = color;
}

// 強制的に遅延を作成
void generate_delay() {
  hword a;
  for (a = 0; a < DELAY_PARAM; a++)
    ;
}
