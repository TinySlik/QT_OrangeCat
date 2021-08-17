#include "runinfomwdstats.h"

RunInfoMwdStats::RunInfoMwdStats()
{

}

int RunInfoMwdStats::getId() const
{
  return id;
}

void RunInfoMwdStats::setId(int value)
{
  id = value;
}

int RunInfoMwdStats::getRunInfoId() const
{
  return runInfoId;
}

void RunInfoMwdStats::setRunInfoId(int value)
{
  runInfoId = value;
}

double RunInfoMwdStats::getDelectionEfficiency() const
{
  return delectionEfficiency;
}

void RunInfoMwdStats::setDelectionEfficiency(double value)
{
  delectionEfficiency = value;
}

int RunInfoMwdStats::getPulseCount() const
{
  return pulseCount;
}

void RunInfoMwdStats::setPulseCount(int value)
{
  pulseCount = value;
}

double RunInfoMwdStats::getPulseRpm() const
{
  return pulseRpm;
}

void RunInfoMwdStats::setPulseRpm(double value)
{
  pulseRpm = value;
}

double RunInfoMwdStats::getGoodMemoryData() const
{
  return goodMemoryData;
}

void RunInfoMwdStats::setGoodMemoryData(double value)
{
  goodMemoryData = value;
}

double RunInfoMwdStats::getPreFloat() const
{
  return preFloat;
}

void RunInfoMwdStats::setPreFloat(double value)
{
  preFloat = value;
}

double RunInfoMwdStats::getPreSeat() const
{
  return preSeat;
}

void RunInfoMwdStats::setPreSeat(double value)
{
  preSeat = value;
}

double RunInfoMwdStats::getPostSeat() const
{
  return postSeat;
}

void RunInfoMwdStats::setPostSeat(double value)
{
  postSeat = value;
}

double RunInfoMwdStats::getCimBatteryUsage() const
{
  return cimBatteryUsage;
}

void RunInfoMwdStats::setCimBatteryUsage(double value)
{
  cimBatteryUsage = value;
}

double RunInfoMwdStats::getSldBatteryUsage() const
{
  return sldBatteryUsage;
}

void RunInfoMwdStats::setSldBatteryUsage(double value)
{
  sldBatteryUsage = value;
}

double RunInfoMwdStats::getPulserBatteryUsage() const
{
  return pulserBatteryUsage;
}

void RunInfoMwdStats::setPulserBatteryUsage(double value)
{
  pulserBatteryUsage = value;
}

double RunInfoMwdStats::getFtwdBatteryUsage() const
{
  return ftwdBatteryUsage;
}

void RunInfoMwdStats::setFtwdBatteryUsage(double value)
{
  ftwdBatteryUsage = value;
}

double RunInfoMwdStats::getPostFloat() const
{
  return postFloat;
}

void RunInfoMwdStats::setPostFloat(double value)
{
  postFloat = value;
}
