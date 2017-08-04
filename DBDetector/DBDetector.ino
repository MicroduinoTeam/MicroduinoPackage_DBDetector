#include "userDef.h"
#include <U8glib.h> 
#include "oled.h"
#include <Microduino_Key.h>
#include <Microduino_ColorLED.h>

DigitalKey KeyButton(keyPin);

ColorLED strip = ColorLED(1, LEDPIN);

void setup() {
  Serial.begin(9600);
  pinMode(micPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  strip.begin();
  strip.show();
}

void loop() {
  
  double db=getDB();//获得分贝数
  analyticDB(db);//分析分贝
  speakerDoing(isAlaram);//蜂鸣器处理
  updateButton();//按键检测
  updateOLED();//刷新OLED
}

void updateOLED() {
  //OLED display
  if (OLEDShowTime > millis()) OLEDShowTime = millis();
  if(millis()-OLEDShowTime>INTERVAL_OLED) {
    OLEDShow(); //调用显示库
    OLEDShowTime = millis();
  } 
}


void buzzer() {
  if (millis() - timer > 10) {
    if (!add) {
      i++;
      if (i >= 800)
        add = true;
    } else {
      i--;
      if (i <= 200) {
        add = false;
      }
    }
    tone(buzzerPin, i);
    timer = millis();
  }
}


double getDB() {
  int voice_data = analogRead(micPin);
  voice_data=map(voice_data,0,1023,0,5);
  double db = (20. * log(10)) * (voice_data / 1.0);
  if(db>recodeDB) {
    recodeDB=db;
  }
  //Serial.println(db);
  return db;
}

void analyticDB(double db) {
  if(db > voice) {
    numNoise++;
    //Serial.println(numNoise);
  }
  if (analytic_time > millis()) analytic_time = millis();
  if (millis() - analytic_time > INTERVALOLED) {
    if(numNoise>maxNoise) {
        i = 200;
        isAlaram= true;
    }
//     Serial.print(numNoise);
//    Serial.print("\t");
//    Serial.println(maxNoise);
    numNoise=0;
    analytic_time = millis();
  }
}

void updateButton() {
    if(KeyButton.readEvent()==SHORT_PRESS) {
      delay(15);
      recodeDB=0;
      isAlaram = false;
    }
}

void speakerDoing(boolean isAlaram) {
  if (isAlaram) {
    buzzer();
    strip.setPixelColor(0, strip.Color(125, 125, 125));
    strip.show();
  } else {
    noTone(buzzerPin);
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
  }
}
