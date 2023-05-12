// Simple Node MCU as a webserver :---

#include<ESP8266WiFi.h>
WiFi.client;
WiFiServer server(80);

int led1 = 14 ; // 14 number is equivlent to "D5" pin of Node_mcu
int led2 = 12 ; // 12 number is equivlent to "D6" pin of Node_mcu

void setup() {
  pinMode(led1 , OUTPUT);
  pinMode(led2 , OUTPUT);
  Serial.begin(9600);
  WiFi.begin("AtoZ","8918172922"); // Bracket ke andar ka pehle wala string hai usme "wifa ka naam" likha hai aur dusre string me "wifi ka password" likha hai.
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting....."); //Ye connecting dikhayega jab esp8266 hamare device se connect horaha hoga tab.
    delay(200);
  }
  server.begin();
  Serial.println("NodeMcu is connected!"); // jab node mcu hamare diye gaye wifi se connect hojaega to "NodeMcu is connected!" likhayega.
  Serial.println(WiFi.localIP());  // "WiFi.localIP()" it is used to know the ip adres of the connected device.
}

void loop() {
  client = server.available();
  if(client == 1 ){
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    
    if(request == "GET /light1on HTTP/1.1"){
      digitalWrite(led1 , HIGH);
    }
    if(request == "GET /light1off HTTP/1.1"){
      digitalWrite(led1 , LOW);
    }

    if(request == "GET /light2on HTTP/1.1"){
      digitalWrite(led2 , HIGH);
    }
    if(request == "GET /light2off HTTP/1.1"){
      digitalWrite(led2 , LOW);
    }
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<!DOCTYPE html>");
  client.println("<html lang="en">");
  client.println("<head>");
  client.println("<meta charset="UTF-8">");
  client.println("<meta http-equiv="X-UA-Compatible" content="IE=edge">");
  client.println("<meta name="viewport" content="width=device-width, initial-scale=1.0">");
  client.println("<title> Home automation using webpage </title>");
  client.println("<style>");
  client.println("button{");
  client.println("border: 2px solid pink;");
  client.println("border-radius: 30px;");
  client.println("width: 150px;");
  client.println("height: 60px;");
  client.println("font-size: 20px;");
  client.println("background-color: #d1ab40;");
  client.println("font-weight: 900;");
  client.println("margin-left: 10px;");
  client.println("}");
  client.println("button:hover{");
  client.println("border-color: black;");
  client.println("}");
  client.println("h1{");
  client.println("color: chocolate;");
  client.println("font-size: 45px;");
  client.println("font-weight: 900;");
  client.println("}");

  client.println("h1:hover{");
  client.println("text-decoration: underline ;");
  client.println("}");

  client.println("div{");
  client.println("margin: 15px;");
  client.println("}");

  client.println("*{");
  client.println("font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;");
  client.println("}");

  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1> Welcome to IOT project : </h1>");
  client.println("<div>");
  client.println("<a href=\"/light1on\"\"><button> light1on </button></a>");
  client.println("<a href=\"/light1off\"\"><button> light1off </button></a>");
  client.println("</div>");

  client.println("<div>");
  client.println("<a href=\"/light2on\"\"><button> light2on </button></a>");
  client.println("<a href=\"/light2off\"\"><button> light2off </button></a>");
  client.println("</div>");

  client.println("</body>");
  client.println("</html>");

}
