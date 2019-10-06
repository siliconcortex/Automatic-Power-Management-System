void getHM2(){
  //called from ethernetMain() at ETH.ino
  
  int HTPointer = 0;
  int alphaPointer = 0;
  int chSlot = 0;
  char chOne = 0;
  char chTen = 0;
  boolean endFlag = 0;
  boolean overflowFlag = 0;

  for(int a=0; a<REQ_BUF_SZ; a++){ //loops until a &HM= is found

    if(HTTP_req[a]=='&' && HTTP_req[a+1]=='H'&& HTTP_req[a+2]=='M'&& HTTP_req[a+3]=='2' && HTTP_req[a+4]=='='){ //found &HM2=
      //Serial.println("HMTAG2 received.");
      HTPointer = a+5;//set pointer to assumed alphabet location

      while(!endFlag){
        if(HTTP_req[HTPointer]==alphabet[alphaPointer]){//if the current alphabet is found
          Serial.print("Div: ");
          Serial.println(HTTP_req[HTPointer]);  //debug
          
          int x;
          if(HTTP_req[HTPointer]==alphabet[20]){//if a "u" is found, incoming is MODES
          x=HTPointer+1;          
                    for(int i=0;i<10;i++){
                      if(HTTP_req[x]==49){ //49 is 1 as string
                        ch2[i][0] = 1;
                        MODE2[i]=1;
                      }else{
                        ch2[i][0] = 0;
                        MODE2[i]=0;
                        Serial.println("Received something from 2");
                      }
                      x++;
                    }
 

          }

          if(HTTP_req[HTPointer+1]==alphabet[alphaPointer+1]){//check, might be empty (next character in HT also alphabet)

            overflowFlag = encodeCh2(57,57,chSlot); //to ETH_HM.ino

            Serial.println("EMPTY");
            chSlot++;
            HTPointer++;
            alphaPointer++;
          }
          else{
            //check if a two or one digit numeral
            if(HTTP_req[HTPointer+2]==alphabet[alphaPointer+1]){//if one digit, two spaces next is the next alphabet
              //one digit
              chOne = HTTP_req[HTPointer+1];
              chTen = 48;
              Serial.print("ONE:");Serial.println(chOne);
              overflowFlag = encodeCh2(chOne, chTen, chSlot); //to ETH_HM.ino

              alphaPointer++;
              HTPointer++;
              chSlot++;
            }
            else{
              //two digit
              chTen = HTTP_req[HTPointer+1];
              Serial.print("TEN:");Serial.println(chTen);
              chOne = HTTP_req[HTPointer+2];
              Serial.print("ONE:");Serial.println(chOne);
              overflowFlag = encodeCh2(chOne, chTen, chSlot); //to ETH_HM.ino

              alphaPointer++;
              HTPointer++;
              chSlot++;
            }
          }

        }
        else{
          HTPointer++;
        }

        //condition to exit loops
        if(chSlot>19){
          endFlag=1;
        }

        if(overflowFlag){
          //Serial.print("Overflow: ");Serial.println(chSlot);
          overflowFlag=0;
        }

      }


    }
  }
  //beep(50,1,1);
}


boolean encodeCh2 (char ones, char tens, int slot){
//called from getHM() at ETH_HM.ino
  delay(1);
  if(slot<10){
    //hour
  
    ch2[slot][1] = (ones-48)+(tens-48)*10;

  Serial.print("ch2:");
  Serial.println(ch2[slot][1]);
  }

  if(slot>=10){
    //minute

    ch2[slot-10][2] = (ones-48)+(tens-48)*10;

  Serial.print("ch2:");
  Serial.print(ch2[slot-10][2]);
  }
  Serial.print("slot: ");
  Serial.print(slot);

  return 0;

}
