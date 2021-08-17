#include "dgr.h"

DGR::DGR()
{

}

int DGR::getId() const
{
  return id;
}

void DGR::setId(int value)
{
  id = value;
}

int DGR::getWellInfoId() const
{
  return wellInfoId;
}

void DGR::setWellInfoId(int value)
{
  wellInfoId = value;
}

int DGR::getRunInfoId() const
{
  return runInfoId;
}

void DGR::setRunInfoId(int value)
{
  runInfoId = value;
}

double DGR::getDistFrom() const
{
  return distFrom;
}

void DGR::setDistFrom(double value)
{
  distFrom = value;
}

QString DGR::getToolSize() const
{
  return toolSize;
}

void DGR::setToolSize(const QString &value)
{
  toolSize = value;
}

double DGR::getTotalCurrentUse() const
{
  return totalCurrentUse;
}

void DGR::setTotalCurrentUse(double value)
{
  totalCurrentUse = value;
}

QString DGR::getSubSN() const
{
  return subSN;
}

void DGR::setSubSN(const QString &value)
{
  subSN = value;
}

QString DGR::getSWVersion() const
{
  return SWVersion;
}

void DGR::setSWVersion(const QString &value)
{
  SWVersion = value;
}

double DGR::getApiCaliFaChanA() const
{
  return apiCaliFaChanA;
}

void DGR::setApiCaliFaChanA(double value)
{
  apiCaliFaChanA = value;
}

double DGR::getApiCaliFaChanB() const
{
  return apiCaliFaChanB;
}

void DGR::setApiCaliFaChanB(double value)
{
  apiCaliFaChanB = value;
}

double DGR::getOffsetChanA() const
{
  return offsetChanA;
}

void DGR::setOffsetChanA(double value)
{
  offsetChanA = value;
}

double DGR::getOffsetChanB() const
{
  return offsetChanB;
}

void DGR::setOffsetChanB(double value)
{
  offsetChanB = value;
}

int DGR::getLowLimitChanA() const
{
  return lowLimitChanA;
}

void DGR::setLowLimitChanA(int value)
{
  lowLimitChanA = value;
}

int DGR::getLowLimitChanB() const
{
  return lowLimitChanB;
}

void DGR::setLowLimitChanB(int value)
{
  lowLimitChanB = value;
}

int DGR::getHighLimitChanA() const
{
  return highLimitChanA;
}

void DGR::setHighLimitChanA(int value)
{
  highLimitChanA = value;
}

int DGR::getHighLimitChanB() const
{
  return highLimitChanB;
}

void DGR::setHighLimitChanB(int value)
{
  highLimitChanB = value;
}

int DGR::getTDelayFirst() const
{
  return tDelayFirst;
}

void DGR::setTDelayFirst(int value)
{
  tDelayFirst = value;
}

int DGR::getTDelaySecond() const
{
  return tDelaySecond;
}

void DGR::setTDelaySecond(int value)
{
  tDelaySecond = value;
}

int DGR::getTDelayThird() const
{
  return tDelayThird;
}

void DGR::setTDelayThird(int value)
{
  tDelayThird = value;
}

int DGR::getSamplePeriodFirst() const
{
  return samplePeriodFirst;
}

void DGR::setSamplePeriodFirst(int value)
{
  samplePeriodFirst = value;
}

int DGR::getSamplePeriodSecond() const
{
  return samplePeriodSecond;
}

void DGR::setSamplePeriodSecond(int value)
{
  samplePeriodSecond = value;
}

int DGR::getSamplePeriodThird() const
{
  return samplePeriodThird;
}

void DGR::setSamplePeriodThird(int value)
{
  samplePeriodThird = value;
}
