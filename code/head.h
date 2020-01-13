#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <math.h>
#include <stdint.h>

#define PI 3.14159265
#define BUFFER_SIZE 210
#define BOTTOM_TH 844
#define MODE 2
#define REPN 2048
#define INC 800