#include "toolparameters.h"


ToolParameters::ToolParameters()
{

}

int ToolParameters::getId() const
{
  return id;
}

void ToolParameters::setId(int value)
{
  id = value;
}

int ToolParameters::getWellInfoId() const
{
  return wellInfoId;
}

void ToolParameters::setWellInfoId(int value)
{
  wellInfoId = value;
}

int ToolParameters::getRunInfoId() const
{
  return runInfoId;
}

void ToolParameters::setRunInfoId(int value)
{
  runInfoId = value;
}

QString ToolParameters::getToolCategory() const
{
  return toolCategory;
}

void ToolParameters::setToolCategory(const QString &value)
{
  toolCategory = value;
}

QString ToolParameters::getToolType() const
{
  return toolType;
}

void ToolParameters::setToolType(const QString &value)
{
  toolType = value;
}

QString ToolParameters::getTableName() const
{
  return tableName;
}

void ToolParameters::setTableName(const QString &value)
{
  tableName = value;
}
