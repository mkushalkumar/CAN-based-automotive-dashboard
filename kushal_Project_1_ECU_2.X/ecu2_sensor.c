#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_rpm()
{
    //Implement the rpm function
    unsigned short rpm = read_adc(CHANNEL4);
    rpm = (7000/1023.0) * rpm;
    return rpm;
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
    return 0;
}

IndicatorStatus indicator = 0;
IndicatorStatus process_indicator()
{
    //Implement the indicator function
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key == SWITCH1)
    {
        indicator = 1;
    }
    else if(key == SWITCH2)
    {
        indicator = 0;
    }
    else if(key == SWITCH3)
    {
        indicator = 2;
    }
    return indicator;
}