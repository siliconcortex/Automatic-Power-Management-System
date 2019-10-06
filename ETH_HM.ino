void getHM(){
  //called from ethernetMain() at ETH.ino
  
  char HTPointer = 0;
  int alphaPointer = 0;
  int chSlot = 0;
  char chOne = 0;
  char chTen = 0;
  boolean endFlag = 0;
  boolean overflowFlag = 0;
  char *uPointer;

  for(int a=0; a<REQ_BUF_SZ; a++){ //loops until a &HM= is found

    if(HTTP_req[a]=='&' && HTTP_req[a+1]=='H'&& HTTP_req[a+2]=='M'&& HTTP_req[a+3]=='='){ //found &HM=
      //Serial.println("HMTAG received.");
      HTPointer = a+4;//set pointer to assumed alphabet location

      while(!endFlag){
        if(HTTP_req[HTPointer]==alphabet[alphaPointer]){//if the current alphabet is found
          Serial.print("Div: ");
          Serial.println(HTTP_req[HTPointer]);  //debug
          
          int x;
          if(HTTP_req[HTPointer]==alphabet[20]){//if a "u" is found, incoming is MODES
          x=HTPointer+1;          
                    for(int i=0;i<10;i++){
                      if(HTTP_req[x]==49){ //49 is 1 as string
                        ch1[i][0] = 1;
                        MODE1[i]=1;
                      }else{
                        ch1[i][0] = 0;
                        MODE1[i]=0;
                      }
                      x++;
                    }
 

          }
          
          if(HTTP_req[HTPointer+1]==alphabet[alphaPointer+1]){//check, might be empty (next character in HT also alphabet)

            overflowFlag = encodeCh1(57,57,chSlot); //to ETH_HM.ino

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
              overflowFlag = encodeCh1(chOne, chTen, chSlot); //to ETH_HM.ino

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
              overflowFlag = encodeCh1(chOne, chTen, chSlot); //to ETH_HM.ino

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
        if(chSlot>20){
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


boolean encodeCh1 (char ones, char tens, int slot){
//called from getHM() at ETH_HM.ino
  delay(1);
  if(slot<10){
    //hour
  
    ch1[slot][1] = (ones-48)+(tens-48)*10;

  Serial.print("ch1:");
  Serial.println(ch1[slot][1]);
  }

  if(slot>=10){
    //minute

    ch1[slot-10][2] = (ones-48)+(tens-48)*10;

  Serial.print("ch1:");
  Serial.print(ch1[slot-10][2]);
  }
  Serial.print("slot: ");
  Serial.print(slot);

  return 0;
 

}


