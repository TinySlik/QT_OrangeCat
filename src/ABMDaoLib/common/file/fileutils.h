#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QDebug>

#include "Windows.h"

class FileUtils
{
public:
  FileUtils();

  static QByteArray readFile(QString fileUrl);
};

#endif // FILEUTILS_H
