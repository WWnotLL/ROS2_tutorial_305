#include <Arduino.h>           // Для ESP32 необходимо подключить заголовочный файл Arduino
#include "MessageFormatter.h"  // Подключаем формирователь сообщений

// ========================================================
// Установление пинов управления моторами
// ========================================================

const byte MOTOR_LF_PWM = 32;  // PWM пин переднего левого мотора
const byte MOTOR_LF = 33;      // Направление переднего левого мотора

const byte MOTOR_RF_PWM = 25;  // PWM пин переднего правого мотора
const byte MOTOR_RF = 26;      // Направление переднего правого мотора

const byte MOTOR_LR_PWM = 19;  // PWM пин заднего левого мотора
const byte MOTOR_LR = 18;      // Направление заднего левого мотора

const byte MOTOR_RR_PWM = 5;  // PWM пин заднего правого мотора
const byte MOTOR_RR = 17;     // Направление заднего правого мотора

// ========================================================
// Настройка энкодеров для четырёх колёс
// ENCODER_PIN_A_* - Пин A
// ENCODER_PIN_B_* - Пин B
// pulseCount_*    - Счетчик импульсов
// lastStateA_*    - Последнее состояние канала A
// direction_*     - Флаг направления: true для прямого, false для обратного
// ========================================================

// ----- Передний левый энкодер -----
const byte ENCODER_PIN_A_LEFT_FRONT = 12;
const byte ENCODER_PIN_B_LEFT_FRONT = 13;

volatile int pulseCount_LEFT_FRONT = 0;
volatile byte lastStateA_LEFT_FRONT = LOW;
volatile bool direction_LEFT_FRONT = true;

// ----- Задний левый энкодер -----
const byte ENCODER_PIN_A_LEFT_REAR = 2;
const byte ENCODER_PIN_B_LEFT_REAR = 15;

volatile int pulseCount_LEFT_REAR = 0;
volatile byte lastStateA_LEFT_REAR = LOW;
volatile bool direction_LEFT_REAR = true;

// ----- Передний правый энкодер -----
const byte ENCODER_PIN_A_RIGHT_FRONT = 14;
const byte ENCODER_PIN_B_RIGHT_FRONT = 27;

volatile int pulseCount_RIGHT_FRONT = 0;
volatile byte lastStateA_RIGHT_FRONT = LOW;
volatile bool direction_RIGHT_FRONT = true;

// ----- Задний правый энкодер -----
const byte ENCODER_PIN_A_RIGHT_REAR = 4;
const byte ENCODER_PIN_B_RIGHT_REAR = 16;

volatile int pulseCount_RIGHT_REAR = 0;
volatile byte lastStateA_RIGHT_REAR = LOW;
volatile bool direction_RIGHT_REAR = true;

// Количество импульсов на один оборот колеса
const int ENCODER_PPR_FRONT = 470;
const int ENCODER_PPR_REAR = 455;

// Глобальное время последнего измерения
unsigned long lastTime = 0;

// Предыдущие значения счётчиков энкодеров
int pulseCountPrev[4] = {0};  

// Период основного цикла отправки данных (мс)
const unsigned long CYCLE_TIME = 100;
unsigned long previousMillis = 0;

// PID-коэффициенты [P, I, D] для каждого колеса
const float coefs[4][3] = {
    {1.0, 0.1, 0.01},  // LF
    {1.0, 0.1, 0.01},  // RF
    {1.0, 0.1, 0.01},  // LR
    {1.0, 0.1, 0.01}   // RR
};

// Хранение состояния PID-контроллера
float previous_error[4] = { 0 };  // Предыдущая ошибка для каждого колеса
float integral[4] = { 0 };        // Интегральная составляющая для каждого колеса

// --------------------------------------------------------------------
// Прототипы функций прерываний
void wheelSpeed_LEFT_FRONT();
void wheelSpeed_LEFT_REAR();
void wheelSpeed_RIGHT_FRONT();
void wheelSpeed_RIGHT_REAR();

void setup() {
  Serial.begin(115200);  // Инициализация UART
  while (!Serial);       // Ждём, пока подключится последовательный порт
  Serial.println("Arduino запущена и готова к работе.");

// Настройка пинов управления моторами на выход
  pinMode(MOTOR_LF, OUTPUT);
  pinMode(MOTOR_RF, OUTPUT);
  pinMode(MOTOR_LR, OUTPUT);
  pinMode(MOTOR_RR, OUTPUT);
  pinMode(MOTOR_LF_PWM, OUTPUT);
  pinMode(MOTOR_RF_PWM, OUTPUT);
  pinMode(MOTOR_LR_PWM, OUTPUT);
  pinMode(MOTOR_RR_PWM, OUTPUT);

  // Настройка энкодеров и прерываний
  // Левый передний
  pinMode(ENCODER_PIN_A_LEFT_FRONT, INPUT);
  pinMode(ENCODER_PIN_B_LEFT_FRONT, INPUT);
  lastStateA_LEFT_FRONT = digitalRead(ENCODER_PIN_A_LEFT_FRONT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A_LEFT_FRONT), wheelSpeed_LEFT_FRONT, CHANGE);

  // Левый задний
  pinMode(ENCODER_PIN_A_LEFT_REAR, INPUT);
  pinMode(ENCODER_PIN_B_LEFT_REAR, INPUT);
  lastStateA_LEFT_REAR = digitalRead(ENCODER_PIN_A_LEFT_REAR);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A_LEFT_REAR), wheelSpeed_LEFT_REAR, CHANGE);

  // Правый передний
  pinMode(ENCODER_PIN_A_RIGHT_FRONT, INPUT);
  pinMode(ENCODER_PIN_B_RIGHT_FRONT, INPUT);
  lastStateA_RIGHT_FRONT = digitalRead(ENCODER_PIN_A_RIGHT_FRONT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A_RIGHT_FRONT), wheelSpeed_RIGHT_FRONT, CHANGE);

  // Правый задний
  pinMode(ENCODER_PIN_A_RIGHT_REAR, INPUT);
  pinMode(ENCODER_PIN_B_RIGHT_REAR, INPUT);
  lastStateA_RIGHT_REAR = digitalRead(ENCODER_PIN_A_RIGHT_REAR);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A_RIGHT_REAR), wheelSpeed_RIGHT_REAR, CHANGE);
}

void loop() {

  int speedRight = 0, speedLeft = 0;
  int targetWheelSpeeds[4] = { 0 }

  // Получение данных от Python через Serial
  if (Serial.available() > 0) {
    String receivedLine = Serial.readStringUntil('\n');
    if (receivedLine.length() > 0) {
      if (parseReceivedMessage(receivedLine, speedRight, speedLeft)) {
        Serial.print("Получено от Python: speedRight = ");
        Serial.print(speedRight);
        Serial.print(", speedLeft = ");
        Serial.println(speedLeft);

        // Задание требуемых скоростей для каждого колеса
        targetWheelSpeeds[0] = speedLeft;
        targetWheelSpeeds[1] = speedRight;
        targetWheelSpeeds[2] = speedLeft;
        targetWheelSpeeds[3] = speedRight;

      } else {
        Serial.print("Ошибка разбора сообщения: ");
        Serial.println(receivedLine);
      }
    }
  }

  // Расчёт текущих угловых скоростей колёс
  float wheelSpeeds[4];
  calculateWheelSpeeds(wheelSpeeds);

  // Вычисление управляющих воздействий PID-регулятором
  int controlSignals[4];
  calculatePID(wheelSpeeds, targetWheelSpeeds, controlSignals);

  // Применение управляющих сигналов к моторам
  applyMotorControl(controlSignals);

  // Отправка данных на Python с заданной периодичностью
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= CYCLE_TIME) {
    previousMillis = currentMillis;

    noInterrupts(); // Защита от прерываний

    int lfCount = pulseCount_LEFT_FRONT;
    int lrCount = pulseCount_LEFT_REAR;
    int rfCount = pulseCount_RIGHT_FRONT;
    int rrCount = pulseCount_RIGHT_REAR;

    // Сброс счетчиков для следующего цикла
    pulseCount_LEFT_FRONT = 0;
    pulseCount_LEFT_REAR = 0;
    pulseCount_RIGHT_FRONT = 0;
    pulseCount_RIGHT_REAR = 0;

    interrupts();

    // Формирование сообщения с помощью функции createMessage()
    String message = createMessage(lfCount, lrCount, rfCount, rrCount);
    // Отправка сформированного сообщения
    Serial.write(message.c_str());
  }
}


// Функция для управления направлением и скоростью моторов
void applyMotorControl(const int controlSignals[4]) {

  // Управление направлением вращения
  digitalWrite(MOTOR_LF, controlSignals[0] > 0 ? LOW : HIGH);
  digitalWrite(MOTOR_RF, controlSignals[1] > 0 ? LOW : HIGH);
  digitalWrite(MOTOR_LR, controlSignals[2] > 0 ? LOW : HIGH);
  digitalWrite(MOTOR_RR, controlSignals[3] > 0 ? LOW : HIGH);

  // Управление скоростью (ШИМ)
  analogWrite(MOTOR_LF_PWM, (int)constrain(abs(controlSignals[0]), 0, 255));
  analogWrite(MOTOR_RF_PWM, (int)constrain(abs(controlSignals[1]), 0, 255));
  analogWrite(MOTOR_LR_PWM, (int)constrain(abs(controlSignals[2]), 0, 255));
  analogWrite(MOTOR_RR_PWM, (int)constrain(abs(controlSignals[3]), 0, 255));
}

// ========================================================
// Прерывания для энкодеров 
// ========================================================

// Левый передний
void wheelSpeed_LEFT_FRONT() {
  byte currentStateA = digitalRead(ENCODER_PIN_A_LEFT_FRONT);

  // Определение направления по фронту и состоянию канала B
  if (lastStateA_LEFT_FRONT == LOW && currentStateA == HIGH) {
    int stateB = digitalRead(ENCODER_PIN_B_LEFT_FRONT);
    direction_LEFT_FRONT = (stateB == LOW);
  } else if (lastStateA_LEFT_FRONT == HIGH && currentStateA == LOW) {
    int stateB = digitalRead(ENCODER_PIN_B_LEFT_FRONT);
    direction_LEFT_FRONT = (stateB == HIGH);
  }

  lastStateA_LEFT_FRONT = currentStateA;

  // Обновление счетчика импульсов на основе флага направления
  if (direction_LEFT_FRONT)
    pulseCount_LEFT_FRONT++;
  else
    pulseCount_LEFT_FRONT--;
}

// Левый задний
void wheelSpeed_LEFT_REAR() {
  byte currentStateA = digitalRead(ENCODER_PIN_A_LEFT_REAR);

  if (lastStateA_LEFT_REAR == LOW && currentStateA == HIGH) {
    int stateB = digitalRead(ENCODER_PIN_B_LEFT_REAR);
    direction_LEFT_REAR = (stateB == LOW);
  } else if (lastStateA_LEFT_REAR == HIGH && currentStateA == LOW) {
    int stateB = digitalRead(ENCODER_PIN_B_LEFT_REAR);
    direction_LEFT_REAR = (stateB == HIGH);
  }

  lastStateA_LEFT_REAR = currentStateA;

  if (direction_LEFT_REAR)
    pulseCount_LEFT_REAR++;
  else
    pulseCount_LEFT_REAR--;
}

// Правый передний
void wheelSpeed_RIGHT_FRONT() {
  byte currentStateA = digitalRead(ENCODER_PIN_A_RIGHT_FRONT);

  if (lastStateA_RIGHT_FRONT == LOW && currentStateA == HIGH) {
    int stateB = digitalRead(ENCODER_PIN_B_RIGHT_FRONT);
    direction_RIGHT_FRONT = (stateB == LOW);
  } else if (lastStateA_RIGHT_FRONT == HIGH && currentStateA == LOW) {
    int stateB = digitalRead(ENCODER_PIN_B_RIGHT_FRONT);
    direction_RIGHT_FRONT = (stateB == HIGH);
  }

  lastStateA_RIGHT_FRONT = currentStateA;

  if (direction_RIGHT_FRONT)
    pulseCount_RIGHT_FRONT++;
  else
    pulseCount_RIGHT_FRONT--;
}

// Правый задний
void wheelSpeed_RIGHT_REAR() {
  byte currentStateA = digitalRead(ENCODER_PIN_A_RIGHT_REAR);

  if (lastStateA_RIGHT_REAR == LOW && currentStateA == HIGH) {
    int stateB = digitalRead(ENCODER_PIN_B_RIGHT_REAR);
    direction_RIGHT_REAR = (stateB == LOW);
  } else if (lastStateA_RIGHT_REAR == HIGH && currentStateA == LOW) {
    int stateB = digitalRead(ENCODER_PIN_B_RIGHT_REAR);
    direction_RIGHT_REAR = (stateB == HIGH);
  }

  lastStateA_RIGHT_REAR = currentStateA;

  if (direction_RIGHT_REAR)
    pulseCount_RIGHT_REAR++;
  else
    pulseCount_RIGHT_REAR--;
}

// ---------------------- PID-регулятор --------------------------
void calculatePID(const float current_vel[4], const int requir_vel[4], float control_input[4]) {
  // Временная переменная для производной составляющей
  float derivative;
  float required_vel[4];

  required_vel[0] = (float)requir_vel[0];
  required_vel[1] = (float)requir_vel[1];
  required_vel[2] = (float)requir_vel[2];
  required_vel[3] = (float)requir_vel[3];

  // Цикл по всем 4 колесам
  for (int i = 0; i < 4; i++) {
    // Рассчитываем ошибку регулирования
    float error = required_vel[i] - current_vel[i];

    // Обновляем интегральную составляющую (с насыщением)
    integral[i] += error;
    // Ограничение интегральной составляющей (антивиндкап)
    if (integral[i] > 100) integral[i] = 100;
    if (integral[i] < -100) integral[i] = -100;

    // Рассчитываем производную составляющую
    derivative = error - previous_error[i];

    // Сохраняем текущую ошибку для следующей итерации
    previous_error[i] = error;

    // Вычисляем управляющее воздействие (ПИД-закон)
    control_input[i] = coefs[i][0] * error +        // Пропорциональная
                       coefs[i][1] * integral[i] +  // Интегральная
                       coefs[i][2] * derivative;    // Дифференциальная

    // Ограничение выходного сигнала (по необходимости)
    if (control_input[i] > 255) control_input[i] = 255;
    if (control_input[i] < -255) control_input[i] = -255;
  }
}


// ------------- Расчёт угловых скоростей (рад/с) -----------------
float calculateWheelSpeeds(float wheelSpeeds[4]) {
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0f;  // Преобразуем в секунды
  lastTime = currentTime;

  // Проверка на минимальный интервал времени
  if (dt <= 0.001f) {  // 1 мс минимальный интервал
    for (int i = 0; i < 4; i++) wheelSpeeds[i] = 0.0f;
    return 0;
  }

  // Коэффициенты преобразования (импульсы -> радианы)
  const float front_conv = 2.0f * M_PI / ENCODER_PPR_FRONT;
  const float rear_conv = 2.0f * M_PI / ENCODER_PPR_REAR;

  int currentPulseCount[4] = {
    pulseCount_LEFT_FRONT,
    pulseCount_RIGHT_FRONT,
    pulseCount_RIGHT_REAR,
    pulseCount_LEFT_REAR
  };

  // Расчёт для передних колёс (LF, RF)
  for (int i = 0; i < 2; i++) {
    int delta = currentPulseCount[i] - pulseCountPrev[i];
    wheelSpeeds[i] = delta * front_conv / dt;
    pulseCountPrev[i] = currentPulseCount[i];
  }

  // Расчёт для задних колёс (LR, RR)
  for (int i = 2; i < 4; i++) {
    int delta = currentPulseCount[i] - pulseCountPrev[i];
    wheelSpeeds[i] = delta * rear_conv / dt;
    pulseCountPrev[i] = currentPulseCount[i];
  }
  return 0;
}
