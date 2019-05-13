#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QFileSystemWatcher>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_OpenFile_clicked();

    void changed(const QString& str);


private:
    Ui::Dialog *ui;
    QStandardItemModel *model;
    QString xmlPath;
    void ReadFile();
    void OpenFile();
    QFileSystemWatcher *watcher;

};
#endif // DIALOG_H
