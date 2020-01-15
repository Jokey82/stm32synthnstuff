#include "commands.h"

uint8_t led_command_check(char* RXs){
						if (strncmp(RXs, "ON1\r", 4) == 0) {
								return LED1_ON;
            }
						if (strncmp(RXs, "ON2\r", 4) == 0) {
								return LED2_ON;
            }
						if (strncmp(RXs, "ON3\r", 4) == 0) {
								return LED3_ON;
            }
						if (strncmp(RXs, "ON4\r", 4) == 0) {
								return LED4_ON;
            }
						if (strncmp(RXs, "DEMO\r", 5) == 0) {
								return DEMO;
            }
						if (strncmp(RXs, "STOP\r", 5) == 0) {
								return STOP;
            }
						else {
							return 0;
						}
}

uint16_t osc_command_check(char* RXs){
	if((uint16_t)strstr(RXs, "FRQ") == (uint16_t)RXs){
		uint16_t val = extract_int(RXs);
		if (val <= 0 || val > MAX_FRQ){
			return INVAL;
		}
		return val;
	}
}