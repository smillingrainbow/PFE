#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidjet = new WidgetImage();
    this->setCentralWidget(mainWidjet);
}

MainWindow::~MainWindow()
{
}
