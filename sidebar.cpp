#include "sidebar.hpp"


// Elements
void SideBar::BackButton(){
    QPushButton *back = new QPushButton(btnBackText, this);
    back->setStyleSheet(btnBackStyle);
    connect(back, &QPushButton::clicked, [this]() {this->setSection(0);this->ReRenderSidebar();});
    layout->addWidget(back);
}



// Grafika
void SideBar::LogoText(){
    QLabel *logoText = new QLabel(this);
    logoText->setText
    (
        "<div style='text-align: center;'><br>"
        "<span style='font-size: 40px; font-weight: bold;color: #121212;'>SilverTool</span><br>"
        "<span style='font-size: 18px;margin-top: -5px;color: #121212;'>Prototyp</span>"
        "<br></div>"
    );
    layout->addWidget(logoText);
}

void SideBar::EndText(){
    QLabel *end_sidebar = new QLabel(this);
    QString end_sidebar_text = QString
    (
        "<br><span style='font-size: 15px; color: #a4a4a4;'>by Silverko</span><br><span style='font-size: 10px; color: #a4a4a4;'>Version: " + 
        APP_VERSION + "</span>"
    );
    end_sidebar->setText(end_sidebar_text);
    layout->addWidget(end_sidebar);
}



// Section
void SideBar::SecMenu(){
    // Tlačítka
    QPushButton *documentation = new QPushButton("Dokumentace", this);
    QPushButton *tools = new QPushButton("Tools", this);

    // Button design
    documentation->setStyleSheet(btnStyle);
    tools->setStyleSheet(btnStyle);

    // Layout
    layout->addWidget(documentation);
    layout->addWidget(tools);

    //Signály
    connect(documentation, &QPushButton::clicked, [this]() {this->setSection(1);this->ReRenderSidebar();});
    connect(tools, &QPushButton::clicked, [this]() {this->setSection(2);this->ReRenderSidebar();});
}

void SideBar::SecDoc(){
    // Tlačítka
    QPushButton *btnCD = new QPushButton("C/C++ Dev.", this);
    QPushButton *btnCO = new QPushButton("Compilation doc.", this);
    QPushButton *btnASM = new QPushButton("Assembly Dev.", this);

    // Button design
    btnCD->setStyleSheet(btnStyle);
    btnCO->setStyleSheet(btnStyle);
    btnASM->setStyleSheet(btnStyle);

    // Layout
    layout->addWidget(btnCO);
    layout->addWidget(btnCD);
    layout->addWidget(btnASM);

    //Signály
    connect(btnCO, &QPushButton::clicked, this, &SideBar::WDclick);
    connect(btnCD, &QPushButton::clicked, this, &SideBar::CDclick);
    connect(btnASM, &QPushButton::clicked, this, &SideBar::ASMclick);
}

void SideBar::SecTools(){
    // Tlačítka
    QPushButton *btnCLRS = new QPushButton("Colors",this);

    // Button design
    btnCLRS->setStyleSheet(btnStyle);

    // Layout
    layout->addWidget(btnCLRS);

    //Signály
    connect(btnCLRS, &QPushButton::clicked, this, &SideBar::CLRSclick);
}



//
void SideBar::setSection(int sec){
    this->section = sec;
};

void SideBar::ReRenderSidebar(){
    if (this->window()) {
        QWidget *focused = this->window()->focusWidget();
        if (focused) focused->clearFocus();
    }
    RenderSidebar();
};

void SideBar::RenderSidebar(){
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr){ // odstraní předchozí části
        if(child->widget()){
            child->widget()->hide();
            child->widget()->deleteLater();
        }
        delete child;
    }

    LogoText();

    if(section!=0){BackButton();} // Back button

    switch(section){
    case 0: // If menu
        SecMenu();
        break;
    case 1: // If documents
        SecDoc();
        break;
    case 2: // If tools
        SecTools();
        break;

    default:
        break;
    }
    

    layout->addStretch();
    EndText();
};
