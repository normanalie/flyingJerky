/*

*/
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//IMU DFRobot
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <DFRobot_QMC5883.h> //Compass
#include "DFRobot_BMP280.h" //Baro+temp

//import locaux
#include "ir.h"

Servo throttle, roll, pitch, yaw, flightmode;
FreeSixIMU imu = FreeSixIMU();
DFRobot_QMC5883 imuCompass;
DFRobot_BMP280_IIC   imuBaro(&Wire, DFRobot_BMP280_IIC::eSdo_low);


#define servoT 1
#define servoR 2
#define servoP 3
#define servoY 4
#define servoFM 5
#define throttleSOS 0   //Valeur de secours à envoyer pour disarm le CC3D
#define flightmodeSOS 0

float servoPos[] = {0, 0, 0, 0, 0};  //GLOBAL Valeurs des servos (0-180) pour le CC3D. Throttle, Roll, Pitch, Yaw, FlightMode 

float seuilDistance = 10; //Seuil pour lequel le drone ne se rapproche pas plus. 
double irDistance[] = {}; //GLOBAL Front, Back, Left, Right, Up, Down
float readSensor;
const char*  irPin[] = {'A0', 'A1', 'A2', 'A3', 'A4', 'A5'}; //GLOBAL Front, Back, Left, Right, Up, Down

bool imuWired = true; //Permet de désactiver l'IMU si il n'est pas connecté
float imuAngles[3]; //yaw, pitch et roll mesure par l'imu

bool started = true; //Permet d'empecher d'entrer dans void loop si false
int time = millis(); //Variable pour créer des timers non bloquants

void setup(){
    char imuAbort; //Variable locale pour passer l'initialisation de l'IMU (bloquante si pas d'IMU connecté)

    Serial.begin(9600);
    Wire.begin();

    throttle.attach(servoT);
    roll.attach(servoR);
    pitch.attach(servoP);
    yaw.attach(servoY);
    flightmode.attach(servoFM);

    Serial.println(F("Waiting for IMU..."));
    time = millis();
    while(millis() < time+5000)
    {
        imuAbort = Serial.read();
    }
    if(imuAbort == "n"){
        imuWired = false;
    }
    if(imuWired){ 
        imu.init(); 
    }

    if(!started){
        Serial.println(F("Fatal error during boot process. Program stop here. Goodbye (⩾﹏⩽)"));
        delay(100); //Time for print
        exit(0);
    }
    if(started){
        Serial.println(F("Boot sequence complete. Goodluck (｡◕‿◕｡)"));
    }
}

void servoUpdate(){
    throttle.write(servoPos[0]);
    roll.write(servoPos[1]);
    pitch.write(servoPos[2]);
    yaw.write(servoPos[3]);
    flightmode.write(servoPos[4]);
}



void printValueSerial(bool ir = true, bool imu = true, bool baro = true, bool servos = true){
    if(ir){
        Serial.println();
        Serial.print(F("------------ ir Sensors values ------------"));
        for (int i = 0; i < sizeof(irPin) / sizeof(irPin[0]); i++){
            Serial.print("Valeur capteur ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(irDistance[i]);
        }
    }

    if(imu){
        Serial.println();
        Serial.print(F("------------ IMU values ------------"));
        Serial.print("Yaw: ");
        Serial.print(imuAngles[0]);
        Serial.print(" || Pitch: ");
        Serial.print(imuAngles[1]);
        Serial.print(" || Roll: ");
        Serial.println(imuAngles[2]);
    }

    if(baro){                      //TO IMPLEMENT
        Serial.println();
        Serial.print(F("------------ Barometer values ------------"));
        Serial.print("hPa: NotImplemented");
    }

    if(servos){
        Serial.println();
        Serial.print(F("------------ Servos values ------------"));
        Serial.print("Throttle: ");
        Serial.println(servoPos[0]);
        Serial.print("Roll: ");
        Serial.print(servoPos[1]);
        Serial.print(" || Pitch: ");
        Serial.print(servoPos[2]);
        Serial.print(" || Yaw: ");
        Serial.println(servoPos[3]);
        Serial.print("FlightMode: ");
        Serial.println(servoPos[4]);
    }
}

/* ------------------------------ LOOP ------------------------------*/

void loop(){ 
    for (int i = 0; i <= 50; i++)
    {
        servoPos[0] = i;
        servoUpdate();
    }
    for (int i = 50; i >= 0; i--)
    {
        servoPos[0] = i;
        servoUpdate();
    }
    if(imuWired){
        imu.getEuler(imuAngles);
    }

    irGetData();
    servoUpdate(); 

    if(irGetDistance("front") < seuilDistance)
    {
        /* code */
    }
    else if(/* condition */)
    {
        /* code */
    }
    else
    {
        /* code */
    }
    
}
