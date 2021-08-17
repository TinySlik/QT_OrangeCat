#include "pcd.h"

PCD::PCD()
{

}

int PCD::getId() const
{
  return id;
}

void PCD::setId(int value)
{
  id = value;
}

int PCD::getWellInfoId() const
{
  return wellInfoId;
}

void PCD::setWellInfoId(int value)
{
  wellInfoId = value;
}

int PCD::getRunInfoId() const
{
  return runInfoId;
}

void PCD::setRunInfoId(int value)
{
  runInfoId = value;
}

double PCD::getDistFrom() const
{
  return distFrom;
}

void PCD::setDistFrom(double value)
{
  distFrom = value;
}

QString PCD::getSurveyType() const
{
  return surveyType;
}

void PCD::setSurveyType(const QString &value)
{
  surveyType = value;
}

QString PCD::getProbeVariant() const
{
  return probeVariant;
}

void PCD::setProbeVariant(const QString &value)
{
  probeVariant = value;
}

QString PCD::getHocSN() const
{
  return hocSN;
}

void PCD::setHocSN(const QString &value)
{
  hocSN = value;
}

QString PCD::getProbeSN() const
{
  return probeSN;
}

void PCD::setProbeSN(const QString &value)
{
  probeSN = value;
}

QString PCD::getAnalogBoardSN() const
{
  return analogBoardSN;
}

void PCD::setAnalogBoardSN(const QString &value)
{
  analogBoardSN = value;
}

QDateTime PCD::getBatteryDate() const
{
  return batteryDate;
}

void PCD::setBatteryDate(const QDateTime &value)
{
  batteryDate = value;
}

QString PCD::getGxAccelSN() const
{
  return gxAccelSN;
}

void PCD::setGxAccelSN(const QString &value)
{
  gxAccelSN = value;
}

QString PCD::getGyAccelSN() const
{
  return gyAccelSN;
}

void PCD::setGyAccelSN(const QString &value)
{
  gyAccelSN = value;
}

QString PCD::getGzAccelSN() const
{
  return gzAccelSN;
}

void PCD::setGzAccelSN(const QString &value)
{
  gzAccelSN = value;
}

QString PCD::getProbeSoftware() const
{
  return probeSoftware;
}

void PCD::setProbeSoftware(const QString &value)
{
  probeSoftware = value;
}

QString PCD::getPicVersion() const
{
  return picVersion;
}

void PCD::setPicVersion(const QString &value)
{
  picVersion = value;
}

int PCD::getMagneticFieldStrength() const
{
  return magneticFieldStrength;
}

void PCD::setMagneticFieldStrength(int value)
{
  magneticFieldStrength = value;
}

double PCD::getMagneticDipAngle() const
{
  return magneticDipAngle;
}

void PCD::setMagneticDipAngle(double value)
{
  magneticDipAngle = value;
}

double PCD::getGravityFieldStrength() const
{
  return gravityFieldStrength;
}

void PCD::setGravityFieldStrength(double value)
{
  gravityFieldStrength = value;
}

double PCD::getTotalCorrection() const
{
  return totalCorrection;
}

void PCD::setTotalCorrection(double value)
{
  totalCorrection = value;
}

QString PCD::getNorthReference() const
{
  return northReference;
}

void PCD::setNorthReference(const QString &value)
{
  northReference = value;
}

QString PCD::getMagneticChecksum() const
{
  return magneticChecksum;
}

void PCD::setMagneticChecksum(const QString &value)
{
  magneticChecksum = value;
}

double PCD::getTotalOffset() const
{
  return totalOffset;
}

void PCD::setTotalOffset(double value)
{
  totalOffset = value;
}

double PCD::getHsgOffset() const
{
  return hsgOffset;
}

void PCD::setHsgOffset(double value)
{
  hsgOffset = value;
}

double PCD::getRigFloorOffset() const
{
  return rigFloorOffset;
}

void PCD::setRigFloorOffset(double value)
{
  rigFloorOffset = value;
}

double PCD::getAzimuthLow() const
{
  return azimuthLow;
}

void PCD::setAzimuthLow(double value)
{
  azimuthLow = value;
}

double PCD::getAzimuthHigh() const
{
  return azimuthHigh;
}

void PCD::setAzimuthHigh(double value)
{
  azimuthHigh = value;
}

double PCD::getInclinationLow() const
{
  return inclinationLow;
}

void PCD::setInclinationLow(double value)
{
  inclinationLow = value;
}

double PCD::getInclinationHigh() const
{
  return inclinationHigh;
}

void PCD::setInclinationHigh(double value)
{
  inclinationHigh = value;
}

double PCD::getTfGravLow() const
{
  return tfGravLow;
}

void PCD::setTfGravLow(double value)
{
  tfGravLow = value;
}

double PCD::getTfGravHigh() const
{
  return tfGravHigh;
}

void PCD::setTfGravHigh(double value)
{
  tfGravHigh = value;
}

double PCD::getTfMagLow() const
{
  return tfMagLow;
}

void PCD::setTfMagLow(double value)
{
  tfMagLow = value;
}

double PCD::getTfMagHigh() const
{
  return tfMagHigh;
}

void PCD::setTfMagHigh(double value)
{
  tfMagHigh = value;
}

double PCD::getDipCalcLow() const
{
  return dipCalcLow;
}

void PCD::setDipCalcLow(double value)
{
  dipCalcLow = value;
}

double PCD::getDipCalcHigh() const
{
  return dipCalcHigh;
}

void PCD::setDipCalcHigh(double value)
{
  dipCalcHigh = value;
}

double PCD::getDipMeasLow() const
{
  return dipMeasLow;
}

void PCD::setDipMeasLow(double value)
{
  dipMeasLow = value;
}

double PCD::getDipMeasHigh() const
{
  return dipMeasHigh;
}

void PCD::setDipMeasHigh(double value)
{
  dipMeasHigh = value;
}

double PCD::getGTotalLow() const
{
  return gTotalLow;
}

void PCD::setGTotalLow(double value)
{
  gTotalLow = value;
}

double PCD::getGTotalHigh() const
{
  return gTotalHigh;
}

void PCD::setGTotalHigh(double value)
{
  gTotalHigh = value;
}

int PCD::getBtCalcLow() const
{
  return btCalcLow;
}

void PCD::setBtCalcLow(int value)
{
  btCalcLow = value;
}

int PCD::getBtCalcHigh() const
{
  return btCalcHigh;
}

void PCD::setBtCalcHigh(int value)
{
  btCalcHigh = value;
}

int PCD::getBtMeasLow() const
{
  return btMeasLow;
}

void PCD::setBtMeasLow(int value)
{
  btMeasLow = value;
}

int PCD::getBtMeasHigh() const
{
  return btMeasHigh;
}

void PCD::setBtMeasHigh(int value)
{
  btMeasHigh = value;
}

QDateTime PCD::getInitialisTime() const
{
  return initialisTime;
}

void PCD::setInitialisTime(const QDateTime &value)
{
  initialisTime = value;
}

QDateTime PCD::getReadTime() const
{
  return readTime;
}

void PCD::setReadTime(const QDateTime &value)
{
  readTime = value;
}

double PCD::getSvssLogPeriod() const
{
  return svssLogPeriod;
}

void PCD::setSvssLogPeriod(double value)
{
  svssLogPeriod = value;
}

double PCD::getModerateXAvg() const
{
  return moderateXAvg;
}

void PCD::setModerateXAvg(double value)
{
  moderateXAvg = value;
}

double PCD::getModerateZAvg() const
{
  return moderateZAvg;
}

void PCD::setModerateZAvg(double value)
{
  moderateZAvg = value;
}

double PCD::getHighXAvg() const
{
  return highXAvg;
}

void PCD::setHighXAvg(double value)
{
  highXAvg = value;
}

double PCD::getHighZAvg() const
{
  return highZAvg;
}

void PCD::setHighZAvg(double value)
{
  highZAvg = value;
}

double PCD::getExcessiveXAvg() const
{
  return excessiveXAvg;
}

void PCD::setExcessiveXAvg(double value)
{
  excessiveXAvg = value;
}

double PCD::getExcessiveZAvg() const
{
  return excessiveZAvg;
}

void PCD::setExcessiveZAvg(double value)
{
  excessiveZAvg = value;
}

double PCD::getModerateXShock() const
{
  return moderateXShock;
}

void PCD::setModerateXShock(double value)
{
  moderateXShock = value;
}

double PCD::getModerateZShock() const
{
  return moderateZShock;
}

void PCD::setModerateZShock(double value)
{
  moderateZShock = value;
}

double PCD::getHighXShock() const
{
  return highXShock;
}

void PCD::setHighXShock(double value)
{
  highXShock = value;
}

double PCD::getHighZShock() const
{
  return highZShock;
}

void PCD::setHighZShock(double value)
{
  highZShock = value;
}

double PCD::getExcessiveXShock() const
{
  return excessiveXShock;
}

void PCD::setExcessiveXShock(double value)
{
  excessiveXShock = value;
}

double PCD::getExcessiveZShock() const
{
  return excessiveZShock;
}

void PCD::setExcessiveZShock(double value)
{
  excessiveZShock = value;
}

double PCD::getDataRate1() const
{
  return dataRate1;
}

void PCD::setDataRate1(double value)
{
  dataRate1 = value;
}

double PCD::getDataRate2() const
{
  return dataRate2;
}

void PCD::setDataRate2(double value)
{
  dataRate2 = value;
}

double PCD::getDataRate3() const
{
  return dataRate3;
}

void PCD::setDataRate3(double value)
{
  dataRate3 = value;
}

QString PCD::getPcdToolMode() const
{
  return pcdToolMode;
}

void PCD::setPcdToolMode(const QString &value)
{
  pcdToolMode = value;
}

int PCD::getWaitPeriod() const
{
  return waitPeriod;
}

void PCD::setWaitPeriod(int value)
{
  waitPeriod = value;
}

int PCD::getAlarmPeriod() const
{
  return alarmPeriod;
}

void PCD::setAlarmPeriod(int value)
{
  alarmPeriod = value;
}

int PCD::getRuninPeriod() const
{
  return runinPeriod;
}

void PCD::setRuninPeriod(int value)
{
  runinPeriod = value;
}

double PCD::getTfCrossover() const
{
  return tfCrossover;
}

void PCD::setTfCrossover(double value)
{
  tfCrossover = value;
}
