/*


	AS5600.C - описание функций для работы с датчиком AS5600


*/

#include "stm32f1xx_hal.h"
#include "as5600.h"

extern I2C_HandleTypeDef hi2c1;

void AS5600_WriteReg(uint8_t Reg, uint8_t Data)
{
	HAL_I2C_Master_Transmit(&hi2c1,AS5600_ADDR,&Data,1,10);	
	HAL_I2C_Mem_Write(&hi2c1,(AS5600_ADDR << 1),Reg,1,&Data,1,100);
}

uint8_t AS5600_ReadReg(uint8_t Reg)
{
	uint8_t DataRead=0;	
	HAL_I2C_Mem_Read(&hi2c1,(AS5600_ADDR << 1),Reg,1,&DataRead,1,100);
	
	
	return DataRead;
}

uint16_t AS5600_GetAngle()
{
	return (int)((float)(AS5600_ReadReg(ANGLE_L) + (AS5600_ReadReg(ANGLE_H) << 8))/4096*360);	
}


uint16_t AS5600_GetRawAngle()
{
	uint16_t AngleVal=AS5600_ReadReg(RAWANG_L) + (AS5600_ReadReg(RAWANG_H) << 8);
	return AngleVal;	
}

uint8_t AS5600_GetStatus()
{
	return AS5600_ReadReg(STATUS) & 0x38;	
}

void AS5600_SetHystheresis(uint8_t Hyst)
{
	uint8_t TmpConfHigh=AS5600_ReadReg(CONF_H);
	TmpConfHigh |= (HYST_MASK & Hyst);	
	AS5600_WriteReg(CONF_H,TmpConfHigh);
}

void AS5600_SetOutputStage(uint8_t OutStage)
{
	uint8_t TmpConfHigh=AS5600_ReadReg(CONF_H);
	TmpConfHigh |= (OUT_STG_MASK & OutStage);
	AS5600_WriteReg(CONF_H,TmpConfHigh);
}

void AS5600_SetPWMFreq(uint8_t Freq)
{
	uint8_t TmpConfHigh=AS5600_ReadReg(CONF_H);
	TmpConfHigh |= (PWMF_MASK & Freq);
	AS5600_WriteReg(CONF_H,TmpConfHigh);
}
