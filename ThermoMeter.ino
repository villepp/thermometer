#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool sent70 = false, sent80 = false, sent90 = false, sent100 = false, sent110 = false, sent120 = false;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    lcd.setCursor(0, 1);
    lcd.print(temperatureC);
    lcd.print(" C    ");

    if (temperatureC > 70 && !sent70) {
      Serial.println("TempOver70");
      sent70 = true;
    } else if (temperatureC > 80 && !sent80) {
      Serial.println("TempOver80");
      sent80 = true;
    } else if (temperatureC > 90 && !sent90) {
      Serial.println("TempOver90");
      sent90 = true;
    } else if (temperatureC > 100 && !sent100) {
      Serial.println("TempOver100");
      sent100 = true;
    } else if (temperatureC > 110 && !sent110) {
      Serial.println("TempOver110");
      sent110 = true;
    } else if (temperatureC > 120 && !sent120) {
      Serial.println("TempOver120");
      sent120 = true;
    }

    if (temperatureC < 60) {
      sent70 = sent80 = sent90 = sent100 = sent110 = sent120 = false;
    }

  } else {
    lcd.setCursor(0, 1);
    lcd.print("Error       ");
  }

  delay(5000);
}
