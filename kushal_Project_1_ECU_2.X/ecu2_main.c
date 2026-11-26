#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#define _XTAL_FREQ 8000000

void my_itoa(char str[], int num) {
    str[0] = (num / 1000) + '0';
    str[1] = ((num / 100) % 10) + '0';
    str[2] = (((num) / 10) % 10) + '0';
    str[3] = (num % 10) + '0';
    str[4] = 0;
}

void init_config() {
    init_adc();
    init_digital_keypad();
    //    init_uart();
    init_can();
}

int main() {
    //call the functions
    TRISB0 = 0;
    TRISB1 = 0;
    PORTB = 0x00;
    init_config();
    int delay = 0;
    unsigned char str_rpm[5];
    while (1) {
        uint16_t rpm = get_rpm();
        IndicatorStatus indicator = process_indicator();
                while (delay++ == 500) {
                    if (indicator == 1) {
                        RB0 = !RB0;
                    } else {
                        RB0 = 0;
                    }
                    
                    if(indicator == 2)
                    {
                        RB1 = !RB1;
                    }
                    else
                    {
                        RB1 = 0;
                        RB0 = 0;
                    }
                    if(indicator == 0)
                    {
                        RB1 = 0;
                        RB0 = 0;
                    }
                    delay = 0;
                }
        indicator += '0';
        my_itoa(str_rpm, rpm);

        can_transmit(0x03, str_rpm, 4);
        __delay_ms(50);

        if (indicator == '0') {
            str_rpm[0] = 'O';
            str_rpm[1] ='F';
            str_rpm[2] ='F';
            str_rpm[3] =' ';

        } else if (indicator == '1') {
            str_rpm[0] = '<';
            str_rpm[1] ='-';
            str_rpm[2] ='-';
            str_rpm[3] =' ';
        } else if (indicator == '2') {
            str_rpm[0] = '-';
            str_rpm[1] ='-';
            str_rpm[2] ='>';
            str_rpm[3] =' ';
        }

        can_transmit(0x04, str_rpm, 4);
        __delay_ms(50);

        //                puts("rpm = ");
        //                puts(str_rpm);
        //        
        //                puts("     indicator= ");
        //                if(indicator == 0)
        //                {
        //                    puts("OFF");
        //           
        //                }
        //                else if(indicator == 1)
        //                {
        //                    puts("<-");
        //                }
        //                else if(indicator == 2)
        //                {
        //                    puts("->");
        //                }
        //                
        //                puts("\n\r");

        //        putch(indicator + '0');
        //        puts("\n\r");

    }

}
