#ifndef WINDOW_HPP
#define WINDOW_HPP

#pragma once
// HEADERS
#include "sidebar.hpp"
#include "actionbar.hpp"
// LIBS
#include <QMainWindow>
#include <QApplication>
#include <QtWebEngineWidgets/qwebengineview.h>
#include <QUrl>
#include <QDir>
#include <QStackedWidget>
#include <QHBoxLayout>



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