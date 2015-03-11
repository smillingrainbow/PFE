#include "window.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    QHBoxLayout *rightLayout = new QHBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    // Création de l'interface
    createLoadGroupBox();
    createDetailsGroupBox();
    createInfoGroupBox();
    createSaveGroupBox();
    createInputGroupBox();
    createOutputGroupBox();

    // Création des connections
    createConnection();

    // Positionnement des widgets
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
    QHBoxLayout *hbox = new QHBoxLayout;
    inputGroupBox = new QGroupBox("Image initiale");
    inputLabel = new QLabel;
    hbox->addWidget(inputLabel);
    inputGroupBox->setLayout(hbox);
    inputGroupBox->hide();
}

void Window::createOutputGroupBox()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    outputGroupBox = new QGroupBox("Image finale");
    outputLabel =  new QLabel;
    hbox->addWidget(outputLabel);
    outputGroupBox->setLayout(hbox);
    outputGroupBox->hide();
}

void Window::createConnection()
{
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

    connect(launchButton, SIGNAL(clicked()), this, SLOT(launchButtonClicked()));

    connect(navLoadButton, SIGNAL(clicked()), this, SLOT(navLoadButtonClicked()));
    connect(navSaveButton, SIGNAL(clicked()), this, SLOT(navSaveButtonClicked()));
}

void Window::navLoadButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "Images (*.png *.jpg *.tif)");
    if(!fileName.isEmpty()){
        loadLineEdit->setText(fileName);
    }

}

void Window::navSaveButtonClicked()
{

}

void Window::loadButtonClicked()
{
    if(!inputGroupBox->isVisible())
        inputGroupBox->show();

    QString fileName = loadLineEdit->text();
    QImage image(fileName);
    if(image.isNull()){
       QMessageBox::information(this, "Chargement de l'image", "Chargemeent impossible de l'image "+fileName);
    }
    else{
        inputLabel->setPixmap(QPixmap::fromImage(image));
    }
}

void Window::launchButtonClicked()
{
    if(!outputGroupBox->isVisible())
        outputGroupBox->show();
}

void Window::saveButtonClicked()
{

}
