
#include "stm32f4xx.h"


int main(void)
{
	// Variable Declaration
	volatile unsigned char buttonpressed=0;
    volatile unsigned int  buttonpressedconfidencelevel=0;
    volatile unsigned int  buttonreleasedconfidencelevel=0;
    volatile unsigned int  confidencethreshold = 200;

	RCC ->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable PORT A ( LED )
	RCC ->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Enable PORT C ( SW )


	// Setting The Control Registers for the LED
    GPIOA ->MODER |= GPIO_MODER_MODER5_0 ; // OUTPUT MODE
    GPIOA ->MODER &= ~(GPIO_MODER_MODER5_1) ;
    /* to ensure the left bit is a zero and not affected by another operation
       so the OR can work Correctly
    */
    GPIOA ->OTYPER &= ~(GPIO_OTYPER_OT_5); // PUSH PULL MODE
    GPIOA ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1 ; //HIGH SPEED MODE
    GPIOA ->PUPDR &= ~(GPIO_PUPDR_PUPDR5);  // None (NOPUPD)

    // Setting The Control Registers for the Switch
    GPIOC ->MODER &= ~(GPIO_MODER_MODER13);  //INPUT MODE
    GPIOC ->PUPDR &= ~(GPIO_PUPDR_PUPDR13);  // None (NOPUPD)



  while (1)
  {

	 if (GPIOC ->IDR & GPIO_IDR_IDR_13 )
	 {
		 if (buttonpressed==0)
		 {

	 	 if (buttonpressedconfidencelevel > confidencethreshold)
	 	 {

			  GPIOA->BSRRH ^= (1<<5); // Toggle Bit 5
   		 	  buttonpressed= 1;
		 	 }
	 	 else
	 	 {
			 buttonpressedconfidencelevel ++ ;
			 buttonreleasedconfidencelevel =0;
	 	      }
		           }

	 }
	 else {
		 	 if (buttonpressed==1)
		 	 {

		 	 if (buttonreleasedconfidencelevel > confidencethreshold)
			 {
	 	  	 GPIOA->BSRRL ^= (1<<5); // Toggle Bit 5
		 	 buttonpressed= 0;
					 	 }
		 	 else {
			 		 buttonreleasedconfidencelevel ++ ;
			 		 buttonpressedconfidencelevel =0 ;
		 	        	 }
		 	 	 }
	 }



  }
}
