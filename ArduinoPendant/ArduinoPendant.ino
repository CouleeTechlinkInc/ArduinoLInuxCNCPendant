

void setup(){
Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop(){
  if (Serial.available() > 0) {
    
  }
}
