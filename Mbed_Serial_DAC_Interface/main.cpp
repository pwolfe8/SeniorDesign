/**
 * mbed Serial Relay 
 * @description:  This is intended for relaying serial data from our
 *                audio plugin on pc to the mbed and then uses SPI to control either the
 *                "internal DAC" (the DAC controlling voltages into our configured synth on the FPAA) or the
 *                "external DAC" (the DAC controlling voltages to the external synth control headphone jacks)
 *
 * @author:  Philip Wolfe
 * @contact: pwolfe854@gmail.com
 **/

#include "mbed.h"

//////////////////////////////////user settings///////////////////////////////////
// define debug mode and DAC voltage parameters here
#define DEBUG 0   // turn on debug for print statements to be sent back to pc

// first DAC settings  (internal synth)
float vref_i = 2.5f; // define reference voltage here
float vmax_i = 2.5f;
float vmin_i = 0.0f;

// second DAC settings (external synth which uses x2 multiplier)
float vref_x = 3.3f; // define reference voltage here
float vmax_x = 3.3f; 
float vmin_x = 0.0f;
//////////////////////////////////////////////////////////////////////////////////

// function prototypes
unsigned short clamp(int val, char synth);
void writeToDAC(char dacLetter, char synth, int val);
void updateLEDs(int val, int vmin_8bit, int vmax_8bit);

// mbed module initializations
Serial pc(USBTX, USBRX);    // tx, rx

SPI spi_i(p5, p6, p7);      // for internal synth DAC control
DigitalOut latch_i(p21);    // latches the DAC

SPI spi_x(p11, p12, p13);   // for external synth DAC control
DigitalOut latch_x(p22);    // latches the DAC


DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// main
int main() {
// Setup the spi for 12 bit data, low steady state clock,
// first edge capture, with a 1MHz clock rate
// 12 bits mode 1 (clock 0, polarity 1)
    spi_i.format(12,1); 
    spi_i.frequency(1000000);
    spi_x.format(12,1); 
    spi_x.frequency(1000000);
    
    // start with latches high
    latch_i.write(1);
    latch_x.write(1);
    
    char buffer[6];
    int eightBitVal = 0;
    
    while(1) {
        pc.gets(buffer, 6);
        if(DEBUG){ pc.printf("got '%s'\r\n", buffer); }
        
        // example incoming msg: ai255 means dac a, internal synth(multiplier x1), value 255
        // example incoming msg: hx000 means dac h, external synth(multiplier x2), value 0
        if( (buffer[0]=='a') || (buffer[0]=='b') || (buffer[0]=='c') || (buffer[0]=='d') || (buffer[0]=='e') || (buffer[0]=='f') || (buffer[0]=='g') || (buffer[0]=='h') )
        {
            if( (buffer[1] == 'i') || (buffer[1]=='x') )
            {
                eightBitVal = clamp(atoi(buffer+2), buffer[1]); // grab 8 bit val (0 to 256) and clamp between allowable voltages.
                writeToDAC(buffer[0], buffer[1], eightBitVal);
            }
        } 
    }
}

unsigned short clamp(int val, char synth) {
    // default internal synth DAC control
    int multiplier = 1;
    float vmin = vmin_i;
    float vmax = vmax_i;
    float vref = vref_i;
    
    // if external synth change multiplier, min and max
    if(synth == 'x') {
        //multiplier = 2;
        vmin = vmin_x;
        vmax = vmax_x;
        vref = vref_x;
    }
    
    // clamp min and max within reasonable limits
    vmin = vmin < 0.0f ? 0.0f : vmin;
    vmax = vmax > vref*multiplier ? vref : vmax;
    
    // calculate 8 bit value versions
    int vmin_8bit = vmin/(vref*multiplier) * 255.0f;
    int vmax_8bit = vmax/(vref*multiplier) * 255.0f;
    
    updateLEDs(val, vmin_8bit, vmax_8bit);
    return (unsigned short)(val<vmin_8bit ? vmin_8bit : (val>vmax_8bit ? vmax_8bit : val));
}

void updateLEDs(int val, int vmin_8bit, int vmax_8bit) {
    
    int qVal = (vmax_8bit - vmin_8bit)/4; // quarter value
    
    if( val >= 4*qVal ) {
        led4 = led3 = led2 = led1 = 1;
    }
    else if( val >= 3*qVal ) {
        led4 = 0;
        led3 = led2 = led1 = 1;
    }
    else if( val >= 2*qVal ) {
        led4 = led3 = 0;
        led2 = led1 = 1;
    }
    else if(val >= qVal){
        led4 = led3 = led2 = 0;
        led1 = 1;
    }
    else {
        led4 = led3 = led2 = led1 = 0;
    }
}

//dac letter (a through h), internal(i) or external(x) synth, and uint8 value
// 12 bit message:
//      3 bits DAC letter 000 to 111 for a to h
//      1 bit multiplier (0 for vref*1, and 1 for vref*2)
//      8 bits DAC uint8 value (vout = vref*(dac value/255)*(multiplier + 1) )
// select spi module: external(x) or internal(i) synth control

void writeToDAC(char dacLetter, char synth, int val) {    
    int dacNum = dacLetter - 'a';
    unsigned short writeVal = (dacNum<<9) | (0xFF&val); // see TLC5628CN datasheet
    
    float vref = vref_i;
    int multiplier = 1;
    if(synth == 'x'){
        //writeVal = (0x1<<8) | writeVal; // add the x2 multiplier to writeVal
        spi_x.write(writeVal);
        latch_x.write(0); latch_x.write(1);  // latch the shift buffer on the DAC falling edge
        vref = vref_x;
        //multiplier = 2;
    } else {
        spi_i.write(writeVal);
        latch_i.write(0); latch_i.write(1);  // latch the shift buffer on the DAC falling edge
    }
    
    if(DEBUG){ pc.printf("writing: 0x%x \t", writeVal); }
    if(DEBUG){ pc.printf("DAC %c, synth: %c, val: %d, volt: %1.11f\r\n", dacLetter, synth, val, val/256.0f*vref*multiplier); }
}
