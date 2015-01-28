/*
 ***************************************************************************************************************************
 * Author: Matthew D Foreman
 * Project: Land Based Rover Firmware (Currently Unnamed Rover)
 * File: main.s
 * Description: First attempt at firmware to run land based rover - including motor control, sensor interface, etc
 * Revision History:
 * .01 - 6 DEC 2014 - initial code setup and testing
 * .02 - 19 DEC 2014 - converted to C
 *
 * Pins:
        40 - TX to Qik
        39 - RX to Qik

        43 - IC2 - CH1 in from receiver
        44 - IC3 - CH2 in from receiver

 ***************************************************************************************************************************
 */

//*** CONFIG DEM PRAGMAS ***//

/*
 SYSCLK = 80 MHz (8 MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
 PBCLK = 40 MHz
*/
//#pragma config FNOSC = PRIPLL // Oscillator selection
#pragma config FNOSC = FRC // Internal Fast RC Oscillator selection
#pragma config POSCMOD = EC // Primary oscillator mode
#pragma config FPLLIDIV = DIV_2 // PLL input divider
#pragma config FPLLMUL = MUL_20 // PLL multiplier
#pragma config FPLLODIV = DIV_1 // PLL output divider
#pragma config FPBDIV = DIV_2 // Peripheral bus clock divider
#pragma config FSOSCEN = OFF // Secondary oscillator enable

#include <p32xxxx.h>
#include <stdio.h>
#include <stdlib.h>
#define _SUPPRESS_PLIB_WARNING
#include <peripheral/ports.h>


//*** GLOBAL VARIABLE DECS ***//
int ch1_old_range, ch2_old_range;
int ch1_new_range, ch2_new_range;
int ch1_old_max = 1970, ch2_old_max = 1970;
int ch1_old_min = 970, ch2_old_min = 970;
int ch1_new_max = 126, ch2_new_max = 126;
int ch1_new_min =  0, ch2_new_min =  0;



//*** FUNCTION FORWARD DECS ***//
void setup_io();
void setup_uart_1(); //bluetooth communication
void setup_uart_2(); //motor controller communication
void setup_timer_1();
void setup_ic_2();
void setup_ic_3();
void get_ch1_value(); //receive, measure, and convert PWM signal to serial data for motor control
void get_ch2_value();


int main(void){

//*** VARIABLE DECS ***//

//*** SETUP RECEIVER PARSES ***//

    //ch1
     ch1_old_range = (ch1_old_max - ch1_old_min);
     ch1_new_range = (ch1_new_max - ch1_new_min);

    //ch2
     ch2_old_range = (ch2_old_max - ch2_old_min);
     ch2_new_range = (ch2_new_max - ch2_new_min);

//*** SETUP FUNCTIONS ***//
     setup_io();
     setup_uart_1();
     setup_uart_2();
     //setup_timer_1();
       
//*** MAIN LOOP **//

    while(1){
        
//        get_ch1_value();
//        get_ch2_value();
     U2TXREG = 0x88;

     int i = 0;

     for (i; i<100000;i++){
         
     }

     U2TXREG = 0x7F;

     U2TXREG = 0x8C;

     int j = 0;

     for (j; j<100000;j++){

     }

     U2TXREG = 0x7F;
    }

   return 0;
}
void setup_io(){

    //*** SETUP TRIS STATES ***//

    //set RX (39) as input - for Qik
    //set TX (40) as output - for Qik
    TRISFbits.TRISF4 = 1;
    TRISFbits.TRISF5 = 0;

    //set ch1 (36) and ch2 (37) as input - from receiver
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;

}

void setup_uart_1(){

    //*** SETUP UART2 ***//

    U1MODEbits.ON = 0;
    U1TXREG = 0x0;
    U1RXREG = 0x0;

    U1BRG = 25; //attempt at 9600 baud - doesn't seem to be working?
                 //note: may be working now, as this code is being ported
                 //from assembler and pragmas may not have been sticking

    //transmit enable
    U1STAbits.UTXEN = 1;
    //receive enable
    U1STAbits.URXEN = 1;

    //enable
    U1MODEbits.ON = 1;
}

void setup_uart_2(){

    //*** SETUP UART2 ***//

    U2MODEbits.ON = 0;
    U2TXREG = 0x0;
    U2RXREG = 0x0;

    U2BRG = 25; //attempt at 9600 baud - doesn't seem to be working?
                 //note: may be working now, as this code is being ported
                 //from assembler and pragmas may not have been sticking

    //transmit enable
    U2STAbits.UTXEN = 1;
    //receive enable
    U2STAbits.URXEN = 1;

    //enable
    U2MODEbits.ON = 1;

    // command for Qik to detect baud rate
    //U2TXREG = 0xAA;
}

void setup_timer_1(){

    //*** INITIALIZE TIMER 2 ***//
    T1CONbits.ON = 0;  //turn off timer 2
    T1CONbits.TCS = 0; //PBCLOCK
    T1CONbits.TCKPS = 0X11; //prescaler = 256

    //*** INITIALIZE TIMER 2 INTERRUPT **//
    IFS0bits.T1IF = 0; //explicitly clear flag
    IPC1bits.T1IP = 6; //priority 6
    IEC0bits.T1IE = 1; //enable

}

void setup_ic_2(){


}

void setup_ic_3(){


}

void __ISR(_TIMER_1_VECTOR, IPL7AUTO) T1Interrupt(void){

 asm volatile ("di");

 IFS0bits.T1IF = 0; //explicitly clear flag

 asm volatile ("ei");

}


void get_ch1_value(){

    // change this shit, yo
    int duration;
    unsigned long ch1;

    //duration = pulseIn(pin, HIGH);  <--- this needs to be taken care of by input capture

    ch1 = (((duration - ch1_old_min) * ch1_new_range) / ch1_old_range) + ch1_new_min;

  //Serial.println(ch1);  <--- is there an alternative for mplab to see values live?

  //send parsed serial data to M0 or M1

}

void get_ch2_value(){

    // change this shit, yo
    int duration;
    unsigned long ch2;

    //duration = pulseIn(pin, HIGH);  <--- this needs to be taken care of by input capture

    ch2 = (((duration - ch2_old_min) * ch2_new_range) / ch2_old_range) + ch2_new_min;

  //Serial.println(ch2);  <--- is there an alternative for mplab to see values live?

  //send parsed serial data to M0 or M1

}