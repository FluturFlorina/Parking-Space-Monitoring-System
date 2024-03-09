#include <math.h>

// definesc pinii pt ssd
int digit_pin[] = { 26, 29, 30, 31 };
int segA = 22;
int segB = 23;
int segC = 24;
int segD = 25;
int segE = A0;
int segF = 27;
int segG = 28;


// definesc pinii pt semafor
const int trigPin = 9;
const int echoPin = 10;
const int buzz = 8;
const int green = 11;
const int yellow = 12;
const int red = 13;


// definesc variabile
long duration;
int distance;
int counter = 0;
int displayValue = 60;

struct struct_digits { //4 ssd
  int digit[4];
};

void setup() {
  //initialize pinii pentru buzzer, si leduri, proximitate
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);

  //initializez pinii pt ssd
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  
  for (int i = 0; i < 4; i++) {
    pinMode(digit_pin[i], OUTPUT);
  }
}

//afisare pe ssd
void lightNumber(int numberToDisplay) {
  //definesc segmentele pt fiecare cifra
  switch (numberToDisplay) {
    case 0:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;
    case 1:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
    case 2:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;
    case 3:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;
    case 4:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 5:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 6:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 7:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
    case 8:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 9:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;
    case 10: //apresc afisarea
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;
  }
}

//unde se afiseaza cifra, pe ce ssd
void SwitchDigit(int digit) {
  for (int i = 0; i < 4; i++) {
    if (i == digit) {
      digitalWrite(digit_pin[i], LOW);
    } else {
      digitalWrite(digit_pin[i], HIGH);
    }
  }
}

///end ssd

void loop() {

  //semafor
  //senzor proximitate
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

//afisare leduri in functie de distanta + buzz
  if (distance <= 50) 
  {
    digitalWrite(green, HIGH);
    if (distance <= 30) 
    {
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      if (distance <= 10) 
      {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);
        if (distance <=5)
        {
          digitalWrite(buzz, HIGH);
          digitalWrite(green, LOW);
          digitalWrite(yellow, LOW);
          digitalWrite(red, HIGH);
        }
        else
        {
          digitalWrite(buzz, LOW);
        }
      }
       else 
      {
        digitalWrite(red, LOW);
      }
    } 
    else
     {
      digitalWrite(yellow, LOW);
    }
  }
   else
   {
    digitalWrite(green, LOW);
  }

//afisare in monitor serial
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.print("Counter: ");
  Serial.println(counter);
  Serial.print("DisplayValue: ");
  Serial.println(displayValue);

  //ssd

  if (distance <= 5)
   {

    counter++;  
    displayValue = 60 - counter;

    // Afișează pe primele două SSD-uri locurile disponibile
    for (int i = 0; i < 2; i++)
     {
      SwitchDigit(i);
      lightNumber(static_cast<int>(displayValue / pow(10, 1 - i)) % 10);
      delay(200);
    }
    digitalWrite(red, LOW);
  } 
  else 
  {
    // Afișează counterul pe ultimele două SSD-uri locurile ocupate
    for (int i = 2; i < 4; i++) 
    {
      SwitchDigit(i);
      lightNumber(static_cast<int>(counter / pow(10, 3 - i)) % 10);//e cifra unitatilor sau zecilor

      delay(200);
    }
  }
  delay(1000);  // Așteaptă 1 secundă între afișări
}
