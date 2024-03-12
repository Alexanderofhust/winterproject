/*
 * sht30.c
 *
 *  Created on: 2024年2月28日
 *      Author: 86135
 */
//#include "MIMXRT1021.h"
#include <stdio.h>
#include "sht30_i2c_drv.h"
#include "stdint.h"
#include "fsl_lpi2c.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#define LPI2C_MASTER_CLOCK_FREQUENCY LPI2C_CLOCK_FREQUENCY


#define EXAMPLE_I2C_MASTER ((LPI2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_BAUDRATE               100000U
#define I2C_DATA_LENGTH            33U
#define    SHT30_ADDR_WRITE    0x44<<1         //10001000
#define    SHT30_ADDR_READ     (0x44<<1)+1     //10001011
#define DELAY 5//单位为微秒

uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
uint8_t g_master_txBuff[I2C_DATA_LENGTH];

/**
 * @brief    向SHT30发送一条指令(16bit)
 * @param    cmd —— SHT30指令（在SHT30_MODE中枚举定义）
 * @retval   无
*/
static unsigned char    SHT30_Send_Cmd(SHT30_CMD cmd)
{
	lpi2c_master_transfer_t *p;
	p=0;
	p->slaveAddress   = SHT30_ADDR_WRITE;
	p->direction      = 0;//write
	p->subaddress     = (uint32_t)0;
	p->subaddressSize = 1;
	p->data           = g_master_rxBuff;
	p->dataSize       = I2C_DATA_LENGTH - 1;
	p->flags          = kLPI2C_TransferDefaultFlag;

    uint8_t cmd_buffer[2];
    cmd_buffer[0] = cmd >> 8;
    cmd_buffer[1] = cmd;
    myi2c_start();
    myi2c_write(cmd);
    myi2c_stop();
   // LPI2C_MasterSend(p,cmd_buffer,2);
  //  return HAL_I2C_Master_Transmit(&hi2c1, SHT30_ADDR_WRITE, (uint8_t* cmd_buffer, 2, 0xFFFF);
    return 0;//need function
}
/**
 * @brief    复位SHT30
 * @param    none
 * @retval    none
*/
void SHT30_reset(void)
{
    SHT30_Send_Cmd(SOFT_RESET_CMD);
   // HAL_Delay(20);
}
/**
 * @brief    初始化SHT30
 * @param    none
 * @retval    无
 * @note    周期测量模式
*/
uint8_t SHT30_Init(void)
{
    return SHT30_Send_Cmd(MEDIUM_2_CMD);
}
/**
 * @brief    从SHT30读取一次数据
 * @param    dat —— 存储读取数据的地址（6个字节数组）
 * @retval    成功 —— 无
*/
uint8_t SHT30_Read_Dat(uint8_t* dat)
{
	lpi2c_master_transfer_t *p2;
	p2=0;
	 p2->slaveAddress   = 0;//slaveaddr is not clear
	    p2->direction      = kLPI2C_Read;
	   p2->subaddress     = (uint32_t)SHT30_ADDR_READ;
	    p2->subaddressSize = 1;
	    p2->data           = g_master_rxBuff;
	   p2->dataSize       = I2C_DATA_LENGTH - 1;
	    p2->flags          = kLPI2C_TransferDefaultFlag;
    SHT30_Send_Cmd(READOUT_FOR_PERIODIC_MODE);
    LPI2C_MasterReceive(p2,dat,6);
   // return HAL_I2C_Master_Receive(&hi2c1, SHT30_ADDR_READ, dat, 6, 0xFFFF);
    return 0;
}
#define CRC8_POLYNOMIAL 0x31

uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value)
{
    uint8_t  remainder;        //余数
    uint8_t  i = 0, j = 0;  //循环变量

    /* 初始化 */
    remainder = initial_value;

    for(j = 0; j < 2;j++)
    {
        remainder ^= message[j];

        /* 从最高位开始依次计算  */
        for (i = 0; i < 8; i++)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1)^CRC8_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /* 返回计算的CRC码 */
    return remainder;
}
/**
 * @brief    将SHT30接收的6个字节数据进行CRC校验，并转换为温度值和湿度值
 * @param    dat  —— 存储接收数据的地址（6个字节数组）
 * @retval    校验成功  —— 返回0
 *             校验失败  —— 返回1，并设置温度值和湿度值为0
*/
uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float* temperature, float* humidity)
{
    uint16_t recv_temperature = 0;
    uint16_t recv_humidity = 0;

    /* 校验温度数据和湿度数据是否接收正确 */
    if(CheckCrc8(dat, 0xFF) != dat[2] || CheckCrc8(&dat[3], 0xFF) != dat[5])
        return 1;

    /* 转换温度数据 */
    recv_temperature = ((uint16_t)dat[0]<<8)|dat[1];
    *temperature = -45 + 175*((float)recv_temperature/65535);

    /* 转换湿度数据 */
    recv_humidity = ((uint16_t)dat[3]<<8)|dat[4];
    *humidity = 100 * ((float)recv_humidity / 65535);

    return 0;
}

void scl(uint8_t value){
	/*
	 * @brief	设置i2c的scl时钟线为指定电平
	 * @param	<uint8_t>要设置的时钟线的电平，取值0(低电平)或1(高电平)
	 * @return	无
	 */
	GPIO2->GDIR |= (1UL << 2);
	GPIO_PinWrite(GPIO2, 2, value);
}

void sda(uint8_t value){
	/*
	 * @brief	设置i2c的sda数据线为指定电平
	 * @param	<uint8_t>要设置的数据线的电平，取值0(低电平)或1(高电平)
	 * @return	无
	 */
	GPIO2->GDIR |= (1UL << 3);
	GPIO_PinWrite(GPIO2, 3, value);
}

uint8_t sda_read(void){
	/*
	 * @brief	读取当前i2c的sda数据线的电平
	 * @param	无
	 * @return	<uint8_t>当前数据线的电平，取值0(低电平)或1(高电平)
	 */
	GPIO2->GDIR |= (1UL << 3);
	GPIO_PinWrite(GPIO2, 3, 0);
	SDK_DelayAtLeastUs(2, SystemCoreClock);
	GPIO2->GDIR &= ~(1UL << 3);
	return GPIO_PinRead(GPIO2, 3);

}

void myi2c_start(void){
	/*
	 * @brief	主机发送i2c起始(Start)信号
	 * @param	无
	 * @return	无
	 */
	scl(1);
	sda(1);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	sda(0);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
}

void myi2c_stop(void){
	/*
	 * @brief	主机发送i2c停止(Stop)信号
	 * @param	无
	 * @return	无
	 */
	scl(1);
	sda(0);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	sda(1);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
}

void myi2c_write(uint8_t data){
	/*
	 * @brief	主机通过i2c发送数据
	 * @param	<uint8_t>要发送的数据
	 * @return	无
	 */
	printf("Prepare to send byte : 0x%02X \n", data);
	scl(0);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	for(uint8_t bit=0x80; bit>0; bit >>= 1){
		if(data & bit){
			sda(1);
		}else{
			sda(0);
		}
		SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
		scl(1);
		SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
		scl(0);
		SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	}
	int idd = 0;
	while(sda_read()){
		if(idd >= 300){
			printf("Software I2C Error : Acknowledgment Error \n");
			break;
		}
		idd++;
	}
	scl(1);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
}

uint8_t myi2c_read(bool hasAck){
	/*
	 * @brief	主机通过i2c读取数据
	 * @param	<bool>是否发送ack信号，为true发送ack，为false发送nack
	 * @return	读取的数据
	 */
	uint8_t data = 0;
	GPIO2->GDIR |= (1UL << 3);
	GPIO_PinWrite(GPIO2, 3, 0);
	SDK_DelayAtLeastUs(1, SystemCoreClock);
	GPIO2->GDIR &= ~(1UL << 3);
	SDK_DelayAtLeastUs(3, SystemCoreClock);


	for(int i=0; i<8; i++){
		data <<= 1;
		scl(0);
		int idd = 0;
		uint8_t i0 = 0;
		uint8_t i1 = 1;
		i0 = GPIO_PinRead(GPIO2, 3);
		while(idd<5){
			i1 = GPIO_PinRead(GPIO2, 3);
			if(i0 == 1 && i1 == 0){
				data |= 0;
				break;
			}else if(i0 == 0 && i1 == 1){
				data |= 1;
				break;
			}
			i0 = i1;
			idd++;
		}
		scl(1);
		SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	}
	SDK_DelayAtLeastUs(1, SystemCoreClock);
	scl(0);
	sda(1);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	if(!hasAck){
		sda(0);
	}
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);
	scl(1);
	SDK_DelayAtLeastUs(DELAY, SystemCoreClock);

	return data;
}


