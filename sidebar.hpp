#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#pragma once
// LIBS
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

//
//
//Konstanty
const QString APP_VERSION = "1dev0";
#define SIDEBAR_WIDTH 250
//
//
//Třída
class SideBar : public QFrame{ // SideBar
    Q_OBJECT
    private:
        QString btnStyle= "QPushButton{color:#121212;border:2px solid transparent;border-radius:8px;background-color: #cacaca;padding: 8px 0px 8px 0px} QPushButton:hover{border:2px solid #a4a4a4;background-color: #121212;color: #e0e0e0;}";
        QString btnBackStyle= "QPushButton{color:#121212;border:2px solid transparent;text-align:left; text-decoration: none} QPushButton:hover{text-decoration: underline}";
        QString btnBackText= "⬅ Zpět do menu";
        QVBoxLayout *layout;
        int section = 0;
        // section: 
        // 0 = menu
        // 1 = dokumentace
        // 2 = nástroje


    public:
        SideBar(QWidget *parent = nullptr) : QFrame(parent){
            // Create panel
            this->setFixedWidth(SIDEBAR_WIDTH);
            this->setStyleSheet("background-color: #e0e0e0;");
            layout = new QVBoxLayout(this);


            ReRenderSidebar();
        };
        void setSection(int sec);
        void RenderSidebar();
        void ReRenderSidebar();
        // Elements
        void BackButton();
        // Grafika
        void LogoText();
        void EndText();
        // Section
        void SecMenu();
        void SecDoc();
        void SecTools();

    signals:
        void TOOLclick();
        void DOCclick();
        void CDclick();
        void WDclick();
        void ASMclick();
        void CLRSclick();
        void CNVclick();
        
    public:
        virtual ~SideBar(){}
};




#endif