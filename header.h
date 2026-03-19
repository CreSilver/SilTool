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
const QString APP_VERSION = "0dev10";

#define SIDEBAR_WIDTH 250
#define ACTIONBAR_HEIGHT 35
//
//
//Třídy
class SideBar : public QFrame{ // SideBar
    Q_OBJECT
    private:
        QString btnStyle= "QPushButton{color:#121212;border:2px solid transparent;border-radius:8px;background-color: #cacaca;padding: 8px 0px 8px 0px} QPushButton:hover{border:2px solid #a4a4a4;background-color: #121212;color: #e0e0e0;}";

    public:
        SideBar(QWidget *parent = nullptr) : QFrame(parent){
            this->setFixedWidth(SIDEBAR_WIDTH);
            this->setStyleSheet("background-color: #e0e0e0;");
            QVBoxLayout *layout = new QVBoxLayout(this);

            // Sidebar prvky
                //Logo
            QLabel *logoText = new QLabel(this);
            logoText->setText(
              "<div style='text-align: center;'><br>"
              "<span style='font-size: 40px; font-weight: bold;color: #121212;'>SilverTool</span><br>"
              "<span style='font-size: 18px;margin-top: -5px;color: #121212;'>Prototyp</span>"
              "<br></div>");
                // By Slverko
                // Version
            QLabel *end_sidebar = new QLabel(this);
            QString end_sidebar_text = QString(
                "<br><span style='font-size: 15px; color: #a4a4a4;'>by Silverko</span><br><span style='font-size: 10px; color: #a4a4a4;'>Version: " + 
                APP_VERSION + "</span>"
            );
            end_sidebar->setText(end_sidebar_text);
                // Tlačítka
            QPushButton *btnCD = new QPushButton("C/C++ Dev.", this);
            QPushButton *btnCO = new QPushButton("Compilation doc.", this);
            QPushButton *btnASM = new QPushButton("Assembly Dev.", this);

            //Button design
            btnCD->setStyleSheet(btnStyle);
            btnCO->setStyleSheet(btnStyle);
            btnASM->setStyleSheet(btnStyle);

            // Pořadí prvků
                // Záleží na pořadí
            layout->addWidget(logoText);
            layout->addWidget(btnCO);
            layout->addWidget(btnCD);
            layout->addWidget(btnASM);
            layout->addStretch();
            layout->addWidget(end_sidebar);

            //Signály
            connect(btnCO, &QPushButton::clicked, this, &SideBar::WDclick);
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


class ActionBar : public QFrame{ // bar pro action tlačítka
    Q_OBJECT
    private:
        QString btnStyle = "QPushButton{color: #121212;border: 2px solid transparent;padding: 5px 3px 5px 3px} QPushButton:hover{border: 2px solid #555555; border-radius:5px}";

    public:
        ActionBar(QWidget *parent = nullptr) : QFrame(parent){
            this->setFixedHeight(ACTIONBAR_HEIGHT);
            this->setStyleSheet("background-color: #d0d0d0;");
            QHBoxLayout *layout = new QHBoxLayout(this);

            // Prvky
            QPushButton *btnBack = new QPushButton("⬅ Zpět", this);
            QPushButton *btnRefresh = new QPushButton("🔄 Obnovit", this);

            // Button Design
            btnBack->setStyleSheet(btnStyle);
            btnRefresh->setStyleSheet(btnStyle);

            // Layout
            layout->setContentsMargins(8, 4, 8, 4);
            layout->addStretch();
            layout->addWidget(btnBack);
            layout->addWidget(btnRefresh);

            // Sgnály
            connect(btnBack, &QPushButton::clicked, this, &ActionBar::backClicked);
            connect(btnRefresh, &QPushButton::clicked, this, &ActionBar::refreshClicked);
        }

        signals:
            void backClicked();
            void refreshClicked();
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
            this->setWindowTitle("SilverTool - Prototyp");           // Název aplikace
            this->resize(1180, 720);
            this->setStyleSheet(
                "QLabel {font-weight: bold; margin-bottom: 20px;}"
            );

            // Nastavení layout
            QHBoxLayout *mainLayout = new QHBoxLayout(this);
            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->setSpacing(0);

            // SideBar
            SideBar *menu = new SideBar(this);
            mainLayout->addWidget(menu);

            // ActionBar
            QVBoxLayout *rightLayout = new QVBoxLayout(this);
            rightLayout->setContentsMargins(0, 0, 0, 0);
            rightLayout->setSpacing(0);
            ActionBar *topBar = new ActionBar(this);
            rightLayout->addWidget(topBar);

            // ViewBar
            contentStack = new QStackedWidget(this);
            rightLayout->addWidget(contentStack);

            // Propojení souborů
            pageStart = createDisplayPage("start.html");
            pageWeb = createDisplayPage("makefile.html");
            pageCE = createDisplayPage("c_dev.html");
            pageASM = createDisplayPage("asm_dev.html");

            // Propojení tlačítek s přepínáním stránek
            mainLayout->addLayout(rightLayout);
            contentStack->setCurrentIndex(0);

            contentStack->addWidget(pageStart);
            contentStack->addWidget(pageWeb); 
            contentStack->addWidget(pageCE);  
            contentStack->addWidget(pageASM);

            connect(menu, &SideBar::WDclick, [=](){ contentStack->setCurrentIndex(1); });
            connect(menu, &SideBar::CDclick, [=](){ contentStack->setCurrentIndex(2); });
            connect(menu, &SideBar::ASMclick, [=](){ contentStack->setCurrentIndex(3); });

            
            //Signály
            connect(topBar, &ActionBar::backClicked, [=](){
                QWebEngineView *currentView = qobject_cast<QWebEngineView*>(contentStack->currentWidget());
                if (currentView) currentView->back();
            });

            connect(topBar, &ActionBar::refreshClicked, [=](){
                QWebEngineView *currentView = qobject_cast<QWebEngineView*>(contentStack->currentWidget());
                if (currentView){
                    currentView->page()->triggerAction(QWebEnginePage::ReloadAndBypassCache);
                }
            });


            this->setLayout(mainLayout);
        };
};


#endif