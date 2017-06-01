#include "batterydialog.h"
#include "ui.h"
#include "option.h"
#include <iostream>

using std::cout;
using std::endl;

BatteryDialog::BatteryDialog(QWidget *parent)
    : QDialog(parent), ui(new GUI::UI(nullptr)){
}

BatteryDialog::BatteryDialog(int optionCounter, char **optionArguments, QWidget *parent)
    //: QDialog(parent), ui(new GUI::UI(new GUI::Option(optionCounter, optionArguments))){
    : QDialog(parent), ui(new GUI::UI(optionCounter, optionArguments)){
}

BatteryDialog::~BatteryDialog(){
    delete this->ui;
}

int BatteryDialog::show(){
    if(this->ui->setUpUI(this)){
        QWidget::show();
        return true;
     }
     return false;
}

int BatteryDialog::getExitStatusCode() const{
    return this->ui->getExitStatusCode();
}
