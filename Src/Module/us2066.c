#include "./Module/us2066.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

static void command(uint8_t);
static void data(uint8_t);

void NHD_US2600Test(void)
{    
    NHD_US2600Init();
    return ;
}

void NHD_US2600Init(void)
{
    
    return ;
}

static void command(uint8_t cmd)
{
    uint8_t i2cBuffer[2] = {0,};

    i2cBuffer[0] = DATA_BYTE_COMMAND;
    i2cBuffer[1] = cmd;
    
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE2W, i2cBuffer, sizeof(i2cBuffer), I2C_TX_TIME_OUT);
    
    return ;
}

static void data(uint8_t data)
{
    uint8_t i2cBuffer[2] = {0,};
    
    i2cBuffer[0] = DATA_BYTE_DATA;
    i2cBuffer[1] = data;

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE2W, i2cBuffer, sizeof(i2cBuffer), I2C_TX_TIME_OUT);
    
    return ;
}

#ifdef SPI_VER
#define VERSION_01

extern SPI_HandleTypeDef hspi1;

static void command(uint8_t);
static void setBuffer(uint8_t *, uint8_t *, uint8_t);

void NHD_US2600Test(void)
{    
    NHD_US2600Init();
    return ;
}

void NHD_US2600Init(void)
{
    FUCTION_SET funcSet;
    
    funcSet.reg.D1 = 1;
    funcSet.reg.D3 = 1;
    funcSet.reg.D5 = 1;
    
    printf("Extended function register = 0x%x\r\n", funcSet.value);
    
    command(funcSet.value);
    command(FUNCTION_SELECTION_A);
    
    return ;
}

static void command(uint8_t cmd)
{
    uint8_t txData[CMD_DATA_SIZE];
    uint8_t rxData[CMD_DATA_SIZE];
    uint8_t lowerData = 0;
    uint8_t upperData = 0;

    setBuffer(&lowerData, &upperData, cmd);
    txData[0] = START_BYTE;
    txData[1] = lowerData;
    txData[2] = upperData;
    
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);           
    HAL_SPI_TransmitReceive(&hspi1, txData, rxData, sizeof(txData), 100);    
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
    
    return ;
}

#ifdef VERSION_01 
static void setBuffer(uint8_t *lData, uint8_t *uData, uint8_t cmd)
{        
    *lData = ((cmd >> 4) | (cmd << 4)) & 0x0F;
    *uData = ((cmd >> 4) | (cmd << 4)) & 0xF0;

    return ;
}
#else
static void setBuffer(uint8_t *lData, uint8_t *uData, uint8_t cmd)
{        
    for(int8_t i = 7; i >= 4; i--)
    {
        *lData |= (cmd & 0x01) << i;
        cmd = cmd >> 1;        
    }

    for(int8_t i = 7; i >= 4; i--)
    {
        *uData |= (cmd & 0x01) << i;
        cmd = cmd >> 1;        
    }
    
    return ;
}
#endif
#endif

