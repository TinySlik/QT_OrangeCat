#include "fileutils.h"

FileUtils::FileUtils()
{

}

QByteArray FileUtils::readFile(QString fileUrl) {
  QFile file(fileUrl);

  if (!file.exists()) {
//    qDebug() << QStringLiteral("文件不存在");
    return nullptr;
  }
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << QStringLiteral("文件打开失败");
    return nullptr;
  }

  QByteArray data = file.readAll();

  file.close();

  return data;
}

static void *ngx_rtmp_mp4_mmap(QString fileName, size_t size, off_t offset, HANDLE *extra)
{
  HANDLE fd = CreateFileA((LPCSTR)fileName.toLatin1(),
                                          GENERIC_READ | GENERIC_WRITE,
                                          FILE_SHARE_READ | FILE_SHARE_WRITE,
                                          NULL,
                                          OPEN_EXISTING,
                                          FILE_ATTRIBUTE_NORMAL,
                                          NULL);

  void           *data;

  *extra = CreateFileMapping(fd, NULL, PAGE_READONLY,
                             (DWORD) ((uint64_t) size >> 32),
                             (DWORD) (size & 0xffffffff),
                             NULL);
  if (*extra == NULL) {
      return NULL;
  }

  data = MapViewOfFile(*extra, FILE_MAP_READ,
                       (DWORD) ((uint64_t) offset >> 32),
                       (DWORD) (offset & 0xffffffff),
                       size);

  if (data == NULL) {
      CloseHandle(*extra);
  }

  /*
   * non-NULL result means map view handle is open
   * and should be closed later
   */

  return data;
}
