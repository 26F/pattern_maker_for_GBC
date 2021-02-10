
#include <gb/gb.h>
#include <gb/drawing.h>

void waitnblanks(int n) {
	int c;
	for (c = 0; c < n; c++) {
		wait_vbl_done();	
	}
}

int whichcolor(char ch) {
	if (ch == '0') {
		return 0;
	}
	return 3;
}

void plotline(int x, int col) {
	plot(x, 0, col);
	plot(x, 1, col);
}

void main() {
	// coords
	int x, y;
	// max of fourty characters for the array
	char bits[160] = {'0'};
	int plotcolor = 0;
	int loc = -1;
	int c;
	// flags
	int takinginput = 1;
	int plotting = 0;
	// positioning
	int xcenter = 80;
	int ycenter = 72;
	int centeroffsetxy[2] = {xcenter, ycenter};
	int ysign = -1;
	int xsign = 1;
	int xchange = 1;
	int ychange = 1;
	int xmov = 0;
	int ymov = 0;
	long int number = 0;
	int index = 0;
	long int totalpixels = 12432;
	int max = 70;
	// display messages to show which keys to use
	gotogxy(0, 17);
	gprintf("BUTTONS: A B START");



	for (;;) {
		while(takinginput) {
			wait_vbl_done();
			if (joypad() & J_A) {
				if (loc < max - 1) {
					loc++;
					bits[loc] = '1';
					plotline(loc, 3);
					waitnblanks(12);
						
				}
				
			}
			else if (joypad() & J_B) {
				if (loc < max - 1) {
					loc++;
					bits[loc] = '0';
					plotline(loc, 1);
					waitnblanks(12);	
				}
				
			} 
			else if (joypad() & J_LEFT) {
				if (loc > -1) {
					plotline(loc, 4);
					loc--;	
					waitnblanks(7);
				}
			}
			else if (joypad() & J_START) {
				takinginput = 0;
				plotting = 1;
			}
		}
		
		while (plotting) {
			ysign = -1;
			xsign = 1;
			xchange = 1;
			ychange = 1;
			xmov = 0;
			ymov = 0;
			number = 0;
			centeroffsetxy[0] = xcenter;
			centeroffsetxy[1] = ycenter;
			index = 0;
			while (number < totalpixels) {

				if (number == 0) {
					plotcolor = whichcolor(bits[0]);
					plot(centeroffsetxy[0], centeroffsetxy[1], plotcolor);
					index++;
				}

				for (xmov = 0; xmov < xchange; xmov++) {
					number++;
					if (number < totalpixels) {
						if (index > loc) {
							index = 0;
						}
						plotcolor = whichcolor(bits[index]);
						centeroffsetxy[0] += 1 * xsign;
						plot(centeroffsetxy[0], centeroffsetxy[1], plotcolor);	
						index++;
					}
					
				}

				for (ymov = 0; ymov < ychange; ymov++) {
					number++;
					if (number < totalpixels) {
						if (index > loc) {
							index = 0;
						}
						plotcolor = whichcolor(bits[index]);
						centeroffsetxy[1] += 1 * ysign;
						plot(centeroffsetxy[0], centeroffsetxy[1], plotcolor);	
						index++;
					}
					
				}

				ysign *= -1;
				xsign *= -1;
				xchange += 1;
				ychange += 1;
				wait_vbl_done();
			}
			
			wait_vbl_done();
			
			takinginput = 1;
			plotting = 0;
		}
		loc = -1;
		for (c = 0; c < 160; c++) {
			plotline(c, 4);
		}
		wait_vbl_done();
	}	
}