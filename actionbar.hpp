#ifndef ACTIONBAR_HPP
#define ACTIONBAR_HPP

#pragma once
// LIBS
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
//
//
//Konstanty
#define ACTIONBAR_HEIGHT 35
//
//
//Třída
class ActionBar : public QFrame{ // bar pro action tlačítka
    Q_OBJECT
    private:
        QString btnStyle = "QPushButton{color: #121212;border: 2px solid transparent;padding: 5px 3px 5px 3px} QPushButton:hover{border: 2px solid #555555; border-radius:5px}";
        QHBoxLayout *layout;

    public:
        ActionBar(QWidget *parent = nullptr) : QFrame(parent){
            this->setFixedHeight(ACTIONBAR_HEIGHT);
            this->setStyleSheet("background-color: #d0d0d0;");
            layout = new QHBoxLayout(this);

            RenderActionBar();
        }
        void RenderActionBar();
        // Elemnents
        void BackButton();
        void RefreshButton();

    signals:
        void backClicked();
        void refreshClicked();
};




#endif