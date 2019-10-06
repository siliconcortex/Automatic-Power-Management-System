void selectAutoManual(){
  //called from loop()

if(fuseFlag == 0){

  if(AUTO1){
     LED_state[0] = CH1AUTO;
     
  }else{
     LED_state[0] = CH1MANUAL;
  }
  
  if(AUTO2){
     LED_state[1] = CH2AUTO;
     
  }else{
     LED_state[1] = CH2MANUAL;
  }
  

}
  
  digitalWrite(outPin1,LED_state[0]);
  digitalWrite(outPin2,LED_state[1]);
  
  boolean autoStat;
  boolean manualStat;
  
  autoStat = AUTO1 || AUTO2;
  manualStat = (!AUTO1) || (!AUTO2);

  digitalWrite(autoPin,autoStat);
  digitalWrite(manualPin,manualStat);

}
