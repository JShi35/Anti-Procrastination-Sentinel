#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskdialog.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window to full screen and make it transparent
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    showFullScreen();  // Set the window to full screen

    // Show task dialog on startup
    TaskDialog taskDialog(this);
    if (taskDialog.exec() == QDialog::Accepted) {
        tasks = taskDialog.getTasks();
        reminderInterval = taskDialog.getReminderInterval();
    }

    if (tasks.isEmpty()) {
        // Create the robot widget
        robotWidget = new RobotWidget(this);
        robotWidget->setParent(this); // Set the robot widget as a child of MainWindow
        robotWidget->move(100, 100); // Move the robot to the desired position

        // Show notification for no tasks
        QMessageBox::information(this, "No Tasks", "Alright, let me know if you have any upcoming tasks later.");
    }
    else {
        // Handle the case where tasks are present
        qDebug() << "Tasks entered:" << tasks;

        robotWidget = new RobotWidget(this);
        robotWidget->setParent(this); // Set the robot widget as a child of MainWindow
        robotWidget->move(100, 100); // Move the robot to the desired position

        // Initialize and set up reminder timer
        reminderTimer = new QTimer(this);
        connect(reminderTimer, &QTimer::timeout, this, &MainWindow::showReminder);
        reminderTimer->start(reminderInterval * 60000); // Set the interval based on user input
    }

    // Ensure the MainWindow is shown
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showReminder()
{
    if (!tasks.isEmpty()) {
        QString task = tasks.first().name;
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Task Reminder",
            "Have you done: " + task + "?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            tasks.removeFirst();
            if (tasks.isEmpty()) {
                QMessageBox::information(this, "All Tasks Done",
                    "Good job! All tasks are completed.");
                reminderTimer->stop(); // Stop the timer when all tasks are done
            }
        }
    }
}
