#pragma once
#include <stdint.h>
#include <stdbool.h>

#define TRUE true
#define FALSE false

#include "gd32f10x.h"
#include "gd32f10x_usart.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x_timer.h"

// User includes
#include "fifo.h"


#define USART_PC USART0
#define LED_TIMER TIMER1
#define SMP_TIMER TIMER0
