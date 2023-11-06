#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItems(
        {"Lowest", "Low", "BelowNormal", "Normal", "AboveNormal", "High", "Highest"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<char> MainWindow::GetEnteredChars()
{
    QString InitialText = ui->lineEdit->text();
    QVector<char> Result;
    for (const QChar &Char : InitialText) {
        if (Char.isLetter()) {
            Result.push_back(Char.toLatin1());
        }
    }
    if (Result.isEmpty()) {
        QMessageBox::information(this, "Error!", "Invalid values in value member!");
    }

    return Result;
}

int MainWindow::GetEnteredPriority()
{
    return ui->comboBox->currentIndex();
}

QString MainWindow::GetPriorityName(int Prio)
{
    switch (Prio) {
    case PriorityQueue::EPriorityTypes::High:
        return "High";
    case PriorityQueue::EPriorityTypes::Highest:
        return "Highest";
    case PriorityQueue::EPriorityTypes::AboveNormal:
        return "AboveNormal";
    case PriorityQueue::EPriorityTypes::Normal:
        return "Normal";
    case PriorityQueue::EPriorityTypes::BelowNormal:
        return "BelowNormal";
    case PriorityQueue::EPriorityTypes::Low:
        return "Low";
    case PriorityQueue::EPriorityTypes::Lowest:
        return "Lowest";
    default:
        return "Undefined";
    }
}
void MainWindow::on_pushButton_clicked()
{
    QVector<char> Chars = GetEnteredChars();
    if (Chars.isEmpty()) {
        return;
    } else {
        int Priority = GetEnteredPriority();
        for (const char &Value : Chars) {
            Queue.Enqueue(Value, Priority);
        }
    }
    OutputQueue();
    OutputStats();
}

void MainWindow::OutputQueue()
{
    ui->QueueWidget->clear();
    if (Queue.GetSize() > 0) {
        QString QueueString = "Main queue: ";
        int Size = Queue.GetSize();
        PriorityQueue Temp = Queue;
        for (int i = 0; i < Size; ++i) {
            int TopIndex = Temp.Top();
            if (i != Size - 1)
                QueueString += QChar(Temp.ValueAt(TopIndex)) + '('
                               + GetPriorityName(Temp.PriorityAt(TopIndex)) + ") -> ";
            else
                QueueString += QString(Temp.ValueAt(TopIndex)) + '('
                               + GetPriorityName(Temp.PriorityAt(TopIndex)) + ")";
            Temp.Dequeue();
        }
        ui->QueueWidget->addItem(new QListWidgetItem(QueueString));
    }

    if (RememberedQueue.GetSize() > 0) {
        QString RememberedQueueString = "Remembered queue: ";
        PriorityQueue Temp = RememberedQueue;
        int Size = Temp.GetSize();
        for (int i = 0; i < Size; ++i) {
            int TopIndex = Temp.Top();
            if (i != Size - 1)
                RememberedQueueString += QChar(Temp.ValueAt(TopIndex)) + '('
                                         + GetPriorityName(Temp.PriorityAt(TopIndex)) + ") -> ";
            else
                RememberedQueueString += QString(Temp.ValueAt(TopIndex)) + '('
                                         + GetPriorityName(Temp.PriorityAt(TopIndex)) + ")";
            Temp.Dequeue();
        }
        ui->QueueWidget->addItem(new QListWidgetItem(RememberedQueueString));
    }

    if (AppendedQueue.GetSize() > 0) {
        QString AppendedQueueString = "Appended queue: ";
        PriorityQueue Temp = AppendedQueue;
        int Size = Temp.GetSize();
        for (int i = 0; i < Size; ++i) {
            int TopIndex = Temp.Top();
            if (i != Size - 1)
                AppendedQueueString += QChar(Temp.ValueAt(TopIndex)) + '('
                                       + GetPriorityName(Temp.PriorityAt(TopIndex)) + ") -> ";
            else
                AppendedQueueString += QString(Temp.ValueAt(TopIndex)) + '('
                                       + GetPriorityName(Temp.PriorityAt(TopIndex)) + ")";
            Temp.Dequeue();
        }
        ui->QueueWidget->addItem(new QListWidgetItem(AppendedQueueString));
    }
}

void MainWindow::OutputStats()
{
    int Size = Queue.GetSize();
    ui->statsWidget->clear();
    if (Size > 0) {
        ui->statsWidget->addItem(new QListWidgetItem("Size: " + QString::number(Size)));
        ui->statsWidget->addItem(new QListWidgetItem("Min: " + QString(QChar(Queue.GetMin()))));
        ui->statsWidget->addItem(new QListWidgetItem("Max: " + QString(QChar(Queue.GetMax()))));
        QChar tempChar = GetBeforeMin();
        if (tempChar != 0)
            ui->statsWidget->addItem(new QListWidgetItem("Before Min: " + QString(tempChar)));
        else
            ui->statsWidget->addItem(new QListWidgetItem("Before Min: none"));

        tempChar = GetAfterMax();
        if (tempChar != 0)
            ui->statsWidget->addItem(new QListWidgetItem("Before Max: " + QString(tempChar)));
        else
            ui->statsWidget->addItem(new QListWidgetItem("Before Max: none"));

        tempChar = GetThird();
        if (tempChar != 0)
            ui->statsWidget->addItem(new QListWidgetItem("Third: " + QString(tempChar)));
        else
            ui->statsWidget->addItem(new QListWidgetItem("Third: none"));

        tempChar = GetBeforeLast();
        if (tempChar != 0)
            ui->statsWidget->addItem(new QListWidgetItem("Before last: " + QString(tempChar)));
        else
            ui->statsWidget->addItem(new QListWidgetItem("Before last: none"));
    }
}

char MainWindow::GetBeforeMin()
{
    int MinIndex = Find(Queue.GetMin());
    PriorityQueue TempQueue(Queue);
    for (int i = 0; i < MinIndex; ++i) {
        if (i == MinIndex - 1)
            return TempQueue.ValueAt(TempQueue.Top());
        TempQueue.Dequeue();
    }
    return 0;
}

char MainWindow::GetAfterMax()
{
    int MaxIndex = Find(Queue.GetMax());
    PriorityQueue TempQueue(Queue);
    int Size = TempQueue.GetSize();
    for (int i = 0; i < Size; ++i) {
        if (i == MaxIndex + 1)
            return TempQueue.ValueAt(TempQueue.Top());
        TempQueue.Dequeue();
    }
    return 0;
}

char MainWindow::GetThird()
{
    PriorityQueue TempQueue(Queue);
    int Size = TempQueue.GetSize();
    for (int i = 0; i < Size; ++i) {
        if (i == 2)
            return TempQueue.ValueAt(TempQueue.Top());
        TempQueue.Dequeue();
    }
    return 0;
}

char MainWindow::GetBeforeLast()
{
    PriorityQueue TempQueue(Queue);
    int Size = TempQueue.GetSize();
    for (int i = 0; i < Size; ++i) {
        if (i == Size - 2)
            return TempQueue.ValueAt(TempQueue.Top());
        TempQueue.Dequeue();
    }
    return 0;
}

int MainWindow::Find(char Character)
{
    PriorityQueue TempQueue(Queue);
    int Size = Queue.GetSize();
    for (int i = 0; i < Size; ++i) {
        char Char = TempQueue.ValueAt(TempQueue.Top());
        if (Char == Character)
            return i;
        TempQueue.Dequeue();
    }
    return -1;
}

void MainWindow::on_rememberButton_clicked()
{
    RememberedQueue = std::move(Queue);
    OutputQueue();
}


void MainWindow::on_AppendButton_clicked()
{
    AppendedQueue = RememberedQueue + Queue;
    OutputQueue();
}


void MainWindow::on_findButton_clicked()
{
    QString Str = ui->findLineEdit->text();
    if (Str.size() > 1) {
        QMessageBox::information(this, "Error!", "You have to enter one character!");
        return;
    } else {
        if (LastItem != nullptr) {
            ui->statsWidget->removeItemWidget(LastItem);
        }
        char Char = Str[0].toLatin1();
        int Index = Find(Char);
        if (Index != -1)
            LastItem = new QListWidgetItem("Finded: " + QString::number(Index + 1));
        else
            LastItem = new QListWidgetItem("Finded: none");
        ui->statsWidget->addItem(LastItem);
    }
}

