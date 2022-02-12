
#include <Servo.h>

//
// Mapeamento de hardware
//

#define GAS_SENSOR_PIN A0

#define SERVO_PIN 7
#define BUZZER_PIN 8

// Define o nível de gás para disparar o alarme em %
#define GAS_ALARM 55

// Instancia o objeto para controlar o servo
Servo servo;

void setup()
{
    // Inicia a comunicação serial com BaundRate de 9600
    Serial.begin(9600);

    // Define os modos de operação dos pinos
    pinMode(GAS_SENSOR_PIN, INPUT);

    pinMode(SERVO_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Conecta a instância do Servo com o pino
    servo.attach(SERVO_PIN);
}

void loop()
{
    // Realiza a letura do valor no sensor
    int gasValue = analogRead(GAS_SENSOR_PIN);

    // Extrai em percentual o valor lido
    gasValue = map(gasValue, 0, 1023, 0, 100);

    // Imprime o valor na serial
    Serial.println(gasValue);

    // Se passar o limite dispara o alarme e aciona o servo
    if (gasValue > GAS_ALARM)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        servo.write(180);
        
        delay(1000);

        digitalWrite(BUZZER_PIN, LOW);

        delay(1000);
    }
    else
    {
        servo.write(0);
        delay(500);
    }
}