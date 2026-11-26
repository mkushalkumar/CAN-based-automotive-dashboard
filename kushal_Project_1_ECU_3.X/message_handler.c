#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
int flag;
void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 10000)
		{
			count = 0;
            flag = 1;
		}
		TMR0IF = 0;
	}
}

volatile unsigned char led_state = LED_OFF, status = e_ind_off;

void handle_speed_data(uint8_t *data, uint8_t len) {
    //Implement the speed function
    char speed[4];
    speed[0] = data[0];
    speed[1] = data[1];
    speed[2] = data[2];
    speed[3] = 0;

    clcd_print(speed, LINE2(0));

}

void handle_gear_data(uint8_t *data, uint8_t len) {
    //    //Implement the gear function
    //    uint8_t gear = data[0];
    char speed[4];
    speed[0] = ' ';
    speed[1] = data[1];
    speed[2] = ' ';
    speed[3] = 0;
    if (speed[1] == '0') {
        speed[0] = ' ';
        speed[1] = 'N';
    } else if (speed[1] == '6') {
        speed[0] = ' ';
        speed[1] = 'R';
    } else if (speed[1] > '0' && speed[1] < '6') {
        speed[0] = 'G';
    }

    
    clcd_print(speed, LINE2(9));

}

void handle_rpm_data(uint8_t *data, uint8_t len) {
    //Implement the rpm function
    uint8_t rpm[5];

    rpm[0] = data[0];
    rpm[1] = data[1];
    rpm[2] = data[2];
    rpm[3] = data[3];
    rpm[4] = 0;

    clcd_print(rpm, LINE2(4));

}

void handle_engine_temp_data(uint8_t *data, uint8_t len) {
    //Implement the temperature function
}
int delay = 0;

void handle_indicator_data(uint8_t *data, uint8_t len) {
    //Implement the indicator function

    uint8_t ind[4];
//    while (delay++ == 50) {
    if(flag==1)
    {
        if (data[0] == '<') {
            RB0 = !RB0;
            RB7 = 0;
        } else if (data[0] == '-') {
            RB7 = !RB7;
            RB0 = 0;
        }
      else if (data[0] == 'O') {
            RB7 = 0;
            RB0 = 0;
        }
        
        flag = 0;
    }
    ind[0] = data[0];
    ind[1] = data[1];
    ind[2] = data[2];
    ind[3] = 0;

    clcd_print(ind, LINE2(13));

}

void process_canbus_data() {
    //process the CAN bus data

    uint16_t msg_id;

    uint8_t data[5] = {0};
    uint8_t len;

    can_receive(&msg_id, data, &len);
    data[len] = 0;
    //    handle_speed_data(data, 3);
    //    handle_gear_data("N", 1);
    //    handle_rpm_data("2500",4);
    //    handle_indicator_data("<--", 3) ;

    if (msg_id == 0x01) {
        handle_speed_data(data, len);
    } else if (msg_id == 0x02) {
        handle_gear_data(data, len);
    } else if (msg_id == 0x03) {
        handle_rpm_data(data, len);
    } else if (msg_id == 0x04) {
        handle_indicator_data(data, len);
    }

}