#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidjet = new widgetImage();
    this->setCentralWidget(mainWidjet);
}

MainWindow::~MainWindow()
{
}
