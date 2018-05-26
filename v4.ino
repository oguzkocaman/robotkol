#include <Servo.h> 
#include <SoftwareSerial.h> 
int bluetoothTx = 10; 
int bluetoothRx = 11;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

Servo servo_0;
Servo servo_1;
Servo servo_2;
Servo servo_3;

Servo flag;

byte trigger= 32;
byte echo = 33;
unsigned long sure;
double toplamYol;
int aradakiMesafe;

const int motorPin1  = 22;  // Pin 14 of L293
const int motorPin2  = 23;  // Pin 10 of L293
//Motor B
const int motorPin3  = 25; // Pin  7 of L293
const int motorPin4  = 24;  // Pin  2 of L293

const int s0 = 46;  
const int s1 = 47;  
const int s2 = 48;  
const int s3 = 49;  
const int out = 50; 

int red = 0;  
//int green = 0;  
int blue = 0;  



int pos[4]={70,30,150,20};
int pos1[4]={120,90,100,80};

int sensorPin0 = A0;    // omuz
int sensorPin1 = A1;    // el
int sensorPin2 = A2;    // dirsek
int sensorPin3 = A3;    // kıskaç
int count0, arrayStep, arrayMax, countverz, Taster, stepsMax, steps, time = 1000, del = 1000, temp;
int countt0, arrayyStep, arrayyMax, counttverz, Tasterr, stepssMax, stepss, dell = 1000, tempp;
int sayac1=0;
int sayac2=0;
// arraystep = bellek dizinde arama 
// arrayMax = diziyi maximum hale getirdiğimiz değişken
// countverz = hareketler arası gecikmeyi hesaplayan değişken
// Taster = Buton(hareket kaydedici buton)
// stepsMax = servo için en uzun hareket değişkeni
// steps = kayıtlı konumlar arasında bir hareket için adım değişkeni
unsigned int  verz = 0;
unsigned int  verzz = 0;

long previousMillis1 = 0;
long previousMillis2 = 0;
long previousMillis3 = 0;
long previousMillis4 = 0;
long previousMicros = 0;
unsigned long currentMillis = millis();
unsigned long currentMicros = micros();

long previousMillis11 = 0;
long previousMillis22 = 0;
long previousMillis33 = 0;
long previousMillis44 = 0;
long previousMicross = 0;
unsigned long currentMilliss = millis();
unsigned long currentMicross = micros();

// arrays
int Delay[7] = {0,0,1,3,15,60,300}; 
int Delayy[7] = {0,0,1,3,15,60,300}; 
int SensVal[4]; 
int SensVall[4];
float dif[4], ist[4], sol[4],  dir[4]; 
float diff[4], istt[4], soll[4],  dirr[4];
int joint0[180];
int joint1[180];
int joint2[180];
int joint3[180];
int top = 179; 

int joint00[180];
int joint11[180];
int joint22[180];
int joint33[180];
int topp = 179;
// status 
boolean playmode = false, Step = false;
boolean playmodee = false, Stepp = false;

void setup()
{
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  
  bluetooth.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);  
  digitalWrite(13, HIGH);   
  servo_0.attach(3); 
  servo_1.attach(5);
  servo_2.attach(8);
  servo_3.attach(9);
  flag.attach(30);
  flag.write(90);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(115200); 
  Serial.println("robot ready...");     
  //delay(1000);
  digitalWrite(13, LOW);

  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW); 
}

void loop() 
{
  if(bluetooth.available()>= 2 )
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.println(realservo);
    if (realservo >= 1000 && realservo <1180) {
      int servo1 = realservo;
      servo1 = map(servo1, 1000, 1180, 0, 180);
      servo_0.write(servo1);
      Serial.println("Servo 1 çalışıyor");
      delay(10);
    }
    if (realservo >= 2000 && realservo <2180) {
      int servo2 = realservo;
      servo2 = map(servo2, 2000, 2180, 0, 180);
      servo_1.write(servo2);
      Serial.println("Servo 2 çalışıyor");
      delay(10);
    }
    if (realservo >= 3000 && realservo <3180) {
      int servo3 = realservo;
      servo3 = map(servo3, 3000, 3180, 0, 180);
      servo_3.write(servo3);
      Serial.println("Servo 3 çalışıyor");
      delay(10);
    }
    if (realservo >= 4000 && realservo <4180) {
      int servo4 = realservo;
      servo4 = map(servo4, 4000, 4180, 0, 180);
      servo_2.write(servo4);
      Serial.println("Servo 4 çalışıyor");
      delay(10);
    }
  }
  
  color();
    
  currentMillis = millis(); 
  currentMicros = micros();
    
  Button();
  
  currentMilliss = millis(); 
  currentMicross = micros();

  Button1();
  while((red < blue &&  red < 130 )||(blue < red && blue<165)){
    delay(150);
color();
  if(bluetooth.available()>= 2 )
  break;
  if((blue < red && blue<165)){
    while(1){
      
    color();
    
  currentMillis = millis(); 
  currentMicros = micros();
    
  Button();
  while (digitalRead(4) == true)
      { 
        Serial.println("durdu");
        digitalWrite(13, HIGH); delay(500);   
        digitalWrite(13, LOW); delay(500);
      }
  
  if(!playmode) // manualy 
  {        
    if(currentMillis - previousMillis1 > 25)
    {
      if (arrayStep < top) 
      {
        previousMillis1 = currentMillis; //reset
        readPot(); 
        mapping();  
        move_servo(); 
        //record();   
      } // end counter < max
    } // end step check
  } // ende manualy move
   
  else if(playmode) // play
  {
    if (Step) // 
    {
      digitalWrite(13, HIGH); //LED
      if (arrayStep < arrayMax) 
      {
         
        arrayStep += 1; 
        Read(); 
        calculate(); 
        Step = 0;
        digitalWrite(13, LOW);
        sayac1++;

        
      }
      else // array read finished > start over
      {
        arrayStep = 0; 
        calc_pause(); 
        countverz = 0; 
        while(countverz < verz) 
        { 
          countverz += 1;
          calc_pause();
          digitalWrite(13, HIGH); delay(25);   
          digitalWrite(13, LOW); delay(75); 
        }
      }
      //Serial.println(arrayStep);
    }
    else 
    {
      if (currentMicros - previousMicros > time) 
      { // 
        previousMicros = currentMicros;
        play_servo(); 
      }
    }
  }// ende playmode
  int k=0;
 while(sayac1>=10 && sayac2>=10){
  
  flag.write(160);
  delay(100);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  sure= pulseIn(echo,HIGH);
  toplamYol=(double)sure*0.034;
  aradakiMesafe=toplamYol/2;

  //Serial.println(aradakiMesafe);

  delay(500);
  digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
     
    if(aradakiMesafe<5){
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
      flag.write(90);
      sayac1=0;
      sayac2=0;
      break;
    }
 }
   
  if(red < blue &&  red <130 )
    break;

    if(sayac1>10)
      sayac1=sayac1-1;
    }
  }

  else if(red < blue &&  red <130 ){
    while(1)
    {
   color();
    currentMilliss = millis(); 
  currentMicross = micros();

  Button1();
  while (digitalRead(4) == true)
      { 
        Serial.println("durdu");
        digitalWrite(13, HIGH); delay(500);   
        digitalWrite(13, LOW); delay(500);
      }
                  if(!playmodee) // manualy 
              {        
               if(currentMilliss - previousMillis11 > 25)
               {
                if (arrayyStep < topp) 
                {
                  previousMillis11 = currentMilliss; //reset
                  readPot1(); 
                  mapping1();  
                  move_servo1(); 
                  //record();   
                } // end counter < max
               } // end step check
              } // ende manualy move
            

            else if(playmodee) // play
            {
              if (Stepp) // 
              {
                digitalWrite(13, HIGH); //LED
                if (arrayyStep < arrayyMax) 
                {
                    arrayyStep += 1; 
                    Read1(); 
                    calculate1(); 
                    Stepp = 0;
                    digitalWrite(13, LOW);
                    sayac2++;

        
                }
                else // array read finished > start over
                  {
                    arrayyStep = 0; 
                    calc_pause1(); 
                    counttverz = 0; 
                    while(counttverz < verzz) 
                    { 
                      counttverz += 1;
                      calc_pause1();
                      digitalWrite(13, HIGH); delay(25);   
                      digitalWrite(13, LOW); delay(75); 
                    }
                  }
                  //Serial.println(arrayStep);
                }
          else 
          {
            if (currentMicross - previousMicross > time) 
            { // 
              previousMicross = currentMicross;
              play_servo1(); 
            }
          }
        }

        
        int k=0;
         while(sayac1==10 && sayac2==10){
  flag.write(160);
  delay(100);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  sure= pulseIn(echo,HIGH);
  toplamYol=(double)sure*0.034;
  aradakiMesafe=toplamYol/2;

 // Serial.println(aradakiMesafe);

  delay(500);
  
  digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    
    if(aradakiMesafe<5){
      
      digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    flag.write(90);
    sayac1=0;
    sayac2=0;
    break;
    }
 }
        
        
        if(blue < red && blue<165)
                break;

        if(sayac2>10)
        sayac2=sayac2-1;
        
  }
  }
  }
  

// ---------------------------------------------------------------------------------Hardware pause switch PIN 6
    while (digitalRead(4) == true)
      { 
        digitalWrite(13, HIGH); delay(500);   
        digitalWrite(13, LOW); delay(500);
      }
// ---------------------------------------------------------------------------------- Textout serial
    
    /*if(currentMillis - previousMillis2 > 5000)
    { 
      previousMillis2 = currentMillis;
      /*count0 = 0;
      while(count0 < 4)
      {
        int val = SensVal[count0];
      // val = map(val, 142, 888, 0, 180);
        Serial.println(val);
        //Serial.println("test");
        count0 += 1;
      }
      Serial.println(playmode); 
      Serial.println(arrayStep);    
      Serial.println(arrayMax);    
      Serial.println(" ");    
    }*/
}

// ---------------------------------------------------------------------------------------- sub routinen
void calc_pause() 
{
    readPot();
    temp = SensVal[3];
    if (temp < 0) temp = 0;
    temp = map(temp, 0, 680, 0 ,6); 
    verz = Delay[temp];
    /*Serial.print(temp);
          Serial.print(" ");
          Serial.print(verz);
          Serial.print(" ");
          Serial.println(countverz);*/
}

void calc_pause1() 
{
    readPot1();
    tempp = SensVall[3];
    if (tempp < 0) tempp = 0;
    tempp = map(tempp, 0, 680, 0 ,6); 
    verzz = Delayy[tempp];
    /*Serial.print(temp);
          Serial.print(" ");
          Serial.print(verz);
          Serial.print(" ");
          Serial.println(countverz);*/
}

void readPot() 
{
   SensVal[0] = analogRead(sensorPin0); SensVal[0] += -10;
   SensVal[1] = analogRead(sensorPin1); SensVal[1] += 280; 
   SensVal[2] = analogRead(sensorPin2); SensVal[2] += -50; 
   SensVal[3] = analogRead(sensorPin3); // SensVal[3] += 0;
   //Serial.print(SensVal[2]);Serial.print(" "); // CHECK
}

void readPot1() 
{
   SensVall[0] = analogRead(sensorPin0); SensVall[0] += -10;
   SensVall[1] = analogRead(sensorPin1); SensVall[1] += 280; 
   SensVall[2] = analogRead(sensorPin2); SensVall[2] += -50; 
   SensVall[3] = analogRead(sensorPin3); // SensVal[3] += 0;
   //Serial.print(SensVal[2]);Serial.print(" "); // CHECK
}
void mapping() 
{
  ist[0] = map(SensVal[0], 150, 900, 600, 2400);
  ist[1] = map(SensVal[1], 1000, 100, 550, 2400);
  ist[2] = map(SensVal[2], 120, 860, 400, 2500);
  ist[3] = map(SensVal[3], 1023, 0, 500, 2500);
  //Serial.println(ist[2]); 
}
void mapping1() 
{
  istt[0] = map(SensVall[0], 150, 900, 600, 2400);
  istt[1] = map(SensVall[1], 1000, 100, 550, 2400);
  istt[2] = map(SensVall[2], 120, 860, 400, 2500);
  istt[3] = map(SensVall[3], 1023, 0, 500, 2500);
  //Serial.println(ist[2]); 
}
void record()
{
    joint0[arrayStep] = ist[0]; 
    joint1[arrayStep] = ist[1];
    joint2[arrayStep] = ist[2];
    joint3[arrayStep] = ist[3];
}
void record1()
{
    joint00[arrayyStep] = istt[0]; 
    joint11[arrayyStep] = istt[1];
    joint22[arrayyStep] = istt[2];
    joint33[arrayyStep] = istt[3];
}
void Read()
{
    sol[0] = joint0[arrayStep]; 
    sol[1] = joint1[arrayStep];
    sol[2] = joint2[arrayStep];
    sol[3] = joint3[arrayStep];
}
void Read1()
{
    soll[0] = joint00[arrayyStep]; 
    soll[1] = joint11[arrayyStep];
    soll[2] = joint22[arrayyStep];
    soll[3] = joint33[arrayyStep];
}
void move_servo()
{       
  servo_0.writeMicroseconds(ist[3]); 
  servo_1.writeMicroseconds(ist[2]); 
  servo_2.writeMicroseconds(ist[0]); 
  servo_3.writeMicroseconds(ist[1]); 
}
void move_servo1()
{       
  servo_0.writeMicroseconds(istt[3]); 
  servo_1.writeMicroseconds(istt[2]); 
  servo_2.writeMicroseconds(istt[0]); 
  servo_3.writeMicroseconds(istt[1]); 
}

// ------------------------------------------------------------ single steps calculating
void calculate()
{
     
      dif[0] = abs(ist[0]-sol[0]);
      dif[1] = abs(ist[1]-sol[1]);
      dif[2] = abs(ist[2]-sol[2]);
      dif[3] = abs(ist[3]-sol[3]);

      stepsMax = max(dif[0],dif[1]);
      stepsMax = max(stepsMax,dif[2]);
      stepsMax = max(stepsMax,dif[3]);
     
      //Serial.println(stepsMax); 
      
     /* if (stepsMax < 500) // 
        del = 450;
      else
        del = 300;*/
         
      if (sol[0] < ist[0]) dir[0] = 0-dif[0]/stepsMax; else dir[0] = dif[0]/stepsMax;
      if (sol[1] < ist[1]) dir[1] = 0-dif[1]/stepsMax; else dir[1] = dif[1]/stepsMax;
      if (sol[2] < ist[2]) dir[2] = 0-dif[2]/stepsMax; else dir[2] = dif[2]/stepsMax;
      if (sol[3] < ist[3]) dir[3] = 0-dif[3]/stepsMax; else dir[3] = dif[3]/stepsMax;
        //Serial.println(dir4); 

}
void calculate1()
{
     
      diff[0] = abs(istt[0]-soll[0]);
      diff[1] = abs(istt[1]-soll[1]);
      diff[2] = abs(istt[2]-soll[2]);
      diff[3] = abs(istt[3]-soll[3]);

      stepssMax = max(diff[0],diff[1]);
      stepssMax = max(stepssMax,diff[2]);
      stepssMax = max(stepssMax,diff[3]);
     
      //Serial.println(stepsMax); 
      
     /* if (stepsMax < 500) // 
        del = 450;
      else
        del = 300;*/
         
      if (soll[0] < istt[0]) dirr[0] = 0-diff[0]/stepssMax; else dirr[0] = diff[0]/stepssMax;
      if (soll[1] < istt[1]) dirr[1] = 0-diff[1]/stepssMax; else dirr[1] = diff[1]/stepssMax;
      if (soll[2] < istt[2]) dirr[2] = 0-diff[2]/stepssMax; else dirr[2] = diff[2]/stepssMax;
      if (soll[3] < istt[3]) dirr[3] = 0-diff[3]/stepssMax; else dirr[3] = diff[3]/stepssMax;
        //Serial.println(dir4); 

}
void play_servo()
{
    steps += 1;
    if (steps < stepsMax) 
    {
      //time = del*5;
      if(steps == 20) time = del*4;         
      else if(steps == 40) time = del*3;    
      else if(steps == 80) time = del*2;    
      else if(steps == 100) time = del-1;    
      
      if(steps == stepsMax-200) time = del*2;       
      else if(steps == stepsMax-80) time = del*3;
      else if(steps == stepsMax-40) time = del*4;
      else if(steps == stepsMax-20) time = del*5;
      
      ist[0] += dir[0]; 
      ist[1] += dir[1];
      ist[2] += dir[2];
      ist[3] += dir[3];

      servo_0.writeMicroseconds(ist[3]); 
      servo_1.writeMicroseconds(ist[2]); 
      servo_2.writeMicroseconds(ist[0]); 
      servo_3.writeMicroseconds(ist[1]); 
    }
    else
    {
      Step = 1; 
      steps = 0; 
    }
}

void play_servo1()
{
    stepss += 1;
    if (stepss < stepssMax) 
    {
      //time = del*5;
      if(stepss == 20) time = dell*4;         
      else if(stepss == 40) time = dell*3;    
      else if(stepss == 80) time = dell*2;    
      else if(stepss == 100) time = dell-1;    
      
      if(stepss == stepssMax-200) time = dell*2;       
      else if(stepss == stepssMax-80) time = dell*3;
      else if(stepss == stepssMax-40) time = dell*4;
      else if(stepss == stepssMax-20) time = dell*5;
      
      istt[0] += dirr[0]; 
      istt[1] += dirr[1];
      istt[2] += dirr[2];
      istt[3] += dirr[3];

      servo_0.writeMicroseconds(istt[3]); 
      servo_1.writeMicroseconds(istt[2]); 
      servo_2.writeMicroseconds(istt[0]); 
      servo_3.writeMicroseconds(istt[1]); 
    }
    else
    {
      Stepp = 1; 
      stepss = 0; 
    }
}

void data_out() 
{
  int i = 0;
  while(i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint0[i]); Serial.print(", ");
  }
  Serial.println("Joint0");
  i = 0;
  while(i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint1[i]); Serial.print(", ");
  }
  Serial.println("Joint1");
  i = 0;
  while(i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint2[i]); Serial.print(", ");
  }
  Serial.println("Joint2");
  i = 0;
  while(i < arrayMax)
  {
    digitalWrite(13, HIGH);
    i += 1;
    Serial.print(joint3[i]); Serial.print(", ");
  }
  Serial.println("Joint3");
}

void data_out1() 
{
  int ii = 0;
  while(ii < arrayyMax)
  {
    digitalWrite(13, HIGH);
    ii += 1;
    Serial.print(joint00[ii]); Serial.print(", ");
  }
  Serial.println("Joint00");
  ii = 0;
  while(ii < arrayyMax)
  {
    digitalWrite(13, HIGH);
    ii += 1;
    Serial.print(joint11[ii]); Serial.print(", ");
  }
  Serial.println("Joint11");
  ii = 0;
  while(ii < arrayyMax)
  {
    digitalWrite(13, HIGH);
    ii += 1;
    Serial.print(joint22[ii]); Serial.print(", ");
  }
  Serial.println("Joint22");
  ii = 0;
  while(ii < arrayyMax)
  {
    digitalWrite(13, HIGH);
    ii += 1;
    Serial.print(joint3[ii]); Serial.print(", ");
  }
  Serial.println("Joint33");
}

void Button() // tek tıkla hareket kaydet çift tıkla otonoma al
{
  if (digitalRead(6) == false)
  {
    delay(20);
    if (digitalRead(6) == true) 
    {
      if (Taster == 0)
      {
        Taster = 1;
        previousMillis3 = currentMillis;
        //Serial.print("Status Record "); Serial.println(Taster); 
      }
      else if ((Taster == 1) && (currentMillis - previousMillis3 < 250))
      {
        Taster = 2;
        //Serial.println(Taster); 
      }
      /*else if ((Taster == 2) && (currentMillis - previousMillis3 < 500))
      {
        Taster = 3;
        Serial.println(Taster); 
      }*/
    }
  }
    
    if ((Taster == 1) && (currentMillis - previousMillis3 > 1000)) // write to array
    {
      arrayStep += 1;
      arrayMax = arrayStep;
      record();
      Taster = 0;
      playmode = false;
      Serial.print("Record Step: "); Serial.println(arrayStep);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    }
    else if (Taster == 2)
    {
      arrayStep = 0;
      playmode = true;
      Taster = 0;
      Step = 1;
      Serial.println("playmode ");
      data_out();
      delay(250);   
      digitalWrite(13, LOW);    
    }
    
    if (currentMillis - previousMillis3 > 2000) 
    {
      Taster = 0;
      //Serial.println("restart ");
    }
}

void Button1() // tek tıkla hareket kaydet çift tıkla otonoma al
{
  if (digitalRead(2) == false)
  {
    delay(20);
    if (digitalRead(2) == true) 
    {
      if (Tasterr == 0)
      {
        Tasterr = 1;
        previousMillis33 = currentMilliss;
        //Serial.print("Status Record "); Serial.println(Taster); 
      }
      else if ((Tasterr == 1) && (currentMilliss - previousMillis33 < 250))
      {
        Tasterr = 2;
        //Serial.println(Taster); 
      }
      /*else if ((Taster == 2) && (currentMillis - previousMillis3 < 500))
      {
        Taster = 3;
        Serial.println(Taster); 
      }*/
    }
  }
    
    if ((Tasterr == 1) && (currentMilliss - previousMillis33 > 1000)) // write to array
    {
      arrayyStep += 1;
      arrayyMax = arrayyStep;
      record1();
      Tasterr = 0;
      playmodee = false;
      Serial.print("Record Step1: "); Serial.println(arrayyStep);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    }
    else if (Tasterr == 2)
    {
      arrayyStep = 0;
      playmodee = true;
      Tasterr = 0;
      Stepp = 1;
      Serial.println("playmodee ");
      data_out1();
      delay(250);   
      digitalWrite(13, LOW);    
    }
    
    if (currentMilliss - previousMillis33 > 2000) 
    {
      Tasterr = 0;
      //Serial.println("restart ");
    }
}

void color()  
{  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  //green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

