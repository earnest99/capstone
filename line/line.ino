#include <Servo.h> //모터제어 라이브러리 추가
Servo servo;

const int servoPin = 2; //모터핀
const int leftSensorPin = A0;   //적외선 센서 핀
const int middleSensorPin = A1;
const int rightSensorPin = A2;

const int wheel_1_1 = 23;    //메카넘휠 핀
const int wheel_1_2 = 22;
const int wheel_2_1 = 24;
const int wheel_2_2 = 25;
const int wheel_3_1 = 26;
const int wheel_3_2 = 27;
const int wheel_4_1 = 29;
const int wheel_4_2 = 28;
const int threshold = 500;    //센서 임계값   이거보다 작으면 검정색 감지
int count = 0;
//////////////////////////////////////////////////////////////////
void setup() {  //셋업
    servo.attach(servoPin); //모터
    pinMode(leftSensorPin, INPUT);     //적외선
    pinMode(middleSensorPin, INPUT);
    pinMode(rightSensorPin, INPUT);

    pinMode(wheel_1_1, OUTPUT);  //메카넘휠
    pinMode(wheel_1_2, OUTPUT);
    pinMode(wheel_2_1, OUTPUT);
    pinMode(wheel_2_2, OUTPUT);
    pinMode(wheel_3_1, OUTPUT);
    pinMode(wheel_3_2, OUTPUT);
    pinMode(wheel_4_1, OUTPUT);
    pinMode(wheel_4_2, OUTPUT);
    Serial.begin(9600);  //시리얼통신
}
/////////////////////////////////////////////////////////////////
void moveLeft() {   //좌회전
    digitalWrite(wheel_1_1, HIGH);
    digitalWrite(wheel_1_2, LOW);
    digitalWrite(wheel_2_1, LOW);
    digitalWrite(wheel_2_2, HIGH);
    digitalWrite(wheel_3_1, LOW);
    digitalWrite(wheel_3_2, HIGH);
    digitalWrite(wheel_4_1, HIGH);
    digitalWrite(wheel_4_2, LOW);
}

void moveRight() {   //우회전
    digitalWrite(wheel_1_1, LOW);
    digitalWrite(wheel_1_2, HIGH);
    digitalWrite(wheel_2_1, HIGH);
    digitalWrite(wheel_2_2, LOW);
    digitalWrite(wheel_3_1, HIGH);
    digitalWrite(wheel_3_2, LOW);
    digitalWrite(wheel_4_1, LOW);
    digitalWrite(wheel_4_2, HIGH);
}

void moveForward() { //전진
    digitalWrite(wheel_1_1, HIGH);
    digitalWrite(wheel_1_2, LOW);
    digitalWrite(wheel_2_1, HIGH);
    digitalWrite(wheel_2_2, LOW);
    digitalWrite(wheel_3_1, HIGH);
    digitalWrite(wheel_3_2, LOW);
    digitalWrite(wheel_4_1, HIGH);
    digitalWrite(wheel_4_2, LOW);
}

void stopMotors() {  //정지
    digitalWrite(wheel_1_1, LOW);
    digitalWrite(wheel_1_2, LOW);
    digitalWrite(wheel_2_1, LOW);
    digitalWrite(wheel_2_2, LOW);
    digitalWrite(wheel_3_1, LOW);
    digitalWrite(wheel_3_2, LOW);
    digitalWrite(wheel_4_1, LOW);
    digitalWrite(wheel_4_2, LOW);
}


void servoControl() {     //모터 제어코드
    int pos = 0;

     delay(2000);   
    for (pos = 0; pos < 30; pos+=6) {  //사료통 열고
        servo.write(pos);
        delay(50);
    }
     delay(800);        //열고 대기부분 보고정해야됨
     servo.write(0);     //닫기
     delay(2000);        //어느정도 대기


}
///////////////////////////////////////////////////////////////////////////////
void oneCycle() {   //한바퀴 코드
    int count = 0;
    while (1) {
        int leftValue = analogRead(leftSensorPin);   //적외선센서 읽기
        int middleValue = analogRead(middleSensorPin);
        int rightValue = analogRead(rightSensorPin);

        if ((middleValue > threshold) && (rightValue > threshold) && (leftValue < threshold)) {  //좌회전
            moveLeft();
        }
        else if ((middleValue > threshold) && (rightValue < threshold) && (leftValue > threshold)) {  //우회전
            moveRight();
        }
        else if ((middleValue < threshold) && (rightValue > threshold) && (leftValue > threshold)) {  //직진1
            moveForward();
        }
        else if ((middleValue > threshold) && (rightValue > threshold) && (leftValue > threshold)) {  //직진2
            moveForward();
        }
        else if ((middleValue < threshold) && (rightValue < threshold) && (leftValue < threshold)) {  //센서,검정색 다 감지부분
            count++;
             Serial. print(count);
            if (count == 1 || count == 5 || count == 6 || count == 10) {  //모서리 회전부분
                moveForward();
                delay(500);
                while (1) {    //90도 회전할때 까지
                    int Value = analogRead(middleSensorPin);
                    moveLeft();
                    if (Value < threshold) break;
                }
            }
            else if (count == 11) {
                count = 0;
                stopMotors();
                break;
            }

            else {       // 소앞에 정지 부분
                stopMotors();
                delay(5000);
                servoControl();// 정지해서 밥주는 코드
                stopMotors();
                delay(4000);
                moveForward();
                delay(500);
            }
        }

    }
}
void sampleCycle() {   //한바퀴 코드
    int count = 0;
    while (1) {
        int leftValue = analogRead(leftSensorPin);   //적외선센서 읽기
        int middleValue = analogRead(middleSensorPin);
        int rightValue = analogRead(rightSensorPin);

        if ((middleValue > threshold) && (rightValue > threshold) && (leftValue < threshold)) {  //좌회전
            moveLeft();
        }
        else if ((middleValue > threshold) && (rightValue < threshold) && (leftValue > threshold)) {  //우회전
            moveRight();
        }
        else if ((middleValue < threshold) && (rightValue > threshold) && (leftValue > threshold)) {  //직진1
            moveForward();
        }
        else if ((middleValue > threshold) && (rightValue > threshold) && (leftValue > threshold)) {  //직진2
            moveForward();
        }
        else if ((middleValue < threshold) && (rightValue < threshold) && (leftValue < threshold)) {  //센서,검정색 다 감지부분
          count++;
          // 소앞에 정지 부분
          stopMotors();
          delay(5000);
          servoControl();// 정지해서 밥주는 코드
          stopMotors();
          delay(4000);
          moveForward();
          delay(500);
            
        }
        if(count==2)break;
    }
}
///////////////////////////////////////////////////////////////////////

/*
void loop() {
    servo.write(0);
   
   if (Serial.available() > 0) {
       int RunCount = Serial.read();  // 시리얼 포트에서 문자를 읽습니다.
       
        if(RunCount >0){
         for (int i = 0; i < RunCount; i++)
          {
              moveForward();
              delay(800);
              oneCycle();
              delay(10000); ///여기는 사용자 시간사이 대기 시간임
          }
          RunCount=0;
        }
        else
          stopMotors();
   }



}*/

void loop() {
    servo.write(0);
   
   if (Serial.available() > 0) {
       int RunCount = Serial.read();  // 시리얼 포트에서 문자를 읽습니다.
       
        if(RunCount >0){
         for (int i = 0; i < RunCount; i++)
          {
              
              sampleCycle();
              delay(10000); ///여기는 사용자 시간사이 대기 시간임
          }
          RunCount=0;
        }
        else
          stopMotors();
   }



}
