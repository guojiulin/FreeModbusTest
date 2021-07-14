/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

#include "port.h"
/* ----------------------- STM32 includes ----------------------------------*/
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"
#include "usart.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
//static void prvvUARTTxReadyISR( void );
//static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
	if (xRxEnable)															
			{
				__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);	
			}
		else
			{
				__HAL_UART_DISABLE_IT(&huart1,UART_IT_RXNE);
			}
		if (xTxEnable)
			{
				__HAL_UART_ENABLE_IT(&huart1,UART_IT_TXE);
			}
		else
			{
				__HAL_UART_DISABLE_IT(&huart1,UART_IT_TXE);
			}
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	
  //GPIO_InitTypeDef  GPIO_InitStructure;
//	UART_HandleTypeDef UART2_Handler;
	
//		(void)ucPORT;  //���޸Ĵ��ں�
//	(void)ucDataBits;  //���޸�����λ����
//	(void)eParity;  //���޸ļ����ʽ

//	__HAL_RCC_GPIOA_IS_CLK_ENABLED();
//	__HAL_RCC_USART2_IS_CLK_ENABLED();
	
	//
	//�ܽŸ���
	//
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	//
	//���͹ܽ� PA.02
	//���չܽ� PA.03
	//
//	GPIO_InitStructure.Pin   = GPIO_PIN_2 | GPIO_PIN_3;
//	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;;
//	GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStructure.Pull  = GPIO_PULLUP;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//
	//���ô��ڲ���
	//
//	UART2_Handler.Instance = USART2;
//	UART2_Handler.Init.BaudRate    = 115200;  //ֻ�޸Ĳ�����
//	UART2_Handler.Init.WordLength  = UART_WORDLENGTH_8B;
//	UART2_Handler.Init.StopBits    = UART_STOPBITS_1;
//	UART2_Handler.Init.Parity      = UART_PARITY_NONE;
//	UART2_Handler.Init.HwFlowCtl   = HAL_UART_ERROR_NONE;
//	UART2_Handler.Init.Mode        = UART_MODE_TX_RX;
//	HAL_UART_Init(&UART2_Handler);

//	HAL_NVIC_SetPriority(USART2_IRQn,0,1);
//	HAL_NVIC_EnableIRQ(USART2_IRQn);
	return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	if(HAL_UART_Transmit(&huart1 ,(uint8_t *)&ucByte,1,0x01) != HAL_OK )
	{
		return FALSE ;
	}
	else
	{
		return TRUE;
	}
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
	if(HAL_UART_Receive (&huart1 ,(uint8_t *)pucByte,1,0x01) != HAL_OK )
	{
		return FALSE ;
	}
	else
	{
		return TRUE;
	}
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
//static 
	void prvvUARTTxReadyISR( void )
{
    pxMBFrameCBTransmitterEmpty(  );
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
//static 
	void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}

void USART1_IRQHandler(void)
{
	
	
if(__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE)!= RESET) 
	{
		prvvUARTRxISR();//�����ж�
	}

	if(__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_TXE)!= RESET) 
	{
		prvvUARTTxReadyISR();//��������ж�
	}
	//HAL_NVIC_ClearPendingIRQ(USART2_IRQn);
               
}
