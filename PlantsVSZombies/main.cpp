#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    static PVZ_Widget* pvzwidget;
    pvzwidget = new PVZ_Widget;
    pvzwidget->show();
    return a.exec();
}
