//
//  i2c.c
//  BMP180
//
//  Created by Atakan on 19/08/16.
//  Copyright © 2016 Atakan. All rights reserved.
//

#include "i2c.h"
#include <stdio.h>

void init_twi() {
    
    // SCL Freq = CPU_CLK / (16 + 2 x (TWBR).(PrescalerValue))
    // TWI clock frequency set 100.00kHz to work @8MHz Cpu Frequency
    TWSR = 0x00; // Prescaler 1
    TWBR = 0x20; // Decimal 32
}

void start_transmission() {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    if (i2cdebug)
        printf("[Info]\tStart condition send & waiting for ack... \n");
    while(!(TWCR & (1<<TWINT)));
    while((TWSR & 0xF8)!= TWI_START_SENT);
    if (i2cdebug)
        printf("[Success]\tAck has been received.\n");
}

void end_transmission() {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    if (i2cdebug)
        printf("[Info]\tTransmission has been ended.\n");
}

void send_addr(uint8_t addr) {
    TWDR = addr;
    TWCR = (1<<TWINT) | (1<<TWEN);
    if (i2cdebug)
        printf("[Info]\tAddress %#02x has been sent. Waiting for ack... \n", addr);
    while(!(TWCR & (1<<TWINT)));
    if (TWI_SLAVE_W_ACK != (TWSR & 0xF8) && TWI_SLAVE_R_ACK != (TWSR & 0xF8))
        terminate();
    else if (i2cdebug)
        printf("[Success]\tAck has been received. \n");
    
}

void send_data(uint8_t data) {
    TWDR = data;
    if (i2cdebug)
        printf("[Info]\tSending data (%#02x).\n", data);
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    if (i2cdebug)
        printf("[Success]\tData sent. Waiting for ack... \n");
    if (TWI_DATA_SENT_ACK != (TWSR & 0xF8))
        terminate();
    else if (i2cdebug)
        printf("[Success]\tAck has been received.\n");
    
}

uint8_t read_data(short ack) {
    if (i2cdebug)
        printf("[Info]\tReading data...\n");
    if (!ack)
        TWCR = (1<<TWINT) | (1<<TWEN);
    else
        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    
    while(!(TWCR & (1<<TWINT)));
    //if (TWI_DATA_RECV_ACK != (TWSR & 0xF8))
        //terminate();
    
    if (i2cdebug)
        printf("[Success]\tData (%#02x) has been read successfuly.\n", TWDR);
    return TWDR;
    
}

void restart(void)
{
    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // wait till restart condition is transmitted
    while((TWSR & 0xF8)!= TWI_R_START_SENT); // Check for the acknoledgement
}

void debug(short cond) {
    i2cdebug = cond;
}
void terminate() {
    //printf("[Error]\tThere is an error occured while transmission. (NACK)\n");
}
