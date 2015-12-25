const int latchPin = 8;//Pin connected to ST_CP of 74HC595
const int clockPin = 12;//Pin connected to SH_CP of 74HC595 
const int dataPin = 11; //Pin connected to DS of 74HC595 

int data[] = {0xFF,                                   /* Start */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xC1,0xBF,0xC1,0xBF,0xC1,               /* "M" */
              0xFF,0xFF,                              /* " " */
              0xC1,0xD5,0xD5,0xC5,                    /* "e" */
              0xFF,0xFF,                              /* " " */
              0xC1,0xEF,0xDF,0xDF,                    /* "r" */
              0xFF,0xFF,                              /* " " */
              0xC1,0xEF,0xDF,0xDF,                    /* "r" */
              0xFF,0xFF,                              /* " " */
              0xC7,0xF5,0xF5,0xC1,                    /* "y" */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xC7,0xBB,0x7D,0x7D,0x7D,0xBB,          /* "C" */
              0xFF,0xFF,                              /* " " */
              0x01,0xEF,0xDF,0xE1,                    /* "h" */
              0xFF,0xFF,                              /* " " */
              0xC1,0xEF,0xDF,0xDF,                    /* "r" */
              0xFF,0xFF,                              /* " " */
              0xA1,                                   /* "i" */
              0xFF,0xFF,                              /* " " */
              0xC5,0xD5,0xD5,0xD1,                    /* "s" */
              0xFF,0xFF,                              /* " " */
              0xDF,0x81,0xDD,                         /* "t" */
              0xFF,0xFF,                              /* " " */
              0xC1,0xEF,0xDF,0xE1,0xDF,0xE1,          /* "m" */
              0xFF,0xFF,                              /* " " */
              0xF1,0xD5,0xD5,0xC1,0xFD,               /* "a" */
              0xFF,0xFF,                              /* " " */
              0xC5,0xD5,0xD5,0xD1,                    /* "s" */
              0xFF,0xFF,                              /* " " */
              0x05,                                   /* "!" */
              0xFF,0xFF,                              /* " " */
              0x55,0x7D,0x01,                         /* ":]" */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF,0xFF,                              /* " " */
              0xFF                                    /* End. */
};
void setup ()
{
  //set pins to output
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}
void loop()
{
  
  for(int n = 0; n < 120; n++)
  {
    for(int t = 0;t < 35;t ++)
    {
      int dat = 0x40;
      for(int num = n; num < 8 + n; num++)
      {
          //shift to simulate right to left scrolling   
          dat = dat>>1;

          shiftOut(dataPin,clockPin,MSBFIRST,~data[num]);
          shiftOut(dataPin,clockPin,MSBFIRST,~dat);    

          //return the latch pin high to signal chip that it 
          //no longer needs to listen for information
          //pull the latchPin to save the data
          digitalWrite(latchPin,HIGH);
          //ground latchPin and hold low 
          //for as long as you are transmitting
          digitalWrite(latchPin,LOW);
      }
    }
  }
}
