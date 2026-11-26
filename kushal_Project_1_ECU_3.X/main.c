#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

void init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();
    init_timer0();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
//    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();
    clcd_print("                              ", LINE2(0));
    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
        clcd_print("sp ", LINE1(0));
        clcd_print("rpm", LINE1(4));
        clcd_print("gear", LINE1(8));
        clcd_print("ind", LINE1(13));
        
        
    }

    return;
}

