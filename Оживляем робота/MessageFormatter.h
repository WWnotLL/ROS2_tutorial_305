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
