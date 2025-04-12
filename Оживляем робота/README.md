Можете посмотреть [видео](https://www.youtube.com/watch?v=X2vb6u348Lo), где мы тестируем работу Lidar на нашем роботе
## __project.zip__
__project.zip__ - архив, в котором лежат файлы, необходимые для сборки контейнера __Docker__ и __ROS2-пакеты__

## box305_ardu_firmware1.1.zip
__box305_ardu_firmware1.1.zip__ - архив, необходимый для работы с ESP32 и всеми компонентами, управляемыми ей

## ___MessageFormatter___ 
Модуль для Ардуино осуществляющий обработку данных, поступающих от Raspberry PI с примером использования<br>
```String createMessage(int a, int b, int c, int d)``` - Формирует строку которую нужно отправлять<br>
```bool parseReceivedMessage(const String &msg, int &num1, int &num2)``` - Разбирает полученные строки, в переменных num1, num2 будут распознанные значения<br>

```c++
#ifndef MESSAGE_FORMATTER_H
#define MESSAGE_FORMATTER_H

#include <Arduino.h>

String createMessage(int a, int b, int c, int d) {
  return String(a) + " " + String(b) + " " + String(c) + " " + String(d) + "\n";
}

bool parseReceivedMessage(const String &msg, int &num1, int &num2) {
  String trimmed = msg;
  trimmed.trim();
  
  // Ищем разделитель между числами
  int spaceIndex = trimmed.indexOf(' ');
  if (spaceIndex == -1) {
    return false;
  }
  
  String strNum1 = trimmed.substring(0, spaceIndex);
  String strNum2 = trimmed.substring(spaceIndex + 1);
  
  num1 = strNum1.toInt();
  num2 = strNum2.toInt();
  
  return true;
}

#endif // MESSAGE_FORMATTER_H
```
## encoder_one.ino

Скрипт для работы с 1 энкодером.

```c++
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
```

**Пояснения к коду**

**Определение пинов и переменных:**   

• Для энкодера левого переднего колеса задаются пины для каналов A и B. 

• Переменные `pulseCount_LEFTF`, `lastStateA_LEFTF` и `direction_LEFTF` объявлены как `volatile`, так как они изменяются в ISR и читаются в основном цикле.

**Функция**  `setup()`**:**   

• Настраиваются пины как входы. 

• Инициализируется последовательный порт для вывода данных.    

• Устанавливается начальное состояние канала A.    

• Функция `wheelSpeed_LEFTF` привязывается к прерыванию по изменению сигнала на пине A.    

• Запоминается стартовое время. 

**Основной цикл** `loop()`**:**    

• Каждые 500 мс выводится накопленное значение импульсов.    

• Счётчик импульсов сбрасывается для накопления новых значений в следующем цикле.   

• Здесь же можно произвести расчёты, например, скорости колеса, зная количество импульсов на оборот и геометрию колеса. 

**Функция обработки прерывания (**`wheelSpeed_LEFTF`**):**    

• Функция вызывается при любом изменении на пине A.    

• В зависимости от перехода (нарастающий или спадающий фронт) считывается состояние канала B, чтобы определить направление движения.    

• По определённому направлению происходит инкремент или декремент счётчика импульсов. Данный вариант кода является более оптимизированным и безопасным для работы с прерываниями на Arduino. Если вам потребуется масштабировать систему на несколько энкодеров, аналогичный шаблон можно применять для остальных модулей.
