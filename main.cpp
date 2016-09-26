#include "dialog.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;

    QFontDatabase fontDB;
    fontDB.addApplicationFont("/fonts/Roboto-Regular.ttf");
    fontDB.addApplicationFont("/fonts/Roboto-Bold.ttf");

    w.setWindowTitle("Interfaz Eolian");
    w.show();

    return a.exec();
}
