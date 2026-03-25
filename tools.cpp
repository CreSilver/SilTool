#include "tools.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>


#define ROUND 5



tools::tools(int type, QWidget *parent) : QWidget(parent){
    switch (type){
    case 0:
        this->currentColor = Qt::white;
        color();
        break;
    case 1:
        conventr();
    
    default:
        break;
    }
}





void tools::conventr(){
    layoutConvt = new QVBoxLayout(this);
    this->setStyleSheet("background-color: #191919;");

    ConverterInch();
    ConverterSteps();
    ConverterYards();
    ConverterMiles();

    layoutConvt->addStretch();
}

void tools::ConverterInch(){
QGroupBox* setInch = new QGroupBox("cm to Inch", this);
    QGridLayout* layout = new QGridLayout(setInch);
    
    layoutConvt->addWidget(setInch);

    QLineEdit* cm = new QLineEdit(this);
    QLineEdit* inch = new QLineEdit(this);

    cm->setStyleSheet(boxStyle);
    inch->setStyleSheet(boxStyle);

    // 1. Převod z CM do INCH
    connect(cm, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double hodnota = text.toDouble(&ok); // Tady nesmí být název 'cm' ani 'inch'
        
        if (ok) {
            inch->setText(QString::number(hodnota / 2.54, 'f', ROUND)); 
        } else if (text.isEmpty()) {
            inch->clear();
        }
    });

    // 2. Převod z INCH do CM
    connect(inch, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double hodnota = text.toDouble(&ok); // Tady nesmí být název 'cm' ani 'inch'
        
        if (ok) {
            cm->setText(QString::number(hodnota * 2.54, 'f', ROUND));
        } else if (text.isEmpty()) {
            cm->clear();
        }
    });

    layout->addWidget(new QLabel("Inch:"), 0, 0);
    layout->addWidget(inch, 0, 1);
    layout->addWidget(new QLabel("CM:"), 0, 2);
    layout->addWidget(cm, 0, 3);
}


void tools::ConverterSteps(){
    QGroupBox* setSteps = new QGroupBox("Steps to Meters", this);
    QGridLayout* layout = new QGridLayout(setSteps);
    layoutConvt->addWidget(setSteps);

    QLineEdit* steps = new QLineEdit(this);
    QLineEdit* meters = new QLineEdit(this);

    steps->setStyleSheet(boxStyle);
    meters->setStyleSheet(boxStyle);

    connect(steps, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            meters->setText(QString::number(val * 0.762, 'f', ROUND)); 
        } else if (text.isEmpty()) { meters->clear(); }
    });

    connect(meters, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            steps->setText(QString::number(val / 0.762, 'f', ROUND));
        } else if (text.isEmpty()) { steps->clear(); }
    });

    layout->addWidget(new QLabel("Steps:"), 0, 0);
    layout->addWidget(steps, 0, 1);
    layout->addWidget(new QLabel("M:"), 0, 2);
    layout->addWidget(meters, 0, 3);
}


void tools::ConverterYards(){
    QGroupBox* setYards = new QGroupBox("Yards to Meters", this);
    QGridLayout* layout = new QGridLayout(setYards);
    layoutConvt->addWidget(setYards);

    QLineEdit* yards = new QLineEdit(this);
    QLineEdit* meters = new QLineEdit(this);

    yards->setStyleSheet(boxStyle);
    meters->setStyleSheet(boxStyle);

    connect(yards, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            meters->setText(QString::number(val * 0.9144, 'f', ROUND));
        } else if (text.isEmpty()) { meters->clear(); }
    });

    connect(meters, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            yards->setText(QString::number(val / 0.9144, 'f', ROUND));
        } else if (text.isEmpty()) { yards->clear(); }
    });

    layout->addWidget(new QLabel("Yards:"), 0, 0);
    layout->addWidget(yards, 0, 1);
    layout->addWidget(new QLabel("M:"), 0, 2);
    layout->addWidget(meters, 0, 3);
}


void tools::ConverterMiles(){
    QGroupBox* setMiles = new QGroupBox("Miles to Kilometers", this);
    QGridLayout* layout = new QGridLayout(setMiles);
    layoutConvt->addWidget(setMiles);

    QLineEdit* miles = new QLineEdit(this);
    QLineEdit* km = new QLineEdit(this);

    miles->setStyleSheet(boxStyle);
    km->setStyleSheet(boxStyle);

    connect(miles, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            km->setText(QString::number(val * 1.60934, 'f', ROUND));
        } else if (text.isEmpty()) { km->clear(); }
    });

    connect(km, &QLineEdit::textEdited, [=](const QString &text) {
        bool ok;
        double val = text.toDouble(&ok);
        if (ok) {
            miles->setText(QString::number(val / 1.60934, 'f', ROUND));
        } else if (text.isEmpty()) { miles->clear(); }
    });

    layout->addWidget(new QLabel("Miles:"), 0, 0);
    layout->addWidget(miles, 0, 1);
    layout->addWidget(new QLabel("KM:"), 0, 2);
    layout->addWidget(km, 0, 3);
}





void tools::color() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setStyleSheet("background-color: #191919;");
    QGroupBox* setTool = new QGroupBox("ColorTool", this);
    QGridLayout* layout = new QGridLayout(setTool);
    mainLayout->addWidget(setTool);

    QWidget* colorPreview = new QWidget();
    colorPreview->setFixedSize(80, 80);
    colorPreview->setStyleSheet("border: 2px solid #292929; background-color: white;");

    // Definice prvků
    QSpinBox* spinR = new QSpinBox(); spinR->setRange(0, 255);
    QSpinBox* spinG = new QSpinBox(); spinG->setRange(0, 255);
    QSpinBox* spinB = new QSpinBox(); spinB->setRange(0, 255);
    QSpinBox* spinH = new QSpinBox(); spinH->setRange(0, 359);
    QSpinBox* spinS = new QSpinBox(); spinS->setRange(0, 255);
    QSpinBox* spinV = new QSpinBox(); spinV->setRange(0, 255);
    QLineEdit* hexEdit = new QLineEdit(); hexEdit->setMaxLength(7);

    spinR->setStyleSheet(boxStyle);
    spinG->setStyleSheet(boxStyle);
    spinB->setStyleSheet(boxStyle);
    spinH->setStyleSheet(boxStyle);
    spinS->setStyleSheet(boxStyle);
    spinV->setStyleSheet(boxStyle);
    hexEdit->setStyleSheet(boxStyle);

    // FUNKCE AKTUALIZACE - Tady je oprava resetování H
    auto updateUI = [=]() {
        spinR->blockSignals(true); spinG->blockSignals(true); spinB->blockSignals(true);
        spinH->blockSignals(true); spinS->blockSignals(true); spinV->blockSignals(true);
        hexEdit->blockSignals(true);

        spinR->setValue(currentColor.red());
        spinG->setValue(currentColor.green());
        spinB->setValue(currentColor.blue());

        int h = currentColor.hsvHue();
        if (h >= 0) spinH->setValue(h); 
        
        spinS->setValue(currentColor.hsvSaturation());
        spinV->setValue(currentColor.value());

        hexEdit->setText(currentColor.name().toUpper());

        colorPreview->setStyleSheet(QString("background-color: %1; border: 2px solid #555;").arg(currentColor.name()));

        spinR->blockSignals(false); spinG->blockSignals(false); spinB->blockSignals(false);
        spinH->blockSignals(false); spinS->blockSignals(false); spinV->blockSignals(false);
        hexEdit->blockSignals(false);
    };

    // PROPOJENÍ RGB
    connect(spinR, &QSpinBox::valueChanged, [this, updateUI](int r) { currentColor.setRed(r); updateUI(); });
    connect(spinG, &QSpinBox::valueChanged, [this, updateUI](int g) { currentColor.setGreen(g); updateUI(); });
    connect(spinB, &QSpinBox::valueChanged, [this, updateUI](int b) { currentColor.setBlue(b); updateUI(); });

    // PROPOJENÍ HSV - Synchronizované nastavení
    auto syncHSV = [this, spinH, spinS, spinV, updateUI]() {
        currentColor.setHsv(spinH->value(), spinS->value(), spinV->value(), currentColor.alpha());
        updateUI();
    };
    connect(spinH, &QSpinBox::valueChanged, [syncHSV](int){ syncHSV(); });
    connect(spinS, &QSpinBox::valueChanged, [syncHSV](int){ syncHSV(); });
    connect(spinV, &QSpinBox::valueChanged, [syncHSV](int){ syncHSV(); });

    connect(hexEdit, &QLineEdit::textEdited, [this, updateUI](const QString &text) {
        if(text.length() == 7 && QColor::isValidColorName(text)) {
            currentColor = QColor(text);
            updateUI();
        }
    });

    layout->addWidget(new QLabel("RGB:"), 0, 0);
    layout->addWidget(spinR, 0, 1); layout->addWidget(spinG, 0, 2); layout->addWidget(spinB, 0, 3);
    
    layout->addWidget(new QLabel("HSV:"), 1, 0);
    layout->addWidget(spinH, 1, 1); layout->addWidget(spinS, 1, 2); layout->addWidget(spinV, 1, 3);

    layout->addWidget(new QLabel("HEX:"), 2, 0);
    layout->addWidget(hexEdit, 2, 1, 1, 3);

    layout->addWidget(new QLabel("Preview:"), 0, 4);
    layout->addWidget(colorPreview, 1, 4, 2, 2);

    mainLayout->addStretch();

    updateUI();
}