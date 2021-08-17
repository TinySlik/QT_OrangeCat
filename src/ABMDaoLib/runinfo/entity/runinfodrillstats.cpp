#include "runinfodrillstats.h"

RunInfoDrillStats::RunInfoDrillStats()
{

}

int RunInfoDrillStats::getId() const
{
  return id;
}

void RunInfoDrillStats::setId(int value)
{
  id = value;
}

int RunInfoDrillStats::getRunInfoId() const
{
  return runInfoId;
}

void RunInfoDrillStats::setRunInfoId(int value)
{
  runInfoId = value;
}

double RunInfoDrillStats::getStartInc() const
{
  return startInc;
}

void RunInfoDrillStats::setStartInc(double value)
{
  startInc = value;
}

double RunInfoDrillStats::getIncMin() const
{
  return incMin;
}

void RunInfoDrillStats::setIncMin(double value)
{
  incMin = value;
}

double RunInfoDrillStats::getIncMinDepth() const
{
  return incMinDepth;
}

void RunInfoDrillStats::setIncMinDepth(double value)
{
  incMinDepth = value;
}

double RunInfoDrillStats::getIncMax() const
{
  return incMax;
}

void RunInfoDrillStats::setIncMax(double value)
{
  incMax = value;
}

double RunInfoDrillStats::getIncMaxDepth() const
{
  return incMaxDepth;
}

void RunInfoDrillStats::setIncMaxDepth(double value)
{
  incMaxDepth = value;
}

double RunInfoDrillStats::getFinalInc() const
{
  return finalInc;
}

void RunInfoDrillStats::setFinalInc(double value)
{
  finalInc = value;
}

double RunInfoDrillStats::getStartAzimuth() const
{
  return startAzimuth;
}

void RunInfoDrillStats::setStartAzimuth(double value)
{
  startAzimuth = value;
}

double RunInfoDrillStats::getFinalAzimuth() const
{
  return finalAzimuth;
}

void RunInfoDrillStats::setFinalAzimuth(double value)
{
  finalAzimuth = value;
}

double RunInfoDrillStats::getMaxOriDogleg() const
{
  return maxOriDogleg;
}

void RunInfoDrillStats::setMaxOriDogleg(double value)
{
  maxOriDogleg = value;
}

double RunInfoDrillStats::getAvgOriDogleg() const
{
  return avgOriDogleg;
}

void RunInfoDrillStats::setAvgOriDogleg(double value)
{
  avgOriDogleg = value;
}

double RunInfoDrillStats::getMaxRotDogleg() const
{
  return maxRotDogleg;
}

void RunInfoDrillStats::setMaxRotDogleg(double value)
{
  maxRotDogleg = value;
}

double RunInfoDrillStats::getAvgRotBuild() const
{
  return avgRotBuild;
}

void RunInfoDrillStats::setAvgRotBuild(double value)
{
  avgRotBuild = value;
}

double RunInfoDrillStats::getAvgRotWalk() const
{
  return avgRotWalk;
}

void RunInfoDrillStats::setAvgRotWalk(double value)
{
  avgRotWalk = value;
}

double RunInfoDrillStats::getMaxDogPushed() const
{
  return maxDogPushed;
}

void RunInfoDrillStats::setMaxDogPushed(double value)
{
  maxDogPushed = value;
}

double RunInfoDrillStats::getMaxDogPulled() const
{
  return maxDogPulled;
}

void RunInfoDrillStats::setMaxDogPulled(double value)
{
  maxDogPulled = value;
}

double RunInfoDrillStats::getOperatingHours() const
{
  return operatingHours;
}

void RunInfoDrillStats::setOperatingHours(double value)
{
  operatingHours = value;
}

double RunInfoDrillStats::getCirculatingHours() const
{
  return circulatingHours;
}

void RunInfoDrillStats::setCirculatingHours(double value)
{
  circulatingHours = value;
}

double RunInfoDrillStats::getDrillingHours() const
{
  return drillingHours;
}

void RunInfoDrillStats::setDrillingHours(double value)
{
  drillingHours = value;
}

double RunInfoDrillStats::getReamingHours() const
{
  return reamingHours;
}

void RunInfoDrillStats::setReamingHours(double value)
{
  reamingHours = value;
}

double RunInfoDrillStats::getMwdBoreholeSize() const
{
  return mwdBoreholeSize;
}

void RunInfoDrillStats::setMwdBoreholeSize(double value)
{
  mwdBoreholeSize = value;
}

double RunInfoDrillStats::getHoleOpenedToSize() const
{
  return holeOpenedToSize;
}

void RunInfoDrillStats::setHoleOpenedToSize(double value)
{
  holeOpenedToSize = value;
}

QString RunInfoDrillStats::getMwdPositionRelative() const
{
  return mwdPositionRelative;
}

void RunInfoDrillStats::setMwdPositionRelative(const QString &value)
{
  mwdPositionRelative = value;
}

double RunInfoDrillStats::getSppMin() const
{
  return sppMin;
}

void RunInfoDrillStats::setSppMin(double value)
{
  sppMin = value;
}

double RunInfoDrillStats::getSppMax() const
{
  return sppMax;
}

void RunInfoDrillStats::setSppMax(double value)
{
  sppMax = value;
}

double RunInfoDrillStats::getSpp() const
{
  return spp;
}

void RunInfoDrillStats::setSpp(double value)
{
  spp = value;
}

double RunInfoDrillStats::getMaxOpPress() const
{
  return maxOpPress;
}

void RunInfoDrillStats::setMaxOpPress(double value)
{
  maxOpPress = value;
}

double RunInfoDrillStats::getTotalBitRev() const
{
  return totalBitRev;
}

void RunInfoDrillStats::setTotalBitRev(double value)
{
  totalBitRev = value;
}

double RunInfoDrillStats::getWob() const
{
  return wob;
}

void RunInfoDrillStats::setWob(double value)
{
  wob = value;
}

double RunInfoDrillStats::getWobOverpull() const
{
  return wobOverpull;
}

void RunInfoDrillStats::setWobOverpull(double value)
{
  wobOverpull = value;
}

double RunInfoDrillStats::getWobMax() const
{
  return wobMax;
}

void RunInfoDrillStats::setWobMax(double value)
{
  wobMax = value;
}

double RunInfoDrillStats::getRop() const
{
  return rop;
}

void RunInfoDrillStats::setRop(double value)
{
  rop = value;
}

double RunInfoDrillStats::getRopMin() const
{
  return ropMin;
}

void RunInfoDrillStats::setRopMin(double value)
{
  ropMin = value;
}

double RunInfoDrillStats::getRopMax() const
{
  return ropMax;
}

void RunInfoDrillStats::setRopMax(double value)
{
  ropMax = value;
}

double RunInfoDrillStats::getRpm() const
{
  return rpm;
}

void RunInfoDrillStats::setRpm(double value)
{
  rpm = value;
}

double RunInfoDrillStats::getRpmMin() const
{
  return rpmMin;
}

void RunInfoDrillStats::setRpmMin(double value)
{
  rpmMin = value;
}

double RunInfoDrillStats::getRpmMax() const
{
  return rpmMax;
}

void RunInfoDrillStats::setRpmMax(double value)
{
  rpmMax = value;
}

double RunInfoDrillStats::getTorqueAvg() const
{
  return torqueAvg;
}

void RunInfoDrillStats::setTorqueAvg(double value)
{
  torqueAvg = value;
}

double RunInfoDrillStats::getTorqueMin() const
{
  return torqueMin;
}

void RunInfoDrillStats::setTorqueMin(double value)
{
  torqueMin = value;
}

double RunInfoDrillStats::getTorqueMax() const
{
  return torqueMax;
}

void RunInfoDrillStats::setTorqueMax(double value)
{
  torqueMax = value;
}

double RunInfoDrillStats::getBendingMomentAvg() const
{
  return bendingMomentAvg;
}

void RunInfoDrillStats::setBendingMomentAvg(double value)
{
  bendingMomentAvg = value;
}

double RunInfoDrillStats::getBendingMomentMin() const
{
  return bendingMomentMin;
}

void RunInfoDrillStats::setBendingMomentMin(double value)
{
  bendingMomentMin = value;
}

double RunInfoDrillStats::getBendingMomentMax() const
{
  return bendingMomentMax;
}

void RunInfoDrillStats::setBendingMomentMax(double value)
{
  bendingMomentMax = value;
}
