#ifndef __US2066_H__
#define __US2066_H__
#ifdef __cplusplus
extern "C" {
#endif

/* I2C Interface Info */
#define SLAVE2W                 0x3CU   /* 0,1,1,1,1,0,SA0,R/W# */
#define DATA_BYTE_COMMAND       0x00    /* Control Byte : Co(Continuation bit) = 0, D/C#(Data/Command Selection bit = 0 */
#define DATA_BYTE_DATA          0x40    /* Control Byte : Co(Continuation bit) = 0, D/C#(Data/Command Selection bit = 1 */

#define I2C_TX_TIME_OUT         100

#define CMD_DATA_SIZE   3

#define START_BYTE      0xF8U
#define START_BYTE_DC   0xFAU

#define FUNCTION_SELECTION_A    0x71U
#define FUNCTION_SELECTION_B    0x72U

#pragma pack(1)

struct _ST_FUCTION_SET {
    unsigned char D0:1;     /* REV:Reverse enable bit (1 = enable, 0 = nomal)            */
    unsigned char D1:1;     /* RE:Extended function register enable = 1                  */
    unsigned char D2:1;     /* BE:CGRAM data blink enable bit                            */
    unsigned char D3:1;     /* N:Display line number control bit (0 = 1-line, 1 = 2-line */
    unsigned char D4:1;     /* RESERVED */
    unsigned char D5:1;     /* 1        */
    unsigned char D6:1;     /* RESERVED */
    unsigned char D7:1;     /* RESERVED */
};

#pragma pack(4)

typedef union _FUCTION_SET {
    struct _ST_FUCTION_SET reg;
    unsigned char value;
}FUCTION_SET;

void NHD_US2600Init(void);
void NHD_US2600Test(void);

#ifdef __cplusplus
}
#endif
#endif /* __US2066_H__ */

