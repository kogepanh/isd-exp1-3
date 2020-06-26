typedef volatile unsigned short hword;
#define VRAM 0x06000000
int  main (void) {
	hword *ptr;
	hword color;
	hword *key;
	key = (hword*) 0x04000130;
	ptr = (hword*) 0x04000000;
	*ptr = 0x0F03;

	while(1) {
		if((*key&0x0001) == 0x0000) {

			color = 0x07C00;
			ptr = (hword*) VRAM;

			*ptr = color;

			ptr = (hword*) 0x06000004;
			*ptr = color;

			ptr = (hword*) 0x06000008;
			*ptr = color;

			ptr = (hword*) 0x0600000C;
			*ptr = color;

		} else {
			ptr = (hword*) 0x04000000;
			*ptr = 0x0F03;

			color = 0x001F;

			ptr = (hword*) VRAM;
			*ptr = color;

			ptr = (hword*) 0x06000004;
			*ptr = color;

			ptr = (hword*) 0x06000008;
			*ptr = color;

			ptr = (hword*) 0x0600000C;
			*ptr = color;
		}
	}
	return(0);
}


