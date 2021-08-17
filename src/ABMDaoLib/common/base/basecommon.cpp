#include "basecommon.h"

BaseCommon::BaseCommon(QObject *parent) : QObject(parent)
{

}

QMap<QString, QVariant> BaseCommon::toMap()
{
//  WellInfoGeneral classTestClass;
  QMap<QString, QVariant> map;

  const QMetaObject *theMetaObject = this->metaObject();//定义一个QMetaObject对象指针，用来获取类classTestClass的相关信息
  int nPropertyCount = theMetaObject->propertyCount();

  for(int nPropertyIndex = 1;nPropertyIndex < nPropertyCount;nPropertyIndex++)
  {
      QMetaProperty property = theMetaObject->property(nPropertyIndex);
//      qDebug() <<"name: " <<property.name()
//               <<"typeName: " <<property.typeName()
//               <<"type" << property.type()
//               <<"isUser: " <<property.isUser()
//               <<"signature: " <<property.userType()
//               << this->property(property.name())
//               << "\n";

      map[property.name()] = this->property(property.name());
  }
  return map;
}
