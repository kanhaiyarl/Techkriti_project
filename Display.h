#ifndef Display_h
#define Display_h
#include <SPI.h>

/* This section is about the pin connection of the arduino to the Display Board */
#define SPI_RCLK_Pin    10
#define SPI_Data_Pin    11
#define SPI_CLK_Pin     13
#define OE_Pin          9


int Row[10] = {7,6,5,4,3,2,A5,A4,A3,A2};
//unsigned char data[10]= {0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned char data[3][10]= {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                            {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

Display()
{
  pinMode(SPI_RCLK_Pin, OUTPUT);
  pinMode(SPI_Data_Pin, OUTPUT);
  pinMode(SPI_CLK_Pin, OUTPUT);
  digitalWrite(SPI_Data_Pin, LOW);
  digitalWrite(SPI_CLK_Pin, LOW);
  digitalWrite(SPI_RCLK_Pin, LOW);
};

Begin()
{
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000,LSBFIRST,SPI_MODE1));
  pinMode(SPI_RCLK_Pin, OUTPUT);
  pinMode(SPI_Data_Pin, OUTPUT);
  pinMode(SPI_CLK_Pin, OUTPUT);
  pinMode(OE_Pin, OUTPUT);
  digitalWrite(SPI_Data_Pin, LOW);
  digitalWrite(SPI_CLK_Pin, LOW);
  digitalWrite(SPI_RCLK_Pin, LOW);
  digitalWrite(OE_Pin,LOW);
  for(int i =0; i < 10; i++)
  {
    pinMode(Row[i], OUTPUT);
    digitalWrite(Row[i],LOW);
  }
  
}

Refresh()
{
  static int i = 0;
  //for(int i= 0;i < 10; i ++)
  //{
    //Serial.print(data);
    digitalWrite(SPI_Data_Pin, LOW);
    digitalWrite(SPI_CLK_Pin, LOW);
    digitalWrite(SPI_RCLK_Pin, LOW);
    SPI.transfer(data[2][i]);
    SPI.transfer(data[1][i]);
    SPI.transfer(data[0][i]);                    // This statement puts the data on Shift Registers.
    if(i == 0){digitalWrite(Row[9],LOW);};
    digitalWrite(Row[i -1] , LOW);
    digitalWrite(SPI_RCLK_Pin, HIGH);
    digitalWrite(Row[i], HIGH);
    i++;
    i = i%10;
    //delay(1000);
  // }
}
#endif
