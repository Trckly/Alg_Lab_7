#pragma once

#include "QtWidgets/qlistwidget.h"
#include "priorityqueue.hpp"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<char> GetEnteredChars();

    int GetEnteredPriority();

    QString GetPriorityName(int Prio);

    void OutputQueue();

    void OutputStats();

    char GetBeforeMin();

    char GetAfterMax();

    char GetThird();

    char GetBeforeLast();

    int Find(char Character);

private slots:
    void on_pushButton_clicked();

    void on_rememberButton_clicked();

    void on_AppendButton_clicked();

    void on_findButton_clicked();

private:
    Ui::MainWindow *ui;

    PriorityQueue Queue;

    PriorityQueue RememberedQueue;

    PriorityQueue AppendedQueue;

    QListWidgetItem *LastItem = nullptr;
};
