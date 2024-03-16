/*
 * sht30.h
 *
 *  Created on: 2024年2月28日
 *      Author: 86135
 */

#ifndef SHT30_H_
#define SHT30_H_

static uint8_t    SHT30_Send_Cmd(SHT30_CMD cmd);
void SHT30_reset(void);
uint8_t SHT30_Init(void);
uint8_t SHT30_Read_Dat(uint8_t* dat);
#define CRC8_POLYNOMIAL 0x31
uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value);
uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float* temperature, float* humidity);

#endif /* SHT30_H_ */
