void main() {
     char ENTER_CONST[] = {13,0};
     char mensagem[31];
     char byte_str[5];
     char int_str[7];
     unsigned char byte_recebido = 0;
     unsigned int temperatura_ate_1023 = 0;
     double temperatura = 0.0;
     double temperatura_escolhida = 0.0;
     int i = 0;
     UART1_Init(19200);
     TRISD = 0;
     TRISC.F1 = 0; //aquecedor
     TRISC.F2 = 0; //ventoinha
     //PORTC.F1 = 1; //liga aquecedor

     
     //ByteToStr(byte, byte_str);
     //IntToStr(byte, int_str);
     //strlen
     //strcmp
    for( i = 0; i<7; i++)
       int_str[i] = 0;
     while(1)
     {
      temperatura_ate_1023 = ADC_Read(3);
      temperatura = (temperatura_ate_1023*(5.0/1023.0)) * 100.0;

      if(temperatura >= 40.0)
      {
//       PORTC.F1 = 0; //desliga aquecedor
//       PORTC.F2 = 1; //liga ventoinha
      }
      if(temperatura <= 25.0)
      {
//       PORTC.F1 = 1; //liga aquecedor
//       PORTC.F2 = 0; //desliga ventoinha
      }
      if(UART1_Data_Ready())
      {
       //UART1_Read_Text(mensagem, ENTER_CONST, 30);
       byte_recebido = UART1_Read();
      }
      if(byte_recebido == 'V')
      {
       if(PORTC.F2)
       {
        PORTC.F2 = 0;
       }
       else
       {
        PORTC.F2 = 1;
       }
       byte_recebido = 0;
      }
      
      if(byte_recebido == 'R')
      {
       if(PORTC.F1)
       {
        PORTC.F1 = 0;
       }
       else
       {
        PORTC.F1 = 1;
       }
       byte_recebido = 0;
      }

      
      Delay_ms(100);
      IntToStr(((int)temperatura), int_str);
      UART1_Write_Text(int_str);
      UART1_Write(10);
      UART1_Write(13);
      for( i = 0; i<7; i++)
       int_str[i] = 0;
      Delay_ms(100);
     }

}
