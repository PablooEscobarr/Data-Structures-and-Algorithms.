#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QQueue>
#include <QString>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Stack operations
    void pushOrder();
    void popOrder();

    // Queue operations
    void enqueueOrder();
    void dequeueOrder();

    // View latest order (Stack)
    void viewLatestOrder();

    // View next order (Queue)
    void viewNextOrder();

private:
    Ui::MainWindow *ui;

    // Stack and Queue to hold orders
    QStack<QString> orderStack;
    QQueue<QString> orderQueue;

    // Helper functions to update the displays
    void updateStackDisplay();
    void updateQueueDisplay();
};

#endif
