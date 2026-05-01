#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char *hex2byte_arr(char *puchMsg);
void print_dec_and_hex(int crcDec);
unsigned short crc_ccitt_xmodem(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short crc16(unsigned char *puchMsg, unsigned int usDataLen);
unsigned int MathCrc16(unsigned  char  *ptr, unsigned  int  len);

/**
 * C语言无类型指针（）
 * @return
 */
int main()
{
	// 682E003001010099999999999925080400000200150099999999999989861124210003270233006C9DA56E => 0FE5
    char *hex = "682E003001010099999999999925080400000200150099999999999989861124210003270233006C9DA56E";
    unsigned char *byte_arr = hex2byte_arr(hex);
    int len = strlen(hex) / 2;

	unsigned short crc_dec = crc16(byte_arr,len);
	print_dec_and_hex(crc_dec);

	crc_dec = MathCrc16(byte_arr,len);
	print_dec_and_hex(crc_dec);
	return 0;
}

/**
 * 十六进制字符串转字节数组
 * @param puchMsg	要进行crc计算的字符串
 */ 
unsigned char *hex2byte_arr(char *puchMsg)
{
	int len = strlen(puchMsg);
	// 分配足够的空间存储字节数组
	unsigned char *bytes = malloc(len / 2);
	for(int i = 0; i < len; i = i + 2)
	{
		// 把十六进制字符每两位组成一个字符串
		char hexbuff[3];
		hexbuff[0] = puchMsg[i];
		hexbuff[1] = puchMsg[i+1];
		hexbuff[2] = '\0';
		// 将每两个字符转换为字节
		bytes[i/2] = (unsigned char)strtol(hexbuff, NULL, 16);
	}
	return bytes;
}

/**
 * 打印十进制和十六进制crc的值
 * @param crcDec 十进制crc的值
 */ 
void print_dec_and_hex(int crcDec)
{
	printf("crc  十进制 = %d\n",crcDec);
	char crcHex[50];
    sprintf(crcHex, "%x", crcDec);
    printf("crc十六进制 = %s\n", crcHex);
    printf("---------------------\n");
}

/**
 * crc_ccitt_xmodem
 * @param puchMsg 要进行crc计算的字符串
 * @param usDataLen 要进行crc计算的字符串的长度
 */ 
unsigned short crc_ccitt_xmodem(unsigned char *puchMsg, unsigned int usDataLen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;

	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for (int i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}

/**
 * crc16
 * @param puchMsg 要进行crc计算的字符串
 * @param usDataLen 要进行crc计算的字符串的长度
 */
unsigned short crc16(unsigned char *puchMsg, unsigned int usDataLen)
{
    unsigned short wCRCin = 0x0000; unsigned short wCPoly = 0x1021;
    unsigned char wChar = 0;
    while (usDataLen--)
    {
        wChar = *(puchMsg++); wCRCin ^= (wChar << 8); for(int i = 0; i < 8; i++)
        {
            if(wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly; else
                wCRCin = wCRCin << 1;
        }
    }
    return (wCRCin) ;
}


unsigned int MathCrc16(unsigned  char  *ptr, unsigned  int  len)
{
	unsigned int crc_val=0xffff;
	unsigned int tmp;
	unsigned int i;

	while (len > 0)

	{
		crc_val ^= *ptr;
		ptr++;
		for(i = 0; i < 8; i++)
		{
			tmp = crc_val;
			crc_val >>= 1;		// CRC校验字节的右移，最低位到C，最高位补0
			if ((tmp & 0x01)==1)crc_val ^= 0xA001;//采用的多项式是：0xA001
		}
		len--;
	}
	return(crc_val);
}
