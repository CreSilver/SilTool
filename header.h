#ifndef HEADER_H
#define HEADER_H

//Knihovny
#include <QFrame>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>   
#include <QFile>
#include <QTextStream>       
#include <QPlainTextEdit> 
#include <QLineEdit>      
#include <QLabel>
#include <QMainWindow>
#include <QApplication>
#include <QtWebEngineWidgets/qwebengineview.h>
#include <QUrl>
#include <QDir>
//
//
//Konstanty
#define SIDEBAR_WIDTH 250
//
//
//Třídy
class SideBar : public QFrame{ // SideBar
    Q_OBJECT
    public:
        SideBar(QWidget *parent = nullptr) : QFrame(parent){
            this->setFixedWidth(SIDEBAR_WIDTH);
            this->setStyleSheet("background-color: #bdddca;");
            QVBoxLayout *layout = new QVBoxLayout(this);


            // Sidebar prvky
            //Logo
            QLabel *logoText = new QLabel("SilverTool", this);
            logoText->setAlignment(Qt::AlignCenter);
            logoText->setStyleSheet("font-size: 35px; color: #121212;padding-top:25px");
            QLabel *logoText2 = new QLabel("SilverTool", this);
            logoText2->setAlignment(Qt::AlignCenter);
            logoText2->setStyleSheet("font-size: 25px; color: #121212; padding-bottom: 50px");



            QPushButton *btnCD = new QPushButton("C/C++ Dev.", this);
            btnCD->setStyleSheet("color: #121212;");
            QPushButton *btnWD = new QPushButton("Website Dev.", this);
            btnWD->setStyleSheet("color: #121212;");
            QPushButton *btnASM = new QPushButton("Assembly Dev.", this);
            btnASM->setStyleSheet("color: #121212;");


            // Pořadí prvků
                // Záleží na pořadí
            layout->addWidget(logoText);
            layout->addWidget(btnWD);
            layout->addWidget(btnCD);
            layout->addWidget(btnASM);
            layout->addStretch();


            //Signály
            connect(btnWD, &QPushButton::clicked, this, &SideBar::WDclick);
            connect(btnCD, &QPushButton::clicked, this, &SideBar::CDclick);
            connect(btnASM, &QPushButton::clicked, this, &SideBar::ASMclick);
        };


    signals:
        void CDclick();
        void WDclick();
        void ASMclick();
        
    public:
        virtual ~SideBar(){}
};



// Musí být poslední
class Window : public QWidget{ // Okno
    Q_OBJECT
    private:
        QStackedWidget *contentStack;
        QWebEngineView *pageStart;
        QWebEngineView *pageWeb;
        QWebEngineView *pageCE;
        QWebEngineView *pageASM;

        QWebEngineView* createDisplayPage(QString fileName) {
        QWebEngineView *view = new QWebEngineView(this);

        QString path = QDir::currentPath() + "/" + fileName;
        view->setUrl(QUrl::fromLocalFile(path));
        view->setContextMenuPolicy(Qt::NoContextMenu);
        
        return view;
        };


    public:
        Window(QWidget *parent=nullptr):QWidget(parent){
            this->setWindowTitle("SilverTool - DevVersion");           // Název aplikace
            this->resize(1180, 720);
            this->setStyleSheet(
                "SideBar {border-right: 1px solid #181a1f;}"
                "QLabel {font-weight: bold; margin-bottom: 20px;}"
            );

            // Nastavení layout
            QHBoxLayout *mainLayout = new QHBoxLayout(this);
            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->setSpacing(0);

            // SideBar
            SideBar *menu = new SideBar(this);
            mainLayout->addWidget(menu);

            // ViewBar
            contentStack = new QStackedWidget(this);
            mainLayout->addWidget(contentStack);

            // Propojení souborů
            pageStart = createDisplayPage("start.html");
            pageWeb = createDisplayPage("web_dev.html");
            pageCE = createDisplayPage("c_dev.html");
            pageASM = createDisplayPage("asm_dev.html");

            // Propojení tlačítek s přepínáním stránek
            contentStack->setCurrentIndex(0);

            contentStack->addWidget(pageStart);
            contentStack->addWidget(pageWeb); 
            contentStack->addWidget(pageCE);  
            contentStack->addWidget(pageASM);

            connect(menu, &SideBar::WDclick, [=](){ contentStack->setCurrentIndex(1); });
            connect(menu, &SideBar::CDclick, [=](){ contentStack->setCurrentIndex(2); });
            connect(menu, &SideBar::ASMclick, [=](){ contentStack->setCurrentIndex(3); });

            
            this->setLayout(mainLayout);
        };
};




#endif