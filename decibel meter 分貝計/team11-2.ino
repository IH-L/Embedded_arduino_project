int micPin=A0;  
int potPin = A5;
int  ledPin=13;
int micVal=0,val=0;
char d[5]="  ";   
byte lightPin1=12,lightPin2=11,lightPin3=10,lightPin4=9,lightPin5=8,lightPin6=7,lightPin7=6,lightPin8=5;   //led的音量顯示器
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);   //pinmpde output setiing
  pinMode(lightPin1,OUTPUT);
  pinMode(lightPin2,OUTPUT);
  pinMode(lightPin3,OUTPUT);
  pinMode(lightPin4,OUTPUT);
  pinMode(lightPin5,OUTPUT);
  pinMode(lightPin6,OUTPUT);
  pinMode(lightPin7,OUTPUT);
  pinMode(lightPin8,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  micVal=analogRead(micPin);
  val=analogRead(potPin);
  Serial.print(micVal);     ///output test
  Serial.print(d);          ///output test
  Serial.println(val);      ///output test
  digitalWrite(lightPin1,LOW);      //將led熄滅
  digitalWrite(lightPin2,LOW);
  digitalWrite(lightPin3,LOW);
  digitalWrite(lightPin4,LOW);
  digitalWrite(lightPin5,LOW);
  digitalWrite(lightPin6,LOW);
  digitalWrite(lightPin7,LOW);
  digitalWrite(lightPin8,LOW);  
  if(micVal>50)                  //依據數值點亮燈炮
  {
    digitalWrite(lightPin1,HIGH);
    }
  else 
  {
    digitalWrite(lightPin1,LOW);
    }
   if(micVal>150)
  {
    digitalWrite(lightPin2,HIGH);
    }
  else 
  {
    digitalWrite(lightPin2,LOW);
    }
   if(micVal>250)
  {
    digitalWrite(lightPin3,HIGH);
    }
  else 
  {
    digitalWrite(lightPin3,LOW);
    }
  if(micVal>350)
  {
    digitalWrite(lightPin4,HIGH);
    }
  else 
  {
    digitalWrite(lightPin4,LOW);
    }
   if(micVal>450)
  {
    digitalWrite(lightPin5,HIGH);
    }
  else 
  {
    digitalWrite(lightPin5,LOW);
    }
  if(micVal>550)
  {
    digitalWrite(lightPin6,HIGH);
    }
  else 
  {
    digitalWrite(lightPin6,LOW);
    }
   if(micVal>650)
  {
    digitalWrite(lightPin7,HIGH);
    }
  else 
  {
    digitalWrite(lightPin7,LOW);
    } 
    if(micVal>750)
  {
    digitalWrite(lightPin8,HIGH);
    }
  else 
  {
    digitalWrite(lightPin8,LOW);
    } 
  delay(200);     //delay
}
