#include "othello.h"

/**
 * 対人オセロゲーム
 * 
 * <操作方法>
 * 矢印キー：移動
 * Aボタン（PCの場合はデフォルトでX）：コマをおく
 * SELECTボタン（PCの場合はデフォルトでBackspace）：強制的にパス（動作検証等で使用できます）
 * 
 * <その他>
 * コマが置けない場合は自動的にスキップされます
 * 勝負がついた場合、勝ったプレイヤーの色に染まります（引き分けの場合はグレーになります）
 */

// メイン関数
int main(void)
{
  // おまじない
  hword *ptr = (hword *)INIT;
  *ptr = 0x0F03;

  play_othello();

  while(1)
  return 0;
}

// 割り算
hword div(hword a, hword b){
  hword ans;
  for (ans = 0; a >= b; ans++){
    a -= b;
  }
  return ans;
}

// プレイヤーの移動
hword move_player(hword x, hword y, hword xn, hword yn){
  if(xn != x){
    if(xn >= 0 && xn <= 7){
      draw_box_line(x, y, BLACK);
      draw_box_line(xn, yn, RED);
      return xn;
    }
    return x;
  }
  else if (yn != y)
  {
    if (yn >= 0 && yn <= 7){
      draw_box_line(x, y, BLACK);
      draw_box_line(xn, yn, RED);
      return yn;
    }
    return y;
  }
}

// コマを置く
hword put_piece(hword x, hword y, hword player){
  hword color;
  if (player == 1)
  {
    color = BLACK;
  }
  else
  {
    color = WHITE;
  }

  draw_box_circle(x, y, color);
  return player;
}

// コマを置けるかどうか判定
hword can_put_piece(hword x, hword y, hword board[BOX_COUNT][BOX_COUNT], hword player){
  // マスにコマがある場合は抜ける
  if(board[y][x] != 0){
    return 0;
  }

  // 相手のターンを判別
  hword enemy = player * -1;

  // 8方向の座標を設定
  hword move[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
  hword locate;
  for (locate = 0; locate < 8; locate++){
    hword x_tmp = x;
    hword y_tmp = y;
    hword flag = 0;
    while (1)
    {
      x_tmp += move[locate][0];
      y_tmp += move[locate][1];

      // 盤面外までいってしまったら抜ける
      if(x_tmp < 0 || 7 < x_tmp || y_tmp < 0 || 7 < y_tmp){
        break;
      }

      // 置けるかの判定
      if(board[y_tmp][x_tmp] == 0){
        break;
      }else if(board[y_tmp][x_tmp] == enemy){
        flag = 1;
      }else if(board[y_tmp][x_tmp] == player){
        if(flag == 1){
          return player;
        }
        break;
      }
    }
  }
  return 0;
}

// どこかしら置くところがあるか
hword can_put_any_piece(hword board[BOX_COUNT][BOX_COUNT], hword player){
  hword i;
  hword j;
  for (j = 0; j < BOX_COUNT; j++){
    for (i = 0; i < BOX_COUNT; i++){
      if(board[j][i] == 0){
        if(can_put_piece(i, j, board, player) == player){
          return player;
        }
      }
    }
  }
  return 0;
}

// 終了判定
void is_gameset(hword board[BOX_COUNT][BOX_COUNT]) {
  hword cnt_blank = 0;
  hword cnt_player = 0;
  hword cnt_enemy = 0;
  hword i;
  hword j;
  for (j = 0; j < BOX_COUNT; j++)
  {
    for (i = 0; i < BOX_COUNT; i++)
    {
      if (board[j][i] == 0){
        cnt_blank++;
      }else if(board[j][i] == YOUR_TURN){
        cnt_player++;
      }else{
        cnt_enemy++;
      }
    }
  }

  if(cnt_player == 0){
    draw_finish_window(WHITE);
  }else if(cnt_enemy == 0){
    draw_finish_window(BLACK);
  }else if(cnt_blank == 0){
    if (cnt_player == cnt_enemy)
    {
      draw_finish_window(GRAY);
    }
    else if (cnt_player > cnt_enemy)
    {
      draw_finish_window(BLACK);
    }
    else
    {
      draw_finish_window(WHITE);
    }
  }else{
    return;
  }

  while(1)
    ;
  return;
}

// 終了時の描画
void draw_finish_window(hword color){
  draw_window(color);
}

// 初期盤面の描画
void draw_board(){
  hword x;
  hword y;
  for (y = 0; y < BOX_COUNT; y++){
    for (x = 0; x < BOX_COUNT; x++){
      draw_box_bg(x, y);
      draw_box_line(x, y, BLACK);
    }
  }
  draw_box_circle(3, 3, BLACK);
  draw_box_circle(4, 4, BLACK);
  draw_box_circle(3, 4, WHITE);
  draw_box_circle(4, 3, WHITE);

  draw_side_circle();
  draw_side_arrow(YOUR_TURN);
}

// 左右のコマを描画
void draw_side_circle(){
  hword x1 = 30;
  hword y1 = 30;
  hword x2 = 210;
  hword y2 = 30;
  hword r = 20;
  draw_circle(x1, y1, r, BLACK);
  draw_circle(x2, y2, r, WHITE);
}

// 左右の矢印を描画
void draw_side_arrow(hword player){
  if(player == 1){
    draw_arrow(30, 60, RED);
    draw_arrow(210, 60, GRAY);
  }else{
    draw_arrow(30, 60, GRAY);
    draw_arrow(210, 60, RED);
  }
}

// 矢印を描画
void draw_arrow(hword x, hword y, hword color){
  hword tmp;
  for (tmp = 0; tmp < 15; tmp++)
  {
    draw_point(x - tmp, y + tmp, color);
    draw_point(x + tmp, y + tmp, color);
  }
  for (tmp = 0; tmp < 30; tmp++){
    draw_point(x, y + tmp, color);
  }
}

// マスの背景描画
void draw_box_bg(hword xn, hword yn){
  hword x1 = div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * xn);
  hword y1 = div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * yn);
  hword x2 = x1 + BOX_SIZE;
  hword y2 = y1 + BOX_SIZE;
  draw_square(x1, x2, y1, y2, GREEN);
}

// マスの枠線描画
void draw_box_line(hword xn, hword yn, hword color){
  hword x1 = div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * xn);
  hword y1 = div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * yn);

  hword i;
  for (i = 0; i <= BOX_SIZE; i++){
    draw_point(x1 + i, y1, color);
    draw_point(x1 + i, y1 + BOX_SIZE, color);
    draw_point(x1, y1 + i, color);
    draw_point(x1 + BOX_SIZE, y1 + i, color);
  }
}

// マスにコマを描画
void draw_box_circle(hword xn, hword yn, hword color){
  hword xc = div(WINDOW_X, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * xn) + div(BOX_SIZE, 2);
  hword yc = div(WINDOW_Y, 2) - (BOX_SIZE * div(BOX_COUNT, 2)) + (BOX_SIZE * yn) + div(BOX_SIZE, 2);
  draw_circle(xc, yc, div(BOX_SIZE, 2), color);
}

// 円の描画
void draw_circle(hword xc, hword yc, hword r, hword color){
  hword x1 = xc - r;
  hword x2 = xc + r;
  hword y1 = yc - r;
  hword y2 = yc + r;

  hword x;
  hword y;
  for (y = y1; y < y2; y++){
    for (x = x1; x < x2; x++){
      if(r*r > (xc-x)*(xc-x) + (yc-y)*(yc-y)){
        draw_point(x, y, color);
      }
    }
  }
}

// 四角形の描画
void draw_square(hword x1, hword x2, hword y1, hword y2, hword color){
  if (x2 < x1)
  {
    hword tmp = x2;
    x2 = x1;
    x1 = tmp;
  }

  if(y2 < y1){
    hword tmp = y2;
    y2 = y1;
    y1 = tmp;
  }

  hword x;
  hword y;
  for (y = y1; y < y2; y++){
    for (x = x1; x < x2; x++){
      draw_point(x, y, color);
    }
  }
}

// 画面の塗りつぶし
void draw_window(hword color){
  hword x;
  hword y;
  for (y = 0; y < WINDOW_Y; y++){
    for (x = 0; x < WINDOW_X; x++)
    {
      draw_point(x, y, color);
    }
  }
}

// 点を描画
void draw_point(hword x, hword y, hword color)
{
  hword *ptr = (hword *)VRAM;
  ptr += (x + y * WINDOW_X);
  *ptr = color;
}

// 強制的に遅延を作成
void generate_delay(){
  hword a;
  for (a = 0; a < DELAY_PARAM; a++)
    ;
}

// オセロゲーム
void play_othello()
{
  hword *key = (hword *)KEY_CTRL;

  // 画面塗りつぶし
  draw_window(GRAY);

  // 初期盤面を描画
  draw_board();

  // プレイヤー位置の初期描画
  hword player_x = 0;
  hword player_y = 0;
  draw_box_line(player_x, player_y, RED);

  // 盤面情報を作成
  hword board[BOX_COUNT][BOX_COUNT];
  hword i;
  hword j;
  for (j = 0; j < BOX_COUNT; j++){
    for (i = 0; i < BOX_COUNT; i++){
      board[j][i] = 0;
    }
  }
  board[3][3] = 1;
  board[4][4] = 1;
  board[3][4] = -1;
  board[4][3] = -1;

  // 先行・後攻の設定
  hword player = YOUR_TURN;
  hword enemy = player * -1;

  // 入力の判定
  while (1)
  {
    if ((*key & KEY_RIGHT) == KEY_NULL)
    {
      player_x = move_player(player_x, player_y, player_x + 1, player_y);
      while ((*key & KEY_RIGHT) != KEY_RIGHT)
        ;
    }
    else if ((*key & KEY_LEFT) == KEY_NULL)
    {
      player_x = move_player(player_x, player_y, player_x - 1, player_y);
      while ((*key & KEY_LEFT) != KEY_LEFT)
        ;
    }
    else if ((*key & KEY_UP) == KEY_NULL)
    {
      player_y = move_player(player_x, player_y, player_x, player_y - 1);
      while ((*key & KEY_UP) != KEY_UP)
        ;
    }
    else if ((*key & KEY_DOWN) == KEY_NULL)
    {
      player_y = move_player(player_x, player_y, player_x, player_y + 1);
      while ((*key & KEY_DOWN) != KEY_DOWN)
        ;
    }
    else if ((*key & KEY_A) == KEY_NULL)
    {
      // 置ける場合
      if(can_put_piece(player_x, player_y, board, player) == player){
        // コマを置く
        board[player_y][player_x] = put_piece(player_x, player_y, player);

        // 挟んだコマを裏返す
        // 8方向の座標を設定
        hword move[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
        hword locate;
        for (locate = 0; locate < 8; locate++)
        {
          hword x_tmp = player_x;
          hword y_tmp = player_y;
          hword flag = 0;
          while (1)
          {
            x_tmp += move[locate][0];
            y_tmp += move[locate][1];

            // 盤面外までいってしまったら抜ける
            if (x_tmp < 0 || 7 < x_tmp || y_tmp < 0 || 7 < y_tmp)
            {
              break;
            }

            // 置けるかの判定
            if (board[y_tmp][x_tmp] == 0)
            {
              break;
            }
            else if (board[y_tmp][x_tmp] == enemy)
            {
              flag = 1;
            }
            else if (board[y_tmp][x_tmp] == player)
            {
              if (flag == 1)
              {
                // 裏返すことができる方向について遡って裏返す
                while(1){
                  x_tmp -= move[locate][0];
                  y_tmp -= move[locate][1];
                  if(board[y_tmp][x_tmp] == player){
                    break;
                  }
                  board[y_tmp][x_tmp] = put_piece(x_tmp, y_tmp, player);
                }
              }
              break;
            }
          }
        }

        // 終了判定
        is_gameset(board);

        // 相手のターン
        player *= -1;
        enemy *= -1;
        draw_side_arrow(player);

        // パスする必要があるか判定
        if(can_put_any_piece(board, player) == 0)
        {
          // 相手のターン
          player *= -1;
          enemy *= -1;
          draw_side_arrow(player);
        }
      }

      // Aボタンを離した判定
      while ((*key & KEY_A) != KEY_A)
        ;
    }
    else if ((*key & KEY_SELECT) == KEY_NULL)
    {
      // 相手のターン
      player *= -1;
      enemy *= -1;
      draw_side_arrow(player);
      while ((*key & KEY_SELECT) != KEY_SELECT)
        ;
    }
  }
}
