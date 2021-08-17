#include "pospulser.h"

PosPulser::PosPulser()
{

}

int PosPulser::getId() const
{
  return id;
}

void PosPulser::setId(int value)
{
  id = value;
}

int PosPulser::getRunInfoId() const
{
  return runInfoId;
}

void PosPulser::setRunInfoId(int value)
{
  runInfoId = value;
}

int PosPulser::getWellInfoId() const
{
  return wellInfoId;
}

void PosPulser::setWellInfoId(int value)
{
  wellInfoId = value;
}

QString PosPulser::getHochosSN() const
{
  return hochosSN;
}

void PosPulser::setHochosSN(const QString &value)
{
  hochosSN = value;
}

QString PosPulser::getPulserSN() const
{
  return pulserSN;
}

void PosPulser::setPulserSN(const QString &value)
{
  pulserSN = value;
}

QString PosPulser::getNmdcSN() const
{
  return nmdcSN;
}

void PosPulser::setNmdcSN(const QString &value)
{
  nmdcSN = value;
}

double PosPulser::getStatorAngle() const
{
  return statorAngle;
}

void PosPulser::setStatorAngle(double value)
{
  statorAngle = value;
}

double PosPulser::getImpellerAngle() const
{
  return impellerAngle;
}

void PosPulser::setImpellerAngle(double value)
{
  impellerAngle = value;
}

double PosPulser::getOrificeSize() const
{
  return orificeSize;
}

void PosPulser::setOrificeSize(double value)
{
  orificeSize = value;
}

double PosPulser::getStandoffSize() const
{
  return standoffSize;
}

void PosPulser::setStandoffSize(double value)
{
  standoffSize = value;
}

QString PosPulser::getPulserName() const
{
  return pulserName;
}

void PosPulser::setPulserName(const QString &value)
{
  pulserName = value;
}

QString PosPulser::getOilType() const
{
  return oilType;
}

void PosPulser::setOilType(const QString &value)
{
  oilType = value;
}
