#ifndef BATTERYDIALOG_H
#define BATTERYDIALOG_H

#include <QDialog>

namespace GUI{
    class UI;
}

class BatteryDialog : public QDialog
{
    Q_OBJECT

public:
    BatteryDialog(QWidget *parent = 0);
    BatteryDialog(int optionCounter, char** optionArguments, QWidget *parent = 0);

    ~BatteryDialog();
    int show();

    int getExitStatusCode() const;

private:
        GUI::UI  * ui;
};

#endif // BATTERYDIALOG_H
