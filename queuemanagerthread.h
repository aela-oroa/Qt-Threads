#ifndef QUEUEMANAGERTHREAD_H
#define QUEUEMANAGERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <QDebug>

// QueueManagerThread is a thread class that manages a shared queue.
// It provides thread-safe methods for adding (pushing) and removing (popping) numbers from the queue.
class QueueManagerThread : public QThread {
    Q_OBJECT

public:
    // Constructor
    explicit QueueManagerThread(QObject *parent = nullptr);

    // Method to add a new value to the queue.
    void push(int value);
    // Method to remove and return the oldest value from the queue.
    int pop();
    // Method to get the current state of the queue.
    QList<int> getQueue();

signals:
    // Signal emitted whenever the queue is updated.
    void queueUpdated(const QList<int>& queue);

protected:
    // The main method for the thread, executed when the thread starts.
    void run() override;

private:
    // FIFO queue to hold integers.
    QList<int> queue;
    // Mutex for thread safety when accessing the queue.
    QMutex mutex;
    // Condition variable for synchronization (used to wait for new data).
    QWaitCondition condition;
};

#endif // QUEUEMANAGERTHREAD_H
