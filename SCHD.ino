void timeTableInit(){
  //called from loop()
  
 //initialize timetable with "disabled" value (DISABLE == 99)
 for(int j = 0; j < timeTableRows; j++)
 {
   for(int i = 0; i < timeTableColumns; i++){
   ch1[j][i] = 99;
   ch2[j][i] = 99;
   }
 }
 
   for(int j = 0; j < timeTableRows; j++){
   ch1[j][0] = 0;
   ch2[j][0] = 0;
   ch1[j][3] = 1;
   ch2[j][3] = 1;
   }

// Serial.println("OK");
}
 
 
void sortSchedule(){
  //called from loop()
  //update, sorting both ch1[] and ch2[]
  

int sort; //temporary cache for swap function

//timetable 1 sort  
Serial.print("Sorting Timetable 1.....");
for (int a = 0; a < 20; a++){ //multiple iterations to ensure good sorting
delay(1);
for (int j = 0; j < (timeTableRows-1) ; j++){
    delay(1);
//  Serial.print("ROWS: ");Serial.print(j);Serial.print(":");Serial.print(j+1);Serial.print(" ");
    int time1, time2; //maximum valid value time can attain 86399 SECONDS
    
    time1 = (ch1[j][1]*60)+(ch1[j][2]);  //values compared are consecutive rows
    time2 = (ch1[j+1][1]*60)+(ch1[j+1][2]); //conversion of time in secons to ease comparison
//    Serial.print("time");Serial.print(j);Serial.print(": ");Serial.print(time1);
//    Serial.print("time");Serial.print(j+1);Serial.print(": ");Serial.println(time2); //debug :(
    if (j < timeTableRows && ch1[j+1][0] != 99){ //stack overflow checker          
      if (time1 > time2){ //swap places operation
          //array transfer
          for (int k = 0; k < timeTableColumns; k++){ //iterate into number of columns
            sort = ch1[j+1][k]; //transfer row j+1 into sort
            ch1[j+1][k] = ch1[j][k]; //transfer entry of j to j+1 in the current value of k
            ch1[j][k] = sort; //transfer j+1's value saved in sort into j
          }
      }      
      }   
  }
}
Serial.println("100%");

//timetable 2 sort
Serial.print("Sorting Timetable 2.....");
for (int a = 0; a < 20; a++){ //multiple iterations to ensure good sorting
delay(1);
for (int j = 0; j < (timeTableRows-1) ; j++){
  delay(1);
//  Serial.print("ROWS: ");Serial.print(j);Serial.print(":");Serial.print(j+1);Serial.print(" ");
    int time1, time2; //maximum valid value time can attain 86399 SECONDS
    
    time1 = (ch2[j][1]*60)+(ch2[j][2]);  //values compared are consecutive rows
    time2 = (ch2[j+1][1]*60)+(ch2[j+1][2]); //conversion of time in secons to ease comparison
//    Serial.print("time");Serial.print(j);Serial.print(": ");Serial.print(time1);
//    Serial.print("time");Serial.print(j+1);Serial.print(": ");Serial.println(time2); //debug :(
    if (j < timeTableRows && ch1[j+1][0] != 99){ //stack overflow checker          
      if (time1 > time2){ //swap places operation
          //array transfer
          for (int k = 0; k < timeTableColumns; k++){ //interate into number of columns
            sort = ch2[j+1][k]; //transfer row j+1 into sort
            ch2[j+1][k] = ch2[j][k]; //transfer entry of j to j+1 in the current value of k
            ch2[j][k] = sort; //transfer j+1's value saved in sort into j
          }
      }      
      }   
  }
}
Serial.println("100%");
}


void checkSched(){
  //called from loop()
  //update, adopting ch2
  
 for (int j = 0; j <timeTableRows; j++){  //check for first sched line of code
//   Serial.println(" ");
//   Serial.print("ROW: "); //debug
   if (ch1[j][1] != 999){ //if timeslot is enabled...
   
//       Serial.println(j);       //debug 
    if(currentTime[3] > ch1[j][1]){       //check hour against hour then...
//           Serial.print("CH > ");
//           Serial.print(ch1[j][1]);
//           Serial.print(" ");
           decisionSwitch(ch1[j][0]);      
                
   }else{
          if(currentTime[4] >= ch1[j][2] && currentTime[3] == ch1[j][1]){      //...minute.if hours are equal...then...
//              Serial.print("CM > ");
//              Serial.print(ch1[j][2]);
//              Serial.print(" ");
              decisionSwitch(ch1[j][0]);
         }
           }    
   }
 }
 
 
 
 //decision switch channel 2
  for (int j = 0; j <timeTableRows; j++){  //check for first sched line of code
//   Serial.println(" ");
//   Serial.print("ROW: "); //debug
   if (ch2[j][1] != 999){ //if timeslot is enabled...
   
//       Serial.println(j);       //debug 
    if(currentTime[3] > ch2[j][1]){       //check hour against hour then...
//           Serial.print("CH > ");
//           Serial.print(ch1[j][1]);
//           Serial.print(" ");
           decisionSwitch2(ch2[j][0]);      
                
   }else{
          if(currentTime[4] >= ch2[j][2] && currentTime[3] == ch2[j][1]){      //...minute.if hours are equal...then...
//              Serial.print("CM > ");
//              Serial.print(ch1[j][2]);
//              Serial.print(" ");
              decisionSwitch2(ch2[j][0]);
         }
           }    
   }
  }
}
//--------------------------decisionSwitch function-----------------------------------
void decisionSwitch (int mode)
{
  //called from checkSched() at SCHD.ino

switch(mode)         //decide based on mode (off or on sched)
        {
           case 0:
               CH1AUTO = 0;
           break; 
           case 1:
               CH1AUTO = 1;
           break; //turn ON channel 1
         }
         
}



void decisionSwitch2 (int mode){
  //called from checkSched() at SCHD.ino

switch(mode)         //decide based on mode (off or on sched)
         {
         case 0:
               CH2AUTO = 0;
           break; 
         case 1:
               CH2AUTO = 1; 
           break; //turn ON channel 1
         }     


}
 

void transferToScheduler(){
  //called from getHM() at ETH_HM.ino
  //called from loop()
  //Serial.print("Transferring modes..");
  for(int i=0; i<timeTableRows;i++){
  ch1[i][0] = MODE1[i];
  ch2[i][0] = MODE2[i];
  }
  //Serial.print("100%");
}

void transferToMemory(){
  //called from getHM() at Main.ino
  //called from loop()
  //Serial.print("Transferring modes..");
  for(int i=0; i<timeTableRows;i++){
  MODE1[i] = ch1[i][0];
  MODE2[i] = ch2[i][0];
  }
  //Serial.print("100%");
}

