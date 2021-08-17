#include "runinfogeneral.h"

RunInfoGeneral::RunInfoGeneral()
{

}

int RunInfoGeneral::getId() const
{
  return id;
}

void RunInfoGeneral::setId(int value)
{
  id = value;
}

int RunInfoGeneral::getWellInfoId() const
{
  return wellInfoId;
}

void RunInfoGeneral::setWellInfoId(int value)
{
  wellInfoId = value;
}

QString RunInfoGeneral::getRun() const
{
  return run;
}

void RunInfoGeneral::setRun(const QString &value)
{
  run = value;
}

QString RunInfoGeneral::getSsInsiteVersuib() const
{
  return ssInsiteVersuib;
}

void RunInfoGeneral::setSsInsiteVersuib(const QString &value)
{
  ssInsiteVersuib = value;
}

QString RunInfoGeneral::getIabcRigBhaNumber() const
{
  return iabcRigBhaNumber;
}

void RunInfoGeneral::setIabcRigBhaNumber(const QString &value)
{
  iabcRigBhaNumber = value;
}

double RunInfoGeneral::getHydrostaticOffset() const
{
  return hydrostaticOffset;
}

void RunInfoGeneral::setHydrostaticOffset(double value)
{
  hydrostaticOffset = value;
}

int RunInfoGeneral::getBhaType() const
{
  return bhaType;
}

void RunInfoGeneral::setBhaType(int value)
{
  bhaType = value;
}

QString RunInfoGeneral::getServices() const
{
  return services;
}

void RunInfoGeneral::setServices(const QString &value)
{
  services = value;
}

int RunInfoGeneral::getDrillOrWipe() const
{
  return drillOrWipe;
}

void RunInfoGeneral::setDrillOrWipe(int value)
{
  drillOrWipe = value;
}

double RunInfoGeneral::getTotalDepthAttempted() const
{
  return totalDepthAttempted;
}

void RunInfoGeneral::setTotalDepthAttempted(double value)
{
  totalDepthAttempted = value;
}

double RunInfoGeneral::getDepthLogged() const
{
  return depthLogged;
}

void RunInfoGeneral::setDepthLogged(double value)
{
  depthLogged = value;
}

double RunInfoGeneral::getDepthWiped() const
{
  return depthWiped;
}

void RunInfoGeneral::setDepthWiped(double value)
{
  depthWiped = value;
}

double RunInfoGeneral::getRunDepthRangeStart() const
{
  return runDepthRangeStart;
}

void RunInfoGeneral::setRunDepthRangeStart(double value)
{
  runDepthRangeStart = value;
}

double RunInfoGeneral::getRunDepthRangeEnd() const
{
  return runDepthRangeEnd;
}

void RunInfoGeneral::setRunDepthRangeEnd(double value)
{
  runDepthRangeEnd = value;
}

QDateTime RunInfoGeneral::getRunTimeRangeStart() const
{
  return runTimeRangeStart;
}

void RunInfoGeneral::setRunTimeRangeStart(const QDateTime &value)
{
  runTimeRangeStart = value;
}

QDateTime RunInfoGeneral::getRunTimeRangeEnd() const
{
  return runTimeRangeEnd;
}

void RunInfoGeneral::setRunTimeRangeEnd(const QDateTime &value)
{
  runTimeRangeEnd = value;
}

QDateTime RunInfoGeneral::getDrillingTimeRangeStart() const
{
  return drillingTimeRangeStart;
}

void RunInfoGeneral::setDrillingTimeRangeStart(const QDateTime &value)
{
  drillingTimeRangeStart = value;
}

QDateTime RunInfoGeneral::getDrillingTimeRangeEnd() const
{
  return drillingTimeRangeEnd;
}

void RunInfoGeneral::setDrillingTimeRangeEnd(const QDateTime &value)
{
  drillingTimeRangeEnd = value;
}

QDateTime RunInfoGeneral::getLogTimeRangeStart() const
{
  return logTimeRangeStart;
}

void RunInfoGeneral::setLogTimeRangeStart(const QDateTime &value)
{
  logTimeRangeStart = value;
}

QDateTime RunInfoGeneral::getLogTimeRangeEnd() const
{
  return logTimeRangeEnd;
}

void RunInfoGeneral::setLogTimeRangeEnd(const QDateTime &value)
{
  logTimeRangeEnd = value;
}

QString RunInfoGeneral::getMwdEngineers() const
{
  return mwdEngineers;
}

void RunInfoGeneral::setMwdEngineers(const QString &value)
{
  mwdEngineers = value;
}

QString RunInfoGeneral::getDirectionalDrillers() const
{
  return directionalDrillers;
}

void RunInfoGeneral::setDirectionalDrillers(const QString &value)
{
  directionalDrillers = value;
}

QString RunInfoGeneral::getSdlEngineers() const
{
  return sdlEngineers;
}

void RunInfoGeneral::setSdlEngineers(const QString &value)
{
  sdlEngineers = value;
}

QString RunInfoGeneral::getAdtEngineers() const
{
  return adtEngineers;
}

void RunInfoGeneral::setAdtEngineers(const QString &value)
{
  adtEngineers = value;
}

QString RunInfoGeneral::getCustomerRep() const
{
  return customerRep;
}

void RunInfoGeneral::setCustomerRep(const QString &value)
{
  customerRep = value;
}

QString RunInfoGeneral::getCustomerGeo() const
{
  return customerGeo;
}

void RunInfoGeneral::setCustomerGeo(const QString &value)
{
  customerGeo = value;
}

QString RunInfoGeneral::getResContactSpec() const
{
  return resContactSpec;
}

void RunInfoGeneral::setResContactSpec(const QString &value)
{
  resContactSpec = value;
}

QString RunInfoGeneral::getOtherEngineers() const
{
  return otherEngineers;
}

void RunInfoGeneral::setOtherEngineers(const QString &value)
{
  otherEngineers = value;
}
