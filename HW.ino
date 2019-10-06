void checkManual(){
  //called from loop()
  
  digitalWrite(switchPin2,1);
  pinMode(switchPin2,OUTPUT);
  delayMicroseconds(CBDelay);
  if(((digitalRead(switchPin)==0) ||(CH1MANUAL == 1 && ethernetManualFlag ==1)) && switchFlag == 0 && holdFlag == 0){ 
    //if hardware button is pressed or
    //check if manual control via ethernet is done
    //also considering toggle variable switchFlag
    //and also considering whether this is a press or a hold.
    //and hold has no function.
    //sendCPU3(1,1); //to CPU3.ino
    delay(1);
    switchFlag = 1;
    holdFlag =1;
    //Serial.println("Switch 1 pressed.");
    beep(20,0,1);
    autoTemp = AUTO1; //temporary container of previous auto setting 
    
    AUTO1 = 0; //override auto scheduler temporarily
    CH1MANUAL = 1; //turn on manual
    
    safetyTime = 10800; //temporary value is for fast debugging, which is in real, 60x60x3 seconds, 3hours you say
    ethernetManualFlag =0; //clear Ethernet flag, if any
    delay(200);
    
  }
  
  if(digitalRead(switchPin)==0 && switchFlag ==1){
   
    CH1MANUAL = 0;  //turn off
    AUTO1 = autoTemp; //return to previuos settings
    safetyTime = 0; //just making sure
    beep(20,100,2);
    //Serial.print("safetime: ");
    //Serial.print("timer expired.");
    switchFlag = 0;
    
  }
  
  
  //release button code
  if(digitalRead(switchPin)==1 && holdFlag ==1){
    
    holdFlag = 0;
    
  }
  digitalWrite(switchPin2,0);
  pinMode(switchPin2,INPUT);
  
  
  digitalWrite(switchPin,1);
  pinMode(switchPin,OUTPUT);
  delayMicroseconds(CBDelay);
  //button for channel 2
    if(((digitalRead(switchPin2)==0) ||(CH2MANUAL == 1 && ethernetManualFlag2 ==1)) && switchFlag2 == 0 && holdFlag2 == 0){ 
    //if hardware button is pressed or
    //check if manual control via ethernet is done
    //also considering toggle variable switchFlag
    //and also considering whether this is a press or a hold.
    //and hold has no function.
    
    //sendCPU3(1,2);//t CPU3.ino
    
    switchFlag2 = 1;
    holdFlag2 =1;
    //Serial.println("Switch 2 pressed.");
    beep(20,0,1);
    autoTemp2 = AUTO2; //temporary container of previous auto setting 
    
    AUTO2 = 0; //override auto scheduler temporarily
    CH2MANUAL = 1; //turn on manual
    
    safetyTime2 = 10800; //temporary value is for fast debugging, which is in real, 60x60x3 seconds, 3hours you say
    ethernetManualFlag2 =0; //clear Ethernet flag, if any
    
    delay(200);
  }
  
  if(digitalRead(switchPin2)==0 && switchFlag2 ==1){
   
    CH2MANUAL = 0;  //turn off
    AUTO2 = autoTemp2; //return to previuos settings
    safetyTime2 = 0; //just making sure
    beep(20,100,2);
    //Serial.print("safetime2: ");
    //Serial.print("timer expired.");
    switchFlag2 = 0;
    
  }
  
  
  //release button code
  if(digitalRead(switchPin2)==1 && holdFlag2 ==1){
    
    holdFlag2 = 0;
    
  }
  digitalWrite(switchPin,0);
  pinMode(switchPin,INPUT);
    
 
  
}

void safetyTimerDecrement(){
  //called from loop()
  
    if (safetyTime>0){
    
    //Serial.print("safetime: ");
    //Serial.println(safetyTime);
    safetyTime--;
    }
    
    if(safetyTime==1){
    CH1MANUAL = 0;  //turn off
    AUTO1 = autoTemp; //return to previuos settings
    safetyTime = 0; //just making sure
    beep(20,100,2);
    switchFlag = 0;
    //Serial.print("safetime: ");
    //Serial.print("timer expired.");
    }
    
    
    if (safetyTime2>0){
    
    //Serial.print("safetime2: ");
    //Serial.println(safetyTime2);
    safetyTime2--;
    }
    
    if(safetyTime2==1){
    CH2MANUAL = 0;  //turn off
    AUTO2 = autoTemp2; //return to previuos settings
    safetyTime2 = 0; //just making sure
    beep(20,100,2);
    switchFlag2 = 0;
    //Serial.print("safetime2: ");
    //Serial.print("timer expired.");
    }
}
