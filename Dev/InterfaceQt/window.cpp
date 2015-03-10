#include "window.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    QHBoxLayout *rightLayout = new QHBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    createLoadGroupBox();
    createDetailsGroupBox();
    createInfoGroupBox();
    createSaveGroupBox();
    createInputGroupBox();
    createOutputGroupBox();

    // connection entre les boutons "charger" et "lancer" avec les l'affichage des images
    connect(loadButton, SIGNAL(clicked()), inputGroupBox, SLOT(show()));
    connect(launchButton, SIGNAL(clicked()), outputGroupBox, SLOT(show()));

    leftVLayout->addWidget(loadGroupBox);
    leftVLayout->addWidget(detailsGroupBox);
    leftVLayout->addWidget(infoGroupBox);
    leftVLayout->addWidget(saveGroupBox);

    rightLayout->addWidget(inputGroupBox);
    rightLayout->addWidget(outputGroupBox);

    mainLayout->addLayout(leftVLayout);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);


}

Window::~Window()
{
}

void Window::createLoadGroupBox()
{
    loadGroupBox = new QGroupBox("Charger une image");
    loadLineEdit = new QLineEdit;
    navLoadButton = new QPushButton("Navigation");
    loadButton = new QPushButton("Charger");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;


    hbox->addWidget(loadLineEdit);
    hbox->addWidget(navLoadButton);
    vbox->addLayout(hbox);
    vbox->addWidget(loadButton);

    loadGroupBox->setLayout(vbox);
}

void Window::createDetailsGroupBox()
{
    QButtonGroup *buttonGroup = new QButtonGroup;
    detailsGroupBox = new QGroupBox("Manipulation des détails");
    raiseCheckBox = new QCheckBox("Réhaussement");
    lowCheckBox = new QCheckBox("Atténuation");
    raiseCheckBox->setChecked(true);

    buttonGroup->addButton(raiseCheckBox);
    buttonGroup->addButton(lowCheckBox);
    buttonGroup->setExclusive(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(raiseCheckBox);
    vbox->addWidget(lowCheckBox);

    detailsGroupBox->setLayout(vbox);
}

void Window::createInfoGroupBox()
{
    infoGroupBox = new QGroupBox("Informations complémentaires");
    infoTextEdit = new QTextEdit;
    launchButton = new QPushButton("Lancer");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(infoTextEdit);
    vbox->addWidget(launchButton);

    infoGroupBox->setLayout(vbox);
}

void Window::createSaveGroupBox()
{
    saveGroupBox = new QGroupBox("Sauvegarder");
    saveLineEdit = new QLineEdit;
    navSaveButton = new QPushButton("Navigation");
    saveButton = new QPushButton("Sauvegarder");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;


    hbox->addWidget(saveLineEdit);
    hbox->addWidget(navSaveButton);
    vbox->addLayout(hbox);
    vbox->addWidget(saveButton);

    saveGroupBox->setLayout(vbox);
}

void Window::createInputGroupBox()
{
    inputGroupBox = new QGroupBox("Image initiale");
    inputLabel = new QLabel;
    inputGroupBox->hide();
}

void Window::createOutputGroupBox()
{
    outputGroupBox = new QGroupBox("Image finale");
    outputLabel =  new QLabel;
    outputGroupBox->hide();
}

