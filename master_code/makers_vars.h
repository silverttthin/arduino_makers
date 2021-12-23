//함수 프로토타입 선언
float print_onsepdo();
float print_dust();
void music();
void test_code();
void over19();
float sepdo_LCD(float now_hum, float dustDensity);
void send_1(float now_hum, float want_hum);
//---------------------------------------------------------------

//전역변수 선언
int vR = A2;       //희망습도 조절용 가변저항 다이얼
int speakerPin = 10;
int measurePin = A0;
int ledPower = 8;  

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;

float temperature; //현재 기온.

//-----------------------------------------------------------------
