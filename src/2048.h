typedef volatile unsigned short hword;

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

#define DIRECTION_UP 0
#define DIRECTION_LEFT 1
#define DIRECTION_DOWN 2
#define DIRECTION_RIGHT 3

#define WINDOW_X 240
#define WINDOW_Y 160

#define BOX_SIZE 36
#define NUMBER_SQ_SIZE 6

#define DELAY_PARAM 5000
#define YOUR_TURN 1

// 関数
hword div(hword, hword);
hword mod(hword, hword);
void play_2048();
void draw_point(hword, hword, hword);
void draw_line_x(hword, hword, hword, hword);
void draw_line_y(hword, hword, hword, hword);
void draw_line(hword, hword, hword, hword, hword);
void draw_window(hword);
void draw_square(hword, hword, hword, hword, hword);
void draw_box_bg(hword, hword, hword);
void draw_box_line(hword, hword, hword);
void draw_board();
void draw_over_board(hword);
void init_board();
void draw_number(hword, hword, hword, hword);
void draw_all_number();
void swipe(hword);
void merge_number(hword, hword);
void move_number(hword, hword);
void clean_board_flag();
void clean_board_red();
void generate_number();
void check_gameover();

void draw_number_0(hword, hword, hword);
void draw_number_1(hword, hword, hword);
void draw_number_2(hword, hword, hword);
void draw_number_3(hword, hword, hword);
void draw_number_4(hword, hword, hword);
void draw_number_5(hword, hword, hword);
void draw_number_6(hword, hword, hword);
void draw_number_7(hword, hword, hword);
void draw_number_8(hword, hword, hword);
void draw_number_9(hword, hword, hword);

void draw_box_2(hword, hword, hword);
void draw_box_4(hword, hword, hword);
void draw_box_8(hword, hword, hword);
void draw_box_16(hword, hword, hword);
void draw_box_32(hword, hword, hword);
void draw_box_64(hword, hword, hword);
void draw_box_128(hword, hword, hword);
void draw_box_256(hword, hword, hword);
void draw_box_512(hword, hword, hword);
void draw_box_1024(hword, hword, hword);
void draw_box_2048(hword, hword, hword);
void draw_box_4096(hword, hword, hword);

// グローバル変数
hword board[4][4];
hword board_flag[4][4];
hword board_red_flag[4][4];
hword *key = (hword *)KEY_CTRL;
hword rand_i = 0;
