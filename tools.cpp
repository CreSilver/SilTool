#include "tools.hpp"
#include <QGridLayout>
#include <QLabel>



tools::tools(int type, QWidget *parent) : QWidget(parent){
    if(type==1){
        this->currentColor = Qt::white;
        color();
    }
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

    QString boxStyle = "heigh: 4rem";

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

    // PROPOJENÍ HEX - Oprava agresivity a varování (isValidColorName)
    connect(hexEdit, &QLineEdit::textEdited, [this, updateUI](const QString &text) {
        // Kontrolujeme délku (7 znaků = #RRGGBB) a platnost názvu
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