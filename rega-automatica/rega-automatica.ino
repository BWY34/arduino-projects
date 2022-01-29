#define WATERLESS_PIN A0
#define G_PIN 5
#define Y_PIN 4
#define R_PIN 3
#define MOTORLESS_PIN 6
int wetValue;
int wetState = 1;

void activeBomb(){
  digitalWrite(MOTORLESS_PIN, LOW);
  delay(1000);
  digitalWrite(MOTORLESS_PIN, HIGH);
  delay(2000);
}

int readSensor(){
  if (wetValue > 0 && wetValue <= 360){
    return 1; 
  }

  if (wetValue > 380 && wetValue <= 670){
    return 2;
  }

  if (wetValue > 690 && wetValue < 1024){
    return 3;
  }
  return 0;
}

void upDateLeds(int led){
  digitalWrite(G_PIN, LOW);
  digitalWrite(Y_PIN, LOW);
  digitalWrite(R_PIN, LOW);
  switch (led){
  case 1:
     digitalWrite(G_PIN, HIGH);
     break; 
  case 2:
     digitalWrite(Y_PIN, HIGH);
     break; 
  case 3:
     digitalWrite(R_PIN, HIGH);
     break;     
  }
  
}

void setup() {
  pinMode(WATERLESS_PIN, INPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(Y_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);
  pinMode(MOTORLESS_PIN, OUTPUT);
  digitalWrite(MOTORLESS_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  wetValue = analogRead(WATERLESS_PIN);
  Serial.println("Umidade: ");
  Serial.println(wetValue);
  int tempState = readSensor();
  
  if (tempState != 0)
  {
    wetState = tempState;  
  }
  Serial.println(wetState);
  upDateLeds(wetState);
  if (wetState == 3)
    activeBomb();
  delay(100);
}