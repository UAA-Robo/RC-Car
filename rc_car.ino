#define LN1 25  // Pin
#define LN2 26  // Pin
#define LN3 32  // Pin
#define LN4 33  // Pin

#define PIN_ENA  12 // Pin for controlling speed
#define PIN_ENB  14 // Pin for controlling speed

#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "MyaESP";  // Enter SSID here
const char* password = "1234";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,2);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);


void setup() {
    pinMode(LN1, OUTPUT);
    pinMode(LN2, OUTPUT);
    pinMode(LN3, OUTPUT);
    pinMode(LN4, OUTPUT);
    pinMode(PIN_ENA, OUTPUT);
    pinMode(PIN_ENB, OUTPUT);

    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
    
    server.on("/", handle_OnConnect);
    server.on("/left", handle_left);
    server.on("/right", handle_right);
    server.on("/up", handle_up);
    server.on("/down", handle_down);
    server.on("/stop", handle_stop);
    server.onNotFound(handle_NotFound);
    Serial.println("Wifi has started");
    server.begin();

}
unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 1000; // Timeout in milliseconds (1 second)
void loop() {
    server.handleClient();
}


void handle_OnConnect() {
    server.send(200, "text/html", SendHTML()); 
}

void handle_down() {
    analogWrite(PIN_ENA, 255); // Full speed (255 max)
    digitalWrite(LN1,LOW);
    digitalWrite(LN2,HIGH);

    analogWrite(PIN_ENB, 255); // Full speed (255 max)
    digitalWrite(LN3,LOW);
    digitalWrite(LN4,HIGH);
    server.send(200, "application/json", "{}"); 
}

void handle_up() {
    analogWrite(PIN_ENA, 255); // Full speed (255 max)
    digitalWrite(LN1,HIGH);
    digitalWrite(LN2,LOW);
    
    analogWrite(PIN_ENB, 255); // Full speed (255 max)
    digitalWrite(LN3,HIGH);
    digitalWrite(LN4,LOW);
    server.send(200, "application/json", "{data:{turn:up}}"); 
}

void handle_right() {
    analogWrite(PIN_ENA, 220); // Lower speed (255 max)
    digitalWrite(LN1,HIGH);
    digitalWrite(LN2,LOW);

    analogWrite(PIN_ENB, 255); // Full speed (255 max)
    digitalWrite(LN3,HIGH);
    digitalWrite(LN4,LOW);
    server.send(200, "application/json", "{}"); 
}

void handle_left() {
    analogWrite(PIN_ENA, 255); // Full speed (255 max)
    digitalWrite(LN1,HIGH);
    digitalWrite(LN2,LOW);

    analogWrite(PIN_ENB, 220); // Lower speed (255 max)
    digitalWrite(LN3,HIGH);
    digitalWrite(LN4,LOW);
    server.send(200, "application/json", "{}"); 
}

void handle_stop(){
    digitalWrite(LN1, LOW);
    digitalWrite(LN2, LOW);
    digitalWrite(LN3, LOW);
    digitalWrite(LN4, LOW);
}

void handle_NotFound(){
    server.send(404, "text/plain", "Not found");
}

String SendHTML(){
String ptr = R"delimiter(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" charset="UTF-8">
    <title>Home</title>
    <style>
        .arrow-buttons {
            display: flex;
            flex-direction: column; /* Stack buttons vertically */

            align-items: center;
            gap: 10px; /* Spacing between buttons */
        }

        .arrow {
            background-color: blue;
            color: white;
            padding: 0px; /* Size of the buttons */
            min-width: 50px; /* Ensuring minimal width */
            font-size: 50px;
            text-align: center;
            font-weight: bold;
            transition: transform 0.1s;
            
            /* Prevent arrows from being selected on mobile */
            -webkit-touch-callout: none; /* iOS Safari */
            -webkit-user-select: none; /* Safari */
            -khtml-user-select: none; /* Konqueror HTML */
            -moz-user-select: none; /* Old versions of Firefox */
            -ms-user-select: none; /* Internet Explorer/Edge */
            user-select: none; /* Non-prefixed version, currently supported by Chrome, Edge, Opera and Firefox */

        }
        .arrow:active {
            transform: translateY(2px);
            
        }

        .middle-buttons {
            display: flex;
            gap: 30px;
        }

        .arrow-buttons button {
            border-radius: 20%;
        }

        .arrow-buttons .middle-buttons button {
            width: 150px !important;
        }

        .arrow-buttons > button {
            height: 150px !important;
        }

    </style>
</head>
<body>
    <div id="main">
        <div id="title-bar" class="title-bar"></div>
        <div id="content">
            <div class="arrow-buttons">
                <!-- Top button -->
                <button type="button" class="arrow" id="up">&#8593;</button>
                
                <!-- Middle buttons -->
                <div class="middle-buttons">
                    <button type="button" class="arrow" id="left">&#8592;</button>
                    <button type="button" class="arrow" id="right">&#8594;</button>
                </div>
                
                <!-- Bottom button -->
                <button type="button" class="arrow" id="down">&#8595;</button>
            </div>
        </div>
    </div>
    <script>
        let intervalId = null;
        let url = "192.168.1.2";
    
        function controlCar(direction) {
            // This function will be called repeatedly while the button is pressed
            fetch(`${direction}`)
            .then(function(response) {
                return response.text();
            })
        }
    
        function startControl(direction) {
            // Call controlCar initially
            controlCar(direction);
            // Set an interval to call it repeatedly every 100ms
            intervalId = setInterval(function() {
                controlCar(direction);
            }, 100);
        }
    
        function stopControl() {
            // Clear the interval to stop calling controlCar
            clearInterval(intervalId);

            // Several stops just in case
            fetch("\stop");
            fetch("\stop");
            fetch("\stop");
        }
    
        document.addEventListener("DOMContentLoaded", function() {
            document.getElementById('up').addEventListener('pointerdown', function() {
                startControl("up");
            });
            document.getElementById('up').addEventListener('pointerup', stopControl);
    
            // Do the same for the other buttons
            document.getElementById('down').addEventListener('pointerdown', function() {
                startControl("down");
            });
            document.getElementById('down').addEventListener('pointerup', stopControl);
    
            document.getElementById('left').addEventListener('pointerdown', function() {
                startControl("left");
            });
            document.getElementById('left').addEventListener('pointerup', stopControl);
    
            document.getElementById('right').addEventListener('pointerdown', function() {
                startControl("right");
            });
            document.getElementById('right').addEventListener('pointerup', stopControl);
        });
    </script>
</body>
</html>
)delimiter";
return ptr;
}
