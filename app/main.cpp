#include "app/windows/widget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu w;
    w.show();
    return a.exec();

}
