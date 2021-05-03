typedef volatile unsigned short hword;
typedef struct {
  short x;
  short y;
  short turn;
} player;

#define VRAM 0x06000000
#define KEY_CTRL 0x04000130
#define INIT 0x04000000

#define BLACK 0x0000
#define RED 0x001F
#define GREEN 0x03E0
#define BLUE 0x7C00
#define YELLOW 0x03FF
#define CYAAN 0x7FE0
#define MAGENTA 0x7C1F
#define WHITE 0x7FFF
#define GRAY 0x6318

#define KEY_NULL 0x0000
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

#define WINDOW_X 240
#define WINDOW_Y 160

#define BOX_SIZE 16
#define BOX_COUNT 8

#define DELAY_PARAM 5000
#define YOUR_TURN 1

// 関数
void play_othello();
hword div(hword, hword);
void put_piece(hword, hword, short);
void move_player(short, short);
// hword can_put_piece(hword, hword, hword[BOX_COUNT][BOX_COUNT], hword);
// hword can_put_any_piece(hword[BOX_COUNT][BOX_COUNT], hword);
// void is_gameset(hword[BOX_COUNT][BOX_COUNT]);
// void draw_finish_window(hword);
void init_board();
void init_piece();
void init_player();
// void draw_board();
// void draw_side_circle();
// void draw_side_arrow(hword);
// void draw_arrow(hword, hword, hword);
void draw_box_bg(hword, hword, hword);
void draw_player(hword, hword, hword);
void draw_piece(hword, hword, hword);
void draw_circle(hword, hword, hword, hword);
void draw_square(hword, hword, hword, hword, hword);
void draw_window(hword);
void draw_point(hword, hword, hword);
void generate_delay();

// グローバル変数
short board[BOX_COUNT][BOX_COUNT];
player player_A, player_B;
hword *key = (hword *)KEY_CTRL;
