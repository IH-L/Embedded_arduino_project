#include <CapacitiveSensor.h>
#include <SPI.h>
#include <math.h>
// Import the CapacitiveSensor Library.

#define speaker A5    //第1蜂鳴器pin，大聲
#define speaker2 A4   //第1蜂鳴器pin，小聲
#define sw1  A2       //即時升階
#define sw2  A1       //鋼琴的右踏板，持續音
#define sw3  A3       //鋼琴的左踏板，弱音
#define sw4  A0       //調基礎音階
int baselevel=2;

// 電容式觸控的pin
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2, 3);
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2, 4);
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2, 5);
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2, 6);
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2, 7);
CapacitiveSensor   cs_2_8 = CapacitiveSensor(2, 8);
CapacitiveSensor   cs_2_9 = CapacitiveSensor(2, 9);
CapacitiveSensor   cs_2_12 = CapacitiveSensor(2, 12);

//8*8矩陣顯示
unsigned char Do[8] = {0xfe, 0x82, 0x44, 0x38, 0x00, 0xe0, 0xa0, 0xe0};
unsigned char Re[8] = {0xfe, 0x32, 0x52, 0x9c, 0x00, 0xf8, 0xa8, 0xb8};
unsigned char Mi[8] = {0xfc , 0x08, 0x10 , 0x08, 0xfc , 0x00, 0xd0 , 0x00};
unsigned char Fa[8] = {0xfe , 0x12, 0x12 , 0x12, 0xe0 , 0xa0, 0x60 , 0x80};
unsigned char So[8] = {0x9e , 0x92, 0x92 , 0xf2, 0x00 , 0xe0, 0xa0 , 0xe0};
unsigned char La[8] = {0xfe , 0x80, 0x80 , 0x00, 0xe0 , 0xa0, 0x60 , 0x80};
unsigned char Si[8] = {0x9e , 0x92, 0x92 , 0xf2, 0x00 , 0x00, 0xd0 , 0x00};

const byte NOOP = 0x0;
const byte DECODEMODE = 0x9;
const byte INTENSITY = 0xA;
const byte SCANLIMIT = 0xB;
const byte SHUTDOWN = 0xc;
const byte DISPLAYTEST = 0xF;

void max7219(byte reg, byte data)
{
  digitalWrite(SS, LOW);
  SPI.transfer(reg);
  SPI.transfer(data);
  digitalWrite(SS, HIGH);
}


void setup()
{


  // Arduino start communicate with computer.
  Serial.begin(9600);
  SPI.begin();
  max7219(SCANLIMIT, 7);
  max7219(DECODEMODE, 0);
  max7219(INTENSITY, 8);
  max7219(DISPLAYTEST, 0);
  max7219(SHUTDOWN, 1);
  for (byte i = 0; i < 8; i++)
  {
    max7219(i + 1, 0);
  }
  //  cs_2_3.set_CS_AutocaL_Millis(0xFFFFFFFF); //關閉自動校正
  /* cs_2_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_7.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_8.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_9.set_CS_AutocaL_Millis(0xFFFFFFFF);
    cs_2_12.set_CS_AutocaL_Millis(0xFFFFFFFF);*/
  
  //重置電容值
  cs_2_3.reset_CS_AutoCal();    
  cs_2_4.reset_CS_AutoCal();
  cs_2_5.reset_CS_AutoCal();
  cs_2_6.reset_CS_AutoCal();
  cs_2_7.reset_CS_AutoCal();
  cs_2_8.reset_CS_AutoCal();
  cs_2_9.reset_CS_AutoCal();
  cs_2_12.reset_CS_AutoCal();

  //擷取時限設定
  cs_2_3.set_CS_Timeout_Millis(30);
  cs_2_4.set_CS_Timeout_Millis(30);
  cs_2_5.set_CS_Timeout_Millis(30);
  cs_2_6.set_CS_Timeout_Millis(30);
  cs_2_7.set_CS_Timeout_Millis(20);
  cs_2_8.set_CS_Timeout_Millis(20);
  cs_2_9.set_CS_Timeout_Millis(20);
  cs_2_12.set_CS_Timeout_Millis(15);
}




void loop()
{
  // Set a timer.
  long start = millis();
  boolean level_up = digitalRead(sw1);      //即時升階
  boolean base = digitalRead(sw4);          //調基礎音階
  boolean weak = digitalRead(sw3);           //鋼琴的左踏板，弱音
  boolean continues = digitalRead(sw2);     //鋼琴的右踏板，持續音
  if(base)
  {
    if(baselevel==2)
    {
      baselevel=1;
    }
    else if(baselevel==1)
    {
      baselevel=2;
    }
  }
  int level=baselevel;
  if (level_up)
  {
    level =level* 2;
  }
  // Set the sensitivity of the sensors.//
  //_______________________________________________________________________________________________________
  //--------------------------------------------------------------------------------------------------------
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~
  //電容感測回饋

  long total1 =  cs_2_3.capacitiveSensor(2);
  if (total1 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(130.81 * level));     //蜂鳴器發出do
    }
    else
    {
      tone(speaker, ceil(130.81 * level)); // frequency
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Do[i]);
    }
  }
  //////////////////////////////////////////////////////////////////2
  long total2 =  cs_2_4.capacitiveSensor(2);
  if (total2 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(146.83 * level));
    }
    else
    {
      tone(speaker, ceil(146.83 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Re[i]);
    }
  }
  ////////////////////////////////////////////////////////////3
  long total3 =  cs_2_5.capacitiveSensor(2);
  if (total3 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(164.81 * level));
    }
    else
    {
      tone(speaker, ceil(164.81 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Mi[i]);
    }
  }
  ////////////////////////////////////////////////////////////////4
  long total4 =  cs_2_6.capacitiveSensor(2);
  if (total4 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(174.61 * level));
    }
    else
    {
      tone(speaker, ceil(174.61 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Fa[i]);
    }
  }
  //////////////////////////////////////////////////////////////////5
  long total5 =  cs_2_7.capacitiveSensor(2);
  if (total5 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(196 * level));
    }
    else
    {
      tone(speaker, ceil(196 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, So[i]);
    }
  }
  ///////////////////////////////////////////////////6
  long total6 =  cs_2_8.capacitiveSensor(2);
  if (total6 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(220 * level));
    }
    else
    {
      tone(speaker, ceil(220 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, La[i]);
    }
  }
////////////////////////////////////////////////////7
  long total7 =  cs_2_9.capacitiveSensor(2);
  if (total7 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(246.94 * level));
    }
    else
    {
      tone(speaker, ceil(246.94 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Si[i]);
    }
  }
  ///////////////////////////////////////////////////////8
  long total8 = cs_2_12.capacitiveSensor(2);
  if (total8 > 0)
  {
    if(weak)
    {
      tone(speaker2, ceil(262.63 * level));
    }
    else
    {
      tone(speaker, ceil(262.63 * level));
    }
    for (byte i = 0; i < 8; i++)
    {
      max7219(i + 1, Do[i]);
    }
  }


  //_______________________________________________________________________________________________________
  //--------------------------------------------------------------------------------------------------------
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~
  //查看用


  Serial.print(millis() - start);      // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing

  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");                    // Leave some space before print the next outpu  Serial.print(total2);                  // print sensor output 2
  Serial.print(total2);                  // print sensor output 1
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total3);                  // print sensor output 3
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total4);                  // print sensor output 4
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total5);                  // print sensor output 5
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total6);                  // print sensor output 6
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total7);                  // print sensor output 7
  Serial.print("\t");                    // Leave some space before print the next output
  Serial.print(total8);                  // print sensor output 8
  Serial.print("\t");
  Serial.print(level_up);
  Serial.print("\t");
  Serial.print(weak);
  Serial.print("\t");
  Serial.println(continues);


  if (continues);     //按住持續則不停
  else if (total1 <= 300  &  total2 <= 300 &  total3 <= 300 &  total4 <= 300 &  total5 <= 300 &  total6 <= 300 &  total7 <= 300 &  total8 <= 300 )
  {
    noTone(speaker);    //停止出聲
    noTone(speaker2);
  }
  delay(10);

  // arbitrary delay to limit data to serial port
}
