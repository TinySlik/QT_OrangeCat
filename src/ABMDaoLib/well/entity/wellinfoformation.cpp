#include "wellinfoformation.h"

WellInfoFormation::WellInfoFormation()
{

}

int WellInfoFormation::getId() const
{
  return id;
}

void WellInfoFormation::setId(int value)
{
  id = value;
}

int WellInfoFormation::getWellInfoId() const
{
  return wellInfoId;
}

void WellInfoFormation::setWellInfoId(int value)
{
  wellInfoId = value;
}

double WellInfoFormation::getDepth() const
{
  return depth;
}

void WellInfoFormation::setDepth(double value)
{
  depth = value;
}

QString WellInfoFormation::getFormationName() const
{
  return formationName;
}

void WellInfoFormation::setFormationName(const QString &value)
{
  formationName = value;
}

int WellInfoFormation::getLithologyType() const
{
  return lithologyType;
}

void WellInfoFormation::setLithologyType(int value)
{
  lithologyType = value;
}

double WellInfoFormation::getDip() const
{
  return dip;
}

void WellInfoFormation::setDip(double value)
{
  dip = value;
}

double WellInfoFormation::getDipDirection() const
{
  return dipDirection;
}

void WellInfoFormation::setDipDirection(double value)
{
  dipDirection = value;
}

QString WellInfoFormation::getFormationDescription() const
{
  return formationDescription;
}

void WellInfoFormation::setFormationDescription(const QString &value)
{
  formationDescription = value;
}

int WellInfoFormation::getPeriod() const
{
  return period;
}

void WellInfoFormation::setPeriod(int value)
{
  period = value;
}

QString WellInfoFormation::getEpoch() const
{
  return epoch;
}

void WellInfoFormation::setEpoch(const QString &value)
{
  epoch = value;
}
