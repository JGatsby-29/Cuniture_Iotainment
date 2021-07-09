#include "config.h"
#include "Servo.h"

Servo servo_d;

// 피드 이름 설정
AdafruitIO_Feed *counter = io.feed("control");

// 핀 번호
// #책상#
// Motor_A1 // D1
// Motor_A2 // D2
// Motor_A_Ena // D3

// servo_d // D5

// trigPin_d // D6
// echoPin_d // D7

// LED // D9

void setup() {
  pinMode(D1, OUTPUT); 
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  servo_d.attach(D5); // 침대 서보
  
  pinMode(D6, OUTPUT);
  pinMode(D7, INPUT);

  pinMode(D9, OUTPUT);
  
  Serial.begin(115200);

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
  // ********여기부터
  ///// 어플 ## 블루투스 이용 했을 때
  if(Serial.available())
  {
    char ch = Serial.read(); // 그러면 읽어온 값을 ch에 받는다.
    Serial.println(ch); // 제대로 입력되는지 확인하기 위해 시리얼 모니터에 입력된 값 써준다.
    if(ch == 'a') // 책상 ## 모터 움직이고 책상 내려오기
    {
      // 초음파 거리 재고 
      while(1){
        float duration_d, distance_d;
        digitalWrite(D6, HIGH);
        delay(10);
        digitalWrite(D6, LOW);

        duration_d = pulseIn(D7, HIGH);
        distance_d = ((float)(340 * duration_d) / 10000) / 2;

        digitalWrite(D1, HIGH);     // Motor 방향설정1
        digitalWrite(D2, LOW);      // Motor 방향설정2
        digitalWrite(D3, HIGH);     // Motor On
        
        char ch = Serial.read(); // 그러면 읽어온 값을 ch에 받는다.
        if(ch == 'c') // 책상 ## 책상 정지
        {
          digitalWrite(D3, LOW);
          break;
        }
        if(distance_d < 12.5){ // 책상 센서 가까이 오면 멈추기
          digitalWrite(D3, LOW);
          break;
        }
      }
      delay(500);
      servo_d.writeMicroseconds(1000); // 서보모터 움직이기 책상 내려오기
      delay(500);
      digitalWrite(D9, HIGH); // LED ON
    }

    if(ch == 'b') // 책상 ## 책상 올라가고 모터 움직이기
    {
      digitalWrite(D9, LOW); // LED OFF
      delay(500);
      servo_d.writeMicroseconds(2000); // 서보모터 움직이기 책상 올라가기
      delay(500);
      while(1){
        float duration_d, distance_d;
        digitalWrite(D6, HIGH);
        delay(10);
        digitalWrite(D6, LOW);

        duration_d = pulseIn(D7, HIGH);
        distance_d = ((float)(340 * duration_d) / 10000) / 2;
        
        digitalWrite(D1, HIGH);     // Motor 방향설정1
        digitalWrite(D2, LOW);      // Motor 방향설정2
        digitalWrite(D3, HIGH);     // Motor On

        char ch = Serial.read(); // 그러면 읽어온 값을 ch에 받는다.
        if(ch == 'c') // 책상 ## 책상 정지
        {
          digitalWrite(D3, LOW);
          break;
        }
        if(distance_d >= 24){ // 책상 멀리 가면 멈추기
          digitalWrite(D3, LOW);
          break;
        }
      }
    }
    
    if(ch == 'c') // 책상 ## 책상 정지
    {
      digitalWrite(D3, LOW);
    }
  }
  // *******여기까지는 없어도 됨
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
  int state = data->toInt();
  
  ///// 구글 어시스턴트 ## 구글 어시스턴트 이용 했을 때
  if(state == 3){ // 책상 ## 책상 움직이고 침대 내려오기
    while(1){
      float duration_d, distance_d;
      digitalWrite(D6, HIGH);
      delay(10);
      digitalWrite(D6, LOW);

      duration_d = pulseIn(D7, HIGH);
      distance_d = ((float)(340 * duration_d) / 10000) / 2;

      digitalWrite(D1, HIGH);     // Motor 방향설정1
      digitalWrite(D2, LOW);      // Motor 방향설정2
      digitalWrite(D3, HIGH);     // Motor On
        
      if(distance_d < 12.5){ // 책상 센서 가까이 오면 멈추기
        digitalWrite(D3, LOW);
        break;
      }
    }
    delay(500);
    servo_d.writeMicroseconds(1000); // 서보모터 움직이기 침대 내려오기
    delay(500);
    digitalWrite(D9, HIGH); // LED ON
  }
  
  else if(state == 4){ // 책상 ## 책상 올라가고 모터 움직이기
    digitalWrite(D9, LOW); // LED OFF
    delay(500);
    servo_d.writeMicroseconds(2000); // 서보모터 움직이기 책상 올라가기
    delay(500);
    while(1){
      float duration_d, distance_d;
      digitalWrite(D6, HIGH);
      delay(10);
      digitalWrite(D6, LOW);

      duration_d = pulseIn(D7, HIGH);
      distance_d = ((float)(340 * duration_d) / 10000) / 2;
        
      digitalWrite(D1, HIGH);     // Motor 방향설정1
      digitalWrite(D2, LOW);      // Motor 방향설정2
      digitalWrite(D3, HIGH);     // Motor On

      if(distance_d >= 24){ // 책상 멀리 가면 멈추기
        digitalWrite(D3, LOW);
        break;
      }
    }
  }
} 
