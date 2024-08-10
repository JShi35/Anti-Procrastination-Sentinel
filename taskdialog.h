#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QSpinBox>
#include <algorithm>
#include <QDebug>

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    struct Task {
        QString name;
        int priority;
    };

    TaskDialog(QWidget* parent = nullptr);
    QList<Task> getTasks() const;
    int getReminderInterval() const;

private slots:
    void addTask();
    void removeTask();

private:
    QLineEdit* taskInput;
    QListWidget* taskList;
    QSpinBox* prioritySpinBox;
    QSpinBox* reminderSpinBox;
    QList<Task> tasks;
};

// Define how QDebug should print TaskDialog::Task
inline QDebug operator<<(QDebug dbg, const TaskDialog::Task& task) {
    dbg.nospace() << "Task(" << task.name << ", Priority: " << task.priority << ")";
    return dbg.space();
}

#endif // TASKDIALOG_H
