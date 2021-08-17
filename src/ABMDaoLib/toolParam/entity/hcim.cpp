#include "hcim.h"

HCIM::HCIM()
{

}

int HCIM::getId() const
{
  return id;
}

void HCIM::setId(int value)
{
  id = value;
}

int HCIM::getWellInfoId() const
{
  return wellInfoId;
}

void HCIM::setWellInfoId(int value)
{
  wellInfoId = value;
}

int HCIM::getRunInfoId() const
{
  return runInfoId;
}

void HCIM::setRunInfoId(int value)
{
  runInfoId = value;
}

QString HCIM::getSWVersion() const
{
  return SWVersion;
}

void HCIM::setSWVersion(const QString &value)
{
  SWVersion = value;
}

QString HCIM::getHCIMType() const
{
  return HCIMType;
}

void HCIM::setHCIMType(const QString &value)
{
  HCIMType = value;
}

QString HCIM::getHSCMemoryType() const
{
  return HSCMemoryType;
}

void HCIM::setHSCMemoryType(const QString &value)
{
  HSCMemoryType = value;
}

QString HCIM::getSubSN() const
{
  return subSN;
}

void HCIM::setSubSN(const QString &value)
{
  subSN = value;
}

QString HCIM::getBatterySN() const
{
  return batterySN;
}

void HCIM::setBatterySN(const QString &value)
{
  batterySN = value;
}

QString HCIM::getHangerSN() const
{
  return hangerSN;
}

void HCIM::setHangerSN(const QString &value)
{
  hangerSN = value;
}

QDateTime HCIM::getInitialzation() const
{
  return initialzation;
}

void HCIM::setInitialzation(const QDateTime &value)
{
  initialzation = value;
}

QDateTime HCIM::getReadTime() const
{
  return readTime;
}

void HCIM::setReadTime(const QDateTime &value)
{
  readTime = value;
}

double HCIM::getCurrentUsage() const
{
  return currentUsage;
}

void HCIM::setCurrentUsage(double value)
{
  currentUsage = value;
}

double HCIM::getSMICurrentUsage() const
{
  return SMICurrentUsage;
}

void HCIM::setSMICurrentUsage(double value)
{
  SMICurrentUsage = value;
}

QString HCIM::getAzimuthalRefe() const
{
  return azimuthalRefe;
}

void HCIM::setAzimuthalRefe(const QString &value)
{
  azimuthalRefe = value;
}

QString HCIM::getECMBBoardName() const
{
  return ECMBBoardName;
}

void HCIM::setECMBBoardName(const QString &value)
{
  ECMBBoardName = value;
}

QString HCIM::getECMBIpAddress() const
{
  return ECMBIpAddress;
}

void HCIM::setECMBIpAddress(const QString &value)
{
  ECMBIpAddress = value;
}
