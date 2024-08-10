#include "taskdialog.h"

TaskDialog::TaskDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Enter Your Tasks");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Enter tasks for today with priority:", this);
    layout->addWidget(label);

    taskInput = new QLineEdit(this);
    layout->addWidget(taskInput);

    QHBoxLayout* priorityLayout = new QHBoxLayout();
    QLabel* priorityLabel = new QLabel("Priority (1-10):", this);
    prioritySpinBox = new QSpinBox(this);
    prioritySpinBox->setRange(1, 10);
    prioritySpinBox->setValue(5);  // Default value
    priorityLayout->addWidget(priorityLabel);
    priorityLayout->addWidget(prioritySpinBox);
    layout->addLayout(priorityLayout);

    QPushButton* addButton = new QPushButton("Add Task", this);
    layout->addWidget(addButton);

    taskList = new QListWidget(this);
    layout->addWidget(taskList);

    QPushButton* removeButton = new QPushButton("Remove Selected Task", this);
    layout->addWidget(removeButton);

    QHBoxLayout* reminderLayout = new QHBoxLayout();
    QLabel* reminderLabel = new QLabel("Reminder Interval (1-180 mins):", this);
    reminderSpinBox = new QSpinBox(this);
    reminderSpinBox->setRange(1, 180);
    reminderSpinBox->setValue(60);  // Default value
    reminderLayout->addWidget(reminderLabel);
    reminderLayout->addWidget(reminderSpinBox);
    layout->addLayout(reminderLayout);

    QPushButton* okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);

    connect(addButton, &QPushButton::clicked, this, &TaskDialog::addTask);
    connect(removeButton, &QPushButton::clicked, this, &TaskDialog::removeTask);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}

void TaskDialog::addTask()
{
    QString task = taskInput->text();
    int priority = prioritySpinBox->value();

    if (!task.isEmpty()) {
        QString taskWithPriority = QString("%1 (Priority: %2)").arg(task).arg(priority);
        tasks.append({ task, priority });
        taskList->addItem(taskWithPriority);
        taskInput->clear();

        // Sort tasks by priority
        std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority > b.priority;
            });

        taskList->clear();
        for (const Task& task : tasks) {
            taskList->addItem(QString("%1 (Priority: %2)").arg(task.name).arg(task.priority));
        }
    }
}

void TaskDialog::removeTask()
{
    int row = taskList->currentRow();
    if (row != -1) {
        tasks.removeAt(row);
        delete taskList->takeItem(row);
    }
}

QList<TaskDialog::Task> TaskDialog::getTasks() const
{
    return tasks;
}

int TaskDialog::getReminderInterval() const
{
    return reminderSpinBox->value();
}
