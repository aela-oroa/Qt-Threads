#ifndef CONSUMERTHREAD_H
#define CONSUMERTHREAD_H

#include <QThread>
#include "queuemanagerthread.h"

// ConsumerThread is a thread class responsible for consuming (popping) numbers from the QueueManagerThread.
// It periodically pops numbers from the queue and emits a signal with the popped number.
class ConsumerThread : public QThread {
    Q_OBJECT

public:
    // Constructor accepting a pointer to the queue manager, which manages the shared queue.
    ConsumerThread(QueueManagerThread *queueManager);

    // The main method for the thread, executed when the thread starts.
    void run() override;

signals:
    // Signal emitted when a number is popped from the queue.
    void numberPopped(int number);

private:
    // Pointer to the queue manager that manages the shared queue.
    QueueManagerThread *queueManager;
};

#endif // CONSUMERTHREAD_H
