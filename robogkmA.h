#include <Arduino.h>
#include <Servo.h>
#define repeat(n) for(uint16_t count_intern=0; count_intern< (n); count_intern++)
#define repeatMillis(ms) for(uint32_t ms_intern = millis(); millis() < ms_intern+(ms);)
#define readA analogRead


#include <Wire.h>
//##################################################################################################
//# Temperatur
//##################################################################################################
#include "Adafruit_SHT31.h"
Adafruit_SHT31 sht31 = Adafruit_SHT31();
boolean tempIsInit = false;

int readTemp(){
	if( ! tempIsInit ){
		sht31.begin(0x44);
		tempIsInit = true;
		delay(100);
	}
	return (int)sht31.readTemperature();
}



//##################################################################################################
//# LCD

#include "rgb_lcd2.h"
rgb_lcd lcd;
boolean _lcdIsConnected = false;
void _connectLcdIfNeeded(){
  if( _lcdIsConnected == false )
  {
    lcd.begin(16,2);
    _lcdIsConnected = true;
  }
}

#define lcdPrint(n) _connectLcdIfNeeded();lcd.print((n))

void lcdClear(){
	_connectLcdIfNeeded();
	lcd.clear();
}

//void rgb_lcd::setCursor(uint8_t col, uint8_t row)
void lcdSetCursor(uint8_t col, uint8_t row){
	_connectLcdIfNeeded();
	lcd.setCursor(col, row);
}
//void rgb_lcd::setRGB(unsigned char r, unsigned char g, unsigned char b)
void lcdSetColor(int color){
	int red = 255*(color & 1);
	int green = (color & 2)/2*255;
	int blue = (color & 4)/4 *255;
	_connectLcdIfNeeded();
	lcd.setRGB(red,green,blue);
		
}

#include <Adafruit_NeoPixel2.h>
#define RED 1
#define GREEN 2
#define BLUE 4
#define BLACK 0
#define WHITE 7
#define YELLOW 3
#define UNCHANGED -1

Servo myservo[4];

Adafruit_NeoPixel pixels;
Adafruit_NeoPixel pixels2;
boolean _neopixelStarted = false;
boolean _neopixelStarted2 = false;

int leds[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



void writeLeds(int pin, int l1, int l2, int l3, int l4, int l5)
{
	if( _neopixelStarted == false ){
		pixels = Adafruit_NeoPixel(8, pin);
		pixels.begin();
		_neopixelStarted = true;
	}

	// die Argumente in einen Array speichern
	int newVals[5];
	newVals[0]=l1; newVals[1]=l2; newVals[2]=l3; newVals[3]=l4; newVals[4]=l5;

	int red;
	int blue;
	int green;
	
	for(int n=0; n<5; n++){
		if( (newVals[n] & 1)>0 ){  red = 50; }else{  red  = 0;}
		if( (newVals[n] & 2)>0 ){green = 50; }else{ green = 0;}
		if( (newVals[n] & 4)>0 ){ blue = 50; }else{ blue  = 0;}
		if(newVals >= 0){
			pixels.setPixelColor(n, pixels.Color(red, green, blue));
			leds[n] = newVals[n];	
		}
	}
	
	pixels.show(); // This sends the updated pixel color to the hardware.
}

void writeLeds(int pin, int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8)
{
	if( _neopixelStarted == false ){
		pixels = Adafruit_NeoPixel(8, pin);
		pixels.begin();
		_neopixelStarted = true;
	}

	// die Argumente in einen Array speichern
	int newVals[8];
	newVals[0]=l1; newVals[1]=l2; newVals[2]=l3; newVals[3]=l4; newVals[4]=l5;
	newVals[5]=l6; newVals[6]=l7; newVals[7]=l8;

	int red;
	int blue;
	int green;
	
	for(int n=0; n<8; n++){
		if( (newVals[n] & 1)>0 ){  red = 50; }else{  red  = 0;}
		if( (newVals[n] & 2)>0 ){green = 50; }else{ green = 0;}
		if( (newVals[n] & 4)>0 ){ blue = 50; }else{ blue  = 0;}
		if(newVals >= 0){
			pixels.setPixelColor(n, pixels.Color(red, green, blue));
			leds[n] = newVals[n];	
		}
	}
	
	pixels.show(); // This sends the updated pixel color to the hardware.
}

void writeLight(int pin, int onOff){
	if( _neopixelStarted2 == false ){
		pixels2 = Adafruit_NeoPixel(8, pin);
		pixels2.begin();
		_neopixelStarted2 = true;
	}
	for(int n=0; n<8; n++){
		pixels2.setPixelColor(n, pixels2.Color(255*onOff,255*onOff,255*onOff));
	}
	pixels2.show(); // This sends the updated pixel color to the hardware.
}



void writeLed(int pin, int whichLed, int color)
{
	if(whichLed <0 || whichLed > 7){
		return;
	}
	if( _neopixelStarted == false ){
		pixels = Adafruit_NeoPixel(8, pin);
		pixels.begin();
		_neopixelStarted = true;
	}
	int red = 0;
	int blue = 0;
	int green = 0;
	if( (color & 1)>0 ){  red = 50; }else{  red  = 0;}
	if( (color & 2)>0 ){green = 50; }else{ green = 0;}
	if( (color & 4)>0 ){ blue = 50; }else{ blue  = 0;}
	if(color >= 0) pixels.setPixelColor(whichLed, pixels.Color(red, green, blue));	
	pixels.show(); // This sends the updated pixel color to the hardware.
}


/* ************************************************
// Serial
*/
boolean _serialIsConnected = false;

void _connectIfNeeded(){
  if( _serialIsConnected == false )
  {
    Serial.begin(9600);
    _serialIsConnected = true;
  }
}

#define serialNewLine() _connectIfNeeded();Serial.println()
#define serialPrint(n) _connectIfNeeded();Serial.print((n))







/* ************************************************
 // Servo
 */

int servoPin[]={
  -1,-1,-1,-1, -1, -1};
int servoPos[]={
  90, 90, 90,90,90,90};



void writeServo(int pin, int pos){
  // welcher Servo haengt an dem Pin?
  for(int n=0; n<4; n++){
    if(servoPin[n] == pin){
      myservo[n].write(pos);
	  servoPos[n] = pos;
      return;
    }     
  }
  // er hat also keinen Servo gefunden
  // mal nach einem freien Slot suchen
  for(int n=0; n<4; n++){
    if(servoPin[n]<0){
      // freier Slot gefunden
      servoPin[n] = pin;
      myservo[n].attach(pin);
      myservo[n].write(pos);
	  servoPos[n] = pos;
      return;
    } 
  }
}

void writeServoSlow(int pin, int pos){
  // welcher Servo haengt an dem Pin?
  for(int n=0; n<4; n++){
    if(servoPin[n] == pin){
		if(pos > servoPos[n] ){
			for(int i=servoPos[n]; i<pos; i++){
				myservo[n].write(i);		
				delay(10);
			}
		}else{
			for(int i=servoPos[n]; i>pos; i--){
				myservo[n].write(i);		
				delay(10);
			}			
		}
		servoPos[n] = pos;	// neue Position merken
		return;
    }     
  }
  // er hat also keinen Servo gefunden
  // mal nach einem freien Slot suchen
  for(int n=0; n<4; n++){
    if(servoPin[n]<0){
		// freier Slot gefunden
		servoPin[n] = pin;
		myservo[n].attach(pin);
		if(pos > servoPos[n] ){
			for(int i = servoPos[n]; i<pos; i++){
				myservo[n].write(i);		
				delay(10);
			}
		}else{
			for(int i = servoPos[n]; i > pos; i--){
				myservo[n].write(i);		
				delay(10);
			}			
		}
		servoPos[n] = pos;	// neue Position merken
		return;
    } 
  }
}

/* ////////////////////////////////////////////
 // Motoren
 */
void drive(int left, int right){
  // PINS als Ausgaenge setzen
  DDRD |= B11110000;
  DDRB |= B00000011;
	int v;
  // bei negativen Werten "OnRev" aufrufen
  if(right == 0) {
	analogWrite(5, 0); //enA
	digitalWrite(4, HIGH); //vrA1
    digitalWrite(9, HIGH);//vrA2    
  }else if(right > 0){
	v = map(right, 0, 100, 0, 255);
	analogWrite(5, v); //enA
	digitalWrite(9, HIGH); //vrA1
    digitalWrite(4, LOW);//vrA2    	  
  }else{
	v = map(right, 0, 100, 0, -255);
	analogWrite(5, v); //enA
	digitalWrite(9, LOW); //vrA1
    digitalWrite(4, HIGH);//vrA2    	  	  
  }

  if(left == 0) {
	analogWrite(6, 0); //enA
	digitalWrite(7, HIGH); //vrA1
    digitalWrite(8, HIGH);//vrA2    
  }else if(left > 0){
	v = map(left, 0, 100, 0, 255);
	analogWrite(6, v); //enA
	digitalWrite(8, HIGH); //vrA1
    digitalWrite(7, LOW);//vrA2    	  
  }else{
	v = map(left, 0, 100, 0, -255);
	analogWrite(6, v); //enA
	digitalWrite(8, LOW); //vrA1
    digitalWrite(7, HIGH);//vrA2    	  	  
  }


}



// #######################################################################################
// #
// # read
// #
// #######################################################################################


/* *************************************************************
 // Ultraschallsensor
 // der US-Sensor darf nicht so oft ausgelesen werden
 // Deswegen merkt sich die Software den Zeitpunkt der letzten Messung
 // wenn die neue Messung MILLISMINDIFF ms und kuerzer zurueckliegt,
 // so wird nicht erneut gemessen sondern der alte Wert zurueckgegeben.
 */
const int MILLISMINDIFF = 30;

int _pin[] = {  // der US-Sensor liegt auf dem Pin
  -1, -1, -1, -1, -1, -1};

unsigned long _lastMillis[] = {
  0ul, 0ul, 0ul, 0ul, 0ul, 0ul};

int _oldUsVal[] = {
  9999, 9999, 9999, 9999, 9999, 9999};


// jetzt di Funktion
int readUltraSonic(int pin){
  /*
  // schaue nach, ob der pin schon mal benutzt wurde
  int pin_number = -1;
  for(int n = 0; n < 6; n++){
    if( pin == _pin[n] ){
      pin_number = n;
      break;
    } 
  }

  // falls der pin noch  nicht benutzt wurde, so 
  // muss er in die Liste eingetragen werden
  if(pin_number == -1){
    // suche nach dem 1. freien Slot
    for(int n = 0; n < 6; n++){
      if(_pin[n] == -1){
        _pin[n] = pin;
        pin_number = n;
        break;
      }
    }
  }

  // wie lange ist die letzte Messung her?
  int millisAgo = millis() - _lastMillis[pin_number];

  // wurde erst vor kurzem gemessen, so soll einfach
  // der alte Wert zurueckgegeben werden
  if(millisAgo < MILLISMINDIFF){
    return _oldUsVal[pin_number];
  }
  */
  // die letzte Messung liegt also schon ein bisschen zurueck
  // wir muessen neu messen
  long duration;
  int mm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(15);
  digitalWrite(pin, LOW);
  delayMicroseconds(20);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH, 20000ul);
  mm = duration / 6; //microsecondsToCentimeters(duration);
  if(mm <= 0) mm = 9999;
  // merke dir den Wert ...
  //_oldUsVal[pin_number] = mm;
  // ... und die Zeit, zu der gemessen wurde
  //_lastMillis[pin_number] = millis();
  return mm;
}


boolean readButton(int pin){
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
  return digitalRead(pin); 
}


int readIr30(int analogPin){
  int result;
  int val = analogRead(analogPin);
  if (val < 3){
    result = 999; // invalid value
  }
  else{
    // v = 24570.0/analogRead(0)+6.0;
    float ret = (24570.0 /((float)val))+6.0;// - 3.0)) - 4.0;
    if(ret > 300){
      result = 999;
    }
    else if(ret < 30)
    {
      result = 0;
    }
    else
    {
      result = ret;
    }
  }
  //log(String(analogPin) + ";" + String(result) + "i");
  return result;
} 


void writePort(int port, int val){
  pinMode(port, OUTPUT);
  digitalWrite(port, val);
}

void writeHigh(int port){
  pinMode(port, OUTPUT);
  digitalWrite(port, HIGH);
}

void writeLow(int port){
  pinMode(port, OUTPUT);
  digitalWrite(port, LOW);
}


//######################################################################################
//# gyro
#include "basicMPU6050.h"

//
basicMPU6050<> imu;
//LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A
boolean gyro_wurde_gestartet = false;
boolean gyro_ok = false;        // hat beim Start ein Gyro geantwortet?

// Gyro fehlt (oder I2C gestoert): LED-Ring dreimal rot blinken und - wenn Serial laeuft - melden.
void __gyroFehlt(){
#if defined(UCSR0B)
  if( UCSR0B & (1 << TXEN0) )   // nur wenn das Programm Serial.begin() aufgerufen hat
#endif
    Serial.println(F("Gyro nicht gefunden - SDA an A4, SCL an A5, VCC und GND pruefen"));
  repeat(3){
    writeLeds(13, 1, 1, 1, 1, 1, 1, 1, 1);
    delay(150);
    writeLeds(13, 0, 0, 0, 0, 0, 0, 0, 0);
    delay(150);
  }
}

// Startet den Gyro (MPU-6050 an 0x68). true = Gyro gefunden.
// Frueher hing das Programm hier fuer immer, wenn der Gyro fehlte oder keinen Strom hatte
// (die I2C-Leitungen bleiben dann unten). Jetzt: Zeitlimit fuer I2C, Meldung, false.
bool gyro_begin(){
  if( gyro_wurde_gestartet ) return gyro_ok;
  gyro_wurde_gestartet = true;
  Wire.begin();
#if defined(ARDUINO_ARCH_AVR) || defined(WIRE_HAS_TIMEOUT)   // AVR-Kern ab 1.8.3 kann das, meldet es aber nicht
  Wire.setWireTimeout(25000, true);   // 25 ms, danach I2C zuruecksetzen statt haengen
#endif
  Wire.beginTransmission(0x68);
  gyro_ok = (Wire.endTransmission() == 0);
  if( gyro_ok ){
    imu.setup();
  }else{
    __gyroFehlt();
  }
  return gyro_ok;
}


void gyroTurn(int winkel){
  if( !gyro_begin() ){ __gyroFehlt(); return; }   // ohne Gyro nicht ewig drehen
  double ziel = (-1) * (double)winkel;
  double summe = 0;
  unsigned long start = millis();       // nach 10 s aufhoeren (haengt fest, Gyro ausgefallen)
  if(winkel > 0){
	  while(summe > ziel && millis() - start < 10000){	// rechts
		summe += (double)imu.gz();//myIMU.readFloatGyroZ();
		delay(10);
	  }
  }else{
	  while(summe < ziel && millis() - start < 10000){	// links
		summe += (double)imu.gz();//myIMU.readFloatGyroZ();
		delay(10);		
	  }
  }
}



void gyroRight(){
  if( !gyro_begin() ){ __gyroFehlt(); return; }
  double ziel = -90.0;//(double)winkel;
  double summe = 0;
  while(summe > ziel){
    summe += (double)imu.gz();
    delay(10);
	Serial.println(summe);
  }
}

void gyroLeft(){
  if( !gyro_begin() ){ __gyroFehlt(); return; }
  double ziel = 90.0;//(double)winkel;
  double summe = 0;
  while(summe < ziel){
    summe += (double)imu.gz();
    delay(10);
	
  }
}


bool gyroSchraeg(){
	gyro_begin();
	double val = sqrt(imu.ax()*imu.ax()+imu.ay()*imu.ay());
	return (int)(val*100);
}

//##################################################################################################
//# Lagesensor BNO055 (Bosch): rechnet die Lage selbst aus und liefert fertige Winkel in Grad
//#
//#   bno_begin();            starten (IMU: Gyro + Beschleunigung, Kurs relativ zum Start, Motoren stoeren nicht)
//#   bno_begin(true);        mit Kompass (NDOF): Kurs absolut nach Norden, aber Motoren/Eisen stoeren
//#   readHeading()           Kurs 0..359 Grad (rechts herum mehr)
//#   readPitch()             Neigung vorn/hinten in Grad (Rampe), readRoll() seitlich
//#   bnoTurn(90);            warten, bis sich der Roboter um 90 Grad gedreht hat (+ rechts, - links)
//#   readBnoCalib()          Kalibrierung des Gyros 0..3 (3 = fertig; nach dem Start kurz stillhalten)
//#
//# Anschluss wie der Gyro: SDA an A4, SCL an A5, VIN 5 V, GND (Grove-Buchse "A5 A4").
//# I2C-Adresse 0x28 (oder 0x29, wenn ADR auf high liegt) - wird selbst gesucht.
//# Ohne Sensor geben die read-Funktionen 9999 zurueck.
//##################################################################################################
byte __bnoAdr = 0;                 // 0 = noch nicht gestartet, 1 = nicht gefunden, sonst Adresse

void __bnoSchreibe(byte reg, byte wert){
  Wire.beginTransmission(__bnoAdr);
  Wire.write(reg);
  Wire.write(wert);
  Wire.endTransmission();
}

byte __bnoLies(byte adr, byte reg){
  Wire.beginTransmission(adr);
  Wire.write(reg);
  if( Wire.endTransmission() != 0 ) return 0;
  if( Wire.requestFrom(adr, (byte)1) != 1 ) return 0;
  return Wire.read();
}

int __bnoLies16(byte reg){         // zwei Bytes (low, high) als vorzeichenbehaftete Zahl
  Wire.beginTransmission(__bnoAdr);
  Wire.write(reg);
  if( Wire.endTransmission() != 0 ) return 32767;
  if( Wire.requestFrom(__bnoAdr, (byte)2) != 2 ) return 32767;
  int lo = Wire.read();
  int hi = Wire.read();
  return (int16_t)((hi << 8) | lo);
}

void __bnoFehlt(){
#if defined(UCSR0B)
  if( UCSR0B & (1 << TXEN0) )
#endif
    Serial.println(F("BNO055 nicht gefunden - SDA an A4, SCL an A5, VIN und GND pruefen"));
  repeat(3){
    writeLeds(13, 1, 1, 1, 1, 1, 1, 1, 1);
    delay(150);
    writeLeds(13, 0, 0, 0, 0, 0, 0, 0, 0);
    delay(150);
  }
}

// true = BNO055 gefunden. kompass = true: mit Magnetfeldsensor (absoluter Kurs)
bool bno_begin(bool kompass = false){
  if( __bnoAdr > 1 ) return true;
  if( __bnoAdr == 1 ) return false;
  Wire.begin();
#if defined(ARDUINO_ARCH_AVR) || defined(WIRE_HAS_TIMEOUT)
  Wire.setWireTimeout(25000, true);
#endif
  __bnoAdr = 1;
  for( int versuch = 0; versuch < 10 && __bnoAdr == 1; versuch++ ){   // braucht nach dem Einschalten ca. 0,7 s
    if( __bnoLies(0x28, 0x00) == 0xA0 ) __bnoAdr = 0x28;              // Register 0 = Chip-ID 0xA0
    else if( __bnoLies(0x29, 0x00) == 0xA0 ) __bnoAdr = 0x29;
    else delay(100);
  }
  if( __bnoAdr == 1 ){ __bnoFehlt(); return false; }
  __bnoSchreibe(0x3D, 0x00);       // Betriebsart CONFIG
  delay(25);
  __bnoSchreibe(0x07, 0x00);       // Registerseite 0
  __bnoSchreibe(0x3E, 0x00);       // Stromsparmodus aus
  __bnoSchreibe(0x3B, 0x00);       // Einheiten: Grad, m/s^2, Grad Celsius
  __bnoSchreibe(0x3D, kompass ? 0x0C : 0x08);   // NDOF bzw. IMU
  delay(30);
  return true;
}

int readHeading(){
  if( !bno_begin() ) return 9999;
  int w = __bnoLies16(0x1A);
  if( w == 32767 ) return 9999;
  return (w / 16) % 360;           // 16 Stufen = 1 Grad
}

int readRoll(){
  if( !bno_begin() ) return 9999;
  int w = __bnoLies16(0x1C);
  return w == 32767 ? 9999 : w / 16;
}

int readPitch(){
  if( !bno_begin() ) return 9999;
  int w = __bnoLies16(0x1E);
  return w == 32767 ? 9999 : w / 16;
}

// Kalibrierstatus des Gyros 0..3 (Register 0x35: Bits 5-4)
int readBnoCalib(){
  if( !bno_begin() ) return 0;
  return (__bnoLies(__bnoAdr, 0x35) >> 4) & 3;
}

// Wartet, bis sich der Kurs um winkel Grad geaendert hat (+ rechts, - links), hoechstens 10 s.
// Die Motoren setzt das Programm selbst, z. B.:  drive(60, -60); bnoTurn(90); drive(0, 0);
void bnoTurn(int winkel){
  if( !bno_begin() ){ __bnoFehlt(); return; }
  int letzter = readHeading();
  if( letzter == 9999 ) return;
  long gedreht = 0;                // aufsummiert, damit auch 180 oder 360 Grad gehen
  unsigned long t0 = millis();
  while( millis() - t0 < 10000 ){
    int jetzt = readHeading();
    if( jetzt == 9999 ) break;
    int d = jetzt - letzter;       // Sprung bei 0/360 ausgleichen
    if( d > 180 ) d -= 360;
    if( d < -180 ) d += 360;
    gedreht += d;
    letzter = jetzt;
    if( winkel > 0 && gedreht >= winkel ) break;
    if( winkel < 0 && gedreht <= winkel ) break;
    delay(10);
  }
}

// ##################################################################################################
// Sensoren
int __pins[] = {0,0,0,0,0,0,0,0};
int __chars[] = {'a','a','a','a','a','a','a','a'};
int __schwellen[] = {100,100,100,100,100,100,100,100};
int __schwellen2[] = {300,300,300,300,300,300,300,300};
int __vals[] = {-1, -1, -1, -1, -1, -1, -1, -1};

void printVals(){
  if( _serialIsConnected == false )
  {
    Serial.begin(9600);
    _serialIsConnected = true;
  }
  int n;
  for (n=0; n<8; n++){
    if( __pins[n] == 0) break;
	Serial.print( __vals[n] );
	Serial.print("\t");
	Serial.print( __chars[n] );
	Serial.print("\t");
  }
  Serial.println();
}

void addLightSensor(char c, int pin, int schwelle){
  // suche den ersten freien Slot
  int n;
  for (n=0; n<8; n++){
    if( __pins[n] == 0) break;
  }
  writeLeds(13,0,0,0,0,0);
  delay(100);
  writeLed(13,n,7);
  delay(100);
  writeLeds(13,0,0,0,0,0);
  __pins[n]  = pin;
  __chars[n] = c;
  __schwellen[n] = schwelle; 
}

void addLightSensor(char c, int pin, int schwelle, int schwelle2){
  // suche den ersten freien Slot
  int n;
  for (n=0; n<8; n++){
    if( __pins[n] == 0) break;
  }
  writeLeds(13,0,0,0,0,0);
  delay(100);
  writeLed(13,n,7);
  delay(100);
  writeLeds(13,0,0,0,0,0);
  __pins[n]  = pin;
  __chars[n] = c;
  __schwellen[n] = schwelle; 
  __schwellen2[n] = schwelle2; 
}

int isDark(char c){
  int n;
  for(n=0; n<8; n++){
    if( __chars[n] == c ){
      int val = analogRead( __pins[n] );
	  // den neuen Wert speichern
      __vals[n] = val;
      if( val < __schwellen[n] ){
		  //writeLed(13, n, 1);
		  return 1;
	  }else{
		  //writeLed(13, n, 2);
		  return 0;
	  }
    }
  }
  return -1;
}

int isBright(char c){
  int n;
  for(n=0; n<8; n++){
    if( __chars[n] == c ){
      int val = analogRead( __pins[n] );
	  // den neuen Wert speichern
      __vals[n] = val;
      if( val > __schwellen2[n] ){
		  //writeLed(13, n, 1);
		  return 1;
	  }else{
		  //writeLed(13, n, 2);
		  return 0;
	  }
    }
  }
  return -1;
}

//##################################################################################################
//# ToF-Abstandssensor VL53L0X (Laser, 3 cm .. ca. 1,2 m, Ergebnis in mm)
//#
//#   addTofSensor('v', 200);          ein Sensor, Schwelle 200 mm fuer isNear('v')
//#   addTofSensor('l', 4, 150);       mehrere Sensoren: jeder braucht einen eigenen XSHUT-Pin (hier 4)
//#   readTof('v')                     Abstand in mm, 9999 = nichts im Messbereich oder Fehler
//#   isNear('v')                      wie beim Ultraschall: true, wenn naeher als die Schwelle
//#
//# Alle VL53L0X haben am Anfang dieselbe I2C-Adresse (0x29). Bei mehreren Sensoren schaltet robogkm
//# beim ersten Lesen alle ueber XSHUT aus, dann einen nach dem anderen ein und gibt jedem eine eigene
//# Adresse (0x30, 0x31, ...). Ein Sensor ohne XSHUT-Pin (-1) geht nur, wenn er der einzige ist.
//# Treiber: VL53L0X_gkm.h/.cpp (Pololu vl53l0x-arduino, MIT-Lizenz, siehe VL53L0X_LICENSE.txt)
//##################################################################################################
#include "VL53L0X_gkm.h"

// Der ToF-Code kommt nur ins Programm, wenn es addTofSensor() aufruft (sonst kostet er 4 KB):
// die Sensoren entstehen erst beim ersten Gebrauch, und isNear() fragt den ToF ueber einen Zeiger,
// den erst addTofSensor() setzt.
const int __TOF_MAX = 4;
VL53L0X& __tof(int n){
  static VL53L0X sensoren[__TOF_MAX];
  return sensoren[n];
}
int __tofIsNear(char c);
int (*__tofIsNearZeiger)(char) = 0;
char __tofChars[__TOF_MAX] = {0, 0, 0, 0};
int __tofXshut[__TOF_MAX] = {-1, -1, -1, -1};
int __tofSchwellen[__TOF_MAX] = {200, 200, 200, 200};
bool __tofOk[__TOF_MAX] = {false, false, false, false};
int __tofAnzahl = 0;
bool __tofGestartet = false;

void addTofSensor(char c, int xshutPin, int schwelle){
  if( __tofAnzahl >= __TOF_MAX ) return;
  __tofChars[__tofAnzahl] = c;
  __tofXshut[__tofAnzahl] = xshutPin;
  __tofSchwellen[__tofAnzahl] = schwelle;
  if( xshutPin >= 0 ){            // gleich ausschalten, damit er beim Start nicht stoert
    pinMode(xshutPin, OUTPUT);
    digitalWrite(xshutPin, LOW);
  }
  __tofAnzahl++;
  __tofGestartet = false;         // beim naechsten Lesen alle (neu) starten
  __tofIsNearZeiger = __tofIsNear;
}

void addTofSensor(char c, int schwelle){
  addTofSensor(c, -1, schwelle);
}

void __tofStarten(){
  Wire.begin();
  for(int n=0; n<__tofAnzahl; n++){     // erst alle mit XSHUT aus
    if( __tofXshut[n] >= 0 ){ pinMode(__tofXshut[n], OUTPUT); digitalWrite(__tofXshut[n], LOW); }
  }
  delay(10);
  for(int n=0; n<__tofAnzahl; n++){     // dann einen nach dem anderen ein, eigene Adresse
    if( __tofXshut[n] < 0 ) continue;
    pinMode(__tofXshut[n], INPUT);      // XSHUT loslassen: die Platine zieht ihn auf high
    delay(10);
    __tof(n).setTimeout(100);
    __tofOk[n] = __tof(n).init();
    if( __tofOk[n] ){
      __tof(n).setAddress(0x30 + n);
      __tof(n).startContinuous();
    }
  }
  for(int n=0; n<__tofAnzahl; n++){     // zuletzt der ohne XSHUT (Adresse 0x29 bleibt)
    if( __tofXshut[n] >= 0 ) continue;
    __tof(n).setTimeout(100);
    __tofOk[n] = __tof(n).init();
    if( __tofOk[n] ) __tof(n).startContinuous();
  }
  __tofGestartet = true;
}

int __tofNummer(char c){
  for(int n=0; n<__tofAnzahl; n++){
    if( __tofChars[n] == c ) return n;
  }
  return -1;
}

int readTof(char c){
  int n = __tofNummer(c);
  if( n < 0 ) return 8888;              // so heisst der Sensor nicht (wie readUs)
  if( !__tofGestartet ) __tofStarten();
  if( !__tofOk[n] ) return 9999;
  int mm = __tof(n).readRangeContinuousMillimeters();
  if( __tof(n).timeoutOccurred() || mm >= 2000 ) return 9999;   // 8190 = nichts im Messbereich
  return mm;
}

// fuer isNear(): -1 = kein ToF-Sensor mit diesem Namen
int __tofIsNear(char c){
  int n = __tofNummer(c);
  if( n < 0 ) return -1;
  return readTof(c) < __tofSchwellen[n];
}


void addUsSensor(char c, int pin, int schwelle){
  // suche den ersten freien Slot
  int n;
  for (n=0; n<8; n++){
    if( __pins[n] == 0) break;
  }
  writeLeds(13,0,0,0,0,0);
  delay(100);
  writeLed(13,n,7);
  delay(100);
  writeLeds(13,0,0,0,0,0);
  __pins[n]  = pin;
  __chars[n] = c;
  __schwellen[n] = schwelle; 
}

int isNear(char c){
  int n;
  for(n=0; n<8; n++){
    if( __chars[n] == c ){
      int val = readUltraSonic(__pins[n] );
      __vals[n] = val;
      if( val < __schwellen[n] ){
		  //writeLed(13, n, 1);
		  return true;
	  }else{
		  //writeLed(13, n, 2);
		  return false;
	  }
    }
  }
  if( __tofIsNearZeiger ) return __tofIsNearZeiger(c);   // kein Ultraschall-Sensor so: vielleicht ein ToF
  return -1;
}

// jetzt di Funktion
int readUs(char c){
  int n;
  for(n=0; n<8; n++){
    if( __chars[n] == c ){
      int val = readUltraSonic( __pins[n] );
      __vals[n] = val;
		  return val;
    }
  }
  return 8888;
}

// jetzt di Funktion
int readLight(char c){
  int n;
  for(n=0; n<8; n++){
    if( __chars[n] == c ){
      int val = analogRead( __pins[n] );
      __vals[n] = val;
		  return val;
    }
  }
  return 8888;
}


