#include "batterydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BatteryDialog w(argc, argv);
    return (w.show() ? a.exec(): w.getExitStatusCode());
}
