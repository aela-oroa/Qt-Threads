#include "consumerthread.h"

// Constructor, initializing the queueManager pointer.
ConsumerThread::ConsumerThread(QueueManagerThread *queueManager) : queueManager(queueManager) {}

// Main method of the thread, runs in a loop until the thread is interrupted.
void ConsumerThread::run() {
    while (!isInterruptionRequested()) {
        // Pop a value from the queue, if valid (not -1), emit the numberPopped signal.
        int value = queueManager->pop();
        if (value != -1) {
            emit numberPopped(value);
        }
        // Wait for 300 ms between pops.
        QThread::msleep(300);
    }
}
