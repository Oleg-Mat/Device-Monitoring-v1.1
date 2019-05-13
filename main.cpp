#include <QtGui/QApplication>
#include <QFileSystemWatcher>
#include "dialog.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog window;
    window.show();
    return a.exec();
}
