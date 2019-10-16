/******************************************************
 * @file us2066.c
 * @date 2019/10/14
 * @author ChangYoub Lim (mystyle1057@gmail.com)
 * @version 1.9
 * @brief OLED DISPLAY NHD-0420CW US2066 Driver 
 ******************************************************/
#include "./Module/us2066.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

static void command(uint8_t);
static void data(uint8_t);

void NHD_US2066Init(void)
{
    FUCTION_SET funcSet;        
    
    if(ROW_N == 2 || ROW_N == 4)
        funcSet.reg.D3 = 1;             /* @brief N = 1 Display 2/4 lines */
    else
        funcSet.reg.D3 = 0;             /* @brief N = 0 Display 1/3 lines */
    funcSet.reg.D5 = 1;                 /* @brief D5 = 1 */ 
    
    funcSet.reg.D1 = 1;                 /* @brief RE = 1 */      
    command(funcSet.value);             /* @brief Function set : extended command set (RE=1)   */
    command(FUNCTION_SELECTION_A);      /* @brief Function selection A                         */ 
    data(DISABLE_INTERNAL_VDD);         /* @brief Disablle internal Vdd regulator at 5V I/O mode (for disable 2.8V I/O) */

    funcSet.reg.D1 = 0;                 /* @brief RE = 0 */
    command(funcSet.value);             /* @brief Function set : fundamental command set (RE=0) (exit from extended command set) */    
    command(DISPLAY_CTRL);              /* @brief Display OFF, Cusor OFF, Blink OFF (default values) */
    
    funcSet.reg.D1 = 1;                 /* @brief RE = 1 */
    command(funcSet.value);
    command(OLED_CHARACTERIZATION_SD);  /* @brief OLED command set enabled (SD=1) */
    command(DISPLAY_SET);               /* @brief Set display clock divide ratio/oscillator frequency */
    command(CLOCK_FREQUENCY);           /* @brief ratio=1, frequency=7 (default values) */

    command(OLED_CHARACTERIZATION);     /* @brief OLED characterization: OLED command set disable (SD=0) (exit from OLED command set) */
    if(ROW_N > 2)
        command(FUNCTION_SET | FUNCTION_SET_NW);    /* @brief Extended function set (RE=1): 5-dot font B/W inverting disabled, 3/4 lines */
    else
        command(FUNCTION_SET);                      /* @brief Extended function set (RE=1): 5-dot font B/W inverting disabled, 1/2 lines */

    command(ENTRY_MODE_SET | ENTRY_MODE_BDC);       /* @brief Entry Mode set (RE=1): COM0->COM31, SEG99->SEG0 */
    
    command(FUNCTION_SELECTION_B);      /* @brief Function selelction B */            
    data(ROM_C | CGROM_250_CGRAM_6);    /* @brief ROM/CGRAM selection: ROM C, CGROM=250, CGRAM=6 */
    
    command(OLED_CHARACTERIZATION_SD);  /* @brief OLED characterization: OLED command set enabled (SD=1) */
    command(SEG_PINS_HARDWARE_CONFIG);  /* @brief Set SEG pins hardware configuration */
    command(ALTERNATIVE);

    command(FUNCTION_SELECTION_C);      /* @brief Function selelction C */            
    command(0x00);                      /* @brief Internal VSL, represents GPIO pin HiZ, input disabled */

    command(CONTRAST_CONTROL);          /* @brief Set contrast control */
    command(CONTRAST_VALUE);            /* @brief contrast = 127 */

    command(PHASE_LENGTH);              /* @brief Set phase length: */
    command(PHASE2|PHASE1);             /* @brief phase2=15, phase1=1 (default: 0x78) */

    command(DESELECT_LEVEL);            /* @brief Set VCOMH deselect level: */
    command(VCC_1);                     /* @brief VCOMH deselect level=1 x Vcc (default: 0x20=0,77 x Vcc) */

    command(OLED_CHARACTERIZATION);     /* @brief OLED characterization: OLED command set disabled (SD=0) (exit from OLED command set) */

    funcSet.reg.D1 = 0;                 /* @brief RE = 0 */
    command(funcSet.value);             /* @brief Function set : fundamental command set (RE=0) (exit from extended command set) */  

    command(CLEAR_DISPLAY);             /* @brief clear display */
    HAL_Delay(2);

    command(SET_DDRAM_ADDRESS);                     /* @brief set DDRAM adddress to 0x00 */
    command(DISPLAY_CTRL | DISPLAY_ONOFF_CONTROL);  /* @brief display ON */

    HAL_Delay(100);
    NHD_US2066Output();
    return ;
}

uint8_t text[ROW_N][COLUMN_N+1] = {"1-Newhaven Display--",
                            	   "2-------Test--------",
                            	   "3-16/20-Characters--",
                            	   "4!@#$%^&*()_+{}[]<>?"};
void NHD_US2066Output(void)
{
    NHD_US2066DisplayClear();
    HAL_Delay(2);

    for(uint32_t row = 0; row < ROW_N; row++)
    {
        NHD_US2066LineFeed((NHD_LineFeedTypeDef)row);
        for(uint32_t column = 0; column < COLUMN_N; column++)
        {
            data((uint8_t)text[row][column]);
        }
    }

    return ;
}

void NHD_US2066DisplayOn(void)
{
    command(DISPLAY_CTRL | DISPLAY_ONOFF_CONTROL | CUSOR_ONOFF_CONTROL | CUSOR_BLINK_ONOFF_CONTROL);    
    return ;
}

void NHD_US2066DisplayOff(void)
{
    command(DISPLAY_CTRL);
    return ;
}

void NHD_US2066DisplayClear(void)
{
    command(CLEAR_DISPLAY);
    return ;
}

void NHD_US2066LineFeed(NHD_LineFeedTypeDef num)
{
    switch(num)
    {
        case LINE_1:
            command(SET_DDRAM_ADDRESS);
            break;

        case LINE_2:
            command(SET_DDRAM_ADDRESS | DDRAM_2LINE_FEED);
            break;

        case LINE_3:
            command(SET_DDRAM_ADDRESS | DDRAM_3LINE_FEED);            
            break;

        case LINE_4:
            command(SET_DDRAM_ADDRESS | DDRAM_4LINE_FEED);            
            break;
            
        default : break;
    }
    
    return ;
}

static void command(uint8_t cmd)
{
    uint8_t i2cBuffer[2] = {0,};

    i2cBuffer[0] = DATA_BYTE_COMMAND;
    i2cBuffer[1] = cmd;
    
    printf("OLED NHD command > 0x%02X\r\n", i2cBuffer[1]);
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE2W, i2cBuffer, sizeof(i2cBuffer), I2C_TX_TIME_OUT);
    
    return ;
}

static void data(uint8_t data)
{
    uint8_t i2cBuffer[2] = {0,};
    
    i2cBuffer[0] = DATA_BYTE_DATA;
    i2cBuffer[1] = data;
    
    printf("OLED NHD data > 0x%02X\r\n", i2cBuffer[1]);
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE2W, i2cBuffer, sizeof(i2cBuffer), I2C_TX_TIME_OUT);
    
    return ;
}

