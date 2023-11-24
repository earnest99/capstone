import paho.mqtt.client as mqtt
import serial

# MQTT 브로커 설정
broker_address = 'test.mosquitto.org'  # MQTT 브로커 주소
broker_port = 1883  # MQTT 브로커 포트

# 구독할 토픽
topic_to_subscribe = "cow/set"  # 구독할 토픽 이름

# COM 포트 설정
com_port = 'COM11'  # COM 포트 이름
baud_rate = 9600  # 통신 속도

data_list = [0]*24

# 연결 완료 시 실행할 콜백 함수


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print('Connected to MQTT broker')
        # 연결 성공 시 토픽 구독
        client.subscribe(topic_to_subscribe)
    else:
        print('Connection to MQTT broker failed with code', rc)

# 메시지가 도착했을 때 실행할 콜백 함수


def on_message(client, userdata, message):
    received_message = message.payload.decode()
    print(f"Received message on topic '{message.topic}': {received_message}")
    
    if received_message.isnumeric():
        received_message_int = int(received_message)  # 문자열을 정수로 변환
        data_list[received_message_int - 1] = data_list[received_message_int - 1] + 1

    count = 0
    for a in data_list:
        if a % 2 == 1:
            count = count + 1
    print(count)

    if received_message == 'A':
         # count를 바이트로 변환
        count_byte = bytes([count])
    
        # 시리얼 포트로 바이트 데이터를 보냅니다
        serial_port.write(count_byte)
        print(f"Sent 'start' to {com_port}")
        for i in range(0,24):
            data_list[i] = 0
        


if __name__ == '__main__':
    # MQTT 클라이언트 초기화
    client = mqtt.Client()
    serial_port = serial.Serial(com_port, baud_rate)
    client.on_connect = on_connect
    client.on_message = on_message

    # MQTT 브로커에 연결
    client.connect(broker_address, broker_port)

    # 메시지 수신을 계속 처리하기 위해 루프 실행
    client.loop_forever()
