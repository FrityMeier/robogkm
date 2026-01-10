#include <Arduino.h>
#include <Servo.h>
#include "SparkFunLSM6DS3.h"
#define repeat(n) for(uint16_t count_intern=0; count_intern< (n); count_intern++)
#define repeatMillis(ms) for(uint32_t ms_intern = millis(); millis() < ms_intern+(ms);)
#define readA analogRead


#include <Wire.h>
//##################################################################################################
//# Temperatur
//##################################################################################################
#include "Seeed_MCP9808.h"
MCP9808  sensor;
boolean tempIsInit = false;

float readTemp(){
	if( ! tempIsInit ){
		sensor.init();
		tempIsInit = true;
		delay(100);
	}
	float temp = 0;
	sensor.get_temp(&temp);
	return temp;
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
  _oldUsVal[pin_number] = mm;
  // ... und die Zeit, zu der gemessen wurde
  _lastMillis[pin_number] = millis();
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
//#include "SparkFunLSM6DS3.h"

LSM6DS3 myIMU( I2C_MODE, 0x6A );  //I2C device address 0x6A
boolean gyro_wurde_gestartet = false;


void gyro_begin(){
  if( !gyro_wurde_gestartet ){
    if( myIMU.begin() != 0 ){
        Serial.println(F("gyro Device error"));
        delay(1000);
    }
	gyro_wurde_gestartet = true;
  }
}


void gyroTurn(int winkel){
  gyro_begin();
  long ziel = (-1) * (long)winkel * 100;
  Serial.println(ziel);
  long summe = 0;
  if(winkel > 0){
	  while(summe > ziel){	// rechts
		summe += (long)myIMU.readFloatGyroZ();
		Serial.println(summe);
		delay(10);
		
	  }
  }else{
	  while(summe < ziel){	// links
		summe += (long)myIMU.readFloatGyroZ();
		delay(10);		
	  }
  }
}



void gyroRight(){
  gyro_begin();
  long summe = 0;
  //driveRight();
  while(summe > -9000){
    summe += (long)myIMU.readFloatGyroZ();
    delay(10);
    
  }
}

void gyroLeft(){
  gyro_begin();
  long summe = 0;
  //driveLeft();
  while(summe < 9000){
    summe += (long)myIMU.readFloatGyroZ();
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



// #######################################
// GREEN-Sensor
unsigned long _readGreen_lastMillis = 0;
unsigned long _readGreen_millisLeft = 0;
unsigned long _readGreen_millisRight = 0;

Adafruit_NeoPixel pixelGreen;
boolean _pixelGreenStarted = false;

void writeLedGreensensor(int pin, int color)
{
	if( _pixelGreenStarted == false )
	{
		pixelGreen = Adafruit_NeoPixel(1, pin);
		pixelGreen.begin();
		_pixelGreenStarted = true;
	}
	int red = 0;
	int blue = 0;
	int green = 0;
	if( (color & 1)>0 ){  red = 255; }else{ red   = 0; }
	if( (color & 2)>0 ){green = 255; }else{ green = 0; }
	if( (color & 4)>0 ){ blue = 255; }else{ blue  = 0; }
	if(color >= 0) pixelGreen.setPixelColor(0, pixelGreen.Color(red, green, blue));
	pixelGreen.show(); // This sends the updated pixel color to the hardware.
}

int readSensor(int analogPin)
{ 
  int v[] = {0,0,0,0,0,0,0,0,0};
  for(int n=0; n<9; n++)
  {
    v[n] = analogRead(analogPin);
    delayMicroseconds(100);
    //Serial.print(v);
    //Serial.print(",");
  }
  int tempv;
  for(int i=0; i<10; i++)
  {
	for(int n=1; n<9; n++)
	{
	  if( v[n] < v[n-1] )
	  {
		tempv = v[n];
		v[n] = v[n-1];
		v[n-1] = tempv;
	  }
	}
  }
  //for(int n=0; n<9; n++){
  //Serial.print(v[n]);
  //Serial.print(";");
  //}
  //Serial.println();
  //Serial.println(result);//"=");
  return v[4];
}

int readGreen(int A_links, int A_rechts, int neoPixelPin){
  boolean DEBUG = false;
  boolean DEBUG_RIGHT = false;
  boolean DEBUG_LEFT  = false;
  
  writeLedGreensensor(neoPixelPin, RED);
  delay(2);
  int rl = readSensor(A_links);
  int rr = readSensor(A_rechts);
  //if( DEBUG_RIGHT ){ print("rr="); print(rr); }
  //if( DEBUG_LEFT ){ print("rl="); print(rl); }
  //if(DEBUG) delay(1000); 
  
  writeLedGreensensor(neoPixelPin, GREEN);
  delay(2);
  int gl = readSensor(A_links);
  int gr = readSensor(A_rechts);
  //if( DEBUG_RIGHT ){ print(" gr="); print(gr); }
  //if( DEBUG_LEFT ) { print(" gl="); print(gl); }
  //if(DEBUG) delay(1000);
  
  //setLedRefr(0,255,255,255);
  //writeLedGreensensor(neoPixelPin ,BLACK);
  //delay(2);
  //int bl = readSensor(A_links);
  //int br = readSensor(A_rechts);
  //if( DEBUG_RIGHT ) {   print(" br="); print(br); }
  //if( DEBUG_LEFT ) {   print(" bl="); print(bl); }
  //if(DEBUG) delay(1000);
  
  writeLedGreensensor(neoPixelPin, WHITE);
  delay(2);
  int wl = readSensor(A_links);
  int wr = readSensor(A_rechts);
  //if( DEBUG_RIGHT ) {   print(" wr="); print(wr); }
  //if( DEBUG_LEFT ) {   print(" wl="); print(wl); }
  //if(DEBUG) delay(1000);


  unsigned long millisDiff = (millis() - _readGreen_lastMillis + 2);
  _readGreen_lastMillis = millis();
  
  _readGreen_millisLeft  > millisDiff ? _readGreen_millisLeft  -= millisDiff : _readGreen_millisLeft  = 0;
  _readGreen_millisRight > millisDiff ? _readGreen_millisRight -= millisDiff : _readGreen_millisRight = 0;

  int resl = ( (abs((float)gl)/40.0) / (abs((float)rl)/60.0) * 100.0 - 100.0);
  // wenn es sehr dunkel ist, dann wird was abgezogen
  if(wl < 70){ 
	resl = resl - 70 + wl;
  } else if (wl > 150){
	resl = resl - (wl + 150)/2;
  }

  
  if( resl > 30)
    _readGreen_millisLeft  = min(_readGreen_millisLeft+200+(resl-30)*2, 3000);

  int resr = ( (((float)gr)/40.0) / (((float)rr)/60.0) * 100.0 - 100.0);
  // wenn es sehr dunkel ist, dann wird was abgezogen
  if(wr < 70){ 
	resr = resr - 70 + wr;
  } else if (wr > 150){
	resr = resr - (wr + 150)/2;
  }
  
  if( resr > 30)
    _readGreen_millisRight = min(_readGreen_millisRight+200+(resr-30)*2, 3000);
  
  
  //if( DEBUG_RIGHT) { print(" r>"); print(resr); }
  //if( DEBUG_LEFT)  { print(" l>"); print(resl); }
  
    //Serial.print("=");
    //Serial.print(resr _readGreen_millisLeft );
  if( DEBUG || DEBUG_LEFT || DEBUG_RIGHT){
	  delay(1000);
		Serial.println();
  }
  
  if( _readGreen_millisLeft == 0 && _readGreen_millisRight == 0 ){
    return 0; // weder links noch rechts
  }else if( _readGreen_millisLeft > 0 && _readGreen_millisRight > 0 ){
    return 2;
  }else if( _readGreen_millisLeft > _readGreen_millisRight){
    return 1;
  }else{
    return -1;
  }
}

int readRed(int A_links, int neoPixelPin, int debug = 0){
  writeLedGreensensor(neoPixelPin, RED);
  delay(2);
  int rl = readSensor(A_links);
  //Serial.print(rl);
  //Serial.print("\t");
  writeLedGreensensor(neoPixelPin, GREEN);
  delay(2);
  int gl = readSensor(A_links);
  //Serial.print(rl);
  //Serial.print("\t"); 
  writeLedGreensensor(neoPixelPin, WHITE);
  
  if(debug > 0){
	//Serial.println( (abs((float)rl)/60.0) / (abs((float)gl)/40.0) * 100.0 - 100.0);
    //printNewLine();
  }
  return ( (abs((float)rl)/60.0) / (abs((float)gl)/40.0) * 100.0 - 100.0);
}


