#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyTabWidget;
class ConvertWidget;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyTabWidget* tab;
    ConvertWidget *convertWidget;
    
};
#endif // MAINWINDOW_H
