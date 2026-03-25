#pragma once
#include <QWidget>
#include <QColor>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>


class tools : public QWidget{
Q_OBJECT
private:
    int type;
    QColor currentColor;

public:
    tools(int type, QWidget *parent = nullptr);
    
    void color();
};


