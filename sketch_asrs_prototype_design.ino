
#include <LiquidCrystal.h>
#include <Keypad.h> 
#include <elapsedMillis.h>
#include <SPI.h>
#include <RFID.h >

// DEFINE STAGE

LiquidCrystal lcd(35, 37, 47, 45, 43, 41);

elapsedMillis timeElapsed;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {16, 17, 23, 25}; 
byte colPins[COLS] = {27, 29, 31, 33}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

#define SS_PIN             53
#define RST_PIN            1 

RFID rfid(SS_PIN,RST_PIN);

#define X_STEP_PIN            54
#define X_DIR_PIN               55
#define X_ENABLE_PIN       38
#define X_MIN_PIN              3
#define X_MAX_PIN             2

#define Y_STEP_PIN            60
#define Y_DIR_PIN               61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN             14
#define Y_MAX_PIN            15

#define Z_STEP_PIN            46
#define Z_DIR_PIN              48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN             18
#define Z_MAX_PIN            19

#define SDPOWER            -1
#define LED_PIN               13

#define PS_ON_PIN          12
#define KILL_PIN               -1

#define MTSAA              49
#define MTSAB              64 
#define MTSBA              42
#define MTSBB              44 
#define MTSCA              65
#define MTSCB              66 
#define STOPP               59 

//INITIAL SETUP STAGE

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(LED_PIN  , OUTPUT);
  
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);
  
  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);
  
  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);

  pinMode(X_MIN_PIN  , INPUT_PULLUP);
  pinMode(Y_MIN_PIN    , INPUT_PULLUP);
  pinMode(Z_MIN_PIN    , INPUT_PULLUP);

  pinMode(MTSAA    , INPUT);
  pinMode(MTSAB    , INPUT);
  pinMode(MTSBA    , INPUT);
  pinMode(MTSBB    , INPUT);
  pinMode(MTSCA    , INPUT);
  pinMode(MTSCB    , INPUT);
  pinMode(STOPP    , INPUT);
  
   digitalWrite(X_ENABLE_PIN    , LOW);
   digitalWrite(Y_ENABLE_PIN    , LOW);
   digitalWrite(Z_ENABLE_PIN    , LOW);

  SPI.begin();      // Initiate  SPI bus
  rfid.init();   // Initiate MFRC522
}

//LOOP STAGES

void loop () {
 lcd.setCursor(0,0);
 lcd.print("ASRS BILLY");
 lcd.setCursor(1,1);
 lcd.print("choose mode:");
 char customKey = customKeypad.getKey();
 int pil = customKey - '0' ;
 
if(pil){
if(pil==1)
  { Serial.println("pil 1");
    lcd.clear();
    lcd.print("Pendan");
    delay (1000);
    lcd.clear();
    pendan();
  }

if(pil==2)
  { Serial.println("pil 2");
    lcd.clear();
    lcd.print("Coordinate");
    delay (1000);
    lcd.clear();
    coor();
  }

if(pil==3)
  { Serial.println("pil 3");
    lcd.clear();
    lcd.print("RFID");
    delay (1000);
    lcd.clear();
    rfidd();
  }
  
if(pil==4)
  { Serial.println("pil 4");
    lcd.clear();
    lcd.print("Auto Home");
    delay(1000);
    lcd.clear();
    ahome();
  }
  
  if(pil>=5)
  { Serial.println("Wrong Input");
    lcd.clear();
    lcd.print("Wrong Input");
    delay(1000);
    lcd.clear();
  }
}
}

void coor () {
int smb = 0;
lcd.clear();
lcd.print ("choose axis:");

do{
char smbgr = customKeypad.getKey();
smb = smbgr - '0' ;
Serial.println(smb); 
}while(smb<=0);  

if(smb){
if(smb==1){
  lcd.setCursor(1,1);
  lcd.print ("X and Y axis");
  delay(1000);  
  lcd.clear();
  sumbuxy();
}
  
if(smb==2){
  lcd.setCursor(1,1);
  lcd.print ("Z Axis");
  delay(1000);  
  lcd.clear();
  sumbuz();
}

if(smb>=3){
  lcd.setCursor(1,1);
  lcd.print ("Wrong Input");
  delay(1000);  
  lcd.clear();
}
}
}

void sumbuxy () {
lcd.print ("Motor X: ?");
int motx = 0;
do{
char motorx = customKeypad.getKey();
motx = motorx - '0' ;
Serial.println(motx);  
}while(motx<=0);

if (motx<=3)
  { Serial.print(motx);
    Serial.println("langkah X");
    lcd.setCursor(1,1);
    lcd.print(motx);
    lcd.print("langkah");
    delay(1000);
    lcd.clear();
    
    unsigned long stime ;
    unsigned long etime ;
    int loopcount = 0;
    int putarx = 0;
    int clcx = 0;
    lcd.print ("clockwise X ?");   
    
    do{
    char clccx = customKeypad.getKey();
    clcx = clccx - '0' ;
    Serial.println(clcx);  
    }while(clcx<=0);
    
    if (clcx==1){
    Serial.println(clcx);
    lcd.setCursor(1,1);
    lcd.print("NO");
    delay(1000);
    lcd.clear();}

    else if (clcx==2){
    Serial.println(clcx);
    lcd.setCursor(1,1);
    lcd.print("YES");
    delay(1000);
    lcd.clear();}

    else  {
    Serial.println(clcx);
    lcd.setCursor(1,1);
    lcd.print("Wrong Input"); 
    delay(1000);}
    
    lcd.print ("Motor Y: ?");
    int moty = 0;
    do{
    char motory = customKeypad.getKey();
    moty = motory - '0' ;
    Serial.println(moty);   
    }while(moty<=0);

    if (moty<=3)
   {Serial.print(moty);
    Serial.println("langkah Y");
    lcd.setCursor(1,1);
    lcd.print(moty);
    lcd.print("langkah");
    delay(1000);
    lcd.clear();
    
    unsigned long  putary = 0;
    int clcy = 0;
    lcd.print ("clockwise? Y");

    do{
    char clccy = customKeypad.getKey();
    clcy = clccy - '0' ;
    Serial.println(clcy);  
    }while(clcy<=0);
    
     if (clcy==1){
     Serial.println(clcy);
     lcd.setCursor(1,1);
     lcd.print("NO");
     delay(1000);
     lcd.clear();}
                 
     else if (clcy==2){
     Serial.println(clcy);
     lcd.setCursor(1,1);
     lcd.print("YES");
     delay(1000);
     lcd.clear();}
                 
     else {
     Serial.println(clcy);
     lcd.setCursor(1,1);
     lcd.print("Wrong Input"); 
     delay(1000);}
                       
 if (clcx==1)    {lcd.print ("processing..");
                 putarx = motx * 2257 * 3; 
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putarx && digitalRead(X_MIN_PIN)){
                 digitalWrite(X_DIR_PIN    , HIGH);
                 digitalWrite(X_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(X_STEP_PIN    , LOW);
                 etime = timeElapsed;
                 loopcount++;
                 }
                 Serial.print("Total looping : ");
                 Serial.println(loopcount,DEC);
                 }

 else if (clcx==2){lcd.print ("processing..");
                 putarx = motx * 2257 * 3; 
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putarx){
                 digitalWrite(X_DIR_PIN    , LOW);
                 digitalWrite(X_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(X_STEP_PIN    , LOW);
                 etime = timeElapsed;
                 loopcount++;
                 }
                 Serial.print("Total looping : ");
                 Serial.println(loopcount,DEC);
                 }
 
    else        {}
    
    if (clcy==1){lcd.print ("processing..");
                 putary = moty * 4218 * 3; 
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putary && digitalRead(Y_MIN_PIN)){
                 digitalWrite(Y_DIR_PIN    , HIGH);     
                 digitalWrite(Y_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(Y_STEP_PIN    , LOW);
                 etime = timeElapsed; 
                 loopcount++;               
                 }
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putary && digitalRead(Y_MIN_PIN)){
                 digitalWrite(Y_DIR_PIN    , HIGH);     
                 digitalWrite(Y_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(Y_STEP_PIN    , LOW);
                 etime = timeElapsed;               
                 }
                 Serial.print("Total looping : ");
                 Serial.println(loopcount,DEC);
                 }
                 
else if (clcy==2){lcd.print ("processing..");
                 putary = moty * 4218 * 3 ; 
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putary){
                 digitalWrite(Y_DIR_PIN    , LOW);     
                 digitalWrite(Y_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(Y_STEP_PIN    , LOW);
                 etime = timeElapsed;
                 loopcount++;
                 }
                 stime=timeElapsed;
                 etime=stime;
                 while((etime-stime)<=putary){
                 digitalWrite(Y_DIR_PIN    , LOW);     
                 digitalWrite(Y_STEP_PIN    , HIGH);
                 delay(1);
                 digitalWrite(Y_STEP_PIN    , LOW);
                 etime = timeElapsed;
                 }
                 Serial.print("Total looping : ");
                 Serial.println(loopcount,DEC);
                 }       
    }
    if (moty>=4){lcd.print("Wrong input"); lcd.clear();}
    }
    if (motx>=4){lcd.print("Wrong input"); lcd.clear();}
    
    lcd.setCursor(1,1);
    lcd.print ("Done");
    delay (1000);
    lcd.clear();
}

void sumbuz (){
unsigned long stime ;
unsigned long etime ;
int loopcount = 0;
lcd.print ("Motor Z: ?");
int motz = 0;
do{
char motorz = customKeypad.getKey();
motz = motorz - '0' ;
Serial.println(motz);   
}while(motz<=0);

    if(motz==1){
      lcd.setCursor(1,1);
      lcd.print("mengambil");
      Serial.println("mengambil");
      delay(1000);
      lcd.clear();
      lcd.print("Processing..");
      stime=timeElapsed;
      etime=stime;
      
      while((etime-stime)<=4150){
      digitalWrite(Z_DIR_PIN    , LOW);
      digitalWrite(Z_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Z_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}
      
      while((etime-stime)<=6150){
      digitalWrite(Y_DIR_PIN    , LOW);
      digitalWrite(Y_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Y_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}      

      while((etime-stime)<=10300 && digitalRead(Z_MIN_PIN)){
      digitalWrite(Z_DIR_PIN    , HIGH);
      digitalWrite(Z_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Z_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;} 

      while((etime-stime)<=12300){
      digitalWrite(Y_DIR_PIN    , HIGH);
      digitalWrite(Y_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Y_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}
      
      Serial.print("Total looping : ");
      Serial.println(loopcount,DEC);
      }
      
    else if(motz==2){
      lcd.setCursor(1,1);
      lcd.print("meletakkan");
      Serial.println("meletakkan");
      delay(1000);
      lcd.clear();
      lcd.print("Processing..");
      stime=timeElapsed;
      etime=stime;

      while((etime-stime)<=2000){
      digitalWrite(Y_DIR_PIN    , LOW);
      digitalWrite(Y_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Y_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}

      while((etime-stime)<=6150){
      digitalWrite(Z_DIR_PIN    , LOW);
      digitalWrite(Z_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Z_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}
      
      while((etime-stime)<=8150){
      digitalWrite(Y_DIR_PIN    , HIGH);
      digitalWrite(Y_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Y_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}
      
      while((etime-stime)<=12300  && digitalRead(Z_MIN_PIN)){
      digitalWrite(Z_DIR_PIN    , HIGH);
      digitalWrite(Z_STEP_PIN    , HIGH);
      delay(1);
      digitalWrite(Z_STEP_PIN    , LOW);
      etime = timeElapsed;
      loopcount++;}

      Serial.print("Total looping : ");
      Serial.println(loopcount,DEC);
      }
      
    else{lcd.print("Wrong input"); delay(1000);}
  
  lcd.setCursor(1,1);
  lcd.print("Done");
  delay(1000);
  lcd.clear();
}

void pendan () {
  lcd.clear();
  lcd.print("Pendan is Ready");
  
  while (digitalRead(STOPP)==0){
    
    if(digitalRead(MTSAA)!=0){     
    while (digitalRead(MTSAA)!=0){
    digitalWrite(X_DIR_PIN    , LOW);
    digitalWrite(X_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN    , LOW);
  }}

    if(digitalRead(MTSAB)!=0){  
    while (digitalRead(MTSAB)!=0 && digitalRead(X_MIN_PIN)){
    digitalWrite(X_DIR_PIN    , HIGH);
    digitalWrite(X_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN    , LOW);
  }}
  
    if(digitalRead(MTSBA)!=0){ 
    while (digitalRead(MTSBA)!=0){
    digitalWrite(Y_DIR_PIN    , LOW);
    digitalWrite(Y_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Y_STEP_PIN    , LOW);
  }}

    if(digitalRead(MTSBB)!=0){ 
    while (digitalRead(MTSBB)!=0 && digitalRead(Y_MIN_PIN)){
    digitalWrite(Y_DIR_PIN    , HIGH);
    digitalWrite(Y_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Y_STEP_PIN    , LOW);
  }}

    if(digitalRead(MTSCA)!=0){
    while (digitalRead(MTSCA)!=0){
    digitalWrite(Z_DIR_PIN    , LOW);
    digitalWrite(Z_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Z_STEP_PIN    , LOW);
  }}

    if(digitalRead(MTSCB)!=0){
    while (digitalRead(MTSCB)!=0 && digitalRead(Z_MIN_PIN)){
    digitalWrite(Z_DIR_PIN    , HIGH);
    digitalWrite(Z_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Z_STEP_PIN    , LOW);
  }}
  
  }
  lcd.setCursor(1,1);
  lcd.print("Done");
  delay(1000);
  lcd.clear();
}

void ahome () {
  lcd.clear();
  lcd.print("Go To Home");
  while(digitalRead(X_MIN_PIN)){
    digitalWrite(X_DIR_PIN    , HIGH);
    digitalWrite(X_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(X_STEP_PIN    , LOW);
    }
  while(digitalRead(Y_MIN_PIN)){
    digitalWrite(Y_DIR_PIN    , HIGH);
    digitalWrite(Y_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Y_STEP_PIN    , LOW);
    }
  while(digitalRead(Z_MIN_PIN)){
    digitalWrite(Z_DIR_PIN    , HIGH);
    digitalWrite(Z_STEP_PIN    , HIGH);
    delay(1);
    digitalWrite(Z_STEP_PIN    , LOW);
    }
  lcd.setCursor(1,1);
  lcd.print("Done");
  delay(1000);
  lcd.clear();
}

void rfidd () {
  ahome();
  while(digitalRead(STOPP)==0){
  lcd.clear();
  lcd.print("Insert Card:");
  lcd.setCursor(1,1);
unsigned long stime ;
unsigned long etime ;

   if(rfid.isCard()){
        if(rfid.readCardSerial()){
            lcd.print(rfid.serNum[0]);
            lcd.print(" ");
            lcd.print(rfid.serNum[1]);
            lcd.print(" ");
            lcd.print(rfid.serNum[2]);
            lcd.print(" ");
            lcd.println(rfid.serNum[3]);
            
            delay(1000);
            lcd.clear();
            int frontser = rfid.serNum[0];
   
            if(frontser==198)
            {
              lcd.setCursor(1,1);
              lcd.print("mengambil");
              Serial.println("mengambil");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=4150){
              digitalWrite(Z_DIR_PIN    , LOW);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=6150){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}      

              while((etime-stime)<=10300 && digitalRead(Z_MIN_PIN)){
              digitalWrite(Z_DIR_PIN    , HIGH);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;} 

              while((etime-stime)<=12300){
              digitalWrite(Y_DIR_PIN    , HIGH);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Go To B2");
              Serial.println("Go To B2");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=(2257*6)){
              digitalWrite(X_DIR_PIN    , LOW);
              digitalWrite(X_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(X_STEP_PIN    , LOW);
              etime = timeElapsed;}

              stime=timeElapsed;
              etime=stime;

              while((etime-stime)<=4218*3){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=4218*3){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}
              
              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Meletakkan");
              Serial.println("Meletakkan");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=2000){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              while((etime-stime)<=6150){
              digitalWrite(Z_DIR_PIN    , LOW);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=8150){
              digitalWrite(Y_DIR_PIN    , HIGH);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=12300  && digitalRead(Z_MIN_PIN)){
              digitalWrite(Z_DIR_PIN    , HIGH);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}

              ahome();
        }

        else if(frontser==39)
             {
              lcd.setCursor(1,1);
              lcd.print("mengambil");
              Serial.println("mengambil");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=4150){
              digitalWrite(Z_DIR_PIN    , LOW);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=6150){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}      

              while((etime-stime)<=10300 && digitalRead(Z_MIN_PIN)){
              digitalWrite(Z_DIR_PIN    , HIGH);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;} 

              while((etime-stime)<=12300){
              digitalWrite(Y_DIR_PIN    , HIGH);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Go To C1");
              Serial.println("Go To C1");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=(2257*9)){
              digitalWrite(X_DIR_PIN    , LOW);
              digitalWrite(X_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(X_STEP_PIN    , LOW);
              etime = timeElapsed;}

              stime=timeElapsed;
              etime=stime;

              while((etime-stime)<=4218*6){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=4218*6){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}
              
              lcd.clear();
              lcd.setCursor(1,1);
              lcd.print("Meletakkan");
              Serial.println("Meletakkan");
              stime=timeElapsed;
              etime=stime;
              
              while((etime-stime)<=2000){
              digitalWrite(Y_DIR_PIN    , LOW);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}

              while((etime-stime)<=6150){
              digitalWrite(Z_DIR_PIN    , LOW);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=8150){
              digitalWrite(Y_DIR_PIN    , HIGH);
              digitalWrite(Y_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Y_STEP_PIN    , LOW);
              etime = timeElapsed;}
      
              while((etime-stime)<=12300  && digitalRead(Z_MIN_PIN)){
              digitalWrite(Z_DIR_PIN    , HIGH);
              digitalWrite(Z_STEP_PIN    , HIGH);
              delay(1);
              digitalWrite(Z_STEP_PIN    , LOW);
              etime = timeElapsed;}

              ahome();
        }

        else 
        {lcd.clear();
         lcd.setCursor(1,1);
         lcd.print("Not Authorized");
         delay(1000);
        }
        }
    rfid.halt();
   } 
  }
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Finished");
  delay(1000);
  lcd.clear();
}

