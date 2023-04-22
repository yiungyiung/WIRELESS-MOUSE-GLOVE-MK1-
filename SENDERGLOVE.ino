
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

Adafruit_MPU6050 mpu;
float RADIANS_TO_DEGREES = 180/3.14159;

int digitalPin = 13;
int lmbpin=15;
int rmbpin=14;
const char *ssid = "Alexahome";
const char *password = "loranthus";
void setup(void) {
  pinMode(digitalPin, INPUT_PULLUP);
  pinMode(lmbpin, INPUT);
  pinMode(rmbpin, INPUT);
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    //Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  //Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  mpu.setGyroRange(MPU6050_RANGE_250_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if(!digitalRead(digitalPin)){
  Serial.print((g.gyro.x));
  Serial.print(',');
  Serial.print((g.gyro.z));
  Serial.print(',');
  Serial.print(digitalRead(lmbpin));
  Serial.println(',');
 float x,y;
  x=g.gyro.x;
  y=g.gyro.z;
  String s;
    s=String(x)+","+String(y)+","+String(digitalRead(lmbpin))+","+String(digitalRead(rmbpin))+",";
   WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;
 
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  // We now create a URI for the request
  String url = "/data/";
  url += "?sensor_reading=";
  url += s;
 

 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    } 
}
  }
  /*float accel_angle_x = atan(a.acceleration.y/sqrt(pow(a.acceleration.x,2) + pow(a.acceleration.z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_y = atan(-1*a.acceleration.x/sqrt(pow(a.acceleration.y,2) + pow(a.acceleration.z,2)))*RADIANS_TO_DEGREES;
  float x=0.96*g.gyro.x+(0.04)*accel_angle_x;
  float y=0.96*g.gyro.y+(0.04)*accel_angle_y;
  Serial.print(x);
  Serial.print(",");
  Serial.print(g.gyro.z);
  Serial.println(',');*/
  delay(100);
}
