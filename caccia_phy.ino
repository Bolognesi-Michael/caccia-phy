#include <LiquidCrystal.h>
LiquidCrystal lcd(9,8,7,6,5,4);
int button1 = A0;
int button2 = A0;
int button3 = A1;
int button4 = A1;
int button5 = A2;
int punti = 0;
int turni = 1;
int vite = 3;
byte Vite[8] =
{B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
byte PiGreco[8] =
{B11111, B01010, B01010, B01010, B01010, B01010, B01010, B10000};
byte Nemico[8] = {
  B00000,
  B00111,
  B00100,
  B00100,
  B10100,
  B11000,
  B10000,
  B00000
};

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  lcd.createChar(0, Vite);
  lcd.createChar(1, PiGreco);
  lcd.createChar(2, Nemico);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  istruzioni();
}
void istruzioni(){
  Serial.println("BENVENUTO IN CACCIA AL PIGRECO");
  Serial.println("------------ISTRUZIONI-----------");
  Serial.println("-premere il pulsante corrispondente al simbolo pigreco per prendere un punto");
  Serial.println("-premere il pulsante corrispondente al nulla od ad un simbolo diverso dal pigreco togliera una vita");
  Serial.println("-ti saranno date 3 vite e perderai se arrivi a 0");
  Serial.println("-vincerai se prenderai almeno 15 punti");
}
void turno(){
  lcd.setCursor(0,0);
  lcd.print("INIZIO PARTITA");
  delay(1500);
  lcd.clear();
  while (vite > 0 && punti != 15){
  int nemico = random(1,6);
  int alleato = random(1,6);
  lcd.setCursor(0,0);
  lcd.print("Turno:" + String(turni));
  lcd.setCursor(13,0);
  stampavite();
  if(alleato == nemico){
    if(alleato == 1){
    nemico+=1;
    }
    else if(alleato == 5){
    nemico-=1;
    }
    else{
    nemico+=1;
    }
    if(!posizione(nemico, alleato)){
    vite--;
    }
    else{
    punti++;
    turni++;
    }
   }
  }
}
void stampavite(){
  if (vite == 3){
    lcd.setCursor(13,0);
    lcd.print(byte(0));
    lcd.setCursor(14,0);
    lcd.print(byte(0));
    lcd.setCursor(15,0);
    lcd.print(byte(0));
  }
    if (vite == 2){
    lcd.setCursor(14,0);
    lcd.print(byte(0));
    lcd.setCursor(15,0);
    lcd.print(byte(0));
  }
    if (vite == 1){
    lcd.setCursor(15,0);
    lcd.print(byte(0));
  }
}
bool posizione(int n, int a){
  lcd.setCursor(n,1);
  lcd.write(byte(2));
  lcd.setCursor(1,a);
  lcd.write(byte(1));
  while(digitalRead(button1) == LOW && digitalRead(button2) == LOW && digitalRead(button3) == LOW && digitalRead(button4) == LOW && digitalRead(button5) == LOW){}  
  if(n == 1){
    if(digitalRead(button1)==HIGH){
      while(digitalRead(button1)==HIGH);
      return true;
    }
    else{
      return false;
    }
  }
    if(n == 2){
    if(digitalRead(button2) == HIGH){
      while(digitalRead(button2)==HIGH);
      return true;
    }
    else{
      return false;
    }
  }
    if(n == 3){
    if(digitalRead(button3) == HIGH){
      while(digitalRead(button3)==HIGH);
      return true;
    }
    else{
      return false;
    }
  }
    if(n == 4){
    if(digitalRead(button4) == HIGH){
      while(digitalRead(button4)==HIGH);
      return true;
    }
    else{
      return false;
    }
  }
    if(n == 5){
    if(digitalRead(button5) == HIGH){
      while(digitalRead(button5)==HIGH);
      return true;
    }
    else{
      return false;
    }
  }
}
void rigioca(){
 lcd.clear();
 lcd.print("rigiocare?");
 lcd.setCursor(7,1);
 lcd.print("Y");
 vite = 3;
 turni = 1;
 punti = 0;
 while(digitalRead(button3) == LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
delay(5000);
turno();
if (vite == 0){
  lcd.clear();
  lcd.print("HAI PERSO");
  delay(2500);
}
if(punti == 15)
  {
  lcd.print("HAI VINTO");
  delay(2500);
  }
rigioca();
}
  
