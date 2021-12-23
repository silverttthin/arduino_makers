#define DHT11PIN 6 

dht11 DHT11;
LiquidCrystal lcd(44, 45, 46, 47, 48, 49);


float print_onsepdo()                  //온습도 출력함수
{
  float now_hum = (float)DHT11.humidity;
  temperature = (float)DHT11.temperature;
//  Serial.println("----온습도----");
  int chk = DHT11.read(DHT11PIN);                    
//  Serial.print("Humidity (%): ");                   // 'Humidity (%): '를 시리얼 통신으로 출력
//  Serial.println(now_hum, 2);         
//  Serial.print("Temperature (oC): ");               // 'Temperature (oC): '를 시리얼 통신으로 출력
//  Serial.println(temperature, 2);     
//  Serial.println("\n"); 

  return now_hum;
}




float print_dust(){                     //미세먼지 출력함수
  float dustDensity;
  Serial.println("----미세먼지 농도----");
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); 

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); 
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 17 * calcVoltage - 0.1;
  
//  if(dustDensity<16) Serial.println("GOOD"); 
//  else if(dustDensity>=16 && dustDensity<36) Serial.println("NORMAL");   
//  else if(dustDensity>=36 && dustDensity<76) Serial.println("BAD"); 
//  else if(dustDensity>76) Serial.println("WORST"); 

  return dustDensity;
}




void test_code(){                      // M-S 간 블루투스 통신 정상여부 확인용 테스트 코드.
  if(Serial1.available()) Serial.write(Serial1.read());
  
  if (Serial.available()) Serial1.write(Serial.read());
}

void over19(){                          //남은 물이 부족하면 경고음악 출력하는 코드.
  if(Serial1.available()){
    char R = Serial1.read();
    if(R == '1') 
      music();
}
}




void music(){              
  int melody[] = {
  NOTE_C5, NOTE_C5, NOTE_C5, 0};
  
  int noteDuration = 6; //6분음표 박자
  
for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
    // 음표 길이를 시간으로 변환
    int noteLength = 1000 / noteDuration;
    // 단음 재생
    tone(speakerPin, melody[thisNote], noteLength);
    delay(noteLength);
    noTone(speakerPin); // 현재 음 재생 중지
  }
}

//보건복지부 및 질병관리본부 피셜 적정 습도는 대게 40-70이 적정.

float sepdo_LCD(float now_hum, float dustDensity){ //희망습도, 추천습도, 적정습도 값 얻어내어 LCD에 출력하는 함수.
  lcd.clear();
  int vR_read = analogRead(vR); //가변저항으로 원하는 습도를 다이얼 돌리듯이 조절.
  float want_hum, recm_hum; 

  want_hum = map(vR_read, 0, 1023, 0, 100);
  recm_hum = 55;
  
  if(temperature <= 20) recm_hum += 5;
  else recm_hum -= 5;

  //하단은 LCD 출력 코드
  String temp = String(now_hum);
  lcd.setCursor(0,0);
  lcd.write("NH:");
  lcd.print(now_hum,1);
  lcd.setCursor(8,0);
  lcd.write("WH:");
  lcd.print(want_hum,1);

  lcd.setCursor(0,1);
  lcd.write("RH:");
  lcd.print(recm_hum,1);
  lcd.setCursor(8,1);
  lcd.write("DS:");
  if(dustDensity<16) lcd.print("GOOD"); 
  else if(dustDensity>=16 && dustDensity<36) lcd.print("SO SO");   
  else if(dustDensity>=36 && dustDensity<76) lcd.print("BAD"); 
  else if(dustDensity>76) lcd.print("WORST"); 

  return want_hum;
}

void send_1(float now_hum, float want_hum){
    if(now_hum >= want_hum){
      Serial.println("Sending 1");
      Serial1.write('1');  
      }
    else 
    {
      Serial.println("Sending 0");
      Serial1.write('0');
    }
}
