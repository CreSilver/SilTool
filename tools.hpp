#pragma once
#include <QWidget>
#include <QColor>
#include <QGroupBox>
#include <QVBoxLayout>


class tools : public QWidget{
Q_OBJECT
private:
    int type;
    QString boxStyle = "heigh: 4rem";
    // ColorTool
    QColor currentColor;
    // Converter
    QVBoxLayout *layoutConvt;

public:
    tools(int type, QWidget *parent = nullptr);
    // ColorTool
    void color();
    // Converter
    void conventr();
    void ConverterInch();
    void ConverterSteps();
    void ConverterYards();
    void ConverterMiles();
};


