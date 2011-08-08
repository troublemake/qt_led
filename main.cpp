#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "widget.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    Widget widget;
    //   widget.show();
    widget.showFullScreen();
    return app.exec();
}
