#include <stdint.h>
#include "otty.h"
#include "ps2keyboard.h"
void obish(){
	uint8_t last_scancode=0;
	uint8_t streak_scancode=0;
	uint32_t counter=0;
	uint8_t streak=0;
	print_str_ln("~~~~~~~~~~~~~~");
	print_str_ln("Ondrux built-in shell - obish");
	print_str_ln("~~~~~~~~~~~~~~");
	while(1){
		uint8_t scancode=getScancode();
		if(scancode!=last_scancode){
			switch(scancode){		
				case 72: terminal_scroll_rel(-1);break;
				case 80: terminal_scroll_rel(1);break;
				default: print_num(scancode);
				print_str_ln(" ");
			}
		}else
			counter++;
		last_scancode=scancode;
		if(!(streak_scancode==scancode||streak_scancode==last_scancode)){
			streak=0;
		}
		if(scancode==last_scancode&&last_scancode!=0&&counter>(!streak?1000000:200000)){
			last_scancode=0;
			counter=0;
			streak=1;
			streak_scancode=scancode;
		}
	}

}
