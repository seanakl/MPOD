/********************************************************************
 * FileName:        (change filename of template).c
 * Processor:       PIC18F4520
 * Compiler:        MPLAB C18 v.3.06
 *
 * This file does the following....
 *
 *
 *       Author               Date              Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// (Your name here) 

/**  Header Files **************************************************/
#include <p18f4520.h>
#include <stdio.h>
#include <adc.h>
#include "LCD Module.h"
#include <portb.h>
#include <delays.h>

/** Configuration Bits *********************************************/
#pragma config OSC = INTIO67
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config BOREN = OFF
#pragma config XINST = OFF

/** Define Constants Here ******************************************/
#define SAMPLE 100
#define LOCKED 1
#define UNLOCKED 0
#define OPEN 0
#define CLOSED 1

/** Local Function Prototypes **************************************/
void low_isr(void);
void high_isr(void);
void sampleFunction(void);

/** Declare Interrupt Vector Sections ****************************/
#pragma code high_vector=0x08

void interrupt_at_high_vector(void) {
    _asm goto high_isr _endasm
}

#pragma code low_vector=0x18

void interrupt_at_low_vector(void) {
    _asm goto low_isr _endasm
}

/** Global Variables ***********************************************/
char keycardCombos = {0b00110011, 0b00101010, 0b00111000};
char buttonSeq1 = {'a', 'b', 'b', 'c'};
char buttonSeq2 = {'b', 'c', 'a', 'a'};
char buttonSeq3 = {'a', 'c', 'a', 'c'};

char line1[9];

/*******************************************************************
 * Function:        void main(void)
 ********************************************************************/
#pragma code

void main(void) {
    // Set the clock to 4 MHz
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;

    // Pin IO Setup
    OpenADC(ADC_FOSC_8 & ADC_RIGHT_JUST & ADC_12_TAD,
            ADC_CH0 & ADC_INT_OFF & ADC_REF_VDD_VSS,
            0x0F); // Four analog pins
    TRISA = 0x00; // All of PORTA output
    TRISB = 0xFF; // All of PORTB input
    TRISC = 0x0F; // All of PORTC output
    TRISD = 0x00; // All of PORTD output
    PORTC = 0x00; // Turn off all 8 Port C LEDs

    // Open LCD
    XLCDInit();
    XLCDClear();

    // Interrupt setup
    RCONbits.IPEN = 1; // Put the interrupts into Priority Mode
    // Add specific interrupts here...

    INTCONbits.GIEH = 1; // Turn on high priority interrupts

    // This area happens once
    // Good for initializing and things that need to happen once

    while (1) {
        if(CLOSED && LOCKED){
            // Go to input function
        }
    }
}

/*****************************************************************
 * Function:        void high_isr(void)
 ******************************************************************/
#pragma interrupt high_isr

void high_isr(void) {
    // Add code here for the high priority Interrupt Service Routine (ISR)
}

/******************************************************************
 * Function:        void low_isr(void)
 ********************************************************************/
#pragma interruptlow low_isr

void low_isr(void) {
    // Add code here for the low priority Interrupt Service Routine (ISR)
}

#pragma code
/*****************************************************************
 * Additional Helper Functions
 ******************************************************************/

/*****************************************************************
 * Function:			void sample(void)
 * Input Variables:	none
 * Output Return:	none
 * Overview:			Use a comment block like this before functions
 ******************************************************************/
void sampleFunction() {
    // Some function that does a specific task
}
