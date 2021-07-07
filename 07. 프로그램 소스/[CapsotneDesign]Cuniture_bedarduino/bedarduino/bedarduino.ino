#include "config.h"
#include "Servo.h"
#include <SoftwareSerial.h>

Servo servo_b;

// 피드 이름 설정
AdafruitIO_Feed *counter = io.feed("control");

// 핀 번호
// #침대#
// Motor_A1 // D1
// Motor_A2 // D2
// Motor_A_Ena // D3

// servo_b // D5

// trigPin_b // D6
// echoPin_b // D7

SoftwareSerial BTSerial(D9, D10); // 블루투스 Tx, Rx // D9, D10


void setup() {
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  servo_b.attach(D5); // 침대 서보
  
  pinMode(D6, OUTPUT);
  pinMode(D7, INPUT);
  
  
  Serial.begin(115200);
  BTSerial.begin(9600);

  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  io.connect();

  counter->onMessage(handleMessage);

  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  counter->get();

  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
  ///// 어플 ## 블루투스 이용 했을 때
  if(BTSerial.available()) // 블루투스에서 입력된 값이 있다.
  {
    char ch = BTSerial.read(); // 그러면 읽어온 값을 ch에 받는다.
    Serial.println(ch); // 제대로 입력되는지 확인하기 위해 시리얼 모니터에 입력된 값 써준다.
    if(ch == 'a') // 침대 ## 모터 움직이고 침대 내려오기
    {
      // 초음파 거리 재기
      while(1){
        float duration_b, distance_b;
        digitalWrite(D6, HIGH);
        delay(10);
        digitalWrite(D6, LOW);

        duration_b = pulseIn(D7, HIGH);
        distance_b = ((float)(340 * duration_b) / 10000) / 2;

        digitalWrite(D1, HIGH);     // Motor 방향설정1
        digitalWrite(D2, LOW);      // Motor 방향설정2
        digitalWrite(D3, HIGH);     // Motor On
        
        if(distance_b < 25){ // 침대 센서 가까이 오면 멈추기
          digitalWrite(D3, LOW);
          break;
        }
      }
      delay(500);
      servo_b.writeMicroseconds(1000); // 서보모터 움직이기 침대 내려오기
    }

    if(ch == 'b') // 침대 ## 침대 올라가고 모터 움직이기
    {
      servo_b.writeMicroseconds(2000); // 서보모터 움직이기 침대 올라가기
      delay(500);
      while(1){
        float duration_b, distance_b;
        digitalWrite(D6, HIGH);
        delay(10);
        digitalWrite(D6, LOW);

        duration_b = pulseIn(D7, HIGH);
        distance_b = ((float)(340 * duration_b) / 10000) / 2;
        
        digitalWrite(D1, HIGH);     // Motor 방향설정1
        digitalWrite(D2, LOW);      // Motor 방향설정2
        digitalWrite(D3, HIGH);     // Motor On

        if(distance_b >= 37){ // 침대 멀리 가면 멈추기
          digitalWrite(D3, LOW);
          break;
        }
      }
    }
  }
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
  int state = data->toInt();
  
  ///// 구글 어시스턴트 ## 구글 어시스턴트 이용 했을 때
  if(state == 1){ // 침대 ## 모터 움직이고 침대 내려오기
    while(1){
      float duration_b, distance_b;
      digitalWrite(D6, HIGH);
      delay(10);
      digitalWrite(D6, LOW);

      duration_b = pulseIn(D7, HIGH);
      distance_b = ((float)(340 * duration_b) / 10000) / 2;

      digitalWrite(D1, HIGH);     // Motor 방향설정1
      digitalWrite(D2, LOW);      // Motor 방향설정2
      digitalWrite(D3, HIGH);     // Motor On
        
      if(distance_b < 25){ // 침대 센서 가까이 오면 멈추기
        digitalWrite(D3, LOW);
        break;
      }
    }
    delay(500);
    servo_b.writeMicroseconds(1000); // 서보모터 움직이기 침대 내려오기
  }
  
  else if(state == 2){ // 침대 ## 침대 올라가고 모터 움직이기
    servo_b.writeMicroseconds(2000); // 서보모터 움직이기 침대 올라가기
    delay(500);
    while(1){
      float duration_b, distance_b;
      digitalWrite(D6, HIGH);
      delay(10);
      digitalWrite(D6, LOW);

      duration_b = pulseIn(D7, HIGH);
      distance_b = ((float)(340 * duration_b) / 10000) / 2;
        
      digitalWrite(D1, HIGH);     // Motor 방향설정1
      digitalWrite(D2, LOW);      // Motor 방향설정2
      digitalWrite(D3, HIGH);     // Motor On

      if(distance_b >= 37){ // 침대 멀리 가면 멈추기
        digitalWrite(D3, LOW);
        break;
      }
    }
  }
}
