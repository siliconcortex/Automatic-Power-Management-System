void power(){

int ADCsamples=500;
temp[0]=0; 
for(int i = 0 ;i<ADCsamples;i++){
temp[0]+=analogRead(0);
delayMicroseconds(500);
}
temp[0]/=ADCsamples;
//computes r power/adc ratio due to nonlinearity

  float floatTemp;
  floatTemp = float(temp[0]);
  actualPower = (0.0005*(square(floatTemp)))+(0.2303*floatTemp)+24.126; //yeah as you know
  powerRaw = temp[0]; //to send to display
  //  costPerHour = (actualPower/1000)*costPerkWh;
  if(actualPower>26.0){
  energy(actualPower); //to ENGY.ino
  }else{
  actualPower=0.0;
  }
  

temp[0]=0; 
for(int i = 0 ;i<ADCsamples;i++){
temp[0]+=analogRead(1);
delayMicroseconds(500);
}
temp[0]/=ADCsamples;
//computes r power/adc ratio due to nonlinearity

  floatTemp = float(temp[0]);
  actualPower2 = (0.0007*(square(floatTemp)))+(0.249*floatTemp)+22.292; //yeah as you know
  powerRaw2 = temp[0]; //to send to display
  //  costPerHour = (actualPower/1000)*costPerkWh;
  if(actualPower2>26.0){
  energy(actualPower2); //to ENGY.ino
  }else{
  actualPower2=0.0;
  }
  


}



void realTimePowerCheck(){


if (actualPower>ADCPowerLimit || actualPower2 > ADCPowerLimit2){
  
  
//  writeSDSettings(0); //to SD.ino
//  writeSDSettings(1); //to SD.ino
  

  fuseFlag = 1;
  digitalWrite(outPin1,0);
  digitalWrite(outPin2,0);
  pinMode(buzPin, OUTPUT);  //buzzer
  digitalWrite(buzPin,1);
  delay(10000);
  digitalWrite(buzPin,0);

  
}


}

void overloadRecover(){

if (actualPower<ADCPowerLimit && actualPower2 < ADCPowerLimit2){
  
  fuseFlag = 0;
//  writeSDSettings(0); //to SD.ino
//  writeSDSettings(1); //to SD.ino
  


}
}

