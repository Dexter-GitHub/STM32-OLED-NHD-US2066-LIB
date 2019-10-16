#ifndef __US2066_H__
#define __US2066_H__
#ifdef __cplusplus
extern "C" {
#endif

/* @brief NHD-0420CW-AW3 Spec */
#define ROW_N                       4

/* @brief I2C Interface Info */
#define I2C_TX_TIME_OUT             100
#define SLAVE2W                     0x3CU   /* @brief 0,1,1,1,1,0,SA0,R/W# */
#define DATA_BYTE_COMMAND           0x00    /* @brief Control Byte : Co(Continuation bit) = 0, D/C#(Data/Command Selection bit = 0 */
#define DATA_BYTE_DATA              0x40    /* @brief Control Byte : Co(Continuation bit) = 0, D/C#(Data/Command Selection bit = 1 */

/* @brief Fundamental Command Set */
#define CLEAR_DISPLAY               0x01U   /* @brief Clear Display: Write "20H" to DDRAM and set DDRAM address to "00H" from AC */
#define SET_DDRAM_ADDRESS           0x80U   /* @brief Set DDRAM address in address counter */

/* @brief Extended Command Set */
#define FUNCTION_SELECTION_A        0x71U   /* @brief Function Selection A */
#define FUNCTION_SELECTION_B        0x72U   /* @brief Function Selection B */
#define FUNCTION_SELECTION_C        0xDCU   /* @brief Function Selection C */
#define OLED_CHARACTERIZATION       0x78U   /* @brief SD=0b: OLED command set is disabled (POR) */
#define OLED_CHARACTERIZATION_SD    0x79U   /* @brief SD=1b: OLED command set is enabled        */

/* @brief Function select A */
#define DISABLE_INTERNAL_VDD        0x00U   /* @brief Disable internal Vdd regulator at 5V I/O application mode */
#define ENABLE_INTERNAL_VDD         0x5CU   /* @brief Enable internal Vdd regulator at 5V I/O application mode  */

/* @brief RE=0 Set display/cusor/blink ON/OFF */
#define DISPLAY_CTRL                0x08U   /* @brief D = 0:display OFF, C = 0:cusor OFF, B = 0:blink OFF */
#define DISPLAY_ONOFF_CONTROL       0x04U   /* @brief D = 1: display ON     */
#define CUSOR_ONOFF_CONTROL         0x02U   /* @brief C = 1: cusor ON       */
#define CUSOR_BLINK_ONOFF_CONTROL   0x01U   /* @brief B = 1: cusor blink ON */

/* @brief OLED Command Set */
#define CONTRAST_CONTROL            0x81U   /* @brief Set Contrast Control */
#define DISPLAY_SET                 0xD5U   /* @brief Set Display Clock Divide Ratio/Oscillator Frequency */
#define PHASE_LENGTH                0xD9U   /* @brief Set Phase Length */
#define SEG_PINS_HARDWARE_CONFIG    0xDAU   /* @brief Set SEG Pins Hardware Configuration */
#define DESELECT_LEVEL              0xDBU   /* Set Vcomh Deselect Level */

/* @brief Contrast Control Command */
#define CONTRAST_VALUE              0x7FU   /* @brief contrast=127 (default value) */

/* @brief Phase Length Command */
#define PHASE2                      0xF0U   /* PHASE2 = 15 */
#define PHASE1                      0x01U   /* PHASE1 = 1  */

/* @brief Deselcet Level Command */
#define VCC_0_65                    0x00U   /* ~0.65 x Vcc */
#define VCC_0_71                    0x10U   /* ~0.71 x Vcc */
#define VCC_0_77                    0x20U   /* ~0.77 x Vcc */
#define VCC_0_83                    0x30U   /* ~0.83 x Vcc */
#define VCC_1                       0x40U   /* 1 x Vcc     */

/* @brief Extended Function Set */
#define FUNCTION_SET                0x08U   /* @brief FW = 0: 5-dot font width | B/W = 0: black/white inverting of cursor disable | NW = 0: 1-line or 2-line display mode */
#define FUNCTION_SET_NW             0x01U   /* @brief NW = 1: 3-line or 4-line display mode */
#define FUNCTION_SET_BW             0x02U   /* @brief B/W = 1: black/white inverting of cusor enable */
#define FUNCTION_SET_FW             0x04U   /* @brief FW = 1: 6-dot font width */

/* @brief Entry Mode Set (R=1 )*/
#define ENTRY_MODE_SET              0x04U   /* @brief BDC = 0: COM31->COM0, BDS = 0: SEG99->SEG0 */
#define ENTRY_MODE_BDC              0x02U   /* @brief BDC(Data shift direction of common) = 1: COM0->COM31  */
#define ENTRY_MODE_BDS              0x01U   /* @btief BDS(Data shift direction of segment) = 1: SEG0->SEG99 */

/* @brief Extended Command Set Data */
#define CLOCK_FREQUENCY             0x70U   /* @brief ratio = 1, frequency = 7 (default values) */

/* @brief OPR[D1:D0]: Select the character no. of character generator */
#define CGROM_240_CGRAM_8           0x00U   /* @brief CGROM = 240, CGRAM = 8 */
#define CGROM_248_CGRAM_8           0x01U   /* @brief CGROM = 248, CGRAM = 8 */
#define CGROM_250_CGRAM_6           0x02U   /* @brief CGROM = 250, CGRAM = 6 */
#define CGROM_256_CGRAM_0           0x03U   /* @brief CGROM = 256, CGRAM = 0 */

/* @brief ROM[D3:D2]: Select character ROM */
#define ROM_A                       0x00U   /* @brief ROM = A */
#define ROM_B                       0x04U   /* @brief ROM = B */
#define ROM_C                       0x08U   /* @brief ROM = C */
#define ROM_INVALID                 0x0CU   /* @brief ROM = Invalid */

/* OLED Command Set Configuration */
#define ALTERNATIVE                 0x10U   /* @brief Alternative (odd/even) SEG pin configuration */
#define SEG_LEFT_RIGHT_REMAP        0x20U   /* @brief Enable SEG Left/Right remap */

#pragma pack(1)
/**
@struct _ST_FUCTION_SET
@brief  Function set register 
*/
struct _ST_FUCTION_SET {
    unsigned char D0:1;     /* @var REV:Reverse enable bit (1 = enable, 0 = nomal)            */
    unsigned char D1:1;     /* @var RE:Extended function register enable = 1                  */
    unsigned char D2:1;     /* @var BE:CGRAM data blink enable bit                            */
    unsigned char D3:1;     /* @var N:Display line number control bit (0 = 1-line, 1 = 2-line */
    unsigned char D4:1;     /* @var RESERVED */
    unsigned char D5:1;     /* @var 1        */
    unsigned char D6:1;     /* @var RESERVED */
    unsigned char D7:1;     /* @var RESERVED */
};
#pragma pack(4)

typedef union _FUCTION_SET {
    struct _ST_FUCTION_SET reg;
    unsigned char value;
}FUCTION_SET;

void NHD_US2066Init(void);
void NHD_US2066DisplayOn(void);
void NHD_US2066DisplayOff(void);
void NHD_US2066DisplayClear(void);

#ifdef __cplusplus
}
#endif
#endif /* __US2066_H__ */

