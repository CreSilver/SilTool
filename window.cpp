#include "window.hpp"
#include <QSpinBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>


void Window::RenderLayout(){
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

    // Tools
    tools *colorTool = new tools(0, this);
    tools *converterTool = new tools(1, this);

    
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
    contentStack->addWidget(colorTool);
    contentStack->addWidget(converterTool);



    connect(menu, &SideBar::WDclick, [=](){ contentStack->setCurrentIndex(1); });
    connect(menu, &SideBar::CDclick, [=](){ contentStack->setCurrentIndex(2); });
    connect(menu, &SideBar::ASMclick, [=](){ contentStack->setCurrentIndex(3); });
    connect(menu, &SideBar::CLRSclick, [=](){ contentStack->setCurrentIndex(4); });
    connect(menu, &SideBar::CNVclick, [=](){ contentStack->setCurrentIndex(5); });


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
}