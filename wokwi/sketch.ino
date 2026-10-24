// ESP32 AUTONOMOUS ENVIRONMENTAL MONITORING SYSTEM
// ESP32 Autonomous Environmental Monitoring System
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>

#define TRIG_PIN   5
#define ECHO_PIN   18
#define BUZZER_PIN 4
#define LED_PIN    2
#define DHT_PIN    15
#define PIR_PIN    27
#define SDA_PIN    21
#define SCL_PIN    22

#define TEMP_MAX       35.0
#define HUM_MAX        80.0
#define DIST_MIN       30.0
#define VIBRATION_MAX  3.0

#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_MPU6050 mpu;

float temperature = 0, humidity = 0, distance = 0, vibration = 0;
bool motion = false;
bool mpuOk = false;

unsigned long lastDHT = 0, lastSensors = 0, lastBlink = 0;
bool ledState = false;

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2;
}

void readMPU() {
  if (!mpuOk) return;
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  float mag = sqrt(a.acceleration.x * a.acceleration.x +
                   a.acceleration.y * a.acceleration.y +
                   a.acceleration.z * a.acceleration.z);
  vibration = fabs(mag - 9.81);
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Environmental");
  display.println("Monitoring System");
  display.println("Starting...");
  display.display();

  mpuOk = mpu.begin(0x68);
  if (!mpuOk) Serial.println("MPU6050 not found");

  delay(1500);
}

void loop() {
  unsigned long now = millis();

  if (now - lastDHT >= 2000) {
    lastDHT = now;
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (!isnan(t)) temperature = t;
    if (!isnan(h)) humidity = h;
  }

  if (now - lastSensors >= 200) {
    lastSensors = now;
    distance = readDistance();
    motion = digitalRead(PIR_PIN) == HIGH;
    readMPU();
  }

  bool tempAlarm = temperature > TEMP_MAX;
  bool humAlarm  = humidity > HUM_MAX;
  bool distAlarm = (distance > 0 && distance < DIST_MIN);
  bool vibAlarm  = vibration > VIBRATION_MAX;
  bool anyAlarm  = tempAlarm || humAlarm || distAlarm || motion || vibAlarm;

  if (anyAlarm) {
    if (now - lastBlink >= 250) {
      lastBlink = now;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
    tone(BUZZER_PIN, distAlarm ? 2000 : 1000);
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
    ledState = false;
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("T:");  display.print(temperature, 1);
  display.print("C H:"); display.print(humidity, 0); display.println("%");
  display.print("Dist: ");
  if (distance < 0) display.println("--");
  else { display.print(distance, 0); display.println(" cm"); }
  display.print("Motion: "); display.println(motion ? "YES" : "no");
  display.print("Vib: "); display.println(vibration, 1);
  display.println("-------------------");
  display.print("Status: "); display.println(anyAlarm ? "ALERT!" : "OK");
  display.display();

  Serial.printf("T=%.1fC H=%.0f%% Dist=%.0fcm Motion=%d Vib=%.1f %s\n",
                temperature, humidity, distance, motion, vibration,
                anyAlarm ? "[ALERT]" : "[OK]");

  delay(100);
}
