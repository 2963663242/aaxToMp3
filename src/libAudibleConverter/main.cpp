#include <QCoreApplication>
#include "AudibleConvert.h"
#include <qDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath = QString::fromLocal8Bit(R"(D:\\Users\\Documents\\1.FabiFuchsundderverloreneNuss-SchatzFabiFuchs_ep7.aax)");
    qDebug() << AudibleConvert::check_type(filePath);
    AudibleConvert converter("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
    AudibleMeta meta = converter.getMeta(filePath);
    /*qDebug() << "key data: " << converter.compute(meta.checksum);*/
    
    return a.exec();
}
