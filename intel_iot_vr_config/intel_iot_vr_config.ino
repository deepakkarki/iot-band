#define MAX_BUF 20

int start = 0xaa;
char buf[MAX_BUF];

void commandWrite(int cmd){
  
  Serial1.write(start); //starting seq
  Serial1.write(cmd);    
  
  delay(250);
  
  if (cmd == 0x11){
    while(Serial.available() == 0){
      if(Serial1.available() > 0){
        int num = Serial1.readBytes(buf, MAX_BUF);
        Serial.write((uint8_t*)buf, num);
      }
    }
  }
  
  else{
    while(Serial1.available() > 0){
      int num = Serial1.readBytes(buf, MAX_BUF);
      Serial.write((uint8_t*)buf, num);
    }
  }
  
  Serial.print("===================================\n");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //USB connected to comp
  Serial1.begin(9600);  //serial rx tx connection
  int i = 10;
  while(i--){
    delay(1000);
  }
  config();

}

void loop(){
  //do nothing here
}

void config() {
  // unit is comminicating at 9600 baud
  
  //0. Switch to common mode
  commandWrite(0x36);
  
  //1. Delete group 1 inst.
  commandWrite(0x01);
  
  //2. Begin to record group 1
  commandWrite(0x11);
        //(finish recording the group)
        
  //3. import the first group
  //commandWrite(0x36);
}
