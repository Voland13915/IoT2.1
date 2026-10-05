#ifndef TASKS_H
#define TASKS_H

void tasksInit();

void taskButtonLed();    // Task 1: кнопка переключает LED1
void taskBlinkLed();     // Task 2: LED2 мигает, пока LED1 выключен
void taskBlinkControl(); // Task 3: кнопки +/- меняют длительность состояния LED2
void taskLevelIndicator(); // Task 4 (доп.): потенциометр -> яркость LED3

#endif
