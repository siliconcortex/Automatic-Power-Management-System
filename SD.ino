void readSDSettings(byte data){
//called from loop()
 File schedFile; //SD sched File
 char character;
 String settingName;
 String settingValue;
 
 switch(data){
   case 0:
   schedFile = SD.open("schedule.txt");
   break;
   case 1:
   schedFile = SD.open("savefile.txt");
   break;
   case 2:
   schedFile = SD.open("sched2.txt");
   break;
 }
 
 if (schedFile) {
 while (schedFile.available()) {
   character = schedFile.read();
     while((schedFile.available()) && (character != '[')){
     character = schedFile.read(); //everything before [
     }
     character = schedFile.read(); // [ allowance
     while((schedFile.available()) && (character != '=')){
     settingName = settingName + character; //save and append everything after [ into settingName
     character = schedFile.read();
     }
     character = schedFile.read(); // = allowance
        
     while((schedFile.available()) && (character != ']')){
     settingValue = settingValue + character; // save setting value
     character = schedFile.read();
     }
 if(character == ']'){ //terminator detection
 
 //Debuuging Printing
// Serial.print("Name: ");
// Serial.print(settingName);
// Serial.print(" ");
// Serial.print("Value: ");
// Serial.println(settingValue);

 
 // Apply the value to the parameter
 //update 01/07/2016 new parameter "data"
 applySetting(settingName,settingValue,data); //to SD.ino
 // Reset Strings
 settingName = "";
 settingValue = "";
 }
 }
 // close the file:
 schedFile.close();
 } else {
 // if the file didn't open, print an error:
 Serial.println("X - ERROR reading ?????.txt");
 }

readSDStatus = 1;

}
 
 
 
 
 
 
 
 /* Apply the value to the parameter by searching for the parameter name
 Using String.toInt(); for Integers
 toFloat(string); for Float
 toBoolean(string); for Boolean
 toLong(string); for Long
 */

 
void applySetting(String settingName, String settingValue,byte data) {
  //called from readSDSettings() at SD.ino
  //new update 01/08/2016, third argument selects whether apply to scheduler
  //or to settings
  
  
 /*
 in SCHEDULE.TXT case 0
 the format of the expected data is 
 
 (4*j)+i = [mode][hour][minute][second]
 e.g.
 0=[1][12][30][00]
 1=[0][11][15][00]
 2=[....
 
 in SAVEFILE.TXT case 1
 the format is
 1 to 4 are ledstates
 [1=led1][2=led2]...
 5 - energymicroWh
 6 - energyWh
 7 - energykWh
 8 - AUTO1
  
  
 or refer to writeSDSettings() for full code 
 */
 
 
  switch (data){ 
      case 0:
        int *ch1Place; //ch1 pointer
        for (int j=0; j<timeTableRows; j++){ //apply row by row
        for (int i=0; i<timeTableColumns; i++){ //apply values into TIMETABLE entry column [mode][h][m][s]
         
         int placeHold = (timeTableColumns*j)+i; //placeHold increments every array focus movement
         ch1Place = &ch1[0][0]; //set the pointer that points to ch1[0][0]
         ch1Place += placeHold; //lock to proper data in ch1[x+j][y+i]
         String stringHold;
         stringHold = (String)placeHold; //stringHold contains data to compare to settingName
         
         if (settingName == stringHold){ //compare current Place to Settingname(which is a number)
         *ch1Place = settingValue.toInt(); //load value to the read setting location
         }
         
        }
        }  
        
      break;
      
      
      case 1:
      int name;
      int value;
      long valueLong;
      float valueFloat;
        name = settingName.toInt();
        value = settingValue.toInt();
        valueLong = toLong(settingValue);
        valueFloat = toFloat(settingValue);
        
        if (name<4){
          
          LED_state[name] = value;
        
        }
        
        switch(name){
        case 4:
        energymicroWh=abs(valueFloat);
        break;
        case 5:
        energyWh=valueLong;
        break;
        case 6:
        energykWh=valueLong;
        break;
        case 7:
        AUTO1=value;
        break;
        case 8:
        AUTO2=value;
        break;
        case 9:
        SMSTimer=value;
        break;
        case 10:
        SMSTimerNow=value;
        break;
        }
        
// storeArray[4] = energymicroWh;
// storeArray[5] = energyWh;
// storeArray[6] = energykWh;
// storeArray[7] = AUTO1; 
 
      break;
      
      
        //Scheduler2
        case 2:
        int *ch2Place; //ch1 pointer
        for (int j=0; j<timeTableRows; j++){ //apply row by row
        for (int i=0; i<timeTableColumns; i++){ //apply values into TIMETABLE entry column [mode][h][m][s]
         
         int placeHold = (timeTableColumns*j)+i; //placeHold increments every array focus movement
         ch2Place = &ch2[0][0]; //set the pointer that points to ch1[0][0]
         ch2Place += placeHold; //lock to proper data in ch1[x+j][y+i]
         String stringHold;
         stringHold = (String)placeHold; //stringHold contains data to compare to settingName
         
         if (settingName == stringHold){ //compare current Place to Settingname(which is a number)
         *ch2Place = settingValue.toInt(); //load value to the read setting location
         }
         
        }
        }  
        
      break;
  }

}



/*
//DEBUGGING
Serial.println("Check RAM values: "); 
for(int j = 0; j < timeTableRows; j++){ //check row by row
for(int i = 0; i < timeTableColumns; i++){ //check values into TIMETABLE entry column [mode][h][m][s]
 Serial.print((timeTableColumns*j)+i);
 Serial.print(": ");
 if (ch1[j][i] == 99){
   Serial.print("DIS ");
   }else{
   Serial.print(ch1[j][i]);
   Serial.print(" / ");
   }
 
}
Serial.println("");
}

*/


/*
 //debug printing
 Serial.print("Current time: ");
 for(int i = 0; i<6; i++){
 Serial.print(currentTime[i]);
 Serial.print("/");
 }
 Serial.println(""); //FORMAT YYYY/MM/DD/HH/MM/SS

 */
 //CONTINUOSLY CHECK RTC AGAINST RAM VALUES-------------------scheduler's main code--------------------------
 //check for hour then minute then second then respond. (off or on).
 //PROBLEM: data in timeTable must be sorted chronologically or
 //else misinterpretation of status will occur 
 
 

 
//why is this needed?<<---------IDE is bugging?



 
// // ------------writeSDSettings------------------------Writes A Configuration (TIMETABLE) file-------------------------------
//void writeSDSettings(byte data) {
//  Serial.print("Write to SD...");
//  //called from getHM() at ETH_HM.ino
//  //called from shutDown() at ST_SH.ino
//   const int arraySize = 8;
//   long storeArray[arraySize];
// 
//  
// 
// switch (data){
// case 0: //schedule.txt--------------------------------------------------------------
// Serial.print("SCHEDULE.TXT");
//
// 
// transferToScheduler(); //transfer ench and mode to cols 0 and 3 
// // Delete the old One
//
// SD.remove("schedule.txt");
// delay(1);
// // Create new one
// 
// schedFile = SD.open("SCHEDULE.txt", FILE_WRITE);
// // writing in the file works just like regular print()/println() function
//
//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s]
// schedFile.print("[");
// schedFile.print((timeTableColumns*j)+i);
// schedFile.print("=");
// schedFile.print(ch1[j][i]);
// schedFile.print("]");
//}
// schedFile.println("");
//}
//
////debugging print written settings
//
//
// schedFile.close();
// delay(1);
// Serial.println("Write done.");
//
//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print((timeTableColumns*j)+i);
// Serial.print(":");
// Serial.print(ch1[j][i]);
// Serial.print("/");
//}
//Serial.println("");
//}
//
// break;
//
//
// case 1: //settings----------------------------------------------------------------------------------
// Serial.print("SETTINGS.TXT");
//
// 
// for (int i = 0; i<4; i++) {
//   storeArray[i] = LED_state[i];  
// }
// storeArray[4] = energymicroWh;
// storeArray[5] = energyWh;
// storeArray[6] = energykWh;
// storeArray[7] = AUTO1; 
// 
// 
// SD.remove("SAVEFILE.txt");
// // Create new one
// schedFile = SD.open("savefile.txt", FILE_WRITE);
// // writing in the file works just like regular print()/println() function
//
//for (int i=0; i<arraySize;i++){ 
// schedFile.print("[");
// schedFile.print(i);
// schedFile.print("=");
// schedFile.print(storeArray[i]);
// schedFile.print("]");
//}
//
////debugging print written settings
//
//Serial.println("Values written to SD Card:");
//for (int i=0; i<arraySize;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print(i);
// Serial.print(":");
// Serial.print(storeArray[i]);
// Serial.println("/");
//}
//
//
// schedFile.close();
// Serial.println("Writing done.");
// break; 
// 
// case 2: //schedule2.txt--------------------------------------------------------------
// Serial.print("SCHED2.TXT");
// 
// transferToScheduler(); //transfer ench and mode to cols 0 and 3 
// // Delete the old One
// SD.remove("SCHED2.txt");
// // Create new one
// schedFile = SD.open("sched2.txt", FILE_WRITE);
// // writing in the file works just like regular print()/println() function
//
//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s]
// schedFile.print("[");
// schedFile.print((timeTableColumns*j)+i);
// schedFile.print("=");
// schedFile.print(ch2[j][i]);
// schedFile.print("]");
//}
// schedFile.println("");
//}
//
////debugging print written settings
//
//Serial.println("Values written to SD Card:");
//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print((timeTableColumns*j)+i);
// Serial.print(":");
// Serial.print(ch2[j][i]);
// Serial.print("/");
//}
//Serial.println("");
//}
//
// schedFile.close();
// Serial.println("Writing done.");
// break;
//
//
// }
//}

//------------------------------------------------------------


void writeSD(){
  
 if(!readSDStatus){
 return;
 } 
  
 File schedFile; //SD sched File
// Serial.println("SCHEDULE.TXT");

 
 transferToScheduler(); //transfer ench and mode to cols 0 and 3 
 // Delete the old One

 SD.remove("schedule.txt");
 delay(1);
 // Create new one
 
 schedFile = SD.open("SCHEDULE.txt", FILE_WRITE);
 // writing in the file works just like regular print()/println() function

for (int j=0;j<timeTableRows;j++){ //load row by row
for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s]
 schedFile.print("[");
 schedFile.print((timeTableColumns*j)+i);
 schedFile.print("=");
 schedFile.print(ch1[j][i]);
 schedFile.print("]");
}
 schedFile.println("");
}

//debugging print written settings


 schedFile.close();
 delay(1);
// Serial.println("Write done.");

//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print((timeTableColumns*j)+i);
// Serial.print(":");
// Serial.print(ch1[j][i]);
// Serial.print("/");
//}
//Serial.println("");
//}
//



// Serial.println("SCHED2.TXT");

 
 transferToScheduler(); //transfer ench and mode to cols 0 and 3 
 // Delete the old One

 SD.remove("sched2.txt");
 delay(1);
 // Create new one
 
 schedFile = SD.open("SCHED2.txt", FILE_WRITE);
 // writing in the file works just like regular print()/println() function

for (int j=0;j<timeTableRows;j++){ //load row by row
for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s]
 schedFile.print("[");
 schedFile.print((timeTableColumns*j)+i);
 schedFile.print("=");
 schedFile.print(ch2[j][i]);
 schedFile.print("]");
}
 schedFile.println("");
}

//debugging print written settings


 schedFile.close();
 delay(1);
// Serial.println("Write done.");
//
//for (int j=0;j<timeTableRows;j++){ //load row by row
//for (int i=0; i<timeTableColumns;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print((timeTableColumns*j)+i);
// Serial.print(":");
// Serial.print(ch2[j][i]);
// Serial.print("/");
//}
//Serial.println("");
//}


// Serial.print("SETTINGS.TXT");

 const int arraySize = 11;   
 long storeArray[arraySize];
 
 for (int i = 0; i<4; i++) {
   storeArray[i] = LED_state[i];  
 }
 storeArray[4] = energymicroWh;
 storeArray[5] = energyWh;
 storeArray[6] = energykWh;
 storeArray[7] = AUTO1; 
 storeArray[8] = AUTO2;
 storeArray[9] = SMSTimer;
 storeArray[10] = SMSTimerNow;
 SD.remove("SAVEFILE.txt");
 // Create new one
 schedFile = SD.open("savefile.txt", FILE_WRITE);
 // writing in the file works just like regular print()/println() function

for (int i=0; i<arraySize;i++){ 
 schedFile.print("[");
 schedFile.print(i);
 schedFile.print("=");
 schedFile.print(storeArray[i]);
 schedFile.print("]");
}

//debugging print written settings
//Serial.println("Writing done.");
//Serial.println("Values written to SD Card:");
//for (int i=0; i<arraySize;i++){ //load values into TIMETABLE entry column [mode][h][m][s][en]
// Serial.print(i);
// Serial.print(":");
// Serial.print(storeArray[i]);
// Serial.println("/");
//}


 schedFile.close();


}


//----------------------------------------
 
