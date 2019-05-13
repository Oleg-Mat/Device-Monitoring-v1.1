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

    //Использование класса QFileSystemWatcher для мониторинга изменения  файла.
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(changed(const QString &)));
    ui->setupUi(this);
    //создаем модель QStandarItemModel.
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
    //Оповещаем о том,что файл изменен и заного перечитываем его с сообщением об обновлениии файла.
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

    //Загружаем XML файл.
    QFile file(xmlPath);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //помещаем данные из файла в document.
        document.setContent(&file);
        file.close();
    }else {

        QMessageBox::information(this,"Error", "File not open");
        return;
    }


    //Получаем root element XML файла.
    QDomElement xmlroot = document.firstChildElement();
    //Задаем root element
    QStandardItem *root = new QStandardItem(xmlroot.tagName());
    root->setIcon(QIcon(":/resources/img/root.png"));
    //присоединяем root element к нашей модели.
    model->appendRow(root);
    //Список детей нашего root element'a.
    QDomNodeList elements = xmlroot.childNodes();

    for(int i = 0; i < elements.size(); i++)
    {
        //Преобразование к типу QDomElement с помощью метода toElement.
        QDomElement element = elements.at(i).toElement();
        if(element.isNull())continue;
        //Добавляем данные в нашу модель из XMl файла.
        QStandardItem *elementitem = new QStandardItem(element.nodeName());
       //Обработка исключительной ситуации ,где в элементе только текст.
        if(element.childNodes().count() == 1)
        {
            if(element.tagName()=="timestamp") { elementitem->setIcon(QIcon(":/resources/img/timestamp.png"));}
            QStandardItem *elementtextitem = new QStandardItem(element.text());
            elementitem->appendRow(elementtextitem);
        }
        //Иконки для элементов.
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
        //Список детей
        QDomNodeList childelements = element.childNodes();

        for(int h = 0; h < childelements.size(); h++)
        {
            //Преобразование к типу QDomElement с помощью метода toElement.
            QDomElement childelement = childelements.at(h).toElement();
            if(childelement.isNull())continue;
            //добавляем данные в нашу модель из XMl файла.
            QStandardItem *childelementitem = new QStandardItem(childelement.nodeName());
            //Проверка не пустой ли элемент.
            if(!childelement.childNodes().isEmpty())
            {
            //Добавляем данные в нашу модель из XMl файла.
            QStandardItem *childelementtextitem = new QStandardItem(childelement.text());
            //Добавляем текстовый узел к  Model
            childelementitem->appendRow(childelementtextitem);
            }
            //Иконки для детей элементов.
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
            //Добавляем дочерние elemnt'ы к нашей Model
            elementitem->appendRow(childelementitem);
        }
        //Добавляем элементы в root к нашей Model
        root->appendRow(elementitem);
    }

}


void Dialog::OpenFile()
{
    if(model)
    {
        //Если QStandardItem передаётся в QStandardItemModel , то права собственности на данные объекты передаются в модель.
        //И при вызове метода clear модель автоматически удаляет эти объекты из памяти.
        model->clear();
        delete model;
    }
    model = new QStandardItemModel(0,1,this);
    ui->treeView->setModel(model);

    QString filter = "XML File (*.xml)";
    xmlPath = QFileDialog::getOpenFileName(this,"open a file", "C://",filter);


    //Путь к watcher
    if(!watcher->files().contains(xmlPath)) watcher->addPath(xmlPath);


    ReadFile();
}






