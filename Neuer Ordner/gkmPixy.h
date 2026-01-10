#include <Arduino.h>
#include <Pixy2.h>

Pixy2 pixy;

boolean _pixyStarted = false;

void pixyBegin(){
  // we must initialize the pixy object
  pixy.init();
  delay(100);
  // Getting the RGB pixel values requires the 'video' program
  pixy.changeProg("video");	
  _pixyStarted = true;
}

void pixyLamp(int lamp){
	if(! _pixyStarted){
		pixyBegin();
	}
	pixy.setLamp(lamp,1);
}

int pixyRead(int x, int y){
	if(! _pixyStarted){
		pixyBegin();
	}
	uint8_t r, g, b;
	pixy.video.getRGB(x, y, &r, &g, &b, false);
	return ((int)r+(int)g+(int)b)/3;
}


int pixyReadGreen(int x1, int y1, int x2, int y2){
	if(! _pixyStarted){
		pixyBegin();
	}
	uint8_t r, g, b;
	int left = 0;
	pixy.video.getRGB(x1, y1, &r, &g, &b, false);
	if( g > 100 && g > (r+b) ){
		left = 1;
	}
	int right = 0;
	pixy.video.getRGB(x2, y2, &r, &g, &b, false);
	if( g > 100 && g > (r+b) ){
		right = 1;
	}

	if(left== 0 && right == 0){
		// kein gruen
		return 0;
	}else if( left == 1 && right == 0 ){
		// links gruen
		return -1;
	}else if( left == 0 && right == 1 ){
		// rechts gruen
		return 1;
	}else{
		// beide gruen
		return 2;
	}
}