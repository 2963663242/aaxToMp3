#include <qstring.h>
#ifdef __APPLE__
#include <unistd.h>
std::string get_executable_dir();
#endif
QString getExeDirectory();
QString os_sep(QString path);
QString getmd5(QString value);
QByteArray get_cover_from_aax(QString aaxfile);
QByteArray get_cover_from_aa(QString aafile);
QString choosename(QString filepath);
QString mkdir(QString path);
