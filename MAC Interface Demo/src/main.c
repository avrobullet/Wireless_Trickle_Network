/**
* RSSI example
*
* Node blinks the boards LED, and sends a message every now and then. Blinking rate
* depends on the RSSI of the last message
*/

#include <asf.h>
#include "mac/mac.h"
#include "radio/radio.h"
#include "message.h"

#define ADDRESSEE_NODE		5 //Your address
#define LED_ON				false
#define LED1 IOPORT_CREATE_PIN(PIOC, 20);
#define LED2 IOPORT_CREATE_PIN(PIOA, 16);
#define LED3 IOPORT_CREATE_PIN(PIOC, 22);


void msg_received(Message *msg);
void ack_received(uint8_t status);
void task_msgsend(bool msg_end);
void task_ledblink(void);
void oled_update(void);
void oled_pause(void);

static uint32_t blink_wait = 2000; //2 secs initial wait
uint8_t msg_state = 1;
bool button0_state = false;
uint32_t value[6];

void Button_Handler(uint32_t id, uint32_t mask)
{
	uint32_t led;
	if( ID_PIOA == id && PIO_PA2 == mask )
	{
		button0_state = !button0_state;
	}
	else { return; }
	ioport_set_pin_level( led, !ioport_get_pin_level(led) );
}


const uint32_t irq_priority = 5;
void configure_buttons(void)
{
	//Configure Pushbutton 0
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_debounce_filter(PIOC, PIN_PUSHBUTTON_0_MASK, 10);
	pio_handler_set(PIOA, ID_PIOA,
	PIN_PUSHBUTTON_0_MASK, PIN_PUSHBUTTON_0_ATTR, Button_Handler);
	NVIC_EnableIRQ((IRQn_Type) ID_PIOA);
	pio_handler_set_priority(PIOA, (IRQn_Type) ID_PIOA, irq_priority);
	pio_enable_interrupt(PIOA, PIN_PUSHBUTTON_0_MASK);
}

void main(void)
{
	sysclk_init();
	board_init();
	configure_buttons();
	ssd1306_init();

	//Init MAC
	if( !mac_init( msg_received, ack_received ) )
	{
		//Error: Xbee's baud rate is different to the one specified in mac_config.h (RADIO SPEED RATE)
		while(1);
	}

	//signal initialization went fine.
	ioport_set_pin_level( IOPORT_CREATE_PIN(PIOC, 23), LED_ON );
	while (1)
	{
		while(button0_state == false)
		{
			delay_ms(1000);
			ioport_set_pin_level( IOPORT_CREATE_PIN(PIOC, 23), !LED_ON );
			oled_pause();
			task_msgsend(false);
		}

		while (msg_state == 1)
		{
			if (ADDRESSEE_NODE == 1)
				break;
			oled_pause();
			task_msgsend(false);
		}

		while(button0_state == true && msg_state == 0)
		{
			oled_update();
			task_msgsend(true);
			task_ledblink();

			delay_ms(blink_wait);
		}
	}
}

void task_msgsend(bool msg_end){
	//sends a message every now and then
	Message msg;
	msg.address = ADDRESSEE_NODE;			//Addressee node
	//msg.data[0] = 7;						//send anything (random value)
	msg.data_length = 1;					//we're sending one byte
	if (msg_end == false)
	{
		msg.data[0] = 1;
	}
	else
	{
		msg.data[0] = 0;
	}
	mac_send(&msg);
}

static bool led_state = LED_ON;

void task_ledblink(void){
	//blinks led. Blink rate depends on rssi received
	ioport_set_pin_level( IOPORT_CREATE_PIN(PIOC, 23), led_state = !led_state );
}


void msg_received(Message *msg_in){
	//updates the blink wait time, based on the RSSI of msg received
	blink_wait = msg_in->rssi * 18 - 700;
	msg_state = msg_in->data[0];
}

void ack_received(uint8_t status){}

void oled_update()
{
	ssd1306_clear();
	ssd1306_set_page_address(0);
	sprintf(value, "%d", blink_wait);
	ssd1306_write_text("Blink wait (ms): ");
	ssd1306_write_text(value);
}

void oled_pause()
{
	ssd1306_clear();
	ssd1306_set_page_address(0);
	ssd1306_write_text("Not receiving");
}
