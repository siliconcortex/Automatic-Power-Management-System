void microRTC(int seconds){
  //called from loop()
  
  currentTime[5] += seconds;
  
  if (currentTime[5] >= 60){
  currentTime[5] = 0;
  currentTime[4]++;
  powerLog();//to ENGY.ino
  }
  
  if (currentTime[4] >= 60){
  currentTime[4] = 0;
  currentTime[3]++;
  
    if(SMSTimer){
      SMSTimer--;
    }else{
      SMSE();//to CPU3.ino
      SMSTimer=SMSTimerNow;
    }
  }

  if (currentTime[3] >= 24){
  currentTime[3] = 0;
  currentTime[2]++;
  }

//            minute            hour*60              day*24*60                month*24*60*mdte
unsigned long num = daysSince(currentTime[1]); 
timeStamp = (currentTime[4])+(currentTime[3]*60)+(currentTime[2]*60*24)+(currentTime[1]*60*24*num);

}

void picRTCRead(){
  //called from loop()
  
Serial.println("Loading time...");

boolean continueF = 1;
boolean clockE =0;
boolean recvF = 1;
long timer = 50000;

while(continueF){

        digitalWrite(reqPin,1);
        if (digitalRead(clockPin) ==1 && clockE == 0){
        digitalWrite(reqPin,0);
        
          clockE = 1;
          //shift all leftwise
          //newwest is zero
          for(int i = 47; i >= 0;i--){
            dataBuf[i] = dataBuf[i-1];
          }
          dataBuf[0] = digitalRead(dataPin);
          
        }
        
        if (digitalRead(clockPin) == 0){
          clockE=0;
        }
        
        //check start and end bytes
        recvF = 1;
        
        
        if (dataBuf[47]==1 && dataBuf[46]==1 && dataBuf[45]==1 && dataBuf[44]==1 && dataBuf[43]==1 && dataBuf[42]==1 && dataBuf[41]==1 && dataBuf[40]==1){
        // or 11111111
        recvF = 1;
        continueF=0;
        //Serial.println("startbits OK");
        }
        
        if(!timer){//timer runs out e.g. RTC not responding
          beep(500,500,10);
          Serial.println("RTC Not Responding");
          shutDown();
        }
        
        timer--;
        delayMicroseconds(100);
}
        
        int index = 39;
        int value;
        if(recvF){
          
            currentTime[4]=0;
            for (int i = 7; i>=0;i--){
                value = raise(2,i);
                currentTime[4]+=dataBuf[index]*value;
                index--;
            }
            Serial.println(currentTime[4]);
            
            currentTime[3]=0;
            for (int i = 7; i>=0;i--){
                value = raise(2,i);
                currentTime[3]+=dataBuf[index]*value;
                index--;
            }
            Serial.println(currentTime[3]);
            
            currentTime[2]=0;
            for (int i = 7; i>=0;i--){
                value = raise(2,i);
                currentTime[2]+=dataBuf[index]*value;
                index--;
            }
            Serial.println(currentTime[2]);
            
            currentTime[1]=0;
            for (int i = 7; i>=0;i--){
                value = raise(2,i);
                currentTime[1]+=dataBuf[index]*value;
                index--;
            }
            Serial.println(currentTime[1]);
            
            //debug
//            for(int i = 47; i>=0;i--){
//            Serial.print(dataBuf[i]);
//            }
            
            Serial.println("Time Loaded.");
            dataBuf[40]=0;
            return;
        }




}




