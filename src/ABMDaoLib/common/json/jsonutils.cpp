#include "jsonutils.h"

JsonUtils::JsonUtils()
{

}

QJsonObject JsonUtils::parseJsonObject(QString string) {
  QJsonParseError error;
  QJsonDocument document = QJsonDocument::fromJson(string.toLatin1(), &error);
  if (document.isNull() || error.error != QJsonParseError::NoError) {
    QJsonObject emptyJson;
    return emptyJson;
  }
  return document.object();
}

QString JsonUtils::toString(QJsonObject object) {
  QJsonDocument document(object);
  return document.toJson(QJsonDocument::Compact);
}

QJsonArray JsonUtils::parseJsonArray(QString string)
{
  QJsonParseError error;
  QJsonDocument document = QJsonDocument::fromJson(string.toLatin1(), &error);
  if (document.isNull() || error.error != QJsonParseError::NoError) {
    QJsonArray emptyJson;
    return emptyJson;
  }
  return document.array();
}

QString JsonUtils::toString(QJsonArray object)
{
  QJsonDocument document(object);
  return document.toJson(QJsonDocument::Compact);
}
