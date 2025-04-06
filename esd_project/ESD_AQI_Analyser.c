#include <lpc17xx.h>
#include <stdio.h>
 
#define refVtg 5
#define digitalMax 0xFFF
#define RS_CTRL  0x00000100  //P0.8
#define EN_CTRL  0x10000200  //P0.9
#define DT_CTRL  0x000000F0  //P0.4 TO P0.7
 
unsigned long int init_command[] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
unsigned long int temp1 = 0, temp2 = 0, i, j, var1, var2;
unsigned char flag1 = 0, flag2 = 0;
unsigned char msg[] = {"Voltage:"};
unsigned char msg2[] = {"AQI: "};
unsigned long int step_pos[] = {0x2,0x1,0x8,0x4};
 
void lcd_init(void);
void lcd_write(void);
void port_write(void);
void delay(unsigned int);
void lcd_print_msg(void);
void lcd_print_msg2(void);
void lcd_print_aval(void);
void lcd_print_dval(void);
 
int main(void) {
    unsigned int mqReading, i;
    float analogVtg;
    char analogVtgStr[14], digitalValStr[14];
 
    SystemInit();
    SystemCoreClockUpdate();
 
    LPC_PINCON->PINSEL1 |= 1<<14; //function 1 on P0.23 for AD0.0
    LPC_SC->PCONP |= (1<<12); //peripheral power supply for ADC
 
    LPC_GPIO0->FIODIR = DT_CTRL | RS_CTRL | EN_CTRL;
   
    lcd_init();
    lcd_print_msg();
        lcd_print_msg2();
 
    LPC_GPIO2->FIODIR = 1 << 13;
 
    while(1) {
        LPC_ADC->ADCR = (1<<0) | (1<<21) | (1<<24);// channel 0, power on,software mode start
        while(((mqReading = LPC_ADC->ADGDR) & 0X80000000) == 0);// waiting for done bit to get high
        mqReading = LPC_ADC->ADGDR;
        mqReading >>= 4;
        mqReading &= 0x00000FFF;
        analogVtg = (((float)mqReading * (float)refVtg))/((float)digitalMax);
 
        sprintf(analogVtgStr, "%0.3fV", analogVtg);// analog voltage
        sprintf(digitalValStr, "%d", (mqReading / 7));// digital voltage
 
        temp1 = 0x89;
        flag1 = 0;
        lcd_write();
        delay(800);
        i=0;
        flag1=1;
 
        while(analogVtgStr[i]!='\0') {
            temp1 = analogVtgStr[i];
            lcd_write();
            i+= 1;
        }
 
        temp1 = 0xC5;
        flag1=0;
        lcd_write();
        delay(800);
        i=0;
        flag1=1;
        while(digitalValStr[i]!='\0'){
            temp1 = digitalValStr[i];
            lcd_write();
            i += 1;
        }
 
        if(mqReading >= 490) {
            LPC_GPIO2->FIOPIN = 1 << 13;
            delay(50000);
            LPC_GPIO2->FIOCLR = 1 << 13;
        }
 
    }
}
 
void lcd_init(void) {
    unsigned int x;
    flag1 = 0; //Command Mode
    for(x=0;x<9;x++) {
        temp1 = init_command[x];
        lcd_write();
    }
    flag1 = 1; //Data Mode
}
 
void lcd_write(void) { //flag2 =0 then write most significant and also least significant 4 bits to LCD  
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
    temp2 = temp1 & 0xf0;
    //temp2 = temp2 << 19;//data lines from 26 to 23
    port_write();
    if (flag2==0) {//send least significant 4 bits only when it is data/command other than 0x30/0x20
        temp2 = temp1 & 0x0f; //26-4+1
        temp2 = temp2 << 4;
        port_write();
    }
}
 
void port_write(void) {
    LPC_GPIO0->FIOPIN = temp2;
    if (flag1 == 0)  
        LPC_GPIO0->FIOCLR = RS_CTRL;
    else
        LPC_GPIO0->FIOSET = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    delay(30000);
}
 
void delay(unsigned int r1) {
    unsigned int r;
    for(r=0;r<r1;r++);
}
 
void lcd_print_msg(void) {
    unsigned int a;
    for(a = 0; msg[a] != '\0'; a++) {
        temp1 = msg[a];
        lcd_write();
    }
}
 
void lcd_print_msg2(void) {
        temp1 = 0xC0;
        flag1 = 0;
        lcd_write();
        delay(800);
        i = 0;
        flag1 = 1;
        while(msg2[i]!='\0'){
                temp1 = msg2[i];
                lcd_write();
                i += 1;
        }
}