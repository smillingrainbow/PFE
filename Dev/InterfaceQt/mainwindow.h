#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgetImage.h"

/**
 * @brief Classe de l'interface de la fenêtre principale
 * @author Natacha Marlio-Marette
 * @version 0.1
 * @date 10/03/2015
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        /**
         * @brief Widget principal de la fenêtre
         */
        WidgetImage *mainWidjet;
};

#endif // MAINWINDOW_H
