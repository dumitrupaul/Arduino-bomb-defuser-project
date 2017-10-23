#include <LiquidCrystal.h>
#include <Tone.h>
#define SEC 30
#define MIN 0
#define lungimecod 3
int v[lungimecod]={8,8,9};

int terminat;
Tone tone1;

int Scount = SEC; // count seconds
int Mcount = MIN; // count minutes
int Hcount = 0; // count hours
long secMillis = 0; // store last time for second add
long interval = 1000; // interval for seconds
int merge=1;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  tone1.begin(10);
  lcd.begin(16, 2);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  lcd.setCursor(1,0);
  lcd.print("Dezamorseaza!!");
}

void loop() {
 START:
 int b7,b8,b9;
 b7=digitalRead(7);
 b8=digitalRead(8);
 b9=digitalRead(9);
    while(b7 == 0 && b8 == 0 && b9 == 0) {
      b7=digitalRead(7);
      b8=digitalRead(8);
      b9=digitalRead(9);
      if(timer()==1){
        reset();
        goto START;
      }
  }
 int s7=0,s8=0,s9=0;
 while(b7==1){
    s7=1;
    b7=digitalRead(7);
    if(timer()==1){
        reset();
        goto START;
      }
    }
    
  if(s7==1) {
  if(v[terminat]!=7) merge=0;
  terminat++;
  delay(50);
  }
  
  while(b8==1){
    s8=1;
    b8=digitalRead(8);
    if(timer()==1){
        reset();
        goto START;
      }
    }
  if(s8==1) {
    if(v[terminat]!=8) merge=0;
    terminat++;
    delay(50);
  }
  
  while(b9==1){
    s9=1;
    b9=digitalRead(9);
    if(timer()==1){
        reset();
        goto START;
      }
    }
    
  if(s9==1) {
    if(v[terminat]!=9) merge=0;
    terminat++;
    delay(50);
  }
  
  if(terminat==1) lcd.clear();
  
  lcd.setCursor(terminat,0);
  lcd.print("X");
  
  if(terminat==lungimecod){
  if(merge==1)
  {
     lcd.clear();
     lcd.setCursor(5,0);
     lcd.print("BOMBA");
     lcd.setCursor(3,1);
     lcd.print("DEZAMORSATA");
     while(1){}
  }
  else{
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Mai incearca");
    merge=1;
    terminat=0;
  }
  }

}

void reset(){
  Scount=SEC;
  Mcount=MIN;
  merge=1;
  secMillis=0;
  terminat=0;
  lcd.clear();
  lcd.noCursor();
}

bool timer()
{
  if (Hcount <= 0)
  {
    if ( Mcount < 0 )
    {
      lcd.noCursor();
      lcd.clear();
      lcd.home();
      //lcd.setCursor (4,0);
      lcd.print("X X BOMBA A  X X");
      lcd.setCursor (0,1);
      lcd.print(" _  EXPLODAT  _ ");
      int b7=0,b8=0,b9=0;
      int i=0;
      while (Mcount < 0 && b7==0 && b8==0 && b9==0) 
      {
        tone1.play(NOTE_A2, 90);
        delay(100); 
        if(i>30){
        b7=digitalRead(7);
        b8=digitalRead(8);
        b9=digitalRead(9);
        }
        i++;
      }
      return 1;
    } 
  }

  lcd.setCursor (0,1); // sets cursor to 2nd line
  lcd.print ("Timp:");

  if (Hcount >= 10)
    {
      lcd.setCursor (7,1);
      lcd.print (Hcount);
    }
  if (Hcount < 10) 
    {
      lcd.setCursor (7,1);
      lcd.write ("0");
      lcd.setCursor (8,1);
      lcd.print (Hcount);
    }

  lcd.print (":");

  if (Mcount >= 10)
    {
      lcd.setCursor (10,1);
      lcd.print (Mcount);
    }
  if (Mcount < 10) 
    {
      lcd.setCursor (10,1);
      lcd.write ("0");
      lcd.setCursor (11,1);
      lcd.print (Mcount);
    }
    
  lcd.print (":");

  if (Scount >= 10) 
    {
      lcd.setCursor (13,1);
      lcd.print (Scount);
    }
  if (Scount < 10) 
    {
      lcd.setCursor (13,1);
      lcd.write ("0");
      lcd.setCursor (14,1);
      lcd.print (Scount);
    }

  if (Hcount <0) 
    {
      Hcount = 0; 
    }

  if (Mcount <0) 
    {
      Hcount --; 
      Mcount = 59; 
    }

  if (Scount <1) // if 60 do this operation
    {
      Mcount --; // add 1 to Mcount
      Scount = 59; // reset Scount
    }

  if (Scount > 0) // do this oper. 59 times
    {
      unsigned long currentMillis = millis();
  
      if(currentMillis - secMillis > interval) 
        {
          tone1.play(NOTE_G5, 200);
          secMillis = currentMillis;
          Scount --; // add 1 to Scount
          delay(10); // waits for a second
          delay(10); // waits for a second
        }
    }
return 0;
}
