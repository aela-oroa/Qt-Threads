#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generatorthread.h"
#include "queuemanagerthread.h"
#include "consumerthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow is the main class representing the application's GUI.
// It manages the threads and updates the user interface based on thread activity.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor and destructor for setting up and tearing down the UI and threads.
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot for starting/stopping the generator thread.
    void onStartStopThread1();
    // Slot for starting/stopping the consumer thread.
    void onStartStopThread3();
    // Slot for updating the first list box with the generated value.
    void updateListBox1(int value);
    // Slot for updating the second list box with the current queue state.
    void updateListBox2(const QList<int>& queue);
    // Slot for updating the third list box with the popped value.
    void updateListBox3(int value);

private:
    // Pointer to the auto-generated UI class.
    Ui::MainWindow *ui;

    // Thread for generating numbers.
    GeneratorThread *thread1;
    // Thread for managing the queue.
    QueueManagerThread *thread2;
    // Thread for consuming numbers from the queue.
    ConsumerThread *thread3;

    // Flags to track whether the threads are running or not.
    bool isThread1Running = false;
    bool isThread3Running = false;
};

#endif // MAINWINDOW_H
