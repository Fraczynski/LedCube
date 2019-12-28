String ReadIncomingRequest() {
  ClientRequest = (client.readStringUntil('\r'));
  if ((ClientRequest.indexOf("HTTP/1.1") > 0) && (ClientRequest.indexOf("/favicon.ico") < 0)) {
    //myresultat = ClientRequest;   //???
  }
  return ClientRequest;
}

void parseRequest() {
  if (request != NULL && request.length() > 0) {
    request.remove(0, 5);
    request.remove(request.length() - 9, 9);
    Serial.println("Incoming request: " + request);
    sendResponse("!!!" + request + "!!!");
    if(request.startsWith("time=")){
      request.remove(0, 5);
      timeScale = request.toDouble();
    }
    else{
      currentEffect = request; 
    }
   loading = true; 
  }
}

void sendResponse(String response) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println(response);
  client.stop();
  delay(1);
  client.flush();
}
