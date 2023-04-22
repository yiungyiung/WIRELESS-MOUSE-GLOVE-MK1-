
#include <ESP8266WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
const char *ssid = "Alexahome";
const char *password = "loranthus";
float x,y;
int JoyStick_button = 12; 
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  pinMode(JoyStick_button, INPUT_PULLUP);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

    Serial.print("Connecting to ");
  Serial.println(ssid);
 
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


  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int button;

  button = digitalRead(JoyStick_button);

  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  /*
   *   float accel_angle_x = atan(a.acceleration.y/sqrt(pow(a.acceleration.x,2) + pow(a.acceleration.z,2)))*RADIANS_TO_DEGREES;
  float accel_angle_y = atan(-1*a.acceleration.x/sqrt(pow(a.acceleration.y,2) + pow(a.acceleration.z,2)))*RADIANS_TO_DEGREES;
  float x=0.96*g.gyro.x+(0.04)*accel_angle_x;
  float y=0.96*g.gyro.y+(0.04)*accel_angle_y;
   */
  x=(a.acceleration.x +1.2);
  y=(a.acceleration.y -7.3);
  Serial.println(button);
  Serial.println("");
  
  String s;
  s=String(x)+","+String(y)+","+String(button);
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
