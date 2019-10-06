

void sendElement(EthernetClient client,int element,int chunkSize ){
  //called from ethernetMain at ETH.ino
  
Serial.println("SENDING element");  
            
            switch(element){
            
              case 0:
              webFile = SD.open("favicon.ico");
              break;
              
              case 1:
              webFile = SD.open("banner.png");
              break;
              
              
              case 3:
              webFile = SD.open("index.txt");
              break;

              case 6:
              webFile = SD.open("bgimg.jpg");
              break;
              
              case 7:
              webFile = SD.open("time.png");
              break;
              
              case 8:
              webFile = SD.open("date.png");
              break;
              
              case 9:
              webFile = SD.open("log.txt");
              break;
            }
  
            delay(1);
            if (webFile) {
              client.println();
              byte clientBuf[chunkSize];
              int clientCount = 0;
              while(webFile.available())
              {
                clientBuf[clientCount] = webFile.read();
                clientCount++;
                if(clientCount > chunkSize-1)
                {
                  // Serial.println("Packet");
                  client.write(clientBuf,chunkSize);
                  clientCount = 0;
                }
              }
              //final <64 byte cleanup packet
              if(clientCount > 0) {
                client.write(clientBuf,clientCount);            
              // close the file:
              webFile.close();

              }
            delay(1);
}
}

