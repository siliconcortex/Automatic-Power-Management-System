void CPU2Main(){
  //called from loop()  

      DispCPU2(0);
      delay(1);
      DispCPU2(0);
      delay(1);
      DispCPU2(0);
      delay(3);

      DispCPU2(1);
      delay(1);
      DispCPU2(1);
      delay(1);
      DispCPU2(1);
      
      delay(3);
      DispCPU2(2);
      delay(1);
      DispCPU2(2);
      delay(1);
      DispCPU2(2);     


}

void DispCPU2(int type){
boolean leadZero = 1;
int i;
  switch(type){
  case 0://time
    D[3] = currentTime[3]/10;
    D[2] = currentTime[3]-(D[3]*10);
    D[1] = currentTime[4]/10;
    D[0] = currentTime[4]-(D[1]*10);
    

    
    sendCPU2(type,D[3],D[2],D[1],D[0],200); //to CPU2.ino
    break;
  case 1://power
    D[3] = powerRaw/1000;
    D[2] = (powerRaw-(D[3]*1000))/100;
    D[1] = (powerRaw-(D[3]*1000)-(D[2]*100))/10;
    D[0] = (powerRaw-(D[3]*1000)-(D[2]*100)-(D[1]*10));

    
    sendCPU2(type,D[3],D[2],D[1],D[0],200); //to CPU2.ino
    break;
   case 2://energy
    D[3] = powerRaw2/1000;
    D[2] = (powerRaw2-(D[3]*1000))/100;
    D[1] = (powerRaw2-(D[3]*1000)-(D[2]*100))/10;
    D[0] = (powerRaw2-(D[3]*1000)-(D[2]*100)-(D[1]*10));

    
    sendCPU2(type,D[3],D[2],D[1],D[0],200); //to CPU2.ino
   break;

  }
}


void sendCPU2(byte sb,byte d4,byte d3,byte d2,byte d1,byte duration){
  //called from DispCPU2() at CPU2.ino
  
  byte startByte = 255;
  int ttimeh = 100;
  int ttimel = 100;
  boolean offFlag = 0; 
  //Serial.println("Sending to CPU2...");
  //start
  digitalWrite(clockPin2,0);
  digitalWrite(reqPin2,1); 
  for(int i=7;i>=0;i--){
    digitalWrite(dataPin2,bitRead(startByte,i));
    digitalWrite(clockPin2,1);
    delayMicroseconds(ttimeh);
    digitalWrite(clockPin2,0);
    digitalWrite(dataPin2,0);
    //debug
    //Serial.print(digitalRead(dataPin2));
    delayMicroseconds(ttimel);
  }

  digitalWrite(reqPin2,0); 

  for(int i=7;i>=0;i--){

    digitalWrite(dataPin2,bitRead(sb,i));
    digitalWrite(clockPin2,1);
    delayMicroseconds(ttimeh);
    digitalWrite(clockPin2,0);
    digitalWrite(dataPin2,0);
    //debug
    //Serial.print(digitalRead(dataPin2));
    delayMicroseconds(ttimel);

  }

  //data    
  for(int j=0;j<=3;j++){
    byte data;

    switch(j){
    case 0:
      data = d4;
      break;

    case 1:
      data = d3;
      break;

    case 2:
      data = d2;
      break;

    case 3:
      data = d1;
      break;

    }

    for(int i=7;i>=0;i--){

      digitalWrite(dataPin2,bitRead(data,i));
      digitalWrite(clockPin2,1);
      delayMicroseconds(ttimeh);
      digitalWrite(clockPin2,0);
      digitalWrite(dataPin2,0);
      //debug
      //Serial.print(digitalRead(dataPin2));
      delayMicroseconds(ttimel);
    }  

  }
  //Serial.println("");
  //return;

  for(int i=7;i>=0;i--){

    digitalWrite(dataPin2,bitRead(duration,i));
    digitalWrite(clockPin2,1);
    delayMicroseconds(ttimeh);
    digitalWrite(clockPin2,0);
    digitalWrite(dataPin2,0);
    //debug
    //Serial.print(digitalRead(dataPin2));
    delayMicroseconds(ttimel);
  } 

}







