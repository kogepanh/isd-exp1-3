// 線分のアルゴリズムを一般化しました．よければ参考にしてください
// アルゴリズムは複雑なので，頑張って読んでください

typedef volatile unsigned short hword;
#define VRAM 0x06000000

void draw_point(hword, hword, hword);
void draw_line(hword, hword, hword, hword, hword);

hword *ptr;
int main(void) {
  // おまじない
  ptr = (hword *)0x04000000;
  *ptr = 0x0F03;

  hword xa, ya, xb, yb;  // 指定された直線の始点と終点
  hword cyan, red;       // 指定された色

  cyan = 0x7FE0;
  red = 0x001F;

  hword x, y;
  for (y = 0; y < 160; y++) {
    for (x = 0; x < 240; x++) {
      draw_point(x, y, cyan);
    }
  }

  // (1) 傾きが正で1より小さい場合
  xa = 10, ya = 10;
  xb = 120, yb = 50;
  draw_line(xa, ya, xb, yb, red);

  // (2) 傾きが1より大きい場合
  xa = 10, ya = 20;
  xb = 50, yb = 120;
  draw_line(xa, ya, xb, yb, red);

  // (3) 傾きが負の場合
  xa = 150, ya = 120;
  xb = 200, yb = 20;
  draw_line(xa, ya, xb, yb, red);

  // (4) 傾きが無限の場合
  xa = 230, ya = 10;
  xb = 230, yb = 140;
  draw_line(xa, ya, xb, yb, red);

  // (5) 傾きが0の場合
  xa = 10, ya = 150;
  xb = 220, yb = 150;
  draw_line(xa, ya, xb, yb, red);

  while (1)
    ;
  return 0;
}

void draw_point(hword x, hword y, hword color) {
  ptr = (hword *)(VRAM + 2 * x + 480 * y);
  *ptr = color;
}

/*
 * 指定された2点を通る直線の方程式を考え，その直線の傾きが正なら直下，負なら直上の整数点を基準に点を打ち直線を描く
 * このとき，下(上)から直線に｢へばりつく｣ようにできる限り上へ(下へ)と動く方針で点を打つ
 * これにより，有名な｢ブレゼンハムのアルゴリズム｣では想定しない，傾きの絶対値が1以上(傾き無限を含む)の直線にも対応できる
 * つまり，ブレゼンハムのアルゴリズムとは異なるので注意すること
 *
 * 直線に｢へばりつく｣ために，for文で横方向へシーケンスに点の判定を移動させるのではなく，while文を使って横にも縦にも点の判定を移動させている
 * また，傾きが負の直線にも対応するため，少々コードが冗長になっている(hwordがunsignedのためこうなってしまう)
 * 総じて，多少の計算量と可読性が犠牲になっている
 */
void draw_line(hword xa, hword ya, hword xb, hword yb, hword color) {
  hword slope = 1;  // 傾きが正なら1，負なら0
  if (ya > yb) {
    slope = 0;
  }

  hword xp, yp;  // 点を打つべきか考えている座標(xp, yp)

  // 初期値は始点(xa, xb)とする
  xp = xa;
  yp = ya;
  while (1) {
    if (slope) {
      // 傾きが正の場合
      if ((xb - xa) * (yp + 1 - ya) <=
          (yb - ya) *
              (xp - xa)) {  // 点を1ドット上に動かしても直線の下に来るか判定
        // 点を上に動かす場合．その上にまだ点を打つ必要があるかもしれないので，xpは更新しない
        yp += 1;
        draw_point(xp, yp, color);  // y軸方向に1つ動かしてから点を打つ
      } else {
        // 点を上に動かさなくてよい場合
        draw_point(xp, yp, color);
        xp += 1;  // 直線の直下に来たので点を打ってから横に移動
      }

      // 終点に到達すれば終了
      if (xp > xb || yp > yb) {
        break;
      }

    } else {
      // 傾きが負の場合
      if ((xb - xa) * (yp - 1 - ya) >
          (yb - ya) *
              (xp - xa)) {  // 点を1ドット下に動かしても直線の上に来るか判定
        // 点を下に動かす場合．その下にまだ点を打つ必要があるかもしれないので，xpは更新しない
        yp -= 1;
        draw_point(xp, yp, color);  // y軸方法に1つ動かしてから点を打つ
      } else {
        // 点を下に動かさなくてよい場合
        draw_point(xp, yp, color);
        xp += 1;  // 直線の直上に来たので点を打ってから横に移動
      }

      // 終点に到達すれば終了
      if (xp > xb || yp < yb) {
        break;
      }
    }
  }
}
