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
#include "controllerthread.h"

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
        /**
         * @brief Gestion de l'évènement click sur le bouton de navigation de chragement de l'image d'entrée
         * Ouvre une fenêtre de navigation et charge l'image choisie.
         */
        void navLoadButtonClicked();
        /**
         * @brief Gestion de l'évènement click sur le bouton de navigation de chragement de l'image de sortie
         * Ouvre une fenêtre de navigation et sauvegarde l'image de sortie.
         */
        void navSaveButtonClicked();
        /**
         * @brief Gestion de l'évènement click sur le bouton de lancement du filtre
         * Récupération s'il y en a des informations saisies par l'utilisateur et vérification de leur validitée. Un objet controlleur est crée prenant en compte ces informations si elles sont présentes ainsi que l'image d'entrée et le niveau de détail demandé. Un objet ControllerThread est crée prenant en paramètre le controlleur précédement crée. Ce thred connecte sa sortie au GUI afin qu'ils puissent communiquer. Le thread est ensuite démarré ce qui lance le traitement sur l'image d'entrée.
         */
        void launchButtonClicked();
        /**
         * @brief Slot reçut lors de la fin de l'exécution du ControllerThread
         * @param img Représente la QImage crée après manipulation de l'image d'entrée
         */
        void calculTermine(QImage *img);

    private:
        /**
         * @brief Crée le widget GroupBox du chargement d'une image ainsi que son contenu.
         */
        void createLoadGroupBox();
        /**
         * @brief Crée le widget GroupBox du choix du niveau de détail ainsi que son contenu.
         */
        void createDetailsGroupBox();
        /**
         * @brief Crée le widget GroupBox permettant à l'utilisateur de rentrer manuellement des informations ainsi que son contenu.
         */
        void createInfoGroupBox();
        /**
         * @brief Crée le widget GroupBox de sauvegarde d'une image ainsi que son contenu.
         */
        void createSaveGroupBox();
        /**
         * @brief Crée le widget GroupBox d'affichage d'une image d'entrée ainsi que son contenu.
         */
        void createInputGroupBox();
        /**
         * @brief Crée le widget GroupBox de l'image de sortie ainsi que son contenu.
         */
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
        /**
         * @brief cThread permettet d'exécuter le controller sur un thread à part
         * L'exécution du controller sur un thread à part permet de ne pas bloquer l'interface lors des calculs.
         */
        ControllerThread *cThread;
};

#endif // WINDOW_H
