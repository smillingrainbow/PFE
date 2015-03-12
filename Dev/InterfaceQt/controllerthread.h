#ifndef CONTROLLERTHREAD_H
#define CONTROLLERTHREAD_H

#include <QThread>
#include "controller.h"

class ControllerThread : public QThread
{
    Q_OBJECT

    public:
        ControllerThread(Controller c):controller(c){}
        ~ControllerThread();
        void run();

    signals :
        void complete(QImage *);

private :
        Controller controller;
};

#endif // CONTROLLERTHREAD_H
