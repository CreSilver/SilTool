#include "header.h"

int main(int argc, char* argv[]){
    QApplication app(argc, const_cast<char**>(argv));
    Window window;
    window.show();


    return app.exec();
}