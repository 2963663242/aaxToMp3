#include "functions.h"
#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>

QString getExeDirectory()
{
	return QCoreApplication::applicationDirPath();
}

QString os_sep(QString path)
{
	return path.replace('/',QDir::separator()).replace('\\', QDir::separator());
}

QString getmd5(QString value)
{
	QCryptographicHash md(QCryptographicHash::Md5);
	md.addData(value.toUtf8());
	QByteArray bb = md.result();
	return bb.toHex();
}

QByteArray get_cover_from_aax(QString aaxfile)
{
	int index = 0;
	QByteArray flag = "covr";
	QByteArray cover_data = "";

	int length = 4096;
	int count = 0;
	QFile file(aaxfile);
	if (file.open(QIODevice::ReadOnly))
	{
		
		count = file.size();
		QByteArray pre = "";
		while (index < count)
		{	
			
			QByteArray chunk = file.read(length);
			index += length;
			pre.append(chunk);
			int finded = pre.indexOf(flag);
			if (finded != -1) {
				index += finded - length - flag.length();
				break;
			}
			pre = chunk.mid(chunk.length() - flag.length());
		}
		if (index < count) {
			file.seek(index + (qint64)flag.length());
			QByteArray buf = file.read(flag.length()).toHex();
			
			file.seek(file.pos() +12);
			bool ok;
			int cover_size =buf.toInt(&ok,16);
			cover_data = file.read(cover_size);
		}
		file.close();
	}

	return cover_data;
}
