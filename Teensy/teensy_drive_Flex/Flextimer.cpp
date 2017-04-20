//
//  Flextimer.cpp
//  
//
//  Created by Jens de Hoog on 09/04/2017.
//
//

#include "Flextimer.hpp"
#include "Arduino.h"

Flextimer::Flextimer() {
    
}

void Flextimer::initialize(int modulus) {
    
    //configure Flextimer 1
    //set write-protect disable (WPDIS) bit to modify other registers
    //FAULTIE=0, FAULTM=00, CAPTEST=0, PWMSYNC=0, WPDIS=1, INIT=0, FTMEN=1(no restriction FTM)
    FTM1_MODE = 0x05;
    
    //set status/control to zero = disable all internal clock sources
    FTM1_SC = 0x00;
    
    //reset count to zero
    FTM1_CNT = 0x0000;
    
    //max modulus = 499 (gives count = 500 on roll-over)
    FTM1_MOD = modulus;
    
    // CHF=0, CHIE=0 (disable interrupt, use software polling), MSB=0 MSA=0, ELSB=0 ELSA=1 (input capture - rising edge), 0, DMA=0
    FTM1_C0SC = 0x04;
    
    //enable FTM1 interrupt within NVIC table
    //NVIC_ENABLE_IRQ(IRQ_FTM1);
    
    //configure Teensy port pins
    PORTA_PCR12 |= 0x703; //MUX = alternative function 7 on Chip Pin 28 (FTM1_QD_PHA) = Teensy Pin 3
    PORTA_PCR13 |= 0x700; //MUX = alternative function 7 on Chip Pin 29 (FTM1_QD_PHB) = Teensy Pin 4
    
    //set flextimer quad decode mode and enable overflow interrupt
    FTM1_QDCTRL = 0x0F; //see section 36.3.21 of ref manual for details
    FTM1_SC = 0x40; // (Note – FTM1_SC [TOF=0 TOIE=1 CPWMS=0 CLKS=00 (internal clocks disabled) PS=000 [no prescale divide])

}

void Flextimer::resetCounter() {
    FTM1_CNT = 0x0000;
}

void Flextimer::trapCount() {
    counter = FTM1_CNT;
}

double Flextimer::getCount() {
    return counter;
}
