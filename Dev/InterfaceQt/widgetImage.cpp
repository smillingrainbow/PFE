#include "widgetImage.h"

WidgetImage::WidgetImage(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    QHBoxLayout *rightLayout = new QHBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    // Création de l'interface
    createLoadGroupBox();
    createDetailsGroupBox();
    createInfoGroupBox();
    launchButton = new QPushButton("Lancer");
    createSaveGroupBox();
    createInputGroupBox();
    createOutputGroupBox();

    // Création des connections
    createConnection();

    // Positionnement des widgets
    leftVLayout->addWidget(loadGroupBox);
    leftVLayout->addWidget(detailsGroupBox);
    leftVLayout->addWidget(infoGroupBox);
    leftVLayout->addWidget(launchButton);
    leftVLayout->addWidget(saveGroupBox);

    rightLayout->addWidget(inputGroupBox);
    rightLayout->addWidget(outputGroupBox);

    mainLayout->addLayout(leftVLayout);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);


}

void WidgetImage::createLoadGroupBox()
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

void WidgetImage::createDetailsGroupBox()
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

void WidgetImage::createInfoGroupBox()
{
    QLabel *nbIterationLabel = new QLabel("Nombre d'itérations");
    QLabel *sigmaSLabel = new QLabel("Sigma S");
    QLabel *sigmaRLabel = new QLabel("Sigma R");
    QLabel *alphaLabel = new QLabel("Alpha");
    QLabel *betaLabel = new QLabel("Beta");
    QHBoxLayout *nbIterationHLayout = new QHBoxLayout;
    QHBoxLayout *sigmaSHLayout = new QHBoxLayout;
    QHBoxLayout *sigmaRHLayout = new QHBoxLayout;
    QHBoxLayout *alphaHLayout = new QHBoxLayout;
    QHBoxLayout *betaHLayout = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;

    infoGroupBox = new QGroupBox("Informations complémentaires");
    nbIterationLineEdit = new QLineEdit;
    sigmaSLineEdit = new QLineEdit;
    sigmaRLineEdit = new QLineEdit;
    alphaLineEdit = new QLineEdit;
    betaLineEdit = new QLineEdit;

    infoGroupBox->setCheckable(true);
    infoGroupBox->setChecked(false);

    nbIterationHLayout->addWidget(nbIterationLabel);
    nbIterationHLayout->addWidget(nbIterationLineEdit);
    sigmaSHLayout->addWidget(sigmaSLabel);
    sigmaSHLayout->addWidget(sigmaSLineEdit);
    sigmaRHLayout->addWidget(sigmaRLabel);
    sigmaRHLayout->addWidget(sigmaRLineEdit);
    alphaHLayout->addWidget(alphaLabel);
    alphaHLayout->addWidget(alphaLineEdit);
    betaHLayout->addWidget(betaLabel);
    betaHLayout->addWidget(betaLineEdit);
    vbox->addLayout(nbIterationHLayout);
    vbox->addLayout(sigmaSHLayout);
    vbox->addLayout(sigmaRHLayout);
    vbox->addLayout(alphaHLayout);
    vbox->addLayout(betaHLayout);

    infoGroupBox->setLayout(vbox);
}

void WidgetImage::createSaveGroupBox()
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

void WidgetImage::createInputGroupBox()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    inputGroupBox = new QGroupBox("Image initiale");
    inputLabel = new QLabel;
    inputImage = new QImage;
    hbox->addWidget(inputLabel);
    inputGroupBox->setLayout(hbox);
    inputGroupBox->hide();
}

void WidgetImage::createOutputGroupBox()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    outputGroupBox = new QGroupBox("Image finale");
    outputLabel =  new QLabel;
    outputImage = new QImage;
    hbox->addWidget(outputLabel);
    outputGroupBox->setLayout(hbox);
    outputGroupBox->hide();
}

void WidgetImage::createConnection()
{
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));

    connect(launchButton, SIGNAL(clicked()), this, SLOT(launchButtonClicked()));

    connect(navLoadButton, SIGNAL(clicked()), this, SLOT(navLoadButtonClicked()));
    connect(navSaveButton, SIGNAL(clicked()), this, SLOT(navSaveButtonClicked()));
}

void WidgetImage::navLoadButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "Images (*.png *.jpg *.tif)");
    if(!fileName.isEmpty()){
        loadLineEdit->setText(fileName);
    }

}

void WidgetImage::navSaveButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::currentPath(), "Images (*.png *.jpg *.tif)");
    if(!fileName.isEmpty()){
        saveLineEdit->setText(fileName);
    }
}

void WidgetImage::loadButtonClicked()
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

void WidgetImage::launchButtonClicked()
{
    if(inputImage->isNull()){
        QMessageBox::information(this, "Erreur : pas d'image", "Veuillez d'abord charger une image avant de lancer l'application");
    }
    else{
        Controller *controller = new Controller;
        // pas d'informations saisis par l'utilisateur
        if(!infoGroupBox->isChecked()){
            outputImage = controller->changeDetails(fileNameInput, raiseCheckBox->isChecked());
            outputLabel->setPixmap(QPixmap::fromImage(*outputImage));
        }
        else{
            bool nbIterationBool=true, sigmaSBool=true,sigmaRBool=true, alphaBool=true, betaBool=true;
            int nbIteration=0;
            float sigmaS=0.0, sigmaR=0.0, alpha=0.0, beta=0.0;

            // Récupération des saisies de l'utilisateur
            if(!nbIterationLineEdit->text().isEmpty())
                nbIteration = nbIterationLineEdit->text().toInt(&nbIterationBool);
            if(!sigmaSLineEdit->text().isEmpty())
                sigmaS = sigmaSLineEdit->text().toFloat(&sigmaSBool);
            if(!sigmaRLineEdit->text().isEmpty())
                sigmaR = sigmaRLineEdit->text().toFloat(&sigmaRBool);
            if(!alphaLineEdit->text().isEmpty())
                alpha = alphaLineEdit->text().toFloat(&alphaBool);
            if(!betaLineEdit->text().isEmpty())
                beta = betaLineEdit->text().toFloat(&betaBool);

            // Vérification de la validité des paramètres saisis
            if(!nbIterationBool || !sigmaSBool || !sigmaRBool || !alphaBool || !betaBool){
                QMessageBox::information(this, "Erreur de parmètre(s)", "Veuillez saisir des paramètres valides");
            }
            else{
                if(nbIteration!=0)
                    controller->setNbIteration(nbIteration);
                if(sigmaS!=0.0)
                    controller->setSigmaS(sigmaS);
                if(sigmaR!=0.0)
                    controller->setSigmaR(sigmaR);
                if(alpha!=0.0)
                    controller->setAlpha(alpha);
                if(beta!=0.0)
                    controller->setBeta(beta);
                outputImage = controller->changeDetailsUser(fileNameInput, raiseCheckBox->isChecked());
                outputLabel->setPixmap(QPixmap::fromImage(*outputImage));
            }

        }

        if(!outputGroupBox->isVisible())
            outputGroupBox->show();
    }
}

void WidgetImage::saveButtonClicked()
{
    if(outputImage->isNull()){
        QMessageBox::information(this, "Erreur pas d'image", "Il n'y a pas d'image à sauvegarder");
    }
    else{
        QString fileName = saveLineEdit->text();
        if(fileName.isEmpty()){
            QMessageBox::information(this, "Erreur pas de fichier", "Veuillez indiquez où enregistrer l'image");
        }
        else{
            outputImage->save(fileName);
            QMessageBox::information(this, "Information", "Votre image a bien été sauvegardée");
        }
    }
}
