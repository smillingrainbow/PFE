#include "controllerthread.h"

ControllerThread::~ControllerThread()
{
    this->quit();
    this->wait();
}

void ControllerThread::run(){
    QImage* img = controller.changeDetailsUser();
    emit complete(img);
}

