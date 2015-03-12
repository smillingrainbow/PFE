#ifndef CONTROLLERTHREAD_H
#define CONTROLLERTHREAD_H

#include <QThread>
#include "controller.h"
/**
 * @brief Classe permettant d'exécuter la fonction <b>changeDetailsUser</b> du Controller dans un thread
 */
class ControllerThread : public QThread
{
    Q_OBJECT

    public:
        ControllerThread(Controller c):controller(c){}
        ~ControllerThread();
        /**
         * @brief Lancement de l'exécution du thread
         * Le thread va appeller la fonction permettant de manipuler une image
         * et lorsqu'il a fini il émet un signal (<b>complete()</b>) pour signifier qu'il a fini.
         */
        void run();

    signals :
        /**
         * @brief Signal qui signifie la fin de l'exécution du thread
         * Ce signal permet de communiquer avec le thread de l'application principale (GUI) en lui envoyant un objet QImage.
         */
        void complete(QImage *);

private :
        Controller controller;
};

#endif // CONTROLLERTHREAD_H
