#include "queuemanagerthread.h"

// Constructor
QueueManagerThread::QueueManagerThread(QObject *parent)
    : QThread(parent) {
}

// Method to pop (remove and return) the oldest value from the queue.
int QueueManagerThread::pop() {
    QMutexLocker locker(&mutex); // Lock the mutex to ensure thread-safe access to the queue.

    // Wait while the queue is empty.
    while (queue.isEmpty()) {
        condition.wait(&mutex); // Block the thread until a new item is added to the queue.
    }

    // Retrieve and remove the first (oldest) item from the queue.
    int value = queue.takeFirst();

    // Emit a signal to notify that the queue has been updated.
    emit queueUpdated(queue);

    // Output the popped value for debugging purposes.
    qDebug() << "Popped from queue:" << value;

    // Return the popped value.
    return value;
}

// Method to push (add) a new value to the queue.
void QueueManagerThread::push(int value) {
    QMutexLocker locker(&mutex); // Lock the mutex to ensure thread-safe access to the queue.

    // Check if the queue size exceeds 20, and remove the oldest element if needed.
    if (queue.size() >= 20) {
        queue.removeFirst(); // Remove the oldest element.
        qDebug() << "Removed oldest element from queue"; // Output for debugging purposes.
    }

    // Add the new value to the end of the queue.
    queue.append(value);

    // Output the pushed value for debugging purposes.
    qDebug() << "Pushed to queue:" << value;

    // Emit a signal to notify that the queue has been updated.
    emit queueUpdated(queue);

    // Wake up one of the threads waiting on the condition variable (e.g., ConsumerThread).
    condition.wakeOne();
}


// Method to retrieve the current state of the queue (for external access if needed)
QList<int> QueueManagerThread::getQueue() {
    QMutexLocker locker(&mutex); // Lock the mutex to ensure thread-safe access.

    // Return a copy of the queue.
    return queue;
}

// The run method is currently not used as the main functionality is driven by push/pop methods
void QueueManagerThread::run() {
    exec(); // Start the event loop for the thread
}
