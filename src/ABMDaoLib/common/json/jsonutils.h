#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class JsonUtils
{
public:
  JsonUtils();

  /**
   * @brief parseJsonObject 字符串转json对象
   * @param string
   * @return
   */
  static QJsonObject parseJsonObject(QString string);
  /**
   * @brief toString json对象转字符串
   * @param object
   * @return
   */
  static QString toString(QJsonObject object);
  /**
   * @brief parseJsonArray  字符串转json数组
   * @param string
   * @return
   */
  static QJsonArray parseJsonArray(QString string);
  /**
   * @brief toString json数组转为字符串
   * @param object
   * @return
   */
  static QString toString(QJsonArray object);
};

#endif // JSONUTILS_H
