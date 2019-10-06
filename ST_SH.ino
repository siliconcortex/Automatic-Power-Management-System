



void checkShutdown(){
  //called from loop
    if(digitalRead(clockPin)==1 && digitalRead(dataPin)==1 ){ //c1 d1 the signal for shutdown.
        delay(100);
        if(digitalRead(clockPin)==1 && digitalRead(dataPin)==1 ){
        shutDown();
        }
    }

}


void shutDown(){ 

  writeSD();
  digitalWrite(outPin1,0);
  delay(2000);
  digitalWrite(outPin2,0);
  Serial.println("Shutting down...");
  beep(250,750,10);
}  
 




