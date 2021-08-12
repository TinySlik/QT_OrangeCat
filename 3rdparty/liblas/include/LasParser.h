#ifndef LASPARSER_H
#define LASPARSER_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMultiMap>
#include <QDebug>
#include "LasDefine.h"
#include "windllsupport.h"

class CLASS_DECLSPEC LasParser : public QObject
{
  Q_OBJECT
public:
  explicit LasParser(QObject *parent = nullptr);

  /**
   * @brief clearLas  清空las
   */
  void clearLas();

  /**
   * @brief createPresetLas 创建默认las
   */
  void createPresetLas();

  /**
   * @brief setDataHead   设置las数据表头
   * @param head          表头
   */
  void setDataHead(const QStringList &head);

  /**
   * @brief addData   添加一组数据
   * @param data      数据
   */
  void addData(const QVector<double> &data);

  /**
   * @brief addMultiData  添加多组数据
   * @param datas
   */
  void addMultiData(const QVector<QVector<double>> &datas);

  /**
   * @brief addInfo 添加一组信息
   * @param info    信息
   */
  void addInfo(const Las::LasInfo &info = Las::LasInfo());

  /**
   * @brief addInfoField  往信息中添加字段
   * @param section       信息类型
   * @param field         字段
   */
  void addInfoField(const Las::LasInfoType &section, const Las::LasField &field = Las::LasField("UNKNOW"));

  /**
   * @brief deleteInfo  删除信息
   * @param section     信息类型
   */
  void deleteInfo(const Las::LasInfoType &section);

  /**
   * @brief deleteInfoField 删除信息中的字段
   * @param section         信息类型
   * @param field           字段名
   */
  void deleteInfoField(const Las::LasInfoType &section, const QString &field);

  /**
   * @brief changeInfoField 修改信息中的字段
   * @param section         信息类型
   * @param field           字段名
   * @param unit            单位
   * @param value           值
   * @param description     描述
   */
  void changeInfoField(const Las::LasInfoType &section, const QString &field, const Las::LasUnit &unit,
                       const QVariant &value, const QString &description);

  /**
   * @brief changeInfoFieldValue 修改信息中的字段值
   * @param section              信息类型
   * @param field                字段名
   * @param value                值
   */
  void changeInfoFieldValue(const Las::LasInfoType &section, const QString &field,
                            const QVariant &value);

  /**
   * @brief getInfoSectionKeys  获取全部信息类型
   * @return
   */
  QList<Las::LasInfoType> getInfoSectionKeys() const;

  /**
   * @brief getInfoSectionFields  获取一个信息类型中的全部字段
   * @param section               信息类型
   * @return
   */
  QList<Las::LasField> getInfoSectionFields(const Las::LasInfoType &section) const;

  /**
   * @brief getInfoSections 获取所有信息
   * @return
   */
  QList<Las::LasInfo> getInfoSections() const;

  /**
   * @brief getDatas 获取数据
   * @return         将数据分为4096行数据一组
   */
  QList<QVector<QVector<double>> > getDatas();


  /**
   * @brief saveFile  保存las文件
   * @param fileName  文件名
   * @return
   */
  bool exportFile(const QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                                                                      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).append("\\").append(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss").append(".las")),
                                                                      tr("Las (*.las)")));

  /**
   * @brief importFile 导入las文件
   * @param fileName   文件名
   * @return
   */
  bool importFile(const QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                                        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                                        tr("Las (*.las)")));
  /**
   * @brief importString  从字符串中导入las
   * @param str           字符串
   */
  void importString(const QString &str);

  QString toString() {
    QString str;
    str.append(m_head.toString());

    foreach (Las::LasInfoType key, m_infos.keys()) {
      QList<Las::LasInfo> values = m_infos[key];

      for(int i = 0; i < values.size(); ++i) {
        str.append(values[i].toString());
      }
    }

    str.append(m_data.toString());

    return str;
  }

private:
  void parseStr(const QString &str);

  void parseVersionHead(const QString &str);

  void parseInfo(const Las::LasInfoType &type, const QString &str);

  void parseData(const QString &str);

signals:

public slots:


private:
  Las::LasData  m_data;
  Las::LasV     m_head;
  QMap<Las::LasInfoType, QList<Las::LasInfo> > m_infos;

};

#endif // LASPARSER_H
