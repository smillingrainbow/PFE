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

/**
 * @brief Classe du widget principal
 * Ce widget est contenu dans la fenêtre principale
 * @author Natacha Marlio-Marette
 * @version 0.1
 * @date 10/03/2015
 */
class Window : public QWidget
{
    Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

    private:
        void createLoadGroupBox();
        void createDetailsGroupBox();
        void createInfoGroupBox();
        void createSaveGroupBox();
        void createInputGroupBox();
        void createOutputGroupBox();

        QGroupBox *loadGroupBox;
        QGroupBox *detailsGroupBox;
        QGroupBox *infoGroupBox;
        QGroupBox *saveGroupBox;
        QGroupBox *inputGroupBox;
        QGroupBox *outputGroupBox;

        QLineEdit *loadLineEdit;
        QLineEdit *saveLineEdit;
        QTextEdit *infoTextEdit;

        QPushButton *navLoadButton;
        QPushButton *loadButton;
        QPushButton *launchButton;
        QPushButton *navSaveButton;
        QPushButton *saveButton;

        QCheckBox *raiseCheckBox;
        QCheckBox *lowCheckBox;

        QLabel *inputLabel;
        QLabel *outputLabel;
};

#endif // WINDOW_H
