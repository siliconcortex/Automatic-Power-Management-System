void sendCPU3(byte cmd,long data){
  //called from DispCPU2() at CPU2.ino
  //data to is is GSMArray[14] (global)

  byte startByte = 170; //10101010
  int ttimeh = 100;
  int ttimel = 100;
  boolean offFlag = 0; 
  //Serial.println("Sending to CPU2...");
  //start
  digitalWrite(clockPin2,0);
 
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

  

  for(int i=7;i>=0;i--){

    digitalWrite(dataPin2,bitRead(cmd,i));
    digitalWrite(clockPin2,1);
    delayMicroseconds(ttimeh);
    digitalWrite(clockPin2,0);
    digitalWrite(dataPin2,0);
    //debug
    //Serial.print(digitalRead(dataPin2));
    delayMicroseconds(ttimel);

  }
  Serial.println("SMS: ");
  Serial.println(data);
  Serial.println(data);
      for(int i=23;i>=0;i--){
      
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



void getFreq(){
  //called from ethernetMain() at ETH.ino
  
  char HTPointer = 0;
  int alphaPointer = 0;
  int chSlot = 0;
  char chOne = 0;
  char chTen = 0;
  char chHun=0;
  char chTho=0;
  
  boolean endFlag = 0;
  boolean overflowFlag = 0;
  char *uPointer;

  for(int a=0; a<REQ_BUF_SZ; a++){ //loops until a &HM= is found

    if(HTTP_req[a]=='&' && HTTP_req[a+1]=='S'&& HTTP_req[a+6]=='E'&& HTTP_req[a+7]=='Q' && HTTP_req[a+8]=='='){ //found &SMSFREQ=
      Serial.println("SMSFRc.");
      HTPointer = a+10;//set pointer to assumed data location
      
      while(!endFlag){
        if(HTTP_req[HTPointer]==alphabet[alphaPointer]){//if the current alphabet is found
          Serial.print("Div: ");
          Serial.println(HTTP_req[HTPointer]);  //debug
          
          if(HTTP_req[HTPointer+1]==alphabet[alphaPointer+1]){//check, might be empty (next character in HT also alphabet)

            //overflowFlag = encodeCh1(57,57,chSlot); //to ETH_HM.ino

            Serial.println("EMPTY");
           
            endFlag++;
          }
          else{
            //check if a two or one digit numeral
            if(HTTP_req[HTPointer+2]==alphabet[alphaPointer+1]){//if one digit, two spaces next is the next alphabet
              //one digit
              chOne = HTTP_req[HTPointer+1];
              chTen = 48;
              SMSTimer=chOne-48;
              Serial.print("ONE:");Serial.println(chOne);
              //overflowFlag = encodeCh1(chOne, chTen, chSlot); //to ETH_HM.ino

              endFlag++;
            }
            else if(HTTP_req[HTPointer+3]==alphabet[alphaPointer+1]){
              
              chOne = HTTP_req[HTPointer+2];
              chTen = HTTP_req[HTPointer+1];
              SMSTimer=((chTen-48)*10)+(chOne-48);
              Serial.print("ONE:");Serial.println(chOne);
              Serial.print("TEN:");Serial.println(chTen);
              //overflowFlag = encodeCh1(chOne, chTen, chSlot); //to ETH_HM.ino

              endFlag++;
            
            }
            
            
            
            
            else if(HTTP_req[HTPointer+4]==alphabet[alphaPointer+1]){
            
              //3 digit
              chOne = HTTP_req[HTPointer+3];
              chTen = HTTP_req[HTPointer+2];
              chHun = HTTP_req[HTPointer+1];
              SMSTimer=((chHun-48)*100)+((chTen-48)*10)+(chOne-48);
              //overflowFlag = encodeCh1(chOne, chTen, chSlot); //to ETH_HM.ino
              endFlag++;
            
            }
          }

        }
        



      }


    }
  }
  //beep(50,1,1);
  }


//boolean encodeSMS (char ones, char tens, int slot){
////called from getHM() at ETH_HM.ino
//  delay(1);
//  if(slot<10){
//    //hour
//  
//    ch1[slot][1] = (ones-48)+(tens-48)*10;
//
//  Serial.print("ch1:");
//  Serial.println(ch1[slot][1]);
//  }
//
//  if(slot>=10){
//    //minute
//
//    ch1[slot-10][2] = (ones-48)+(tens-48)*10;
//
//  Serial.print("ch1:");
//  Serial.print(ch1[slot-10][2]);
//  }
//  Serial.print("slot: ");
//  Serial.print(slot);
//
//  return 0;
// 
//
//}


void SMSE(){
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
sendCPU3(1,energyWh);//0 is for test
delayMicroseconds(1);
beep(50,50,5);
}



