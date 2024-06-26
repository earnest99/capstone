# 지능형 가축관리 모빌리티
  본 작품은 축사 운영의 높은 비용과 노동력 부담 문제를 해결하기 위해 로봇을 활용하여 정해진 시간과 양에 맞춰 소에게 사료를 자동으로 배급하는 시스템을 구현하여 농장주의 노동력을 감소시키고 농장 생산성을 향상시키는 것이다.
  체온 측정을 포함한 다양한 모니터링을 통해 소의 건강을 지속적으로 관리하고, 이상이 감지되면 즉시 농장 관리자에게 알림을 전송하는 알림 시스템도 구축한다. 
  또한, 논문에서 개발된 가축관리 모바일 관리 시스템은 소뿐만 아니라 다양한 가축에도 적용 가능하여 응용 확장성이 매우 크다.
  
[![Video Label](https://img.youtube.com/vi/TlR1G6WdV5w/0.jpg)](https://youtu.be/TlR1G6WdV5w)
* 사진 클릭 시 결과 영상으로 이동

## YOLOv5를 활용한 소와 소귀표 객체 인식
 YOLOv5의 객체 인식 성능을 평가하기 위해 소 귀표 번호 Roboflow[2] 데이터셋을 사용하였다. 소 귀표 번호는 0부터 9까지의 숫자로 라벨링되어 있으며, 다양한 환경과 조건에서 획득된 이미지로 구성되었다. 
 
 YOLOv5 모델을 소, 소 귀표 데이터셋에 대해 학습하였다. 모델은 SGD otimizer를 사용하였으며, 학습은 Google Colab[3] T4 GPU를 활용하여 가속화되었다. Batch size 32와 학습은 100 epoch 동안 진행되었으며, initial learning rate은 0.001로 설정되었다.
## MQTT를 활용한 아두이노와 어플간의 통신
  final_mqtt.py는 무료mqtt브로커 주소와 포트를 사용, 아두이노에서 측정한 데이터를 발행하여 전송 후 데이터를 받아와 어플에 표시한다. 

## 기타 
  아두이노 메가, 온도센서, 서보모터, DC모터*4, 모터드라이브*2, 이온배터리*4, 적외선센서*3, 카메라
