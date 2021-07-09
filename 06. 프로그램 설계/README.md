## 프로그램 설계

![설계 1](https://user-images.githubusercontent.com/75825682/124733559-451ef800-df4f-11eb-9887-d73cff723ef5.png)

구글 어시스턴트를 활용하여 명령어 호출 시 
아두이노(마이크로 컨트롤러, 정해진 기능을 수행하는 컴퓨터)를 작동시키고자 함

![설계 2](https://user-images.githubusercontent.com/75825682/124733701-68e23e00-df4f-11eb-8b6a-6f71f73b7c9d.png)

두 기기 간에 데이터 통신을 하기 위해서는 프로토콜이 필요
굉장히 적은 데이터로도 통신할 수 있어 사물인터넷에 최적화된 MQTT 프로토콜을 사용
(해당 플랫폼으로써 adafruit를 선택)

![설계 3](https://user-images.githubusercontent.com/75825682/124733716-6bdd2e80-df4f-11eb-90b1-4c0f5d2d0f9e.png)

구글 어시스턴트와 adafruit를 연결하기 위해 
IFTTT 사용(타 소프트웨어를 관리할 수 있도록 도와주는 프로그램)

![설계 4](https://user-images.githubusercontent.com/75825682/124733721-6da6f200-df4f-11eb-9f02-d9d2ff12d602.png)

① 구글 어시스턴트를 통해 명령어 호출   
② IFTTT로 명령어에 해당하는 특정 데이터를 adafruit에 전송   
③ 다시 한 번 adafruit가 특정 데이터를 아두이노로 전송   
④ 아두이노에 전송된 값에 따라 해당 모드 실행
