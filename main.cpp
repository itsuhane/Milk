#include <QApplication>
#include "milkmainwindow.h"
#include <mmd/mmd.hxx>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(MilkResources);

    QFile file(":/ui/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(styleSheet);

    MilkMainWindow w;
    w.show();

    return a.exec();
}
