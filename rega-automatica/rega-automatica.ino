//
// Mapeamento de hardware
//

// Pino conectado ao sensor de umidade de solo
#define WATER_SENSOR_PIN A0

// Pinos dos leds de monitoramento
#define LEDG_PIN 5  // Verde
#define LEDY_PIN 4  // Amarelo
#define LEDR_PIN 3  // Vermelho

// Pino conectado ao relé reponsável por ativar a rega
#define BOMB_RELAY_PIN 6

//
// Percentuais de umidade, ajustar conforme a planta
//
//            RED      YELLOW     GREEN
// SECO 0% ........./........../.......... 100% ÚMIDO
//            REGA
//

#define HIGH_HUMIDITY 70    // Umidade alta
#define MEDIUM_HUMIDITY 20  // Umidade média

#define HUMIDITY_DELTA 2    // Intervalo para os estados mudarem

//
// Globais
//

// Valor da umidade lida pelo sensor
int wetValue = 0;

// Estdado do led, usando (1 VERDE), (2 AMARELO),       (3 VERMELHO) 
// Estado da umidade      (1 UMIDO), (2 INTERMEDIÁRIO), (3 SECO) 
int wetState = 1;

// Função para acionar a bomba de água
void activeBomb()
{
    digitalWrite(BOMB_RELAY_PIN, LOW);
    delay(150);

    digitalWrite(BOMB_RELAY_PIN, HIGH);
    delay(4000);
}

// Função para ler o estado atual do solo
// (1 UMIDO), (2 INTERMEDIÁRIO), (3 SECO) 
int readSensor()
{
    if (wetValue > (HIGH_HUMIDITY + HUMIDITY_DELTA) && wetValue <= 100)
        return 1;

    if (wetValue > (MEDIUM_HUMIDITY + HUMIDITY_DELTA) && wetValue <= (HIGH_HUMIDITY - HUMIDITY_DELTA))
        return 2;

    if (wetValue > 0 && wetValue <= (MEDIUM_HUMIDITY - HUMIDITY_DELTA))
        return 3;

    return 0;
}

// Recebe um estado e aciona o led correspondente
// (1 VERDE), (2 AMARELO), (3 VERMELHO) 
void upDateLeds(int led)
{
    digitalWrite(LEDG_PIN, LOW);
    digitalWrite(LEDY_PIN, LOW);
    digitalWrite(LEDR_PIN, LOW);
    
    switch (led)
    {
        case 1:
            digitalWrite(LEDG_PIN, HIGH);
            break; 
        case 2:
            digitalWrite(LEDY_PIN, HIGH);
            break; 
        case 3:
            digitalWrite(LEDR_PIN, HIGH);
            break;     
    }
}

// Quando o arduino liga
void setup()
{
    // Inicia o comunicação serial com BaundRate 9600
    Serial.begin(9600);

    // Seta o modo de operação de cada pino
    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(LEDG_PIN, OUTPUT);
    pinMode(LEDY_PIN, OUTPUT);
    pinMode(LEDG_PIN, OUTPUT);
    pinMode(BOMB_RELAY_PIN, OUTPUT);

    // Coloca o pino do relay em alto para desligar a bomba
    digitalWrite(BOMB_RELAY_PIN, HIGH);
}

void loop()
{
    // Realiza a leitura e converte para porcentagem o valor
    // lido no sensor
    wetValue = analogRead(WATER_SENSOR_PIN);
    wetValue = map(wetValue, 1023, 0, 0, 100); // 1023 -> 0% / 0 -> 100%

    Serial.print("Umidade: ");
    Serial.println(wetValue);

    // Verifica em qual estado a planta está
    int tempState = readSensor();

    // Se não estiver entre os deltas (Região duvidosa) atualiza o
    // estado, caso estiver nos deltas, conserva o estado anterior
    if (tempState != 0)
        wetState = tempState;

    // Atualiza os leds
    upDateLeds(wetState);

    // Caso estiver no SECO, rega a planta
    if (wetState == 3)
        activeBomb();

    delay(100);
}