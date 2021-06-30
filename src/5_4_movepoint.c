typedef volatile unsigned short hword;
#define VRAM 0x06000000

void draw_point (hword, hword, hword);

int main (void) {
	hword *ptr ;
	hword color;
	hword x;
	hword y;
	hword *key;
	key = (hword*) 0x04000130;
	ptr = (hword*) 0x04000000;
	*ptr = 0x0F03;
	color = 0x7FE0;
	int a;

	for(y = 0; y < 160; y++){
		for(x = 0; x < 240; x++){
			draw_point(x ,y , color);
		}
	}

	x = ((525) + (3)) % 59 + 60;
	y = (525) * (3) % 39 + 81;
	draw_point(x, y , 0x001F);

	while(1){
		if((*key&0x0010) == 0x0000) {
			draw_point(x, y , 0x7FE0);
			x +=1;
			draw_point(x, y , 0x001F);
		} else if((*key&0x0020) == 0x0000) {
			draw_point(x, y , 0x7FE0);
			x -=1;
			draw_point(x, y , 0x001F);
		} else if((*key&0x0040) == 0x0000) {
			draw_point(x, y , 0x7FE0);
			y -=1;
			draw_point(x, y , 0x001F);
		} else if((*key&0x0080) == 0x0000) {
			draw_point(x, y , 0x7FE0);
			y +=1;
			draw_point(x, y , 0x001F);
		}

		for(a=0; a < 5000; a++){}
	}
	return(0);
}

void draw_point (hword x , hword y , hword color) {
	hword *ptr = (hword*)VRAM;
	ptr +=(x + y*240);
	*ptr = color;
}
