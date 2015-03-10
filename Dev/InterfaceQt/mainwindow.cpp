#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidjet = new Window();
    this->setCentralWidget(mainWidjet);
}

MainWindow::~MainWindow()
{
}
