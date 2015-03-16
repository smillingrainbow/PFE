#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

#include "controller.h"

/**
 * @brief Classe du widget principal
 * Ce widget est contenu dans la fenêtre principale
 * @author Natacha Marlio-Marette
 * @version 0.1
 * @date 10/03/2015
 */
class WidgetImage : public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief Constructeur du widget
         * @param parent
         */
        explicit WidgetImage(QWidget *parent = 0);
        /**
          * @brief Destructeur
          **/
        ~WidgetImage(){}

    private slots:
        void navLoadButtonClicked();
        void navSaveButtonClicked();
        void launchButtonClicked();

    private:
        void createLoadGroupBox();
        void createDetailsGroupBox();
        void createInfoGroupBox();
        void createSaveGroupBox();
        void createInputGroupBox();
        void createOutputGroupBox();
        /**
         * @brief Création des connections
         *  Cette méthode permet de créer les connections entre les boutons et les actions qu'ils engendrent
         */
        void createConnection();

        QGroupBox *loadGroupBox;
        QGroupBox *detailsGroupBox;
        QGroupBox *infoGroupBox;
        QGroupBox *saveGroupBox;
        QGroupBox *inputGroupBox;
        QGroupBox *outputGroupBox;

        QLineEdit *loadLineEdit;
        QLineEdit *saveLineEdit;
        QLineEdit *nbIterationLineEdit;
        QLineEdit *sigmaSLineEdit;
        QLineEdit *sigmaRLineEdit;
        QLineEdit *alphaLineEdit;
        QLineEdit *betaLineEdit;

        QPushButton *navLoadButton;
        QPushButton *launchButton;
        QPushButton *navSaveButton;

        QCheckBox *raiseCheckBox;
        QCheckBox *lowCheckBox;

        QLabel *inputLabel;
        QLabel *outputLabel;

        QImage *inputImage;
        QImage *outputImage;

        QString fileNameInput;
};

#endif // WINDOW_H
