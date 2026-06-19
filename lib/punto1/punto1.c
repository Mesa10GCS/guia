#include "punto1.h"

int pasosc[8][4]={
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1},
  
};


void mPaP_Init(motores_t* mpap){
    if(mpap->puerto== GPIOA) RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
    if(mpap->puerto== GPIOB) RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
    if(mpap->puerto== GPIOC) RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
    if(mpap->puerto== GPIOD) RCC->APB2ENR|=RCC_APB2ENR_IOPDEN;
    if(mpap->puerto== GPIOE) RCC->APB2ENR|=RCC_APB2ENR_IOPEEN;
        for(int i=0; i<4; i++){
        if(mpap->pines[i]<8){ 
            mpap->puerto->CRL&=~(0xf<<(mpap->pines[i]*4));
            mpap->puerto->CRL|=(0x1<<mpap->pines[i]*4);
        }else{
            mpap->puerto->CRH&=~(0xf<<(mpap->pines[i]%8)*4);
            mpap->puerto->CRH|=(0x1<<(mpap->pines[i]%8)*4);
        }
        }
}

void mPap_Steps(motores_t* mpap){
    int pasos;
    int gradofinal;
    if(mpap->grado_final>mpap->grado_inicial){
        gradofinal = mpap->grado_final- mpap->grado_inicial;
        pasos= gradofinal/0.9;
        for(int i=0; i < (pasos); i++){
        for(int j=0; j<4; j++){
            if(pasosc[i%8][j])mpap->puerto->BSRR|=(1<<mpap->pines[j]);
            else GPIOA ->BSRR |=(1<<(mpap->pines[j]+16)); 
        }

        }
    }

    if(mpap->grado_inicial>mpap->grado_final){
        gradofinal = mpap->grado_inicial - mpap->grado_final;
        pasos = gradofinal/0.9;
        for(int i=pasos; i > 0; i--){
        for(int j=0; j<4; j++){
            if(pasosc[i%8][j])mpap->puerto->BSRR|=(1<<mpap->pines[j]);
            else GPIOA ->BSRR |=(1<<(mpap->pines[j]+16)); 
        }
    }    
}
}
