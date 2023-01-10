//=========================================
//HTML + CSS + JavaScript codes for webpage
//=========================================
#ifndef _MY_OTA_
#define _MY_OTA_

WebServer server(80);
#include <Update.h>
/*
 * Server Index Page
 */
static const char serverIndex[] PROGMEM =
  R"=====(
<html>
  <head>
      <meta charset="utf-8">
      <title>OTAWebServer</title>

      <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
  </head>
  <body>
    <form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
      <input type='file' name='update'>
      <input type='submit' value='Update'>
    </form>
    <div id='prg'>progress: 0%</div>
    <script>
    $('form').submit(function(e){
      e.preventDefault();
      var form = $('#upload_form')[0];
      var data = new FormData(form);
      $.ajax({
      url: '/update',
      type: 'POST',
      data: data,
      contentType: false,
      processData:false,
      xhr: function() {
      var xhr = new window.XMLHttpRequest();
      xhr.upload.addEventListener('progress', function(evt) {
      if (evt.lengthComputable) {
      var per = evt.loaded / evt.total;
      $('#prg').html('progress: ' + Math.round(per*100) + '%');
      }
      }, false);
      return xhr;
      },
      success:function(d, s) {
      console.log('success!')
     },
     error: function (a, b, c) {
     }
     });
     });
   </script>
 </body>
</html>
)=====";
void My_updade_OTA(){
  /*return index page which is stored in serverIndex */
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
        } else {
          Update.printError(Serial);
        }
      }
    });  
}
#endif
