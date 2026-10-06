# Ultra_Sonic_Sensor

LilyGO T-Display-S3에서 초음파 센서로 거리를 재고 내장 화면과 시리얼에 표시하는 PlatformIO 예제

## 개요

Trig/Echo 방식 초음파 거리 센서로 1초마다 거리를 측정합니다. Echo 펄스 폭을 cm로 환산해 시리얼 모니터에 출력하고, 같은 값을 TFT_eSPI 라이브러리로 보드 화면에 표시합니다. 작성 시기는 2024년 10월입니다(커밋 기록 기준).

## 하드웨어

- 보드: LilyGO T-Display-S3 (`board = lilygo-t-display-s3`, ESP32-S3, 화면 내장)
- 입력: Trig/Echo 핀을 가진 초음파 거리 센서 1개
- 출력: 보드 내장 TFT 화면

| 신호 | GPIO | 설정 |
|------|------|------|
| Trig (`trigPin`) | 43 | `OUTPUT` |
| Echo (`echoPin`) | 44 | `INPUT` |

## 동작 방식

1. `setup()`
   - 시리얼을 115200 bps로 열고 `starting...`을 출력합니다.
   - 화면을 초기화합니다(`setRotation(1)` 가로 방향, 검은 배경, 흰 글자, 글자 크기 2).
2. `loop()`: 1초마다 다음을 반복합니다.
   - Trig 핀을 LOW 2 us → HIGH 10 us → LOW로 만들어 초음파를 발사합니다.
   - `pulseIn(echoPin, HIGH)`로 Echo가 HIGH인 시간(us)을 잽니다.
   - 거리 계산: `distance = duration * 0.017` (cm). 음속 약 340 m/s = 0.034 cm/us를 왕복 거리이므로 2로 나눈 값입니다.
   - 시리얼 출력 형식: `Duration = <us>, Distance = <cm>cm`
   - 화면을 지우고 `UltraSonic Sensor`와 `Distance : <값> cm`를 표시합니다.

## 개발 환경

| 항목 | 값 |
|------|----|
| 도구 | PlatformIO |
| 플랫폼 | `espressif32` |
| 프레임워크 | `arduino` |
| 라이브러리 | `bodmer/TFT_eSPI @ ^2.5.22` |
| 모니터 속도 | `monitor_speed = 115200` |

## 빌드 및 업로드

```bash
pio run -t upload
pio device monitor
```

## 폴더 구조

```
Ultra_Sonic_Sensor/
├── platformio.ini
└── src/
    └── main.cpp
```

## 참고

- TFT_eSPI는 사용하는 보드와 화면에 맞는 설정(User_Setup)을 골라야 화면이 나옵니다. 이 저장소의 `platformio.ini`에는 해당 설정(`build_flags` 등)이 없으므로, 라이브러리 쪽에서 T-Display-S3용 설정을 선택해 두어야 합니다.
- GPIO 43/44는 ESP32-S3의 기본 UART0(TX/RX) 핀입니다. 같은 보드를 쓰는 Adjustable_Lamp_Switch, QRCode_Display는 `-DARDUINO_USB_CDC_ON_BOOT=1`로 시리얼을 USB로 돌리지만, 이 프로젝트에는 그 플래그가 없습니다.
- `pulseIn()`에 타임아웃을 주지 않아, 반사파가 돌아오지 않으면 기본 타임아웃(1초)만큼 기다린 뒤 0을 반환하고 거리도 0으로 표시됩니다.
