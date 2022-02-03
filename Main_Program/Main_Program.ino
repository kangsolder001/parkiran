#include <Servo.h>
#include "Adafruit_Thermal.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <TimeLib.h>
Adafruit_Thermal printer(&Serial2);
//======================PIN LED dan IR==============================================
String room[]  = {"L1.1", "L1.2", "L1.3", "L1.4", "L1.5", "L1.6", "L1.7", "L1.8", "L1.9", "L1.10", "L2.11", "L2.12", "L2.13", "L2.14", "L2.15", "L2.16", "L2.17", "L2.18", "L2.19", "L2.20"};
int ir [] = {50, 48, 46, 44, 42, 5, 4, 3, 2, 52, 43, A15, A14, A13, A12, A11, A10, A9, A8, A7};
int pin [] = {30, 28, 26, 24, 22, 40, 38, 36, 34, 32, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41};
int irlt1 [] = { A7, A8, A9, A10, A11, A12, A13, A14, A15};
//int ir_before[] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int ir_before[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool ir_now[20];
// =================================================================================
int serFront = 9;
int irFront = 10;
int serBack = 7;
int irBack = 8;
int buzz = 11;
int PB = 6;
bool bPB;
bool statFrontGate;
bool statBackGate;
unsigned long prevGetTime, prevbgetTime, secBefore;
//==============================IdPark========================
uint32_t TimeId [20];
int ParkId [20];
int indexTimeId = 0;
int indexParkId = 0;
Servo Front;
Servo Back;
int totalparkir;
bool bupdateLCD = true;
bool bgetTime;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print(" Selamat Datang ");
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(9600);
  pinMode(irFront, INPUT);
  pinMode(irBack, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(PB, INPUT);
  printer.begin();
  for (int i = 0; i <= 19; i++)
  {
    pinMode(pin[i], OUTPUT);
  }
  for (int i = 0; i <= 19; i++)
  {
    pinMode(ir[i], INPUT);
  }
  Serial.print("inisialisai selesai ");
  lcd.clear();
}
uint32_t before;
void loop() {
  if ( now() != before)
  {
    Serial.println(now());
    Serial.println(getFulldate());
    before = now();
  }
  readDataESP();
  getTimeESP();
  readPB();
  SerialTest();
  readIR();
  CloseGate();
  LCD();
}
