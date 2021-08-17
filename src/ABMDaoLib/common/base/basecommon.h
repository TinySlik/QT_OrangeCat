#ifndef BASECOMMON_H
#define BASECOMMON_H

#include <QObject>
#include <QVariant>
#include <QMetaProperty>
#include <QDebug>


class BaseCommon : public QObject
{
  Q_OBJECT
public:
  explicit BaseCommon(QObject *parent = nullptr);

  QMap<QString,QVariant> toMap();
signals:

public slots:
};

#endif // BASECOMMON_H
