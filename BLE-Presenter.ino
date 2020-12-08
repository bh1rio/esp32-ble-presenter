#include <Arduino.h>
#include <Button2.h>
#include "SSD1306.h"
#include <BleKeyboard.h>
#include "esp_adc_cal.h"

#define ADC_PINS 35
int vref = 1100;

#define BUTTON_UP_PIN 32
#define BUTTON_DOWN_PIN 33
#define BUTTON_CENTER_PIN 39
#define BUTTON_LEFT_PIN 34
#define BUTTON_RIGHT_PIN 36
#define BUTTON_BATT_PIN 0

Button2 button_up = Button2(BUTTON_UP_PIN);
Button2 button_down = Button2(BUTTON_DOWN_PIN);
Button2 button_center = Button2(BUTTON_CENTER_PIN);
Button2 button_left = Button2(BUTTON_LEFT_PIN);
Button2 button_right = Button2(BUTTON_RIGHT_PIN);
Button2 button_batt = Button2(BUTTON_BATT_PIN);

#define SSD1306_ADDRESS 0x3c
#define I2C_SDA 21
#define I2C_SCL 22
SSD1306 oled(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);

BleKeyboard bleKeyboard("BLE Presenter", "BH1RIO", 100);

void button_up_click(Button2& btn)
{
  Serial.println("Button Up Clicked!");

  oled.clear();
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Up");
  oled.display();

  if(bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_UP_ARROW);
    delay(100);
    bleKeyboard.releaseAll();
    
  }
}

void button_down_click(Button2& btn)
{
  Serial.println("Button Down Clicked!");
  oled.clear();
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Down");
  oled.display();

  if(bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_DOWN_ARROW);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void button_center_click(Button2& btn)
{
  Serial.println("Button Center Clicked!");
  oled.clear();
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Center");
  oled.display();

  if(bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void button_left_click(Button2& btn)
{
  Serial.println("Button Left Clicked!");
  oled.clear();
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Left");
  oled.display();

  if(bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_LEFT_ARROW);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void button_right_click(Button2& btn)
{
  Serial.println("Button Right Clicked!");
  oled.clear();
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Right");
  oled.display();

  if(bleKeyboard.isConnected()) {
    bleKeyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

void button_batt_click(Button2& btn)
{
  uint16_t v = analogRead(ADC_PINS);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);

  String voltage = "Voltage :" + String(battery_voltage) + "V";
  oled.clear();
  if(battery_voltage> 2.9)
  {
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, voltage);
  }
  else
  {
    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Low Power!!!");
  }
  oled.display();
}

void batt_level()
{
  uint16_t v = analogRead(ADC_PINS);
  float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  int battery_level=floor(((4.25-v)/1.5)*100); 
  bleKeyboard.setBatteryLevel(battery_level);
}

void setup()
{
  Serial.begin(115200);

  button_up.setPressedHandler(button_up_click);
  button_down.setPressedHandler(button_down_click);
  button_center.setPressedHandler(button_center_click);
  button_left.setPressedHandler(button_left_click);
  button_right.setPressedHandler(button_right_click);
  button_batt.setPressedHandler(button_batt_click);

  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  oled.init();
  oled.flipScreenVertically();
  oled.setFont(ArialMT_Plain_16);
  oled.setTextAlignment(TEXT_ALIGN_CENTER);
  delay(50);
  oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Ready!");
  oled.display();
}

void loop()
{
    button_up.loop();
    button_down.loop();
    button_center.loop();
    button_left.loop();
    button_right.loop();
    button_batt.loop();
}
