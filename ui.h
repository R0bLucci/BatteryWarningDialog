#ifndef UI_H
#define UI_H

#include <QWidget>



namespace GUI {

    class Option;

    class UI {
    private:
        int getScreenHeight();
        int getScreenWidth();
        double setHeightPos();
        double setWidthPos();

        Option * option;
    public:
        UI();
        UI(int argc, char** argv);
        UI(Option * option);
        ~UI();
        bool setUpUI(QWidget * parent);
        int getExitStatusCode() const;
    };
}

#endif // UI_H
