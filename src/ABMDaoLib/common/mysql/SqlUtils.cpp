#include "SqlUtils.h"

SqlUtils::SqlUtils(QString databaseName,QString userName,QString password,
                   QString host,int port,QObject *parent) :
  QObject(parent),
  m_sqlQuery(nullptr)
{
  m_database = QSqlDatabase::addDatabase("QMYSQL");
  m_database.setHostName(host);
  m_database.setDatabaseName(databaseName);
  m_database.setUserName(userName);
  m_database.setPassword(password);
  m_database.setPort(port);
}

SqlUtils::SqlUtils(const SqlLocationType &type, QString databaseName,QString userName,QString password,
                   QString host,int port,QObject *parent) {
  if (type == SqlLocationType::Sqldefault) {
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    m_database.setHostName(host);
    m_database.setDatabaseName(databaseName);
    m_database.setUserName(userName);
    m_database.setPassword(password);
    m_database.setPort(port);
  } else if (type == SqlLocationType::SqlWell){
    m_database = QSqlDatabase::addDatabase("QMYSQL", "well");
    m_database.setHostName(host);
    m_database.setDatabaseName(databaseName);
    m_database.setUserName(userName);
    m_database.setPassword(password);
    m_database.setPort(port);
  } else if (type == SqlLocationType::SqlRun){
    m_database = QSqlDatabase::addDatabase("QMYSQL", "run");
    m_database.setHostName(host);
    m_database.setDatabaseName(databaseName);
    m_database.setUserName(userName);
    m_database.setPassword(password);
    m_database.setPort(port);
  }
}

std::shared_ptr<SqlUtils> SqlUtils::create(const SqlLocationType &type, QString databaseName,QString userName,QString password,
                 QString host,int port,QObject *parent) {
  std::shared_ptr<SqlUtils> res(new SqlUtils(type, databaseName, userName, password, host, port, parent));
  return res;
};

SqlUtils::~SqlUtils()
{
  if(!m_sqlQuery){
    delete  m_sqlQuery;
  }

  m_database.close();
}

bool SqlUtils::connectDatabase()
{
  if (!m_database.open()){
    qDebug() << "Error: Failed to connect database." << m_database.lastError();
    return false;
  } else {
    m_sqlQuery = new QSqlQuery(m_database);
  }
  return true;
}

bool SqlUtils::createTable(const QString &tableName, const QMap<QString, SqlDataType> &datas, const QString &primaryKey)
{
  QString sqlStr = QString("create table if not exists %1 (").arg(tableName);

  for(auto it = datas.cbegin(); it != datas.cend(); ++it){
    sqlStr.append(QString("`%1` %2,").arg(it.key()).arg(typeToString(it.value())));
  }

  if(!primaryKey.isEmpty()){
    sqlStr.append(QString("PRIMARY KEY (%1)").arg(primaryKey));
  } else {
    sqlStr.remove(-1,1);
  }

  sqlStr.append(");");

  return execSql(sqlStr);
}

bool SqlUtils::insertValue(const QString &tableName, QMap<QString, QVariant> &datas, const bool replace)
{
  if(datas.isEmpty()) {return false;}

  QStringList keyList;
  QStringList valueList;
  for(auto it = datas.cbegin(); it != datas.cend(); ++it){
    keyList << QString("`%1`").arg(it.key());

    valueList << this->judgeInsertValue(it.value());
  }

  QString sqlStr;
  if(replace) {
    sqlStr = QString("replace into ");
  } else {
    sqlStr = QString("insert into ");
  }

  sqlStr.append(tableName);
  sqlStr.append(QString("(%1) VALUES").arg(keyList.join(',')));
  sqlStr.append(QString("(%1);").arg(valueList.join(',')));

  if(execSql(sqlStr)){
    datas["id"] = m_sqlQuery->lastInsertId();
    return true;
  }else{
    return false;
  }
}

bool SqlUtils::insertValues(const QString &tableName, const QVector<QMap<QString, QVariant> > &datas, const bool replace, QStringList keyList)
{
  if(datas.isEmpty()) {return false;}

  if(keyList.isEmpty()) {
      keyList = datas[0].keys();
  }
  //防止关键字报错
  foreach (QString key, keyList) {
    key = QString("`%1`").arg(key);
  }

  QStringList valueList;
  for(int i = 0; i < datas.size(); ++i) {
    QStringList onceValueList;

    foreach (QString var, keyList) {
      QVariant value = datas[i][var];

      onceValueList << this->judgeInsertValue(value);
    }
    valueList.append(QString("(%1)").arg(onceValueList.join(',')));
  }

  QString sqlStr;
  if(replace) {
    sqlStr = QString("replace into ");
  } else {
    sqlStr = QString("insert into ");
  }

  sqlStr.append(tableName);
  sqlStr.append(QString("(%1) VALUES").arg(keyList.join(',')));
  sqlStr.append(QString("%1;").arg(valueList.join(',')));

  return execSql(sqlStr);
}

bool SqlUtils::updateValue(const QString &tableName, const QMap<QString, QVariant> &datas, const QVector<SqlCondition> &conditions)
{
  if(datas.isEmpty()) {return false;}

  QStringList keyValueList;

  for(auto it = datas.cbegin(); it != datas.cend(); ++it){
    QString keyValue = this->judgeUpdateValue(it.key(),it.value());
    if(keyValue == nullptr){
      continue;
    }
    keyValueList << keyValue;
  }

  QString sqlStr = QString("UPDATE %1 SET ").arg(tableName);
  sqlStr.append(keyValueList.join(','));
  sqlStr.append(conditionsToString(conditions));

  return execSql(sqlStr.append(';'));
}

bool SqlUtils::deleteValue(const QString &tableName, const QVector<SqlCondition> &conditions)
{
  QString sqlStr = QString("DELETE FROM %1").arg(tableName);
  sqlStr.append(conditionsToString(conditions));
  return execSql(sqlStr.append(';'));
}

int SqlUtils::count(const QString &tableName, const QVector<SqlCondition> &conditions)
{
  QString sqlStr = QString("SELECT COUNT(*) FROM %1").arg(tableName);
  sqlStr.append(conditionsToString(conditions));

  if(execSql(sqlStr.append(';'))){
    while (m_sqlQuery->next()) {
      return m_sqlQuery->value(0).toInt();
    }
  } else {
    return 0;
  }
}

bool SqlUtils::queryDatas(const QString &tableName, const QVector<SqlCondition> &conditions, QList<QMap<QString, QVariant> > &resultDatas)
{
  QString sqlStr = QString("SELECT * FROM %1").arg(tableName);
  sqlStr.append(conditionsToString(conditions));

  if(execSql(sqlStr.append(';'))){
    QStringList fieldNames;
    QSqlRecord record = m_sqlQuery->record();

    int recordSize = record.count();
    for(int i = 0; i < recordSize; ++i){
      fieldNames << record.fieldName(i);
    }

    while(m_sqlQuery->next()){
      QMap<QString, QVariant> onceValue;
      foreach (QString var, fieldNames) {
        onceValue[var] = m_sqlQuery->value(var);
      }

      resultDatas.append(onceValue);
    }

    return true;
  } else {
    return false;
  }
}

bool SqlUtils::queryPage(const QString &tableName, const QVector<SqlCondition> &conditions, const int pageSize, const int pageNum, SqlPage &pageData)
{
  QString sqlStr = QString("SELECT * FROM %1").arg(tableName);
  sqlStr.append(conditionsToString(conditions));
  sqlStr.append(QString(" LIMIT %1,%2;").arg((pageNum - 1)*pageSize).arg(pageSize));

  if(execSql(sqlStr.append(';'))){
    QStringList fieldNames;
    QSqlRecord record = m_sqlQuery->record();

    int recordSize = record.count();
    for(int i = 0; i < recordSize; ++i){
      fieldNames << record.fieldName(i);
    }

    while(m_sqlQuery->next()){
      QMap<QString, QVariant> onceValue;
      foreach (QString var, fieldNames) {
        onceValue[var] = m_sqlQuery->value(var);
      }

      pageData.dataList.append(onceValue);
    }

    int count = this->count(tableName,conditions);
    pageData.pageNum = pageNum;
    pageData.pageSize = pageSize;
    pageData.totalPage = (int)ceil((double)count/pageSize);

    return true;
  } else {
    return false;
  }
}

bool SqlUtils::queryOne(const QString &tableName, const QVector<SqlCondition> &conditions, QMap<QString, QVariant> &resultData)
{
  QString sqlStr = QString("SELECT * FROM %1").arg(tableName);
  sqlStr.append(conditionsToString(conditions));

  if(execSql(sqlStr.append(';'))){
    QStringList fieldNames;
    QSqlRecord record = m_sqlQuery->record();

    int recordSize = record.count();
    for(int i = 0; i < recordSize; ++i){
      fieldNames << record.fieldName(i);
    }

    while(m_sqlQuery->next()){
      foreach (QString var, fieldNames) {
        resultData[var] = m_sqlQuery->value(var);
      }
      break;
    }

    return true;
  } else {
    return false;
  }
}

QString SqlUtils::typeToString(const SqlDataType type)
{
  switch (type) {
  case SqlInt:
    return "int";
  case SqlDouble:
    return "double";
  case SqlString:
    return "varchar(255)";
  case SqlDateTime:
    return "datetime";
  default:
    return "text";
  }
}

QString SqlUtils::conditionsToString(const QVector<SqlCondition> &conditions)
{
  if(conditions.isEmpty()){return QString();}

  QString str = " WHERE ";

  for(int i = 0; i < conditions.size(); ++i){
    if(i > 0){
      str.append(static_cast<SqlCondition>(conditions.at(i)).toString(true));
    } else {
      str.append(static_cast<SqlCondition>(conditions.at(i)).toString(false));
    }
  }

  return str;
}

bool SqlUtils::execSql(const QString &sqlStr)
{
  qDebug() << sqlStr;
  m_sqlQuery->prepare(sqlStr);

  if(!m_sqlQuery->exec())
  {
    qDebug() << "Error: Fail to create table." << m_sqlQuery->lastError();
    return false;
  }
  return true;
}

QString SqlUtils::judgeInsertValue(QVariant value)
{
  switch (value.type()) {
    case QVariant::String:{
      return QString("'%1'").arg(value.toString());
    }
    case QVariant::DateTime:{
      if(value.toDateTime().isValid()){
        return QString("'%1'").arg(value.toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
      }else{
        return "null";
      }
    }
    default:
      return value.toString();
  }
}

QString SqlUtils::judgeUpdateValue(QString key,QVariant value)
{
    switch (value.type()) {
      case QVariant::String:{
        if(value.isNull()){
//          qDebug() << key;
          return nullptr;
        }
        return QString(" `%1` = '%2' ").arg(key).arg(value.toString());
      }
      case QVariant::DateTime:{
        if(value.toDateTime().isValid()){
          return QString(" `%1` = '%2' ").arg(key).arg(value.toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }else{
          return nullptr;
        }
      }
      default:
        return QString(" `%1` = %2 ").arg(key).arg(value.toString());
    }
}

SqlCondition::SqlCondition()
{
}

SqlCondition::SqlCondition(const SqlOperator _sqlOperator, const QString _key, const QVariant _value, const bool _isAnd, const QVariant _expand)
  :sqlOperator(_sqlOperator), key(_key), value(_value), isAnd(_isAnd), expand(_expand)
{
}

QString SqlCondition::operatorToString()
{
  QString operatorStr;

  switch (sqlOperator) {
  case SqlEqual:
    operatorStr = "=";
    break;
  case SqlNoEqual:
    operatorStr = "<>";
    break;
  case SqlGT:
    operatorStr = ">";
    break;
  case SqlLT:
    operatorStr = "<";
    break;
  case SqlGTE:
    operatorStr = ">=";
    break;
  case SqlLTE:
    operatorStr = "<=";
    break;
  case SqlLike:{
    if(expand.canConvert<SqlLikeType>()) {
      switch (expand.value<SqlLikeType>()) {
      case SqlLikeFront:
        return QString(" `%1` LIKE '%2%' ").arg(key).arg(value.toString());
      case SqlLikeMid:
        return QString(" `%1` LIKE '%%2%' ").arg(key).arg(value.toString());
      case SqlLikeBack:
        return QString(" `%1` LIKE '%%2' ").arg(key).arg(value.toString());
      }

    } else {
      operatorStr = "LIKE";
      break;
    }
  } case SqlBetween :
    if(value.type() == QVariant::String){
      return QString(" `%1` BETWEEN '%2' AND '%3' ").arg(key).arg(value.toString()).arg(expand.toString());
    } else {
      return QString(" `%1` BETWEEN %2 AND %3 ").arg(key).arg(value.toString()).arg(expand.toString());
    }
  }

  if(value.type() == QVariant::String){
    return QString(" `%1` %2 '%3' ").arg(key).arg(operatorStr).arg(value.toString());
  } else {
    return QString(" `%1` %2 %3 ").arg(key).arg(operatorStr).arg(value.toString());
  }
}

QString SqlCondition::toString(const bool showConjunction)
{
  QString resultStr;
  if(showConjunction){
    if(isAnd){
      resultStr.append(" AND ");
    } else {
      resultStr.append(" OR ");
    }
  }

  return resultStr.append(operatorToString());
}
