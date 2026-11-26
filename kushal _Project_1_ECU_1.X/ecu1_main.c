#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#define _XTAL_FREQ 8000000

void my_itoa(int speed,char* str)
{
    str[0] = speed/100 + '0';
    str[1] = (speed/10)%10 +'0';
    str[2] = speed%10 + '0';
    str[3] = 0;
}

void init_config()
{
    init_adc();
    init_digital_keypad();
//    init_uart();
    init_can();
}

void delay(int i)
{
    for(i=20000 ;i-- ;);
}

int main()
{
    //Call the functions
    init_config();
    
    unsigned int speed;
    unsigned char gear ;
    
    char str_s[4];
    while(1)
    {
        speed = get_speed();
        my_itoa(speed, str_s);
        can_transmit(0x01, str_s, 3);
        __delay_ms(50);
        
        
        gear = get_gear_pos();
        str_s[0] = ' ';
        str_s[1] = gear;
        str_s[2]=0;
        can_transmit(0x02 ,str_s ,3);
        __delay_ms(50);        
        
////        printing using uart 
//        puts("speed is : ");
//        puts(str_s);
//        
//        puts("    Gear : ");
//        puts(str_gear);
//        puts("\n\r");
    }
}