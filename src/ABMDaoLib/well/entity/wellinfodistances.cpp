#include "wellinfodistances.h"

WellInfoDistances::WellInfoDistances()
{

}

int WellInfoDistances::getId() const
{
  return id;
}

void WellInfoDistances::setId(int value)
{
  id = value;
}

int WellInfoDistances::getWellInfoId() const
{
  return wellInfoId;
}

void WellInfoDistances::setWellInfoId(int value)
{
  wellInfoId = value;
}

double WellInfoDistances::getDrillFloor() const
{
  return drillFloor;
}

void WellInfoDistances::setDrillFloor(double value)
{
  drillFloor = value;
}

double WellInfoDistances::getGroundLevel() const
{
  return groundLevel;
}

void WellInfoDistances::setGroundLevel(double value)
{
  groundLevel = value;
}

double WellInfoDistances::getKellyBushing() const
{
  return kellyBushing;
}

void WellInfoDistances::setKellyBushing(double value)
{
  kellyBushing = value;
}

double WellInfoDistances::getWaterDepth() const
{
  return waterDepth;
}

void WellInfoDistances::setWaterDepth(double value)
{
  waterDepth = value;
}

double WellInfoDistances::getAirGap() const
{
  return airGap;
}

void WellInfoDistances::setAirGap(double value)
{
  airGap = value;
}

QString WellInfoDistances::getPermanentDatum() const
{
  return permanentDatum;
}

void WellInfoDistances::setPermanentDatum(const QString &value)
{
  permanentDatum = value;
}

double WellInfoDistances::getElevationOfPd() const
{
  return elevationOfPd;
}

void WellInfoDistances::setElevationOfPd(double value)
{
  elevationOfPd = value;
}

QString WellInfoDistances::getLogMeasuredFrom() const
{
  return logMeasuredFrom;
}

void WellInfoDistances::setLogMeasuredFrom(const QString &value)
{
  logMeasuredFrom = value;
}

double WellInfoDistances::getHeightAbovePd() const
{
  return heightAbovePd;
}

void WellInfoDistances::setHeightAbovePd(double value)
{
  heightAbovePd = value;
}

QString WellInfoDistances::getDrillingMeasuredFrom() const
{
  return drillingMeasuredFrom;
}

void WellInfoDistances::setDrillingMeasuredFrom(const QString &value)
{
  drillingMeasuredFrom = value;
}

QString WellInfoDistances::getLinesStrung() const
{
  return linesStrung;
}

void WellInfoDistances::setLinesStrung(const QString &value)
{
  linesStrung = value;
}

double WellInfoDistances::getMechanicalEfficency() const
{
  return mechanicalEfficency;
}

void WellInfoDistances::setMechanicalEfficency(double value)
{
  mechanicalEfficency = value;
}

double WellInfoDistances::getTvdssReference() const
{
  return tvdssReference;
}

void WellInfoDistances::setTvdssReference(double value)
{
  tvdssReference = value;
}

double WellInfoDistances::getTravBlockWeight() const
{
  return travBlockWeight;
}

void WellInfoDistances::setTravBlockWeight(double value)
{
  travBlockWeight = value;
}
