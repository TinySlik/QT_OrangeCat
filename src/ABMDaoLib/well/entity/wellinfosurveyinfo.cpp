#include "wellinfosurveyinfo.h"

WellInfoSurveyInfo::WellInfoSurveyInfo()
{

}

int WellInfoSurveyInfo::getId() const
{
  return id;
}

void WellInfoSurveyInfo::setId(int value)
{
  id = value;
}

int WellInfoSurveyInfo::getWellInfoId() const
{
  return wellInfoId;
}

void WellInfoSurveyInfo::setWellInfoId(int value)
{
  wellInfoId = value;
}

double WellInfoSurveyInfo::getVericalSectionDirection() const
{
  return vericalSectionDirection;
}

void WellInfoSurveyInfo::setVericalSectionDirection(double value)
{
  vericalSectionDirection = value;
}

int WellInfoSurveyInfo::getCalcVarticalSection() const
{
  return calcVarticalSection;
}

void WellInfoSurveyInfo::setCalcVarticalSection(int value)
{
  calcVarticalSection = value;
}

int WellInfoSurveyInfo::getHolePositionCalcMethod() const
{
  return holePositionCalcMethod;
}

void WellInfoSurveyInfo::setHolePositionCalcMethod(int value)
{
  holePositionCalcMethod = value;
}

double WellInfoSurveyInfo::getBulkDensity() const
{
  return bulkDensity;
}

void WellInfoSurveyInfo::setBulkDensity(double value)
{
  bulkDensity = value;
}

int WellInfoSurveyInfo::getGravityRefeCalcEnvironment() const
{
  return gravityRefeCalcEnvironment;
}

void WellInfoSurveyInfo::setGravityRefeCalcEnvironment(int value)
{
  gravityRefeCalcEnvironment = value;
}

double WellInfoSurveyInfo::getGravityFieldStrength() const
{
  return gravityFieldStrength;
}

void WellInfoSurveyInfo::setGravityFieldStrength(double value)
{
  gravityFieldStrength = value;
}

double WellInfoSurveyInfo::getMagneticFiledStrength() const
{
  return magneticFiledStrength;
}

void WellInfoSurveyInfo::setMagneticFiledStrength(double value)
{
  magneticFiledStrength = value;
}

QString WellInfoSurveyInfo::getMagneticModel() const
{
  return magneticModel;
}

void WellInfoSurveyInfo::setMagneticModel(const QString &value)
{
  magneticModel = value;
}

QDateTime WellInfoSurveyInfo::getMagneticDataDate() const
{
  return magneticDataDate;
}

void WellInfoSurveyInfo::setMagneticDataDate(const QDateTime &value)
{
  magneticDataDate = value;
}

QString WellInfoSurveyInfo::getMagneticFieldDataSource() const
{
  return magneticFieldDataSource;
}

void WellInfoSurveyInfo::setMagneticFieldDataSource(const QString &value)
{
  magneticFieldDataSource = value;
}

int WellInfoSurveyInfo::getNorthReference() const
{
  return northReference;
}

void WellInfoSurveyInfo::setNorthReference(int value)
{
  northReference = value;
}

double WellInfoSurveyInfo::getTotalCorrection() const
{
  return totalCorrection;
}

void WellInfoSurveyInfo::setTotalCorrection(double value)
{
  totalCorrection = value;
}

double WellInfoSurveyInfo::getMagDedination() const
{
  return magDedination;
}

void WellInfoSurveyInfo::setMagDedination(double value)
{
  magDedination = value;
}

double WellInfoSurveyInfo::getGridConvergence() const
{
  return gridConvergence;
}

void WellInfoSurveyInfo::setGridConvergence(double value)
{
  gridConvergence = value;
}

int WellInfoSurveyInfo::getChecksumInsiteCalculated() const
{
  return checksumInsiteCalculated;
}

void WellInfoSurveyInfo::setChecksumInsiteCalculated(int value)
{
  checksumInsiteCalculated = value;
}

QString WellInfoSurveyInfo::getChecksumInsiteMagutm() const
{
  return checksumInsiteMagutm;
}

void WellInfoSurveyInfo::setChecksumInsiteMagutm(const QString &value)
{
  checksumInsiteMagutm = value;
}

int WellInfoSurveyInfo::getChecksumDosCalculated() const
{
  return checksumDosCalculated;
}

void WellInfoSurveyInfo::setChecksumDosCalculated(int value)
{
  checksumDosCalculated = value;
}

double WellInfoSurveyInfo::getMagneticDipAngle() const
{
  return magneticDipAngle;
}

void WellInfoSurveyInfo::setMagneticDipAngle(double value)
{
  magneticDipAngle = value;
}
