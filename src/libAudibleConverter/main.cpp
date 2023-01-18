#include <QCoreApplication>
#include "AudibleConvert.h"
#include <qDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath = QString::fromLocal8Bit(R"(D:\\Users\\Documents\\1.FabiFuchsundderverloreneNuss-SchatzFabiFuchs_ep7.aax)");
    QString coverPath = R"(C:\Users\Administrator\AppData\Roaming\EpuborAudible\cover\417cc7e3e401d28e4431b9c2ac758c09.jpg)";
    QString m4bPath = "C:\\Users\\Administrator\\EpuborAudible\\1. Fabi Fuchs und der verlorene Nuss-Schatz_ Fabi Fuchs.m4b";
    qDebug() << AudibleConvert::check_type(filePath);
    AudibleConvert converter("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
    AudibleMeta meta = converter.getMeta(filePath);
    /* qDebug() << "key data: " << converter.seek_code(meta.checksum);
    qDebug() << "valitdate title: " << AudibleConvert::validate_title("\"[]<>");
    qDebug() << "timestamp: " << AudibleConvert::timestamp("fsdffsdfsdfsdfsdfsdfsdf"); 
    converter.get_chapters(filePath);
    */
    //converter.set_mp3_meta(R"(‪D:\Users\Documents\10.So Far Away (SUGA, 진, 정국 Ver.).mp3)", meta);
    //AudibleConvert::set_m4b_cover(m4bPath, coverPath);
    converter.process(meta, filePath,convparam::CHAPTERS);

    
    return a.exec();
}
