#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_speed()
{
    // Implement the speed function
    unsigned short speed = read_adc(CHANNEL4);
    speed = (200/1023.0)*speed;
    return speed;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    static unsigned char gear = '0';
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    if(key == SWITCH1)
    {
        if(gear<'6')
        {
            gear++;
        }
    }
    else if(key == SWITCH2)
    {
        if(gear > '0')
        {
            gear--;
        }
    }
    return gear;
}