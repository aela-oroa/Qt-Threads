#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor, setting up the UI and creating the threads.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    thread1(new GeneratorThread), thread2(new QueueManagerThread), thread3(new ConsumerThread(thread2)) {

    ui->setupUi(this);

    // Connect buttons to start/stop thread slots.
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::onStartStopThread1);
    connect(ui->button2, &QPushButton::clicked, this, &MainWindow::onStartStopThread3);

    // Connect thread signals to update the GUI.
    connect(thread1, &GeneratorThread::newNumberGenerated, thread2, &QueueManagerThread::push);
    connect(thread1, &GeneratorThread::newNumberGenerated, this, &MainWindow::updateListBox1);
    connect(thread2, &QueueManagerThread::queueUpdated, this, &MainWindow::updateListBox2);
    connect(thread3, &ConsumerThread::numberPopped, this, &MainWindow::updateListBox3);
}

// Destructor, ensuring threads are properly interrupted and joined.
MainWindow::~MainWindow() {
    thread1->requestInterruption();
    thread3->requestInterruption();
    thread1->wait();
    thread3->wait();
    delete ui;
}

// Slot to start or stop the generator thread.
void MainWindow::onStartStopThread1() {
    if (isThread1Running) {
        thread1->requestInterruption();
        thread1->wait();
        isThread1Running = false;
    } else {
        thread1->start();
        isThread1Running = true;
    }
}

// Slot to start or stop the consumer thread.
void MainWindow::onStartStopThread3() {
    if (isThread3Running) {
        thread3->requestInterruption();
        thread3->wait();
        isThread3Running = false;
    } else {
        thread3->start();
        isThread3Running = true;
    }
}

// Slot to update the first list box with the generated value.
void MainWindow::updateListBox1(int value) {
    ui->listWidget1->addItem(QString::number(value));
}

// Slot to update the second list box with the current queue state.
void MainWindow::updateListBox2(const QList<int>& queue) {
    ui->listWidget2->clear();
    for (int val : queue) {
        ui->listWidget2->addItem(QString::number(val));
    }
}

// Slot to update the third list box with the popped value.
void MainWindow::updateListBox3(int value) {
    ui->listWidget3->addItem(QString::number(value));
}
