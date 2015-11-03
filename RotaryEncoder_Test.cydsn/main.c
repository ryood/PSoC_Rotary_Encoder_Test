/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

char strBuff[80];
    
//------------------------------------------------//
// Rotary Encoder
//
//------------------------------------------------//
// 戻り値: ロータリーエンコーダーの回転方向
//         0:変化なし 1:時計回り -1:反時計回り
//

int readRE()
{
    static uint8_t index;
    uint8_t rd;
    int retval = 0;
    
    rd = Pin_RE_Read();
    /*
    sprintf(strBuff, "%d\t", rd);
    UART_UartPutString(strBuff);
    */
    
    index = (index << 2) | rd;
	index &= 0b1111;

	switch (index) {
	// 時計回り
	case 0b0001:	// 00 -> 01
	case 0b1110:	// 11 -> 10
	    retval = 1;
	    break;
	// 反時計回り
	case 0b0010:	// 00 -> 10
	case 0b1101:	// 11 -> 01
	    retval = -1;
	    break;
    }
    return retval;
}

int main()
{

    int rv;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_UartPutString("Rotary Encoder Test.\r\n");

    for(;;)
    {
        rv = readRE();
        //rv = Pin_RE_Read();
        if (rv != 0) {
            sprintf(strBuff, "%d\r\n", rv);
            UART_UartPutString(strBuff);
        }
        
        //CyDelay(10);
    }
}

/* [] END OF FILE */
