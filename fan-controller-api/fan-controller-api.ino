// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid     = "<ssid>";
const char* password = "<ssid-passphrase>";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Light
const int light = 16;
// Fan Low
const int low = 5;
// Fan Medium
const int med = 4;
// Fan High
const int high = 0;
// Fan Off
const int foff = 2;

// Remote DIP Switches
const int f4 = 14;
const int f3 = 12;
const int f2 = 13;
const int f1 = 15;

// Button Press Time
const int buttonTime = 300;

void setup() {
  // Baud rate
  Serial.begin(115200);
  delay(100);

  // Set outputs to be used for Fan and light controls
  pinMode(light, OUTPUT);
  digitalWrite(light, LOW);
  pinMode(low, OUTPUT);
  digitalWrite(low, LOW);
  pinMode(med, OUTPUT);
  digitalWrite(med, LOW);
  pinMode(high, OUTPUT);
  digitalWrite(high, LOW);

  pinMode(foff, OUTPUT);
  digitalWrite(foff, LOW);
  
  // Fan Selectors
  pinMode(f4, OUTPUT);
  digitalWrite(f4, LOW);
  pinMode(f3, OUTPUT);
  digitalWrite(f3, LOW);
  pinMode(f2, OUTPUT);
  digitalWrite(f2, LOW);
  pinMode(f1, OUTPUT);
  digitalWrite(f1, LOW);
  delay(300);      

  // Function to be exposed
  rest.function("office",office);
  rest.function("livingroom",livingRoom);
  rest.function("familyroom",familyRoom);
  rest.function("masterbedroom",masterBedroom);
  rest.function("guestbedroom",guestBedroom);
  rest.function("sparebedroom",spareBedroom);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("6");
  rest.set_name("hbfans");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  Serial.print("Board Initialized and Reset.\n");
    
}

// Main Program
void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}


// Custom function accessible by the API
int fanOption(String command) {

  // Get state from command
  int state = command.toInt();
  Serial.println(state);
  if (state == 0) {
    digitalWrite(light, HIGH);
    delay(buttonTime);
    digitalWrite(light, LOW);
  }
  if (state == 1) {
    digitalWrite(low, HIGH);
    delay(buttonTime);
    digitalWrite(low, LOW);
  }
  if (state == 2) {
    digitalWrite(med, HIGH);
    delay(buttonTime);
    digitalWrite(med, LOW);
  }
  if (state == 3) {
    digitalWrite(high, HIGH);
    delay(buttonTime);
    digitalWrite(high, LOW);
  }
  if (state == 4) {
    digitalWrite(foff, HIGH);
    delay(buttonTime);
    digitalWrite(foff, LOW);
  }
  return state;
}

int office(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(f1, HIGH);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f1, LOW);
  delay(buttonTime);
  return 1;
}

int livingRoom(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(f1, LOW);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f2, LOW);
  delay(buttonTime);
  return 1;
}

int familyRoom(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, HIGH);
  digitalWrite(f2, LOW);
  digitalWrite(f1, LOW);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f3, LOW);
  delay(buttonTime);
  return 1;
}

int masterBedroom(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(f1, HIGH);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f2, LOW);
  digitalWrite(f1, LOW);
  delay(buttonTime);
  return 1;
}

int guestBedroom(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, HIGH);
  digitalWrite(f2, LOW);
  digitalWrite(f1, HIGH);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f3, LOW);
  digitalWrite(f1, LOW);
  delay(buttonTime);
  return 1;
}

int spareBedroom(String command){
  // Fan Selectors
  digitalWrite(f4, LOW);
  digitalWrite(f3, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(f1, LOW);

  delay(buttonTime);
  fanOption(command);
  delay(buttonTime);

  digitalWrite(f3, LOW);
  digitalWrite(f2, LOW);
  delay(buttonTime);
  return 1;
}

