#ifndef WINDOW_HPP
#define WINDOW_HPP

#pragma once
// HEADERS
#include "sidebar.hpp"
#include "actionbar.hpp"
#include "tools.hpp"
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
        QWebEngineView *toolColors;

        QWebEngineView* createDisplayPage(QString fileName) {
        QWebEngineView *view = new QWebEngineView(this);

        QString path = QDir::currentPath() + "/" + fileName;
        view->setUrl(QUrl::fromLocalFile(path));
        view->setContextMenuPolicy(Qt::NoContextMenu);
        
        return view;
        };


    public:
        Window(QWidget *parent=nullptr):QWidget(parent){
            this->setWindowTitle("SilverTool - Prototyp"); 
            this->setStyleSheet("background-color: #191919;");
            this->resize(1180, 720);
            this->setStyleSheet(
                "QLabel {font-weight: bold; margin-bottom: 20px;}"
            );

            RenderLayout();
        };
        void RenderLayout();

};



#endif