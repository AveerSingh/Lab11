SYSTEM_MODE(MANUAL)
SYSTEM_THREAD(ENABLED)

#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

LIS3DH accelerometer;
Adafruit_SSD1306 display(128, 32, &Wire, -1);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
unsigned long lastPrintSample = 0;

void setup()
{
  Serial.begin(9600);

  delay(5000);
  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_100_HZ);

  bool setupSuccess = accelerometer.setup(config);
  Serial.printlnf("setupSuccess=%d", setupSuccess);

  display.begin();

  display.clearDisplay();
  display.display();

}

void loop()
{

 if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
		}
		else {
			Serial.println("no sample");
		}
	

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("X: ");
  display.println(sample.x);
  display.print("Y: ");
  display.println(sample.y);
  display.print("Z: ");
  display.println(sample.z);
  display.display();

  delay(100);
}
}
