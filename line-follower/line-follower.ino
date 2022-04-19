//
// mapeamento de hardware
//

#define MA1 4
#define MA2 2
#define MA_CONTROL 3
#define SPEED_MA 105
#define MB1 7
#define MB2 5
#define MB_CONTROL 6
#define SPEED_MB 105

#define SENSOR_LEFT 9
#define SENSOR_RIGHT 8

void setup()
{
    pinMode(MA1, OUTPUT);
    pinMode(MA2, OUTPUT);
    pinMode(MB1, OUTPUT);
    pinMode(MB2, OUTPUT);
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
    
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
    analogWrite(MA_CONTROL, SPEED_MA);
    analogWrite(MB_CONTROL, SPEED_MB);
}

void loop()
{
    analogWrite(MA_CONTROL, SPEED_MA);
    analogWrite(MB_CONTROL, SPEED_MB);

    bool readSensorLeft = digitalRead(SENSOR_LEFT);
    bool readSensorRight = digitalRead(SENSOR_RIGHT);

    if (readSensorLeft == false && readSensorRight == false)
    {
        digitalWrite(MA2, HIGH);
        digitalWrite(MA1, LOW);
        digitalWrite(MB2, HIGH);
        digitalWrite(MB1, LOW);
    }
    if (readSensorLeft == true && readSensorRight == false)
    {
        digitalWrite(MA2, LOW);
        digitalWrite(MA1, HIGH);
        digitalWrite(MB2, HIGH);
        digitalWrite(MB1, LOW);
    }
    if (readSensorLeft == false && readSensorRight == true)
    {
        digitalWrite(MA2, HIGH);
        digitalWrite(MA1, LOW);
        digitalWrite(MB2, LOW);
        digitalWrite(MB1, HIGH);
    }
    if (readSensorLeft == true && readSensorRight == true)
    {
        digitalWrite(MA2, LOW);
        digitalWrite(MA1, LOW);
        digitalWrite(MB2, LOW);
        digitalWrite(MB1, LOW);
    }
}