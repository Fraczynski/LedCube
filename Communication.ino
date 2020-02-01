String ReadIncomingRequest() {
  ClientRequest = (client.readStringUntil('\r'));
  return ClientRequest;
}

void parseRequest() {
  if (request != NULL && request.length() > 0) {
    request.remove(0, 5);
    request.remove(request.length() - 9, 9);
    Serial.println("Incoming request: " + request);
    sendResponse(request);
    if(request.startsWith("time=")){
      request.remove(0, 5);
      timeScale = 4 - request.toDouble();
      currentEffectTime = currentEffectOriginalTime * timeScale;
    }
    else if(request.startsWith("text=")){
      request.remove(0, 5);
      textToDisplay= String(request);
      textToDisplay.replace("%20", " ");
      loading = true; 
      timeScale = 1;
    }
    else{
      currentEffect = request;
      loading = true;  
      timeScale = 1;
    }
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
