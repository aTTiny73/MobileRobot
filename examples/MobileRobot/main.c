#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "print.h"


int main(void)
{

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // enable clock for port GPIOC
  GPIOA->CRH &= ~(0x00f00000); // clean default value (0x44444444)
  GPIOA->CRH |= 0x0000BBBB;

  GPIOA->CRL &= ~(0x44444444); // clean default value (0x44444444) FFFFFF
  GPIOA->CRL |= 0x30300000;


  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  TIM1->PSC = 720- 0x0001;
  TIM1->ARR = 2000;

  TIM1->BDTR = TIM_BDTR_MOE; // Specific for Tim1 and Tim8

  TIM1->CCR1 = 0x0000;
  TIM1->CCR2 = 0x0000;
  TIM1->CCR3 = 0x0000;
  TIM1->CCR4 = 0x0000;

  TIM1->SMCR &=~TIM_SMCR_SMS;//clear sms->use internal clock
  TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM1->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM1->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;

// set active mode high for pulse polarity
		TIM1->CCER &= ~((TIM_CCER_CC1P)|(TIM_CCER_CC2P)|(TIM_CCER_CC3P)|(TIM_CCER_CC4P));
		TIM1->CR1 |= (TIM_CR1_ARPE)|(TIM_CR1_URS);

		// update event, reload all config
		TIM1->EGR |= TIM_EGR_UG;
		// activate capture compare mode
		TIM1->CCER |= (TIM_CCER_CC1E)|(TIM_CCER_CC2E)|(TIM_CCER_CC3E)|(TIM_CCER_CC4E);
		// start counter
		TIM1->CR1 |= TIM_CR1_CEN;

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // enable clock for port GPIOC
  GPIOB->CRL &= ~(0x00f00000); // clean default value (0x44444444)
  GPIOB->CRL |= 0xBB000000;

  GPIOB->CRH &= ~(0x00f00000); // clean default value (0x44444444)
  GPIOB->CRH |= 0x000000BB;

  GPIOB->ODR = 0x0000;



  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->PSC = 720- 0x0001;

  TIM4->ARR = 2000;

  TIM4->CCR1 = 0x0000;
  TIM4->CCR2 = 0x0000;
  TIM4->CCR3 = 0x0000;
  TIM4->CCR4 = 0x0000;

  TIM4->SMCR &=~TIM_SMCR_SMS;//clear sms->use internal clock

  TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM4->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM4->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;

// set active mode high for pulse polarity
		TIM4->CCER &= ~((TIM_CCER_CC1P)|(TIM_CCER_CC2P)|(TIM_CCER_CC3P)|(TIM_CCER_CC4P));
		TIM4->CR1 |= (TIM_CR1_ARPE)|(TIM_CR1_URS);

		// update event, reload all config
		TIM4->EGR |= TIM_EGR_UG;
		// activate capture compare mode
		TIM4->CCER |= (TIM_CCER_CC1E)|(TIM_CCER_CC2E)|(TIM_CCER_CC3E)|(TIM_CCER_CC4E);
		// start counter
		TIM4->CR1 |= TIM_CR1_CEN;



  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  TIM3->PSC = 720- 0x0001;

  TIM3->ARR = 2000;

  TIM3->CCR1 = 0x0000;
  TIM3->CCR2 = 0x0000;
  TIM3->CCR3 = 0x0000;
  TIM3->CCR4 = 0x0000;

  TIM3->SMCR &=~TIM_SMCR_SMS;//clear sms->use internal clock

  TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM3->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
  TIM3->CCMR2 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;

// set active mode high for pulse polarity
		TIM3->CCER &= ~((TIM_CCER_CC1P)|(TIM_CCER_CC2P)|(TIM_CCER_CC3P)|(TIM_CCER_CC4P));
		TIM3->CR1 |= (TIM_CR1_ARPE)|(TIM_CR1_URS);

		// update event, reload all config
		TIM3->EGR |= TIM_EGR_UG;
		// activate capture compare mode
		TIM3->CCER |= (TIM_CCER_CC1E)|(TIM_CCER_CC2E)|(TIM_CCER_CC3E)|(TIM_CCER_CC4E);
		// start counter
		TIM3->CR1 |= TIM_CR1_CEN;


  int motor1Inital = 150; // period 1.5 ms -> 90 degrees
  int motor2Inital = 200;
  int motor3Inital = 40; 
  int motor4Inital = 150;
  int motor5Inital = 60;
  int motor6Inital = 150;
  int motor7Inital = 150;

  TIM4->CCR1 = motor1Inital; //MOTOR1
  TIM4->CCR2 = motor4Inital; //MOTOR4
  TIM4->CCR3 = motor3Inital; //MOTOR3
  TIM4->CCR4 = motor5Inital; //MOTOR5

  TIM1->CCR2 = motor2Inital; //MOTOR2
  TIM1->CCR3 = motor6Inital; //MOTOR6

  TIM3->CCR1 = motor7Inital; //MOTOR7



  currentData = '1';

  systimer_init(); 
  uint32_t sysTime = systimer_get(); 
  usart2_init(USART_BAUDRATE_9600); // Bluetooth HC-06 baudrate      
  print_init(usart2_tx_byte);
  GPIOA->ODR &= ~(0xA0);

  while(1)
  {
    if(systimer_timeout_flag(sysTime,40) == SYSTIMER_TIMEOUT )
    {
      sysTime = systimer_get();
      switch (currentData){
    case 'w':
      GPIOA->ODR &= ~(0xA0);
      GPIOA->ODR |= 0x20;
      TIM1->CCR1 = 1500;
      TIM1->CCR4 = 1500;
      //print("↑ Forward ↑\n");
    break;

    case 's':
      GPIOA->ODR &= ~(0xA0);
      GPIOA->ODR |= 0x80;
      TIM1->CCR1 = 1500;
      TIM1->CCR4 = 1500;
      //print("↓ Backward ↓\n");
    break;

    case 'd':
      GPIOA->ODR &= ~(0xA0);
      TIM1->CCR1 = 1500;
      TIM1->CCR4 = 1500;
      //print("→ Right →\n");
    break;

    case 'a':
      GPIOA->ODR &= ~(0xA0);
      GPIOA->ODR |= 0x20;
      GPIOA->ODR |= 0x80;
      TIM1->CCR1 = 1500;
      TIM1->CCR4 = 1500;
      //print("← Left ←\n");
    break;

    case 'r':
      motor1Inital=motor1Inital + 1;
      if(motor1Inital > 260){
        motor1Inital = 260;
      }
      TIM4->CCR1 = motor1Inital;
      //print(" Motor1 : %d\n",motor1Inital);
    break;

    case 'f':
     motor1Inital=motor1Inital - 1;
     if(motor1Inital < 35){
        motor1Inital = 35;
      }
      TIM4->CCR1 = motor1Inital;
      //print(" Motor1 : %d\n",motor1Inital);
    break;
    
    case 't':
      motor2Inital=motor2Inital + 1;
      if(motor2Inital > 260){
        motor2Inital = 260;
      }
      TIM1->CCR2 = motor2Inital;
      //print(" Motor2 : %d\n",motor2Inital);
    break;

    case 'g':
     motor2Inital=motor2Inital - 1;
     if(motor2Inital < 35){
        motor2Inital = 35;
      }
      TIM1->CCR2 = motor2Inital;
      //print(" Motor2 : %d\n",motor2Inital);
    break;

    case 'y':
      motor3Inital=motor3Inital + 1;
      if(motor3Inital > 260){
        motor3Inital = 260;
      }
      TIM4->CCR3 = motor3Inital;
      //print(" Motor3 : %d\n",motor3Inital);
    break;

    case 'h':
     motor3Inital=motor3Inital - 1;
     if(motor3Inital < 35){
        motor3Inital = 35;
      }
      TIM4->CCR3 = motor3Inital;
      //print(" Motor3 : %d\n",motor3Inital);
    break;

    case 'u':
      motor4Inital=motor4Inital + 1;
      if(motor4Inital > 250){
        motor4Inital = 250;
      }
      TIM4->CCR2 = motor4Inital;
      //print(" Motor4 : %d\n",motor4Inital);
    break;

    case 'j':
     motor4Inital=motor4Inital - 1;
     if(motor4Inital < 45){
        motor4Inital = 45;
      }
      TIM4->CCR2 = motor4Inital;
      //print(" Motor4 : %d\n",motor4Inital);
    break;

    case 'i':
      motor5Inital=motor5Inital + 1;
      if(motor5Inital > 260){
        motor5Inital = 260;
      }
      TIM4->CCR4 = motor5Inital;
      //print(" Motor5 : %d\n",motor5Inital);
    break;

    case 'k':
     motor5Inital=motor5Inital - 1;
     if(motor5Inital < 35){
        motor5Inital = 35;
      }
      TIM4->CCR4 = motor5Inital;
      //print(" Motor5 : %d\n",motor5Inital);
    break;

    case 'o':
      motor6Inital=motor6Inital + 1;
      if(motor6Inital > 250){
        motor6Inital = 250;
      }
      TIM1->CCR3 = motor6Inital;
      //print(" Motor6 : %d\n",motor6Inital);
    break;

    case 'l':
     motor6Inital=motor6Inital - 1;
     if(motor6Inital < 45){
        motor6Inital = 45;
      }
      TIM1->CCR3 = motor6Inital;
      //print(" Motor6 : %d\n",motor6Inital);
    break;

    case 'z':
      motor7Inital=motor7Inital + 1;
      if(motor7Inital > 260){
        motor7Inital = 260;
      }
      TIM3->CCR1 = motor7Inital;
      //print(" Motor7 : %d\n",motor7Inital);
    break;

    case 'x':
     motor7Inital=motor7Inital - 1;
     if(motor7Inital < 35){
        motor7Inital = 35;
      }
      TIM3->CCR1 = motor7Inital;
      //print(" Motor7 : %d\n",motor7Inital);
    break;

    case 'b':
      currentData='\0';
    break;

    default:
      TIM1->CCR1 = 0;
      TIM1->CCR4 = 0;
      TIM4->CCR1 = motor1Inital;
      TIM1->CCR2 = motor2Inital;
      TIM4->CCR3 = motor3Inital;
      TIM4->CCR2 = motor4Inital;
      TIM4->CCR4 = motor5Inital;
      TIM1->CCR3 = motor6Inital;
      TIM3->CCR1 = motor7Inital; 
       
      break;
    } 
      
    }

  }
  return 0;
}
