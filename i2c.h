//
//  i2c.h
//  BMP180
//
//  Created by Atakan on 19/08/16.
//  Copyright © 2016 Atakan. All rights reserved.
//

#ifndef i2c_h
#define i2c_h
#include <avr/io.h>

// Master twi transmitter status codes

#define TWI_START_SENT      0x08
#define TWI_R_START_SENT    0x10
#define TWI_SLAVE_W_ACK     0x18
#define TWI_SLAVE_W_NACK    0x20
#define TWI_DATA_SENT_ACK   0x28
#define TWI_DATA_SENT_NACK  0x30
#define TWI_ARBIT_LOST      0x38

// Master twi receiver status codes

#define TWI_SLAVE_R_ACK     0x40
#define TWI_SLAVE_R_NACK    0x48
#define TWI_DATA_RECV_ACK   0x50
#define TWI_DATA_RECV_NACK  0x58

void init_twi(void);
void start_transmission(void);
void end_transmission(void);
void terminate(void);
void send_addr(uint8_t addr);
void send_data(uint8_t data);
uint8_t read_data(short);

uint8_t i2cdebug = 0;
#endif /* i2c_h */
