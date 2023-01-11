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

			int finded = (pre+ chunk).indexOf(flag);
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

QByteArray get_cover_from_aa(QString aafile)
{
	QByteArray magic_jfif = "\xff\xd8\xff\xe0\x00\x10JFIF";
	QByteArray magic_exif = "\xff\xd8\xff\xe1\x00\x18";
	magic_exif = magic_exif.append("Exif");

	QByteArray flagAry[] = { magic_exif, magic_jfif };
	QByteArray cover_data = "";
	int length = 4096;
	int count = 0;

	QFile f(aafile);
	f.open(QIODevice::ReadOnly);
	
	for each (QByteArray flag in  flagAry)
	{
		f.seek(0);
		if (!cover_data.isEmpty())
			break;
		else {
			QByteArray pre = "";
			count = f.size();
			int index = 0;
			while (index < count)
			{
				QByteArray chunk = f.read(length);
				if (!cover_data.isEmpty())
					cover_data += chunk;
				else {
					int finded = (pre + chunk).indexOf(flag);
					if (finded != -1)
						cover_data = (pre + chunk).mid(finded);
					pre = chunk.mid(chunk.length() - flag.length());
				}

			}

		}
	}

	return cover_data;
}
