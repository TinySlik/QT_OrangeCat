#include "abi.h"

ABI::ABI()
{

}

int ABI::getId() const
{
  return id;
}

void ABI::setId(int value)
{
  id = value;
}

int ABI::getWellInfoId() const
{
  return wellInfoId;
}

void ABI::setWellInfoId(int value)
{
  wellInfoId = value;
}

int ABI::getRunInfoId() const
{
  return runInfoId;
}

void ABI::setRunInfoId(int value)
{
  runInfoId = value;
}

double ABI::getDistFrom() const
{
  return distFrom;
}

void ABI::setDistFrom(double value)
{
  distFrom = value;
}

QString ABI::getSWVersion() const
{
  return SWVersion;
}

void ABI::setSWVersion(const QString &value)
{
  SWVersion = value;
}

QString ABI::getReceiverSN() const
{
  return receiverSN;
}

void ABI::setReceiverSN(const QString &value)
{
  receiverSN = value;
}

QString ABI::getReceiverVersion() const
{
  return receiverVersion;
}

void ABI::setReceiverVersion(const QString &value)
{
  receiverVersion = value;
}

QString ABI::getReceiverTXSN() const
{
  return receiverTXSN;
}

void ABI::setReceiverTXSN(const QString &value)
{
  receiverTXSN = value;
}

QString ABI::getReceiverGMSN() const
{
  return receiverGMSN;
}

void ABI::setReceiverGMSN(const QString &value)
{
  receiverGMSN = value;
}

QString ABI::getReceiverB1SN() const
{
  return receiverB1SN;
}

void ABI::setReceiverB1SN(const QString &value)
{
  receiverB1SN = value;
}

QString ABI::getReceiverB2SN() const
{
  return receiverB2SN;
}

void ABI::setReceiverB2SN(const QString &value)
{
  receiverB2SN = value;
}

QString ABI::getTransmitterSN() const
{
  return transmitterSN;
}

void ABI::setTransmitterSN(const QString &value)
{
  transmitterSN = value;
}

QString ABI::getTransmitterVersion() const
{
  return transmitterVersion;
}

void ABI::setTransmitterVersion(const QString &value)
{
  transmitterVersion = value;
}

QString ABI::getInserterSN() const
{
  return inserterSN;
}

void ABI::setInserterSN(const QString &value)
{
  inserterSN = value;
}

QString ABI::getInserterPreAMPSN() const
{
  return inserterPreAMPSN;
}

void ABI::setInserterPreAMPSN(const QString &value)
{
  inserterPreAMPSN = value;
}

QString ABI::getInserterRXSN() const
{
  return inserterRXSN;
}

void ABI::setInserterRXSN(const QString &value)
{
  inserterRXSN = value;
}

QString ABI::getInserterRTCSN() const
{
  return inserterRTCSN;
}

void ABI::setInserterRTCSN(const QString &value)
{
  inserterRTCSN = value;
}

double ABI::getIVSSModerateAvg() const
{
  return IVSSModerateAvg;
}

void ABI::setIVSSModerateAvg(double value)
{
  IVSSModerateAvg = value;
}

double ABI::getIVSSModerateShock() const
{
  return IVSSModerateShock;
}

void ABI::setIVSSModerateShock(double value)
{
  IVSSModerateShock = value;
}

double ABI::getIVSSHighAvg() const
{
  return IVSSHighAvg;
}

void ABI::setIVSSHighAvg(double value)
{
  IVSSHighAvg = value;
}

double ABI::getIVSSHighShock() const
{
  return IVSSHighShock;
}

void ABI::setIVSSHighShock(double value)
{
  IVSSHighShock = value;
}

double ABI::getIVSSExcessiveAvg() const
{
  return IVSSExcessiveAvg;
}

void ABI::setIVSSExcessiveAvg(double value)
{
  IVSSExcessiveAvg = value;
}

double ABI::getIVSSExcessiveShock() const
{
  return IVSSExcessiveShock;
}

void ABI::setIVSSExcessiveShock(double value)
{
  IVSSExcessiveShock = value;
}

