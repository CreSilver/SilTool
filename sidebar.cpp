#include "sidebar.hpp"



void SideBar::setSection(int sec){
    this->section = sec;
};



void SideBar::Rerender(){
    if (this->window()) {
        QWidget *focused = this->window()->focusWidget();
        if (focused) focused->clearFocus();
    }
    render();
};




void SideBar::render(){
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr){ // odstraní předchozí části
        if(child->widget()){
            child->widget()->hide();
            child->widget()->deleteLater();
        }
        delete child;
    }

    // Logo
    QLabel *logoText = new QLabel(this);
    logoText->setText
    (
        "<div style='text-align: center;'><br>"
        "<span style='font-size: 40px; font-weight: bold;color: #121212;'>SilverTool</span><br>"
        "<span style='font-size: 18px;margin-top: -5px;color: #121212;'>Prototyp</span>"
        "<br></div>"
    );
    layout->addWidget(logoText);

    if(section!=0){ // Back button
        QPushButton *back = new QPushButton(btnBackText, this);
        back->setStyleSheet(btnBackStyle);
        connect(back, &QPushButton::clicked, [this]() {this->setSection(0);this->Rerender();});
        layout->addWidget(back);
    }
    if(section==0){ // If menu
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
        connect(documentation, &QPushButton::clicked, [this]() {this->setSection(1);this->Rerender();});
        connect(tools, &QPushButton::clicked, [this]() {this->setSection(2);this->Rerender();});

    }
    else if(section == 1){ // If documents
        // Tlačítka
        QPushButton *btnCD = new QPushButton("C/C++ Dev.", this);
        QPushButton *btnCO = new QPushButton("Compilation doc.", this);
        QPushButton *btnASM = new QPushButton("Assembly Dev.", this);

        //Button design
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
    else if(section==2){}



    // Fotter
    QLabel *end_sidebar = new QLabel(this);
    QString end_sidebar_text = QString
    (
        "<br><span style='font-size: 15px; color: #a4a4a4;'>by Silverko</span><br><span style='font-size: 10px; color: #a4a4a4;'>Version: " + 
        APP_VERSION + "</span>"
    );
    end_sidebar->setText(end_sidebar_text);




    //Layout
    layout->addStretch();
    layout->addWidget(end_sidebar);
};
