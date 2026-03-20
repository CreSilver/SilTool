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

            // Sgnály
            connect(btnBack, &QPushButton::clicked, this, &ActionBar::backClicked);
            connect(btnRefresh, &QPushButton::clicked, this, &ActionBar::refreshClicked);

            // Layout
            layout->setContentsMargins(8, 4, 8, 4);
            layout->addStretch();
            layout->addWidget(btnBack);
            layout->addWidget(btnRefresh);
        }

    signals:
        void backClicked();
        void refreshClicked();
};




#endif