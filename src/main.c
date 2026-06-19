#include "stm32f103xb.h"
#include "punto1.h"
#define PC10 10
#define PC11 11
#define led1 1
#define led2 2
#define led3 3
#define led4 4
int tren_entrando;
int  tren_saliendo;

int main(void) {
    motores_t motor;
    motor.puerto = GPIOA;
    motor.pines[0] = led1;
    motor.pines[1] = led2;
    motor.pines[2] = led3;
    motor.pines[3] = led4;

    RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN|RCC_APB2ENR_AFIOEN; 
    GPIOC -> CRH &=~ (0xF << ((PC10 % 8) * 4));
    GPIOC -> CRH |= (0x8 << ((PC10 % 8) * 4)); 
    GPIOC -> BSRR |= (1 << PC10);
    GPIOC -> CRH &= ~(0xF << ((PC11 % 8) * 4));
    GPIOC -> CRH |= (0x8 << ((PC11 % 8) * 4)); 
    GPIOC -> BSRR |= (1 << PC11);
    mPaP_Init(&motor);

    AFIO -> EXTICR[2] |= (0X2 << (PC10%4) * 4);
    AFIO -> EXTICR[2] |= (0X2 << (PC11%4) * 4);

    EXTI -> IMR |= (1 << PC10);
    EXTI -> FTSR |= (1 << PC10);
    EXTI -> RTSR &= ~(1 << PC10);

    EXTI -> IMR |= (1 << PC11);
    EXTI -> FTSR |= (1 << PC11);
    EXTI -> RTSR &= ~(1 << PC11);

    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 1);
while(1){
    if(tren_entrando==1){
        motor.grado_inicial =60;
        motor.grado_final=0;
        tren_entrando=0;
    }
    if(tren_saliendo==1){
        delay(10000);
        motor.grado_inicial =0;
        motor.grado_final=60;
        tren_saliendo=0;
    }
mPap_Steps(&motor);

}   
return 0;
}

void EXTI15_10_IRQHandler(void){
    if(EXTI->PR & (1 << PC10)){
        tren_entrando=1;
        EXTI->PR |= (1 << PC10); 
    }
    if(EXTI->PR & (1 << PC11)){
        delay(10000);
        tren_saliendo=1;
        EXTI->PR |= (1 << PC11); 
    }
}
