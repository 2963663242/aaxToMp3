#include <QCoreApplication>
#include "IAudibleConvert.h"
#include <qDebug>
#include <thread>

class ConvertSTATECALLBACK:public STATECALLBACK {
public:
   virtual void stateInform(ItemTable item) {
        qDebug() << item.rate;
    }
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filePath = QString::fromLocal8Bit(R"(D:\\Users\\Documents\\1.FabiFuchsundderverloreneNuss-SchatzFabiFuchs_ep7.aax)");
    QString coverPath = R"(C:\Users\Administrator\AppData\Roaming\EpuborAudible\cover\417cc7e3e401d28e4431b9c2ac758c09.jpg)";
    QString m4bPath = "C:\\Users\\Administrator\\EpuborAudible\\1. Fabi Fuchs und der verlorene Nuss-Schatz_ Fabi Fuchs.m4b";
    qDebug() << IAudibleConvert::check_type(filePath);
    //AudibleConvert converter("C:\\Users\\Administrator\\AppData\\Roaming\\.EpuborAudible");
    IAudibleConvert* converter = IAudibleConvert::Create();
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
    std::thread obj([&]() {
        qDebug() << converter->process(meta, filePath, convparam::CHAPTERS);
        });
    getchar();
    converter->stop();
    qDebug() << "stop" << endl;
    return a.exec();
}
