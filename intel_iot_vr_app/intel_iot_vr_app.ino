#include <SoftwareSerial.h>

SoftwareSerial btSerial(8, 9); // RX, TX

#define MAX_BUF 20

//have number to text mapping
char text[6] = {
  'x',
  '1', //on
  '2', //off
  '3', //high
  '4', //low
  '5' //ok
};
int start = 0xaa;
char buf[MAX_BUF];
int input = 3;

void commandWrite(int cmd){
  
  Serial1.write(start); //starting seq
  Serial1.write(cmd);    
  
  delay(250);
  
  while(Serial1.available() > 0){
    int num = Serial1.readBytes(buf, MAX_BUF);
   Serial.write((uint8_t*)buf, num);
  }
  
  Serial.print("===================================\n");
}


void setup() {
  pinMode(input, INPUT_PULLUP);  
  
  //Init serial stream
  Serial.begin(9600);  //USB connected to comp
  Serial1.begin(9600);  //serial rx tx connection
  btSerial.begin(9600);// bluetooth
  delay(10000);
  
  //put the VR in non-compact mode
  commandWrite(0x36);
  
  //put the VR in wait mode
  commandWrite(0x00);

}

void loop() {
  //if button pressed
  if(buttonPressed()){
    
    //1. Select the first group; clear the o/p buffer
    commandWrite(0x21);
    while(Serial1.available()){
      Serial1.read();
    }
    
    //2. let the user speak ://TESTING change
    while(Serial1.available() == 0){};
    
    //3. get and decode the response
    char rsp[9];
    Serial1.readBytes(rsp, 9); //"RESULT:11"; resp[8] will give me desired num as 'char'
    
    //4. put VR back into waiting mode
    commandWrite(0x00);
    
    //5. use the number to code mapping 
    //6. serial.write it out to the bt module
    //Serial.write(rsp[8]); //for now; should be replaced by S/W serial that runs bluetooth later.
    Serial.write(rsp[8]);
    //FETCH - IR CODE
      //Transmit
      //recieve
    btSerial.write(rsp[8]);
    btSerial.write(",1");//+dev_id); --assume id == 1
  }
}

bool buttonPressed(){
  /*
  //TODO : must implement
  Serial.println("Press button");
  while(digitalRead(input) == HIGH){
    //wait
  }
  
    //=> button is now clicked 
  if(digitalRead(input) == LOW){
    while(digitalRead(input) == LOW);//wait
  }
  Serial.println("Button Pressed");
  return true;
  */
    Serial.println("enter a command");
    while(Serial.available() == 0){
    }
    while(Serial.available() != 0){
      Serial.read();
    }
    Serial.println("command entered");
    return true;
}
