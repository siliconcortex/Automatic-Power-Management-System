
void ethernetInit() {
    // called from loop()

    if (!SD.begin(sdcard)) {
        Serial.println("SDCARD FAILED");
        return;    // init failed
    }
    
    // check for index.txt file (homepage)
    if (!SD.exists("index.txt")) {
        Serial.println("MISSING index.txt");
        shutDown(); // can't find index file
    }
    
}


void ethernetMain(){
 //called from loop()
 
// int imageSend;
 EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // limit the size of the stored received HTTP request
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    //image request


                        if (StrContains(HTTP_req, "GET /favicon.ico")) {                        
                        sendElement(client,0,128); //to ETH_SEL.ino
                        }
                        if (StrContains(HTTP_req, "GET /banner.png")) {                        
                        sendElement(client,1,128); //to ETH_SEL.ino
                        }

                        if (StrContains(HTTP_req, "GET /bgimg.jpg")) {                        
                        sendElement(client,6,128); //to ETH_SEL.ino
                        }
                        
                        if (StrContains(HTTP_req, "GET /time.png")) {                        
                        sendElement(client,7,256); //to ETH_SEL.ino
                        }
                        
                        if (StrContains(HTTP_req, "GET /date.png")) {                        
                        sendElement(client,8,256); //to ETH_SEL.ino
                        }
                        
                        if (StrContains(HTTP_req, "GET /log.txt")) {                        
                        sendElement(client,9,32); //to ETH_SEL.ino
                        }
                        


                    // Ajax request - send XML file                   
                    if (StrContains(HTTP_req, "ajax_inputs")) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                        //Retrieve LED(relay) values
                        ReceiveHTTP(); //to ETH.ino
                        ReceiveHTTP2(); //to ETH.ino
                        // send XML file containing input states and RTC
                        XML_response(client); //to ETH_XML.ino
                        
                    }else{
                    sendElement(client,3,128); //to ETH_SEL.ino
                    }
                    // display received HTTP request on serial port
                    Serial.println("-------------------");
                    Serial.println(HTTP_req);
                    Serial.println("-------------------");
                    
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ); //to math_etc.ino
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    }else{
    Ethernet.begin(mac, ip);  // initialize Ethernet module
    server.begin();           // start to listen for clients
    } // end if (client)
}//end func


void ReceiveHTTP(void){
  //called from ethernetMain() at ETH.ino
  
    // Relay 1 (pin 6)
    if (StrContains(HTTP_req, "LED1=1")) {
        CH1MANUAL = 1;  // save LED state
        ethernetManualFlag = 1;
        //digitalWrite(6, HIGH);
    }
    else if (StrContains(HTTP_req, "LED1=0")) {
        CH1MANUAL = 0;  // save LED state
        ethernetManualFlag = 1;
        //digitalWrite(6, LOW);
    }
    // Relay 2 (pin 7)
    if (StrContains(HTTP_req, "LED2=1")) {
        CH2MANUAL = 1;  // save LED state
        ethernetManualFlag2 = 1;
        //digitalWrite(7, HIGH);
    }
    else if (StrContains(HTTP_req, "LED2=0")) {
        CH2MANUAL = 0;  // save LED state
        ethernetManualFlag2 = 1;
        //digitalWrite(7, LOW);
    }
    
        // AUTO 1
    if (StrContains(HTTP_req, "AUTO1=1")) {
        if(AUTO1){ 
          AUTO1= 0;
        }else{
          AUTO1= 1;
        }  // save LED state
        
    }
    

    
    //HOURMINUtedata
    if (StrContains(HTTP_req, "HM=")) {
    getHM(); //to ETH_HM.ino
    //transferToScheduler(); //to SCHD.ino
    sortSchedule();        //to SCHD.ino 
    
     }
     
    if (StrContains(HTTP_req, "HM2=")) {
    getHM2(); //to ETH_HM.ino
    //transferToScheduler(); //to SCHD.ino
    sortSchedule();        //to SCHD.ino 
    
     }
     
    if (StrContains(HTTP_req, "SMSTEST=1")) {
    SMSE(); //to CPU3.ino
    
    
     }
     
    if (StrContains(HTTP_req, "SMSFREQ=")) {
    getFreq(); //to CPU3.ino
    
    
     }
//     
     //HMLOAD
//    if (StrContains(HTTP_req, "LOADHM")) {
//    HMDATAreq = 1;
//    Serial.println("HM req received.");
//    }     
//     
     
}
   




