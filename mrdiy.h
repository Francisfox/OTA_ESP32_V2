/*  ============================================================================================================

    Sample code for create a websocket on an ESP8266 board.

    For more info, please watch my video at https://youtu.be/fREqfdCphRA
    MrDIY.ca

  ============================================================================================================== */

#ifndef _MRDIYH_
#define _MRDIYH_
#include <WebSocketsServer.h>                         //incluindo a class WebSocketsServer 

WebSocketsServer webSocket = WebSocketsServer(81);

char html_template[] PROGMEM = R"=====(
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>MrDIY Socket Example</title>
      <script>
        socket = new WebSocket("ws:/" + "/" + location.host + ":81");
        socket.onmessage = function(e) {  
            document.getElementById("mrdiy_value").innerHTML = e.data;
        };
      </script>
   </head>
   <body style="max-width:400px;margin: auto;font-family:Arial, Helvetica, sans-serif;text-align:center">
      <div><h1><br />My Value</h1></div>
      <div><p id="mrdiy_value" style="font-size:100px;margin:0"></p></div>
   </body>
</html>
)=====";

void handleMain() {
  server.send_P(200, "text/html", html_template ); 
}
void Evento_server_mrdiy(){                                     //evento para enviar para a pagina
  String JSONtxt2; 
  unsigned long int contador = millis();
  JSONtxt2 = String(contador);
  webSocket.broadcastTXT(JSONtxt2);
}
#endif
