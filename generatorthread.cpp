#include "generatorthread.h"

// Main method of the thread, runs in a loop until the thread is interrupted.
void GeneratorThread::run() {
    int counter = 0;
    while (!isInterruptionRequested()) {
        // Generate a new number and emit the newNumberGenerated signal.
        emit newNumberGenerated(counter++);
        // Wait for 300 ms between generations.
        QThread::msleep(300);
    }
}
