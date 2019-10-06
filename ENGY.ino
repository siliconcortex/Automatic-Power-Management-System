void energy(float reading){
  //called from power() at PWR.ino
  
  energymicroWh += reading * energyFactor;
  
  while (energymicroWh >= 1000000.0){
    float tempval;
    tempval = energymicroWh - 1000000.0;
    energyWh += 1;
    energymicroWh = tempval;
      
  }
  
  
//  if (energyWh >=1000){
//    energykWh += energyWh/1000;
//    energyWh = 0;
//    
//  }
//  
//  if (energykWh > 9999999){
//    energykWh = 0;
//    
//  }
//  
  //-----------------------------------------------------
  

  

}


void powerLog(){
  //called from RTC.ino
   File logFile; //SD log File
// Serial.println("LOG.TXT");
 
 logFile = SD.open("log.txt", FILE_WRITE);
 // writing in the file works just like regular print()/println() function
unsigned long energy=(1000*energykWh)+energyWh;

logFile.print(timeStamp);
logFile.print(",");
logFile.print(energy);
logFile.println(",");

//debugging print written settings


 logFile.close();
 delay(1);
  
  
  
//  Serial.println("Energy: ");
//  Serial.println(energymicroWh);
//  Serial.println(energyWh);
//  Serial.println("----");

}
