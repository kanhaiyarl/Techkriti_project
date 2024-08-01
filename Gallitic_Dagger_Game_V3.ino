 # include "Display.h"
 
int x = 7;
unsigned char by = 5;
unsigned int in = -1;

unsigned int bombval = 0;
unsigned int bomb_x = x;
unsigned int bomb_y = 5;

unsigned int enemy_x = 2;
unsigned int enemy_y = 2;

int timer1_counter;
unsigned long previousMillis = 0;        // will store last time LED was updated


//unsigned char data[3][10]= {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//                         {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
//                         {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};


// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
 
void setup() {
  // put your setup code here, to run once:
  Display();
  Begin();
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  
  // initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0; 
  
  // timer1_counter = 64911;// preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286; // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz

  TCNT1 = 34286;   // preload timer
  TCCR1B |= (1 << CS11);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts(); // enable all interrupts
  
  //for(int i=0;i<10;++i)
  //{
  //  for(int j=0;j<8;++j)
  //  {
  //    data[i][j] = 0b0;
  //  } 
  //}
  //data[10] = {0xff,0x00,0x00,0x00,0xc0,0x60,0xc0,0x00,0x00,0xff};
  //data[x][7] = 0b1;
  //data[x][6] = data[x][7];
  
  //data[x+1][4] = data[x][7];
  //data[x+1][5] = data[x][7];
  
  //data[x+2][7] = data[x][7];
  //data[x+2][6] = data[x][7];
  
}
/*

void loop() {
  // put your main code here, to run repeatedly:
  
  if((x-in)<0 || (x+in)>10);
//  else if(in == 0)
//  {
//    data[x] = 0x00
//    
//    x -= 1;
//    data[x][7]=0b1;
//    data[x][6]=0b1;
//    data[x+1][5]=0b1;
//    data[x+1][6]=data[x+1][5];
//    data[x+2][7]=data[x][7];
//    data[x+2][6]=data[x][6];
//  }
//  else if(in == 1)
//  {
//    data[x][7]=0b0;
//    data[x][6]=0b0;
//    data[x+1][5]=0b0;
//    data[x+1][6]=data[x+1][5];
//    data[x+2][7]=data[x][7];
//    data[x+2][6]=data[x][6];
//    
//    x +=1;
//    data[x][7]=0b1;
//    data[x][6]=0b1;
//    data[x+1][5]=0b1;
//    data[x+1][6]=data[x+1][5];
//    data[x+2][7]=data[x][7];
//    data[x+2][6]=data[x][6];
//  }
  P7.Refresh(data);
}*/


// interrupt service routine
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 63000; // preload timer
  Refresh();
  //moveme('1');
}

void moveme(unsigned char dir)
{
  data[0][x] &= 0x3F;
  data[0][x+1] &= 0x9F;
  data[0][x+2] &= 0x3F;

  if(dir == 0)
  {
    x = x -1;
    if(x < 0)
    {
      x = 0;
    }
  }
  else if(dir == 4)
  {
    x = x + 1;
    if(x > 7)
    {
      x = 7;
    }
  }
  //Serial.println(x);
      data[0][x] |= 0xC0;
      data[0][x+1] |= 0x60;
      data[0][x+2] |= 0xC0;
    
  
}
int mypos = 0;
int mydir = -1;

void create_emny()
{
  data[2][bomb_x] |= 0x30;
  data[2][bomb_x+1] |= 0x60;
  data[2][bomb_x+2] |= 0x30;
  
}
void move_emny(unsigned char x)
{
  //if(data[x][by] == 0x60)
   // move_emny[x][x] = move_emny[2][x];
}
void destroy(unsigned char bx)
{
  
  if(data[enemy_y][x] != 0x00 && data[bx][by] != 0x60)
  {
    enemy_y -= 1;
    data[bx];
  }

  if(data[bx]);
}

void placebmb(unsigned char bx,unsigned char by, unsigned char bombval)
{
  if(bombval == 1)
  {
  if(by>=1 && by<= 8)
  {
    by = 9-by;
  }
  else if (by>=9 && by<= 16)
  {
    by = 25-by;
  }
  else if(by>=17 && by<= 23 )
  {
    by= 40-by;
  }
  //data[bx][by] = data[bx][by] & (data[bx][by] >> 1);
  
  data[(by & 0b11111000) >> 3][bx] &= (0xff ^ (0x01 << (by & 0x07)));
  
  data[((by-1) & 0b11111000) >>3][bx] |= (0x01 << (by-1 & 0x07));
  }
  by++;
  //data[bx][by] = 0x
//  data[bx][by>>1]
//  if (by ==1)
//  {
//    x++;
//    by = 0x8;
//    
//  }
}

void loop() {
// your program
  in = map(analogRead(A0),0,1023,0,4);
  bombval = digitalRead(A1);
  
  Serial.println(bombval);
  //delay(1000);
  unsigned long currentMillis = millis();
  //Refresh();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    placebmb(x,by, bombval);
    create_emny();
    moveme(in);

//  if(random(0,10)>5)
//  {
//    moveme(1);
//  }
//  else
//  {
//    moveme(0);
//  }
//
  by++;    
 }
 placebmb(x,by,bombval);
 if(data[x][by] != 0x00)
 {
   data[x][by];  
 }
}
