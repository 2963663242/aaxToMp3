#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include "MyTabWidget.h"
#include "ConvertWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    tab = new MyTabWidget;

    convertWidget = new ConvertWidget;
    tab->addTab(new QWidget, "   下载  ");
    tab->addTab(convertWidget, "   转换  ");
    
   

   ui->verticalLayout->addWidget(tab);
   ui->verticalLayout->setSpacing(0);
   ui->verticalLayout->setMargin(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

