#include "widgetImage.h"

widgetImage::widgetImage(QWidget *parent) :
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

void widgetImage::createLoadGroupBox()
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

void widgetImage::createDetailsGroupBox()
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

void widgetImage::createInfoGroupBox()
{
    infoGroupBox = new QGroupBox("Informations complémentaires");
    infoTextEdit = new QTextEdit;
    launchButton = new QPushButton("Lancer");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(infoTextEdit);
    vbox->addWidget(launchButton);

    infoGroupBox->setLayout(vbox);
}

void widgetImage::createSaveGroupBox()
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

void widgetImage::createInputGroupBox()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    inputGroupBox = new QGroupBox("Image initiale");
    inputLabel = new QLabel;
    inputImage = new QImage;
    hbox->addWidget(inputLabel);
    inputGroupBox->setLayout(hbox);
    inputGroupBox->hide();
}

void widgetImage::createOutputGroupBox()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    outputGroupBox = new QGroupBox("Image finale");
    outputLabel =  new QLabel;
    outputImage = new QImage;
    hbox->addWidget(outputLabel);
    outputGroupBox->setLayout(hbox);
    outputGroupBox->hide();
}

void widgetImage::createConnection()
{
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

    connect(launchButton, SIGNAL(clicked()), this, SLOT(launchButtonClicked()));

    connect(navLoadButton, SIGNAL(clicked()), this, SLOT(navLoadButtonClicked()));
    connect(navSaveButton, SIGNAL(clicked()), this, SLOT(navSaveButtonClicked()));
}

void widgetImage::navLoadButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "Images (*.png *.jpg *.tif)");
    if(!fileName.isEmpty()){
        loadLineEdit->setText(fileName);
    }

}

void widgetImage::navSaveButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::currentPath(), "Images (*.png *.jpg *.tif)");
    if(!fileName.isEmpty()){
        saveLineEdit->setText(fileName);
    }
}

void widgetImage::loadButtonClicked()
{
    fileNameInput = loadLineEdit->text();

    if(fileNameInput.isEmpty()){
        QMessageBox::information(this, "Erreur : pas d'image", "Veuillez indiquez où se situe l'image à charger");
    }
    else{
        inputImage->load(fileNameInput);
        if(inputImage->isNull()){
           QMessageBox::information(this, "Chargement de l'image", "Chargemeent impossible de l'image "+fileNameInput);
        }
        else{
            if(!inputGroupBox->isVisible())
                inputGroupBox->show();
            inputLabel->setPixmap(QPixmap::fromImage(*inputImage));
        }
    }
}

void widgetImage::launchButtonClicked()
{
    if(inputImage->isNull()){
        QMessageBox::information(this, "Erreur : pas d'image", "Veuillez d'abord charger une image avant de lancer l'application");
    }
    else{
        Controller *controller = new Controller;
        outputImage = controller->changeDetails(fileNameInput, raiseCheckBox->isChecked());

        if(!outputGroupBox->isVisible())
            outputGroupBox->show();
        outputLabel->setPixmap(QPixmap::fromImage(*outputImage));
    }
}

void widgetImage::saveButtonClicked()
{
    if(outputImage->isNull()){
        QMessageBox::information(this, "Erreur pas d'image", "Il n'y a pas d'image à sauvegarder");
    }
    else{
        QString fileName = saveLineEdit->text();
        if(!fileName.isEmpty()){
            QMessageBox::information(this, "Erreur pas de fichier", "Veuillez indiquez où enregistrer l'image");
        }
        else{
            outputImage->save(fileName);
        }
    }
}
