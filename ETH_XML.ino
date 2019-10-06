
void XML_response(EthernetClient cl)
{
  //called from ethernetMain() at ETH.ino
  
    int analog_val;            // stores value read from analog inputs
    int count;                 // used by 'for' loops
    int sw_arr[] = {2, 3, 4, 5};  // pins interfaced to switches
    
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");
    // read analog inputs
//    for (count = 0; count <= 5; count++) { // A0 to A5
//        analog_val = analogRead(count);
//        cl.print("<analog>");
//        cl.print(analog_val);
//        cl.println("</analog>");
//    }
//    // read switches
//    for (count = 0; count < 4; count++) {
//        cl.print("<switch>");
//        if (digitalRead(sw_arr[count])) {
//            cl.print("ON");
//        }
//        else {
//            cl.print("OFF");
//        }
//        cl.println("</switch>");
    //}
    
    
    // checkbox LED states
    // LED1
    cl.print("<LED>");
    if (CH1MANUAL) {
        cl.print("checked");
    }
    else {
        cl.print("unchecked");
    }
    cl.println("</LED>");
    // LED2
    cl.print("<LED>");
    if (CH2MANUAL) {
        cl.print("checked");
    }
    else {
        cl.print("unchecked");
    }
     cl.println("</LED>");
    // button LED states
    
    // RTC
    cl.print("<DateNow>");
    switch(currentTime[1]){
      case 1:
        cl.print("January ");
        break;
      case 2:
        cl.print("February ");
        break;
      case 3:
        cl.print("March ");
        break;
        case 4:
        cl.print("April ");
        break;
        case 5:
        cl.print("May ");
        break;
        case 6:
        cl.print("June ");
        break;
        case 7:
        cl.print("July ");
        break;
        case 8:
        cl.print("August ");
        break;
        case 9:
        cl.print("September ");
        break;
        case 10:
        cl.print("October ");
        break;
        case 11:
        cl.print("November ");
        break;
        case 12:
        cl.print("December ");
        break;
        
    }
    cl.print(currentTime[2]);
    
    cl.println("</DateNow>");
 
     // RTC
    cl.print("<TimeNow>");


        cl.print(currentTime[3]);
        cl.print("HH:");
        cl.print(currentTime[4]);
        cl.print("MM:");
        cl.print(currentTime[5]);
        cl.print("SS:");
  
       
    
    cl.println("</TimeNow>");   
    
    String lowLoad = "UNABLE TO READ AT LOW LOADS";
    cl.print("<POWER>");
    if(!fuseFlag){
      if(actualPower>26.0){  
        cl.print(actualPower);
        cl.print("W");
      }else{
        cl.print(lowLoad);
      }
    }
    else{
      cl.print("OVERLOAD");
    }
    
    cl.println("</POWER>"); 

    cl.print("<POWER>");
    if(!fuseFlag){
      if(actualPower2>26.0){  
        cl.print(actualPower2);
        cl.print("W");
      }else{
        cl.print(lowLoad);
      }
    }else{
    cl.print("OVERLOAD");
    }
    
    
    cl.println("</POWER>"); 

    cl.print("<POWER>");
    float totalPower = actualPower + actualPower2;;
    cl.print(totalPower);
    cl.print("W");
    cl.println("</POWER>"); 
    
    cl.print("<POWER>");
//    cl.print(energykWh);
//    cl.print("kWh ");
    cl.print(energyWh);
    cl.print("Wh");
    cl.println("</POWER>");
    
    cl.print("<SCHED>");
       for(int i =0; i<timeTableRows;i++){
         if(ch1[i][1] != 99 || ch1[i][2] != 99 ){
             cl.print("/");
             
             cl.print(ch1[i][1]);
             cl.print(":");
             cl.print(ch1[i][2]);
             
             if(ch1[i][0]){
               cl.print("-ON");
             }else{
               cl.print("-OFF");
             }
             
         }
       }
    cl.println("</SCHED>"); 
    
    cl.print("<SCHED>");
       for(int i =0; i<timeTableRows;i++){
         if(ch2[i][1] != 99 || ch2[i][2] != 99 ){
             cl.print("/");
             
             cl.print(ch2[i][1]);
             cl.print(":");
             cl.print(ch2[i][2]);
             
             if(ch2[i][0]){
               cl.print("-ON");
             }else{
               cl.print("-OFF");
             }
             
         }
       }
    cl.println("</SCHED>"); 
    
    cl.print("<MSG>");
      if(AUTO1){
        cl.print("ON");
      }else{
        cl.print("OFF");
      }
    cl.println("</MSG>");
    
    cl.print("<MSG>");
      if(AUTO2){
        cl.print("ON");
      }else{
        cl.print("OFF");
      }
    cl.println("</MSG>");
    
//    //HMLOADDATA
//if(HMDATAreq){    
//for(int i = 1;i<3;i++){
//  
//  for(int j = 0;j<10;j++){
//  int data = ch1[j][i];
//  cl.print( "<HOURMIN>");
//  cl.print(data);
//  Serial.print("o - Sent: ");
//  Serial.println(data);
//  cl.println("</HOURMIN>");
//  }
//}
//HMDATAreq = 0;
//Serial.println();
//Serial.println("debug - HM req catered.");
//}
//    
    //DEBUG
    cl.print("<DEBUG>");
      //led
      cl.print("LED:");
      for(int i = 0 ; i<4; i++){       
        cl.print("/");
        cl.print(LED_state[i]);
     }

       //auto1
       
       cl.print("  AUTO1:");
       cl.print(AUTO1); 

      //ch1row1
       
       cl.print("  CH1hr:");
       for(int i =0; i<timeTableRows;i++){
       cl.print("/");
       cl.print(ch1[i][1]);
       cl.print("/");
       cl.print(ch1[i][2]);
       }
       
//       
//       //ench1slots
//       cl.print("  CH1SLOTS: ");
//       for(int i =0; i<11;i++){
//       cl.print("/");
//       cl.print(ENCH1[i]);   }
//       
       //mode
 
       cl.print("  MODE1: ");
       for(int i =0; i<10;i++){
       cl.print("/");
       cl.print(MODE1[i]);   }

       cl.print("ch1AT/MA: ");
       cl.print(CH1AUTO);
       cl.print("/");
       cl.print(CH1MANUAL); 

//------------------------
       cl.print("  AUTO2:");
       cl.print(AUTO2); 

      //ch1row1
       
       cl.print("  CH2hr:");
       for(int i =0; i<timeTableRows;i++){
       cl.print("/");
       cl.print(ch2[i][1]);
       cl.print("/");
       cl.print(ch2[i][2]);
       cl.print("\n");
       }
       
      
       
       //mode
 
       cl.print("  MODE2: ");
       for(int i=0; i<10;i++){
       cl.print("/");
       cl.print(MODE2[i]);   }

       cl.print("ch1AT/MA: ");
       cl.print(CH2AUTO);
       cl.print("/");
       cl.print(CH2MANUAL);
//--------------------------
       cl.print("ADC0: ");
       cl.print(analogRead(0));
       cl.print("ADC1: ");
       cl.print(analogRead(1));
       
       cl.print("SMSTIMER: ");
       cl.print(SMSTimer);
       cl.print("SMSTIMERNOW: ");
       cl.print(SMSTimerNow);
       
       cl.print("eUWH: ");
       cl.print(energymicroWh);
              
       
    cl.println("</DEBUG>");
    
    
    //HMDATA
    cl.print(HMLoadStr);
    
    cl.print("</inputs>");
}


