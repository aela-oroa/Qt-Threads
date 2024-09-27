#ifndef GENERATORTHREAD_H
#define GENERATORTHREAD_H

#include <QThread>

// GeneratorThread is a thread class responsible for generating new numbers.
// It emits a signal whenever a new number is generated.
class GeneratorThread : public QThread {
    Q_OBJECT

public:
    // The main method for the thread, executed when the thread starts.
    void run() override;

signals:
    // Signal emitted when a new number is generated.
    void newNumberGenerated(int number);
};

#endif // GENERATORTHREAD_H
