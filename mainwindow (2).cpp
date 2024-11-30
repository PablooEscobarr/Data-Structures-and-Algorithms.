#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStack>
#include <QQueue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushorder_2, &QPushButton::clicked, this, &MainWindow::pushOrder);
    connect(ui->poporder_2, &QPushButton::clicked, this, &MainWindow::popOrder);
    connect(ui->enqueueorder_2, &QPushButton::clicked, this, &MainWindow::enqueueOrder);
    connect(ui->dequeueorder_2, &QPushButton::clicked, this, &MainWindow::dequeueOrder);
    connect(ui->viewlatest_2, &QPushButton::clicked, this, &MainWindow::viewLatestOrder);
    connect(ui->viewnextorder_2, &QPushButton::clicked, this, &MainWindow::viewNextOrder);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushOrder()
{
    QString order = ui->forcompleteorder_2->text();
    if (order.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Order cannot be empty!");
        return;
    }
    orderStack.push(order);
    updateStackDisplay();
    ui->forcompleteorder_2->clear();
}

void MainWindow::popOrder()
{
    if (orderStack.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Order Stack is Empty!");
        return;
    }
    orderStack.pop();
    updateStackDisplay();
}

void MainWindow::enqueueOrder()
{
    QString order = ui->forpending_2->text();
    if (order.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Order cannot be empty!");
        return;
    }
    orderQueue.enqueue(order);
    updateQueueDisplay();
    ui->forpending_2->clear();
}

void MainWindow::dequeueOrder()
{
    if (orderQueue.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Order Queue is Empty!");
        return;
    }
    orderQueue.dequeue();
    updateQueueDisplay();
}

void MainWindow::viewLatestOrder()
{
    if (orderStack.isEmpty()) {
        ui->LatestOrder_2->setText("No Recent Orders");
    } else {
        ui->LatestOrder_2->setText("Latest Order: " + orderStack.top());
    }
}

void MainWindow::viewNextOrder()
{
    if (orderQueue.isEmpty()) {
        ui->Next_2->setText("No Pending Orders");
    } else {
        ui->Next_2->setText("Next Order: " + orderQueue.head());
    }
}

void MainWindow::updateStackDisplay()
{
    QString stackDisplay = "Order Stack: ";
    if (orderStack.isEmpty()) {
        stackDisplay += "Empty";
    } else {
        QStack<QString> tempStack = orderStack;
        while (!tempStack.isEmpty()) {
            stackDisplay += tempStack.pop() + " -> ";
        }
        stackDisplay = stackDisplay.left(stackDisplay.length() - 4); // Remove trailing " -> "
    }
    ui->Status_2->setText(stackDisplay);  // Display stack status in Status_2 label
}

void MainWindow::updateQueueDisplay()
{
    QString queueDisplay = "Order Queue: ";
    if (orderQueue.isEmpty()) {
        queueDisplay += "Empty";
    } else {
        QQueue<QString> tempQueue = orderQueue;
        while (!tempQueue.isEmpty()) {
            queueDisplay += tempQueue.dequeue() + " -> ";
        }
        queueDisplay = queueDisplay.left(queueDisplay.length() - 4); // Remove trailing " -> "
    }
    ui->Status_2->setText(queueDisplay);  // Display queue status in Status_2 label
}
