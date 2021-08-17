#ifndef CONFIG_H
#define CONFIG_H

#include "QObject"

#include "dao/currentdatadao.h"

class Config
{
public:
  Config();

  QString getSystemWellId();
  void setSystemWellId(const QString &value);

  QString getSystemRun() ;
  void setSystemRun(const QString &value);

private:
  QString getCurrentData(QString key);

  bool setCurrentData(QString key, QString value,QString model = "system",QString remark = nullptr);
private:
  QSharedPointer<CurrentData> m_currentData;

};

#endif // CONFIG_H
