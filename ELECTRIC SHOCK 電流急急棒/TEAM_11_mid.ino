const byte dataPin1 = 2;
const byte latchPin1 = 3;
const byte clockPin1 = 4;
const byte dataPin2 = 5;
const byte latchPin2 = 6;
const byte clockPin2 = 7;
const byte sw = 12;   //輕觸
const byte led_start = 13;    //開始亮燈
const byte led_end = 9;     //結束亮燈
const byte SHOCK = 8;    //電流急急棒
byte index1 = 0, index2 = 0;
boolean val;      //是否開始
int count = 75, stopp = 0;
int dead = 0;
//7段顯示設計
const byte LEDs[10] = {
  B01111110,
  B00110000,
  B01101101,
  B01111001,
  B00110011,
  B01011011,
  B01011111,
  B01110000,
  B01111111,
  B01110011

};

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);         
  randomSeed(analogRead(A0));
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(SHOCK, INPUT);
  pinMode(led_start, OUTPUT);
  pinMode(led_end, OUTPUT);
}

void loop() {
  delay(200);
  val = digitalRead(12);    //輕觸開關判斷
  dead = 0;
  if (count == 0 && stopp ==0)    //遊戲結束後，響手機鈴聲一次
  {
    //      digitalWrite(buzzer, HIGH);
    digitalWrite(led_end, HIGH);    
    for ( int ii = 0; ii < 40; ii++ )   //音樂
    {

      tone(led_end, 1000);

      delay(50);

      tone(led_end, 500);

      delay(50);
    }
    stopp++;
    noTone(led_end);    //關
  }
  if (val)    //案輕觸後為true
  {

    count = 75;   //75秒時間
    stopp = 0;    //重製(結束鈴聲)計數
    while (count > 0)   //倒數用迴圈
    {

      digitalWrite(led_start, LOW);
      if (count == 75)
      {
        digitalWrite(led_start, HIGH);
      }


      digitalWrite(latchPin1, LOW);
      shiftOut(dataPin1, clockPin1, LSBFIRST, LEDs[count / 10]);   ///資料位移輸出
      digitalWrite(latchPin1, HIGH);  // 開啟閘門
      digitalWrite(latchPin2, LOW);
      shiftOut(dataPin2, clockPin2, LSBFIRST, LEDs[count % 10]);
      digitalWrite(latchPin2, HIGH);  // 開啟閘門
      for (int i = 0; i < 4; i++)
      {
        delay(200);
        byte isboon = digitalRead(SHOCK);   //觸碰判斷
        Serial.println(dead);           //觸碰次數
        if (isboon == 0)
        {
          digitalWrite(led_end, HIGH);  //如果有導通時就亮
          dead++;
        }
        else {
          digitalWrite(led_end, LOW); //如果沒有導通時就不亮

        }

      }
      if (count > 0)    //倒數
      {
        count -= 1;
      }
      if (dead > 5)   //碰6次，結束歸零
      {
        count = 0;
        dead = 0;
      }
    }

  } 
   //持續亮燈
  digitalWrite(latchPin1, LOW);        
  shiftOut(dataPin1, clockPin1, LSBFIRST, LEDs[count / 10]);   ///資料位移輸出
  digitalWrite(latchPin1, HIGH);  // 開啟閘門
  digitalWrite(latchPin2, LOW);
  shiftOut(dataPin2, clockPin2, LSBFIRST, LEDs[count % 10]);
  digitalWrite(latchPin2, HIGH);  // 開啟閘門
}
