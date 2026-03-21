#include "actionbar.hpp"

// Elements
void ActionBar::BackButton(){
    QPushButton *btnBack = new QPushButton("⬅ Zpět", this);
    btnBack->setStyleSheet(btnStyle);
    connect(btnBack, &QPushButton::clicked, this, &ActionBar::backClicked);
    layout->addWidget(btnBack);
}

void ActionBar::RefreshButton(){
    QPushButton *btnRefresh = new QPushButton("🔄 Obnovit", this);
    btnRefresh->setStyleSheet(btnStyle);
    connect(btnRefresh, &QPushButton::clicked, this, &ActionBar::refreshClicked);
    layout->addWidget(btnRefresh);
}


//
void ActionBar::RenderActionBar(){
    layout->setContentsMargins(8, 4, 8, 4);
    layout->addStretch();
    BackButton();
    RefreshButton();    
}