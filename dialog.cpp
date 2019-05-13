#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QFileSystemWatcher>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    //������������� ������ QFileSystemWatcher ��� ����������� ���������  �����.
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(changed(const QString &)));
    ui->setupUi(this);
    //������� ������ QStandarItemModel.
    model = new QStandardItemModel(0,1,this);
    ui->treeView->setModel(model);
    ui->treeView->header()->hide();
    setWindowTitle("Device Monitoring");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //this->resize(640,480);
    QIcon windowIcon(":/resources/img/qt.png");
    this->setWindowIcon(windowIcon);

}

Dialog::~Dialog()
{
    delete model;
    delete ui;
}


void Dialog::on_OpenFile_clicked()
{
    OpenFile();
}


void Dialog::changed(const QString &str)
{
    //��������� � ���,��� ���� ������� � ������ ������������ ��� � ���������� �� ����������� �����.
    Q_UNUSED(str)
    int ret = QMessageBox::information(this,"File Modified", "Your File is modified");
    if(ret)
    {

        ReadFile();

        QMessageBox::information(this,"File updated", "Your File is updated");
    }
}
void Dialog::ReadFile()
{
    if(model) delete model;
    model = new QStandardItemModel(0,1,this);
    ui->treeView->setModel(model);

    QDomDocument document;

    //��������� XML ����.
    QFile file(xmlPath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //�������� ������ �� ����� � document.
        document.setContent(&file);
        file.close();
    }else {

        QMessageBox::information(this,"Error", "File not open");
        return;
    }


    //�������� root element XML �����.
    QDomElement xmlroot = document.firstChildElement();
    //������ root element
    QStandardItem *root = new QStandardItem(xmlroot.tagName());
    root->setIcon(QIcon(":/resources/img/root.png"));
    //������������ root element � ����� ������.
    model->appendRow(root);
    //������ ����� ������ root element'a.
    QDomNodeList elements = xmlroot.childNodes();

    for(int i = 0; i < elements.size(); i++)
    {
        //�������������� � ���� QDomElement � ������� ������ toElement.
        QDomElement element = elements.at(i).toElement();
        if(element.isNull())continue;
        //��������� ������ � ���� ������ �� XMl �����.
        QStandardItem *elementitem = new QStandardItem(element.nodeName());
       //��������� �������������� �������� ,��� � �������� ������ �����.
        if(element.childNodes().count() == 1)
        {
            if(element.tagName()=="timestamp") { elementitem->setIcon(QIcon(":/resources/img/timestamp.png"));}
            QStandardItem *elementtextitem = new QStandardItem(element.text());
            elementitem->appendRow(elementtextitem);
        }
        //������ ��� ���������.
        if(element.tagName()=="timestamp") { elementitem->setIcon(QIcon(":/resources/img/timestamp.png"));}
        if(element.tagName()=="bios") { elementitem->setIcon(QIcon(":/resources/img/bios.png"));}
        if(element.tagName()=="system") { elementitem->setIcon(QIcon(":/resources/img/system.png"));}
        if(element.tagName()=="baseboard") { elementitem->setIcon(QIcon(":/resources/img/baseboard.png"));}
        if(element.tagName()=="chassis") { elementitem->setIcon(QIcon(":/resources/img/chassis.png"));}
        if(element.tagName()=="processor") { elementitem->setIcon(QIcon(":/resources/img/processor.png"));}
        if(element.tagName()=="memory") { elementitem->setIcon(QIcon(":/resources/img/memory.png"));}
        if(element.tagName()=="pci_dev") { elementitem->setIcon(QIcon(":/resources/img/pci_dev.png"));}
        if(element.tagName()=="usb_dev") { elementitem->setIcon(QIcon(":/resources/img/usb_dev.png"));}
        if(element.tagName()=="storage") { elementitem->setIcon(QIcon(":/resources/img/storage.png"));}
        if(element.tagName()=="host") { elementitem->setIcon(QIcon(":/resources/img/host.png"));}
        if(element.tagName()=="timestamp") { elementitem->setIcon(QIcon(":/resources/img/timestamp.png"));}
        if(element.tagName()=="monitor") { elementitem->setIcon(QIcon(":/resources/img/monitor.png"));}
        //������ �����
        QDomNodeList childelements = element.childNodes();

        for(int h = 0; h < childelements.size(); h++)
        {
            //�������������� � ���� QDomElement � ������� ������ toElement.
            QDomElement childelement = childelements.at(h).toElement();
            if(childelement.isNull())continue;
            //��������� ������ � ���� ������ �� XMl �����.
            QStandardItem *childelementitem = new QStandardItem(childelement.nodeName());
            //�������� �� ������ �� �������.
            if(!childelement.childNodes().isEmpty())
            {
            //��������� ������ � ���� ������ �� XMl �����.
            QStandardItem *childelementtextitem = new QStandardItem(childelement.text());
            //��������� ��������� ���� �  Model
            childelementitem->appendRow(childelementtextitem);
            }
            //������ ��� ����� ���������.
            if(element.tagName()=="bios") { childelementitem->setIcon(QIcon(":/resources/img/bios.png"));}
            if(element.tagName()=="system") { childelementitem->setIcon(QIcon(":/resources/img/system.png"));}
            if(element.tagName()=="baseboard") { childelementitem->setIcon(QIcon(":/resources/img/baseboard.png"));}
            if(element.tagName()=="chassis") { childelementitem->setIcon(QIcon(":/resources/img/chassis.png"));;}
            if(element.tagName()=="processor") { childelementitem->setIcon(QIcon(":/resources/img/processor.png"));}
            if(element.tagName()=="memory") { childelementitem->setIcon(QIcon(":/resources/img/memory.png"));}
            if(element.tagName()=="pci_dev") { childelementitem->setIcon(QIcon(":/resources/img/pci_dev.png"));}
            if(element.tagName()=="usb_dev") { childelementitem->setIcon(QIcon(":/resources/img/usb_dev.png"));}
            if(element.tagName()=="storage") { childelementitem->setIcon(QIcon(":/resources/img/storage.png"));}
            if(element.tagName()=="host") { childelementitem->setIcon(QIcon(":/resources/img/host.png"));}
            if(element.tagName()=="timestamp") { childelementitem->setIcon(QIcon(":/resources/img/timestamp.png"));}
            if(element.tagName()=="monitor") { childelementitem->setIcon(QIcon(":/resources/img/monitor.png"));}
            //��������� �������� elemnt'� � ����� Model
            elementitem->appendRow(childelementitem);
        }
        //��������� �������� � root � ����� Model
        root->appendRow(elementitem);
    }

}


void Dialog::OpenFile()
{
    if(model)
    {
        //���� QStandardItem ��������� � QStandardItemModel , �� ����� ������������� �� ������ ������� ���������� � ������.
        //� ��� ������ ������ clear ������ ������������� ������� ��� ������� �� ������.
        model->clear();
        delete model;
    }
    model = new QStandardItemModel(0,1,this);
    ui->treeView->setModel(model);

    QString filter = "XML File (*.xml)";
    xmlPath = QFileDialog::getOpenFileName(this,"open a file", "C://",filter);


    //���� � watcher
    if(!watcher->files().contains(xmlPath)) watcher->addPath(xmlPath);


    ReadFile();
}






