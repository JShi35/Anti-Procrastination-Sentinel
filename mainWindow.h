#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "robotwidget.h"
#include "taskdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void showReminder();

private:
    Ui::MainWindow* ui;
    RobotWidget* robotWidget = nullptr;
    QTimer* reminderTimer = nullptr;
    QList<TaskDialog::Task> tasks;
    int reminderInterval;
};

#endif // MAINWINDOW_H
