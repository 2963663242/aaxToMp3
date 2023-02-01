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
    tab->addTab(new QWidget, QString::fromLocal8Bit("   ÏÂÔØ  "));
    tab->addTab(convertWidget, QString::fromLocal8Bit("   ×ª»»  "));
    
   

   ui->verticalLayout->addWidget(tab);
   ui->verticalLayout->setSpacing(0);
   ui->verticalLayout->setMargin(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

