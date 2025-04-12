#include <time.h>

// ========================================================
// Настройка для энкодера левого переднего колеса
// ========================================================

// Определяем пины для каналов A и B энкодера
const byte ENCODER_PIN_A_LEFTF = 12; // Пин A энкодера (подключён к прерыванию)
const byte ENCODER_PIN_B_LEFTF = 13; // Пин B энкодера

// volatile переменные, изменяемые в ISR, для корректной работы в многозадачной среде:
volatile int pulseCount_LEFTF = 0;           // Счётчик импульсов энкодера (начальное значение 0)
volatile byte lastStateA_LEFTF = LOW;          // Предыдущее состояние пина A
volatile boolean direction_LEFTF = true;       // Флаг направления: true – вперёд, false – назад

// Временной интервал для основного цикла (в миллисекундах)
const int CYCLE_TIME = 500; // 500 мс

unsigned long startTime = 0; // Переменная для хранения времени старта

// Прототип функции обработчика прерывания энкодера
void wheelSpeed_LEFTF();

void setup() {
  // Настраиваем пины энкодера как входы
  pinMode(ENCODER_PIN_A_LEFTF, INPUT);
  pinMode(ENCODER_PIN_B_LEFTF, INPUT);

  // Инициализируем последовательный порт для вывода данных
  Serial.begin(115200);   // Скорость 115200 бод

  // Считываем начальное состояние канала A
  lastStateA_LEFTF = digitalRead(ENCODER_PIN_A_LEFTF);

  // Привязываем функцию обработки прерывания к пину A энкодера
  // Функция будет вызываться при любом изменении сигнала (CHANGE)
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A_LEFTF), wheelSpeed_LEFTF, CHANGE);

  // Сохраняем стартовое время
  startTime = millis();
}

void loop() {
  // Выводим в Serial Monitor количество импульсов, накопленных за интервал
  Serial.print("Pulses: ");
  Serial.println(pulseCount_LEFTF);

  // Пример вычисления частоты обновления (циклов в секунду)
  float frequency = 1000.0 / CYCLE_TIME;
  // Если необходим расчёт скорости, можно использовать формулу:
  // скорость (м/с) = (pulseCount_LEFTF / импульсов_на_оборот) * (2 * PI * радиус_колеса) * frequency;

  // Сбрасываем счётчик импульсов для следующего интервала
  pulseCount_LEFTF = 0;

  // Задержка для формирования временного окна измерения
  delay(CYCLE_TIME);
}

// ========================================================
// Функция обработки прерывания для энкодера левого переднего колеса
// ========================================================
void wheelSpeed_LEFTF() {
  // Считываем текущее состояние канала A энкодера
  byte currentStateA = digitalRead(ENCODER_PIN_A_LEFTF);

  // Обработка переходов канала A (рекомендуется обрабатывать как нарастущий, так и спадающий фронт)
  if (lastStateA_LEFTF == LOW && currentStateA == HIGH) {
    // При нарастающем фронте определяем направление по состоянию канала B:
    // Если B = LOW, считаем, что движение вперёд, иначе назад
    int stateB = digitalRead(ENCODER_PIN_B_LEFTF);
    direction_LEFTF = (stateB == LOW);
  }
  else if (lastStateA_LEFTF == HIGH && currentStateA == LOW) {
    // При спадающем фронте также определяем направление:
    // Если B = HIGH, считаем, что движение вперёд, иначе назад
    int stateB = digitalRead(ENCODER_PIN_B_LEFTF);
    direction_LEFTF = (stateB == HIGH);
  }

  // Обновляем предыдущее состояние канала A для отслеживания следующего перехода
  lastStateA_LEFTF = currentStateA;

  // Обновляем счётчик импульсов:
  // Если направление "вперёд" (direction_LEFTF == true) – увеличиваем счётчик,
  // иначе – уменьшаем (можно использовать абсолютное значение, если важно только количество импульсов)
  if (direction_LEFTF)
    pulseCount_LEFTF++;
  else
      pulseCount_LEFTF--;
}
