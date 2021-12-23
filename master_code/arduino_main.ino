#include <LiquidCrystal.h>
#include <dht11.h>      
#include  <pitches.h>  
#include "makers_vars.h"     
#include "makers_func.h" 
                       
#define DHT11PIN 6

/*핀 정리
온습도 핀 = 6번
미세먼지 LED핀 2번, OUT핀 A0
스피커핀 10번
가변저항핀 A2
*/

void setup()
{
  Serial1.begin(38400);
  Serial.begin(38400);   
  pinMode(ledPower, OUTPUT);
  pinMode(vR, INPUT);
  lcd.begin(16, 2); // LCD 초기화
}

void loop() 
{ 
  float dustDensity = print_dust(); //미세먼지 농도
  
  float now_hum = print_onsepdo(); // 현재습도 
  
  over19(); //수위 미달 시 경고음악 출력

  float want_hum = sepdo_LCD(now_hum, dustDensity); // 관련 습도 데이터들을 LCD모니터에 출력

  send_1(now_hum, want_hum); //희망습도와 현재습도 비교
  
  delay(500);
//    test_code();
}
