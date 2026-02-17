#ifndef HEADER_H
#define HEADER_H

//Knihovny
#include <QFrame>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit> 
#include <QLineEdit>      
#include <QLabel>
#include <QMainWindow>
#include <QApplication>
//
//
//Konstanty
#define SIDEBAR_WIDTH 250
//
//
//Třídy
class SideBar : public QFrame{ // SideBar
    Q_OBJECT;
    public:
        SideBar(QWidget *parent = nullptr) : QFrame(parent){
            this->setFixedWidth(SIDEBAR_WIDTH);
            this->setStyleSheet("background-color: #70899f;");
            QVBoxLayout *layout = new QVBoxLayout(this);


            // Tlačítka
            QPushButton *btnCD = new QPushButton("C/C++ Dev.", this);
            btnCD->setStyleSheet("color: #121212;");
            QPushButton *btnWD = new QPushButton("Website Dev.", this);
            btnWD->setStyleSheet("color: #121212;");
            QPushButton *btnASM = new QPushButton("Assembly Dev.", this);
            btnASM->setStyleSheet("color: #121212;");


            // Pořadí prvků
                // Záleží na pořadí
            layout->addWidget(btnWD);
            layout->addWidget(btnCD);
            layout->addWidget(btnASM);
            layout->addStretch();
        };

    virtual ~SideBar(){}
};


// Musí být poslední
class Window : public QWidget{ // Okno
    Q_OBJECT;
    public:
        Window(QWidget *parent=nullptr):QWidget(parent){
            this->setWindowTitle("SilTool - DevVersion");           // Název aplikace
            this->resize(1180, 720);
            this->setStyleSheet("background-color: #3d4750;");

            // Nastavení layout
            QHBoxLayout *mainLayout = new QHBoxLayout(this);
            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->setSpacing(0);

            // SideBar
            SideBar *menu = new SideBar(this);
            mainLayout->addWidget(menu);

            // ViewBar
            QWidget *prazdnyObsah = new QWidget(this);
            mainLayout->addWidget(prazdnyObsah);

            
            this->setLayout(mainLayout);
        };
};




#endif