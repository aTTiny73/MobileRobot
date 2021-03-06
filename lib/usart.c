#include "usart.h"
#include "print.h"

/* Memory organization BUFFER */
/* |valid_command|circular buffer| */
/*   64 Byte       448 Byte */

 uint8_t g_usart2_rx_buffer[USART2_BUFFER_SIZE] = {0};
 uint16_t g_usart2_tx_wcnt = MAX_COMMAND_LENGHT + 1;
 uint16_t g_usart2_tx_rcnt = MAX_COMMAND_LENGHT + 1;
 uint16_t g_usart2_tx_cmdcnt = 0; //for creating valid command string & enables backspace


 uint16_t g_usart2_widx = 0;
 uint16_t g_usart2_ridx = ((USART2_BUFFER_SIZE) - 1);

void usart2_init(uint16_t baudrate)/*{{{*/
{
  //enable clock for USART
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  //enable clock for Tx and Rx pins
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  GPIOA->CRL &= ~(GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF2_1 |
      GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF3_1);
  GPIOA->CRL |= (GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1); //TX(alt - push_pull - 50mhz)
  GPIOA->CRL |= (GPIO_CRL_CNF3_0); //RX(floating input)

  //USART CONFIGURATION:
  //  - 8 bit data
  //  - 1 stop bit
  //  - no polarity bit
  USART2->BRR = baudrate;
  USART2->CR1 &= ~(USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE);
  USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE;
  NVIC_EnableIRQ(USART2_IRQn);
}/*}}}*/
void usart2_tx_byte(uint8_t data)/*{{{*/
{
  while (!(USART2->SR & USART_SR_TC))
  {
    //wait until previus transfer is complete
  }
  USART2->DR = data;
}/*}}}*/
uint8_t usart2_rx_byte(void)/*{{{*/
{

  while (!(USART2->SR & USART_SR_RXNE))
  {
    // waitin to receive data
  }
  return USART2->DR;
}/*}}}*/

// void usart2_irq_enable(void)/*{{{*/
// {
//   USART2->CR1 &= ~(USART_CR1_UE);
//   NVIC_EnableIRQ(USART2_IRQn);
//   USART2->CR1 |= (USART_CR1_UE)|(USART_CR1_RE)|(USART_CR1_RXNEIE);

// }/*}}}*/
void usart2_irq_disable(void)/*{{{*/
{
  USART2->CR1 &= ~( (USART_CR1_UE) | (USART_CR1_RXNEIE)  );
  NVIC_DisableIRQ(USART2_IRQn);
  USART2->CR1 |= (USART_CR1_UE);

}/*}}}*/




// void USART2_IRQHandler(void)
// {
//     //dataReady='0';
// 	if(USART2->SR&(USART_SR_RXNE))
// 	{
// 		g_usart2_buffer[g_usart2_widx] = USART2->DR;
// 		g_usart2_widx++;
// 		if(USART2->DR == '\r' || USART2->DR == '\n')
// 		{
// 			g_usart2_buffer[g_usart2_widx]=0;
// 			g_usart2_widx = 0;
// 		//	dataReady='1';
// 		}else if(g_usart2_widx >= (USART2_BUFFER_SIZE)){
// 			g_usart2_widx = 0;
// 		}
// 	}
	
//   print("%c",USART2->DR);
// }

uint8_t * usart2_read_rx_buffer(void)/*{{{*/
{
  volatile  uint8_t data = 0;
  if((g_usart2_tx_cmdcnt == 0) && (*g_usart2_rx_buffer != '\n'))
  {
    *g_usart2_rx_buffer = '\n';
    print("> ");
  }
  if(g_usart2_tx_rcnt != g_usart2_tx_wcnt) // chech if new data is available
  {
    data = g_usart2_rx_buffer[g_usart2_tx_rcnt];
    ++g_usart2_tx_rcnt;
    g_usart2_tx_rcnt >= USART2_BUFFER_SIZE  && (g_usart2_tx_rcnt = MAX_COMMAND_LENGHT + 1); //reset g_rx_rcnt
    if(data == 0x08 || data == 0x7F)
    {
      if(g_usart2_tx_cmdcnt)
      {
        usart2_tx_byte('\b'); // backspace
        usart2_tx_byte(' '); // delete
        usart2_tx_byte('\b'); // backspace
        g_usart2_rx_buffer[--g_usart2_tx_cmdcnt] = '\n';
      }
      else
      {
        *g_usart2_rx_buffer = '\n';
      }
    }
    else if(data == '\n' || data == '\r' || g_usart2_tx_cmdcnt >= (MAX_COMMAND_LENGHT - 1))
    {
      usart2_tx_byte('\n');
      usart2_tx_byte('\r');
      g_usart2_rx_buffer[g_usart2_tx_cmdcnt] = '\0';
      g_usart2_rx_buffer[MAX_COMMAND_LENGHT] = '\0'; // command end indicator
      g_usart2_tx_cmdcnt = 0;
      return g_usart2_rx_buffer;
    }
    else
    {
      USART2->DR = data; //show insterted characters to user
      g_usart2_rx_buffer[g_usart2_tx_cmdcnt++] = data;
    }
  }
  return 0;
}/*}}}*/

void putcharUSART2(uint8_t data)
{/// print one character to USART2
	while(!(USART2->SR & USART_SR_TC));									
	
	USART2->DR = data;												    
}

void USART2_IRQHandler(void)/*{{{*/
{
  //putcharUSART2(USART2->DR);
  currentData = USART2->DR;
  // g_usart2_rx_buffer[g_usart2_tx_wcnt] = USART2->DR;
  // ++g_usart2_tx_wcnt;
  // g_usart2_tx_wcnt >= USART2_BUFFER_SIZE  && (g_usart2_tx_wcnt = MAX_COMMAND_LENGHT + 1); //reset g_rx_wcnt

// }/*}}}*/
}

