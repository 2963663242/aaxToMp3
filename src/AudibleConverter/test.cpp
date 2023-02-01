#include <QCoreApplication>
#include "IAudibleConvert.h"
#include <qDebug>
#include <thread>
#include <QtCore/qdir.h>

class ConvertSTATECALLBACK:public STATECALLBACK {
public:
   virtual void stateInform(ItemTable item) {
       if(item.st == status::downloading)
            qDebug() << item.rate;
       else if (item.st == status::finished) {
           qDebug() << "convert finished . filepath: " << item.filepath;
       }
    }
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath = QString::fromLocal8Bit(R"(D:\Users\Downloads\TheGreatestMenaceInsidetheGayPrisonExperiment_ep7.aax)");
    QString coverPath = R"(C:\Users\Administrator\AppData\Roaming\EpuborAudible\cover\417cc7e3e401d28e4431b9c2ac758c09.jpg)";
    QString m4bPath = "C:\\Users\\Administrator\\EpuborAudible\\1. Fabi Fuchs und der verlorene Nuss-Schatz_ Fabi Fuchs.m4b";
    qDebug() << IAudibleConvert::check_type(filePath);
    //AudibleConvert converter("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
    auto converter = IAudibleConvert::Create();
    AudibleMeta meta = converter->getMeta(filePath);
    /* qDebug() << "key data: " << converter.seek_code(meta.checksum);
    qDebug() << "valitdate title: " << AudibleConvert::validate_title("\"[]<>");
    qDebug() << "timestamp: " << AudibleConvert::timestamp("fsdffsdfsdfsdfsdfsdfsdf"); 
    converter.get_chapters(filePath);
    */
    //converter.set_mp3_meta(R"(‪D:\Users\Documents\10.So Far Away (SUGA, 진, 정국 Ver.).mp3)", meta);
    //AudibleConvert::set_m4b_cover(m4bPath, coverPath);
    STATECALLBACK* cb = new ConvertSTATECALLBACK;
    converter->setCallback(cb);
    converter->convert(meta, filePath, convparam::SINGLE,".m4b");
    
    getchar();
    converter->stop();
    qDebug() << "stop";
    return a.exec();
}
