#ifndef TOOLPARAMETERS_H
#define TOOLPARAMETERS_H

#include "../../common/base/basecommon.h"

static QStringList TOOL_CATEGORY = QStringList{"Processor","Pulsing","Directional","Gamma","Resistivity",
    "Drilling Efficiency","Density","Porosity","Battery","Rotary Steerable","FTWD"};

static QMap<QString,QString> TOOL_TYPE = QMap<QString,QString>{{"HCIM","u_hcim"},{"ABI","u_abi"}};

class ToolParameters : public BaseCommon
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( QString tool_category READ getToolCategory WRITE setToolCategory)
  Q_PROPERTY( QString tool_type READ getToolType WRITE setToolType)
  Q_PROPERTY( QString table_name READ getTableName WRITE setTableName)

public:
  ToolParameters();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  QString getToolCategory() const;
  void setToolCategory(const QString &value);

  QString getToolType() const;
  void setToolType(const QString &value);

  QString getTableName() const;
  void setTableName(const QString &value);

private:
  int id = 0;
  int wellInfoId;
  int runInfoId;
  QString toolCategory;
  QString toolType;
  QString tableName;
};

#endif // TOOLPARAMETERS_H
