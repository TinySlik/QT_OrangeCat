#ifndef SQLUTILS_H
#define SQLUTILS_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <QPair>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct SqlPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QMap<QString, QVariant>> dataList;
};

/**
 * @brief The SqlDataType enum  数据库数据枚举
 */
enum SqlDataType{
  SqlInt,
  SqlDouble,
  SqlString,
  SqlDateTime
};

enum SqlOperator{
  SqlEqual,     //等于
  SqlNoEqual,   //不等于
  SqlGT,        //大于
  SqlLT,        //小于
  SqlGTE,       //大于等于
  SqlLTE,       //小于等于
  SqlLike,      //在某个范围内
  SqlBetween    //搜索某种模式
};

enum SqlLikeType{
  SqlLikeFront, //以X开头
  SqlLikeMid,   //包含X
  SqlLikeBack   //以X结尾
};
Q_DECLARE_METATYPE(SqlLikeType)


struct SqlCondition{
  SqlOperator sqlOperator;  //操作符
  QString     key;          //字段名
  QVariant    value;        //值
  bool        isAnd;        //AND 还是 OR
  QVariant    expand;       //扩展，暂用于LIKE和BETWEEN
                            //LIKE: SqlLikeType匹配模式,若为空,则使用传入字符串
                            //SqlCondition condition(SqlLike,"name","aa",true,SqlLikeFront); -->name LIKE 'aa%'
                            //SqlCondition condition(SqlLike,"name","aa%",true);             --> name LIKE 'aa%'
                            //BETWEEN:传入的第二个参数

  SqlCondition();
  SqlCondition(const SqlOperator _sqlOperator, const QString _key, const QVariant _value,
               const bool _isAnd = true, const QVariant _expand = QVariant());

  QString operatorToString();

  QString toString(const bool showConjunction = true);
};



/**
 * @brief The SqlUtils class
 * Sqlit 数据库封装
 */
class SqlUtils : public QObject
{
  Q_OBJECT
public:
  explicit SqlUtils(QString databaseName,QString userName,QString password,
                    QString host = "localhost",int port = 3306,QObject *parent = nullptr);

  ~SqlUtils();

  /**
   * @brief connectDatabase 连接数据库
   * @return
   */
  bool connectDatabase();

  /**
   * @brief createTable 创表
   * @param tableName   表名
   * @param datas       字段数据：字段名，数据类型
   * @param primaryKey  主键名
   * @return
   */
  bool createTable(const QString &tableName, const QMap<QString,SqlDataType> &datas, const QString &primaryKey = "");

  /**
   * @brief insertValue 插入单条数据
   * @param tableName   表名
   * @param datas       字段数据：字段名，数据类型
   * @param replace     是否使用replace方式插入
   * @return
   */
  bool insertValue(const QString &tableName, QMap<QString, QVariant> &datas, const bool replace = false);

  /**
   * @brief insertValues  插入多条数据
   * @param tableName     表名
   * @param datas         字段数据数组：字段名，数据
   * @param keyList       字段名list， 若为空，则使用第一组数据的字段列表
   * @return
   */
  bool insertValues(const QString &tableName, const QVector<QMap<QString, QVariant>> &datas,
                    const bool replace = false, QStringList keyList = QStringList());

  /**
   * @brief updateValue   更新单条数据
   * @param tableName     表名
   * @param datas         字段数据数组:字段名，数据
   * @param conditions    条件数组,具体条件格式参考SqlCondition结构体
   * @return
   */
  bool updateValue(const QString &tableName, const QMap<QString,QVariant> &datas, const QVector<SqlCondition> &conditions);

  /**
   * @brief deleteValue   删除数据库数据
   * @param tableName     表名
   * @param conditions    条件数组,具体条件格式参考SqlCondition结构体
   * @return
   */
  bool deleteValue(const QString &tableName, const QVector<SqlCondition> &conditions);

  /**
   * @brief count       统计满足条件的数据数量
   * @param tableName   表名
   * @param conditions  条件数组,具体条件格式参考SqlCondition结构体
   * @return
   */
  int count(const QString &tableName, const QVector<SqlCondition> &conditions);

  /**
   * @brief queryDatas    数据库查询
   * @param tableName     表名
   * @param conditions    条件数组,具体条件格式参考SqlCondition结构体
   * @param resultDatas   查找结果引用
   * @return
   */
  bool queryDatas(const QString &tableName, const QVector<SqlCondition> &conditions, QList<QMap<QString, QVariant>> &resultDatas);

  /**
   * @brief queryPage     分页查询
   * @param tableName     表名
   * @param conditions    条件数组,具体条件格式参考SqlCondition结构体
   * @param pageSize      每页条数
   * @param pageNum       页码
   * @param pageData      查找结果引用
   * @return
   */
  bool queryPage(const QString &tableName, const QVector<SqlCondition> &conditions, const int pageSize, const int pageNum, SqlPage &pageData);

  /**
   * @brief queryOne      数据库查询
   * @param tableName     表名
   * @param conditions    条件数组,具体条件格式参考SqlCondition结构体
   * @param resultData    查找结果引用
   * @return
   */
  bool queryOne(const QString &tableName, const QVector<SqlCondition> &conditions, QMap<QString, QVariant> &resultData);

private:
  /**
   * @brief typeToString  数据库数据枚举转sql语句字符串
   * @param type          数据类型
   * @return
   */
  static QString typeToString(const SqlDataType type);

  /**
   * @brief conditionsToString  条件数组转字符串 where..............
   * @param conditions          条件数组
   * @return
   */
  static QString conditionsToString(const QVector<SqlCondition> &conditions);

  /**
   * @brief execSql   执行sql语句
   * @param sqlStr    sql语句字符串
   * @return
   */
  bool execSql(const QString &sqlStr);

  /**
   * @brief judgeInsertValue  判断插入的值
   * @param value
   */
  QString judgeInsertValue(QVariant value);

  /**
   * @brief judgeUpdateValue  判断更新的值
   * @param key
   * @param value
   */
  QString judgeUpdateValue(QString key, QVariant value);


signals:

public slots:

private:
  QSqlDatabase  m_database;
  QSqlQuery    *m_sqlQuery;
};

#endif // SQLUTILS_H
