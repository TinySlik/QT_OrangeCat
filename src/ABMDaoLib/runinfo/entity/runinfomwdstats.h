#ifndef RUNINFOMWDSTATS_H
#define RUNINFOMWDSTATS_H

#include "../../common/base/baseentity.h"

class RunInfoMwdStats : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( double delection_efficiency READ getDelectionEfficiency WRITE setDelectionEfficiency)
  Q_PROPERTY( int pulse_count READ getPulseCount WRITE setPulseCount)
  Q_PROPERTY( double pulse_rpm READ getPulseRpm WRITE setPulseRpm)
  Q_PROPERTY( double good_memory_data READ getGoodMemoryData WRITE setGoodMemoryData)
  Q_PROPERTY( double pre_float READ getPreFloat WRITE setPreFloat)
  Q_PROPERTY( double pre_seat READ getPreSeat WRITE setPreSeat)
  Q_PROPERTY( double post_float READ getPostFloat WRITE setPostFloat)
  Q_PROPERTY( double post_seat READ getPostSeat WRITE setPostSeat)
  Q_PROPERTY( double cim_battery_usage READ getCimBatteryUsage WRITE setCimBatteryUsage)
  Q_PROPERTY( double sld_battery_usage READ getSldBatteryUsage WRITE setSldBatteryUsage)
  Q_PROPERTY( double pulser_battery_usage READ getPulserBatteryUsage WRITE setPulserBatteryUsage)
  Q_PROPERTY( double ftwd_battery_usage READ getFtwdBatteryUsage WRITE setFtwdBatteryUsage)

public:
  RunInfoMwdStats();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  double getDelectionEfficiency() const;
  void setDelectionEfficiency(double value);

  int getPulseCount() const;
  void setPulseCount(int value);

  double getPulseRpm() const;
  void setPulseRpm(double value);

  double getGoodMemoryData() const;
  void setGoodMemoryData(double value);

  double getPreFloat() const;
  void setPreFloat(double value);

  double getPreSeat() const;
  void setPreSeat(double value);

  double getPostSeat() const;
  void setPostSeat(double value);

  double getCimBatteryUsage() const;
  void setCimBatteryUsage(double value);

  double getSldBatteryUsage() const;
  void setSldBatteryUsage(double value);

  double getPulserBatteryUsage() const;
  void setPulserBatteryUsage(double value);

  double getFtwdBatteryUsage() const;
  void setFtwdBatteryUsage(double value);

  double getPostFloat() const;
  void setPostFloat(double value);

private:
  int id = 0;
  int runInfoId;
  double delectionEfficiency;
  int pulseCount;
  double pulseRpm;
  double goodMemoryData;
  double preFloat;
  double preSeat;
  double postFloat;
  double postSeat;
  double cimBatteryUsage;
  double sldBatteryUsage;
  double pulserBatteryUsage;
  double ftwdBatteryUsage;

};

#endif // RUNINFOMWDSTATS_H
