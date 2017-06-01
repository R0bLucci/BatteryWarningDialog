#include <ui.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSize>
#include <iostream>
#include <QScreen>
#include <QGuiApplication>
#include "option.h"

using std::cout;
using std::endl;

GUI::UI::UI(): option(nullptr){}
GUI::UI::UI(int argc, char** argv) : GUI::UI::UI() {
    if(argc > 1) option = new GUI::Option(argc, argv);
}

GUI::UI::UI(Option * option): option(option){}

GUI::UI::~UI(){}

bool GUI::UI::setUpUI(QWidget *parent){
    if(parent == Q_NULLPTR) return false;

    if(!option){
        option = new GUI::Option;
    } else if(!this->option->parseOptions()) {
        return false;
    }

    parent->setWindowTitle(QString((option->getValue(GUI::Option::titleOption) +
                                   " (" +
                                    option->getValue(GUI::Option::levelOption)
                                    + "%)").c_str()
                                   ));

    parent->resize(QSize(this->setWidthPos(), this->setHeightPos()));

    QPushButton * closeBtn = new QPushButton("Close", parent);
    parent->connect(closeBtn, SIGNAL(released()), parent, SLOT(close()));
    QLabel * message = new QLabel(QString(option->getValue(GUI::Option::msgOption).c_str()), parent);
    message->setFont(QFont("Times", 23, QFont::Bold));
    //QHBoxLayout * hBox = new QHBoxLayout();
    QVBoxLayout * vBox = new QVBoxLayout();
    vBox->addWidget(message);
    //hBox->addWidget(closeBtn);
    vBox->addWidget(closeBtn);
    //vBox->addLayout(hBox);
    // Main window layout
    parent->setLayout(vBox);

    return true;
}

// get Height of the screen
int GUI::UI::getScreenHeight(){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    return screenGeometry.height();
}
// get Width of the screen
int GUI::UI::getScreenWidth(){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    return screenGeometry.width();
}

double GUI::UI::setWidthPos(){
    double width = this->getScreenWidth();
    return width / 3.0;
}

double GUI::UI::setHeightPos(){
    double  height = this->getScreenHeight();
    return  height / 6.0;
}

int GUI::UI::getExitStatusCode() const{
    return this->option->getExitStatusCode();
}
