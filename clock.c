
#include "application.h"

void isr_timer0(void);
volatile uint8 seconds_counter=0;
uint8 minutes_counter=0,hours_counter=0;
uint8 value,first_digit,second_digit;

int main() {
   Std_ReturnType ret = E_NOT_OK;
   
   
   chr_lcd_8bit_t lcd_user = {
      .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
      .lcd_en.logic = GPIO_LOW , 
      .lcd_en.port = PORTB_INDEX , 
      .lcd_en.pin = GPIO_PIN0,
      
      .lcd_rs.direction = GPIO_DIRECTION_OUTPUT , 
      .lcd_rs.logic = GPIO_LOW , 
      .lcd_rs.port = PORTB_INDEX , 
      .lcd_rs.pin = GPIO_PIN1,
      
      .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[0].logic = GPIO_LOW , .lcd_data[0].port = PORTA_INDEX , .lcd_data[0].pin = GPIO_PIN0,
      .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[1].logic = GPIO_LOW , .lcd_data[1].port = PORTA_INDEX , .lcd_data[1].pin = GPIO_PIN1,
      .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[2].logic = GPIO_LOW , .lcd_data[2].port = PORTA_INDEX , .lcd_data[2].pin = GPIO_PIN2,
      .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[3].logic = GPIO_LOW , .lcd_data[3].port = PORTA_INDEX , .lcd_data[3].pin = GPIO_PIN3,
      .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[4].logic = GPIO_LOW , .lcd_data[4].port = PORTC_INDEX , .lcd_data[4].pin = GPIO_PIN7,
      .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[5].logic = GPIO_LOW , .lcd_data[5].port = PORTA_INDEX , .lcd_data[5].pin = GPIO_PIN5,
      .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[6].logic = GPIO_LOW , .lcd_data[6].port = PORTB_INDEX , .lcd_data[6].pin = GPIO_PIN2,
      .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT , .lcd_data[7].logic = GPIO_LOW , .lcd_data[7].port = PORTB_INDEX , .lcd_data[7].pin = GPIO_PIN3,
    };
   keypad_t keypad_user = {
    .keypad_row_pins[0].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic=GPIO_LOW,
    .keypad_row_pins[0].port=PORTD_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[1].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic=GPIO_LOW,
    .keypad_row_pins[1].port=PORTD_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[2].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic=GPIO_LOW,
    .keypad_row_pins[2].port=PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[3].direction=GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic=GPIO_LOW,
    .keypad_row_pins[3].port=PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,

    .keypad_col_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[0].logic=GPIO_LOW,
    .keypad_col_pins[0].port=PORTD_INDEX,
    .keypad_col_pins[0].pin = GPIO_PIN4,
    .keypad_col_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[1].logic=GPIO_LOW,
    .keypad_col_pins[1].port=PORTD_INDEX,
    .keypad_col_pins[1].pin = GPIO_PIN5,
    .keypad_col_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[2].logic=GPIO_LOW,
    .keypad_col_pins[2].port=PORTD_INDEX,
    .keypad_col_pins[2].pin = GPIO_PIN6,
    .keypad_col_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_col_pins[3].logic=GPIO_LOW,
    .keypad_col_pins[3].port=PORTD_INDEX,
    .keypad_col_pins[3].pin = GPIO_PIN7,
    };
   
   segment_t seg1 = {
    .segment_pins[0].port = PORTB_INDEX,
    .segment_pins[0].pin = GPIO_PIN4,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].port = PORTB_INDEX,
    .segment_pins[1].pin = GPIO_PIN5,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].port = PORTB_INDEX,
    .segment_pins[2].pin = GPIO_PIN6,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].port = PORTB_INDEX,
    .segment_pins[3].pin = GPIO_PIN7,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_type = SEGMENT_COMMON_CATHODE
    };
   
   pin_config_t en1 = {.port = PORTC_INDEX, .pin = GPIO_PIN0, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   pin_config_t en2 = {.port = PORTC_INDEX, .pin = GPIO_PIN1, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   pin_config_t en3 = {.port = PORTC_INDEX, .pin = GPIO_PIN2, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   pin_config_t en4 = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   pin_config_t en5 = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   pin_config_t en6 = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_LOW};
   
   timer0_t tmr0 = {
    .timer0_InterruptHandler  = isr_timer0,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_register_size = TIMER0_16BIT_MODE,
    .timer0_prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_preload_value = 3036
    };
    
    gpio_pin_initialize(&en1);
    gpio_pin_initialize(&en2);
    gpio_pin_initialize(&en3);
    gpio_pin_initialize(&en4);
    gpio_pin_initialize(&en5);
    gpio_pin_initialize(&en6);
    seven_segment_initialize(&seg1);
    lcd_8bit_initialize(&lcd_user);
    keypad_initialize(&keypad_user);
    timer0_init(&tmr0);
    lcd_8bit_send_string(&lcd_user , "press 1 to");
    lcd_8bit_send_char_str_pos(&lcd_user , 2, 1,"set clock" );
	timer0_init(&tmr0);
    
   while(1){
       ret = keypad_get_value(&keypad_user , &value);
		if (value!=KEY_RELEASED){
			if (value=='1'){
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
                ret = lcd_8bit_send_string(&lcd_user , "hours=--");
				__delay_ms(500);
				do{
					ret = keypad_get_value(&keypad_user , &first_digit);	
				} while (first_digit==KEY_RELEASED);
				ret = lcd_8bit_send_char_data_pos(&lcd_user , 1, 7, first_digit);
				__delay_ms(300);
				do{
                    ret = keypad_get_value(&keypad_user , &second_digit);	
				} while (second_digit==KEY_RELEASED);
                ret = lcd_8bit_send_char_data(&lcd_user , second_digit);
				__delay_ms(300);
				hours_counter=(second_digit-48)+10*(first_digit-48);
				ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
				ret = lcd_8bit_send_string(&lcd_user , "minutes=--");
              
				do{
                    ret = keypad_get_value(&keypad_user , &first_digit);
				} while (first_digit==KEY_RELEASED);
                ret = lcd_8bit_send_char_data_pos(&lcd_user , 1, 9, first_digit);
				__delay_ms(300);
				do{
                    ret = keypad_get_value(&keypad_user , &second_digit);
				} while (second_digit==KEY_RELEASED);
				ret = lcd_8bit_send_char_data(&lcd_user , second_digit);
				__delay_ms(300);
				minutes_counter=(second_digit-48)+10*(first_digit-48);
				ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
				
                ret = lcd_8bit_send_string(&lcd_user , "seconds=--");
				
				do{
                    ret = keypad_get_value(&keypad_user , &first_digit);	
				} while (first_digit==KEY_RELEASED);
				ret = lcd_8bit_send_char_data_pos(&lcd_user , 1, 9, first_digit);
				__delay_ms(300);
				do{
					ret = keypad_get_value(&keypad_user , &second_digit);
				} while (second_digit==KEY_RELEASED);
                ret = lcd_8bit_send_char_data(&lcd_user , second_digit);
				__delay_ms(300);
				seconds_counter=(second_digit-48)+10*(first_digit-48);
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
				lcd_8bit_send_string(&lcd_user , "press 1 to");
                lcd_8bit_send_char_str_pos(&lcd_user , 2, 1,"set clock" );
			}
			else{
                ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
                lcd_8bit_send_string(&lcd_user , "wrong choice");
				__delay_ms(1000);
				ret = lcd_8bit_send_command(&lcd_user , LCD_CLEAR);
				lcd_8bit_send_string(&lcd_user , "press 1 to");
                lcd_8bit_send_char_str_pos(&lcd_user , 2, 1,"set clock" );
			}
		}
		
        gpio_pin_write_logic(&en1,GPIO_LOW);
        gpio_pin_write_logic(&en2,GPIO_HIGH);
        gpio_pin_write_logic(&en3,GPIO_HIGH);
        gpio_pin_write_logic(&en4,GPIO_HIGH);
        gpio_pin_write_logic(&en5,GPIO_HIGH);
        gpio_pin_write_logic(&en6,GPIO_HIGH);
        seven_segment_write_number(&seg1 ,seconds_counter%10 );
		__delay_ms(10);
		
        gpio_pin_write_logic(&en1,GPIO_HIGH);
        gpio_pin_write_logic(&en2,GPIO_LOW);
        gpio_pin_write_logic(&en3,GPIO_HIGH);
        gpio_pin_write_logic(&en4,GPIO_HIGH);
        gpio_pin_write_logic(&en5,GPIO_HIGH);
        gpio_pin_write_logic(&en6,GPIO_HIGH);
        seven_segment_write_number(&seg1 ,seconds_counter/10 );
		__delay_ms(10);
		
		gpio_pin_write_logic(&en1,GPIO_HIGH);
        gpio_pin_write_logic(&en2,GPIO_HIGH);
        gpio_pin_write_logic(&en3,GPIO_LOW);
        gpio_pin_write_logic(&en4,GPIO_HIGH);
        gpio_pin_write_logic(&en5,GPIO_HIGH);
        gpio_pin_write_logic(&en6,GPIO_HIGH);
        seven_segment_write_number(&seg1 ,minutes_counter%10 );
		__delay_ms(10);
        
		gpio_pin_write_logic(&en1,GPIO_HIGH);
        gpio_pin_write_logic(&en2,GPIO_HIGH);
        gpio_pin_write_logic(&en3,GPIO_HIGH);
        gpio_pin_write_logic(&en4,GPIO_LOW);
        gpio_pin_write_logic(&en5,GPIO_HIGH);
        gpio_pin_write_logic(&en6,GPIO_HIGH);
        seven_segment_write_number(&seg1 ,minutes_counter/10 );
		__delay_ms(10);
		
		gpio_pin_write_logic(&en1,GPIO_HIGH);
        gpio_pin_write_logic(&en2,GPIO_HIGH);
        gpio_pin_write_logic(&en3,GPIO_HIGH);
        gpio_pin_write_logic(&en4,GPIO_HIGH);
        gpio_pin_write_logic(&en5,GPIO_LOW);
        gpio_pin_write_logic(&en6,GPIO_HIGH);
        seven_segment_write_number(&seg1 ,hours_counter%10);
		__delay_ms(10);
		
        gpio_pin_write_logic(&en1,GPIO_HIGH);
        gpio_pin_write_logic(&en2,GPIO_HIGH);
        gpio_pin_write_logic(&en3,GPIO_HIGH);
        gpio_pin_write_logic(&en4,GPIO_HIGH);
        gpio_pin_write_logic(&en5,GPIO_HIGH);
        gpio_pin_write_logic(&en6,GPIO_LOW);
        seven_segment_write_number(&seg1 ,hours_counter/10);
		__delay_ms(10);
		
		
		if (seconds_counter==60){
			seconds_counter=0;
			minutes_counter++;
		}
		if (minutes_counter==60){
			minutes_counter=0;
			hours_counter++;
		}
		if (hours_counter==24){
			hours_counter=0;
		}
        
   }

    return (EXIT_SUCCESS);
}

void isr_timer0(void){
	seconds_counter++;	
}