#ifndef PCD_H
#define PCD_H

#include "../../common/base/baseentity.h"

class PCD : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( double dist_from READ getDistFrom WRITE setDistFrom)
  Q_PROPERTY( QString survey_type READ getSurveyType WRITE setSurveyType)
  Q_PROPERTY( QString probe_variant READ getProbeVariant WRITE setProbeVariant)
  Q_PROPERTY( QString hoc_sn READ getHocSN WRITE setHocSN)
  Q_PROPERTY( QString probe_sn READ getProbeSN WRITE setProbeSN)
  Q_PROPERTY( QString analog_board_sn READ getAnalogBoardSN WRITE setAnalogBoardSN)
  Q_PROPERTY( QDateTime battery_date READ getBatteryDate WRITE setBatteryDate)
  Q_PROPERTY( QString gx_accel_sn READ getGxAccelSN WRITE setGxAccelSN)
  Q_PROPERTY( QString gy_accel_sn READ getGyAccelSN WRITE setGyAccelSN)
  Q_PROPERTY( QString gz_accel_sn READ getGzAccelSN WRITE setGzAccelSN)
  Q_PROPERTY( QString probe_software READ getProbeSoftware WRITE setProbeSoftware)
  Q_PROPERTY( QString pic_version READ getPicVersion WRITE setPicVersion)
  Q_PROPERTY( int magnetic_field_strength READ getMagneticFieldStrength WRITE setMagneticFieldStrength)
  Q_PROPERTY( double magnetic_dip_angle READ getMagneticDipAngle WRITE setMagneticDipAngle)
  Q_PROPERTY( double gravity_field_strength READ getGravityFieldStrength WRITE setGravityFieldStrength)
  Q_PROPERTY( double total_correction READ getTotalCorrection WRITE setTotalCorrection)
  Q_PROPERTY( QString north_reference READ getNorthReference WRITE setNorthReference)
  Q_PROPERTY( QString magnetic_checksum READ getMagneticChecksum WRITE setMagneticChecksum)
  Q_PROPERTY( double total_offset READ getTotalOffset WRITE setTotalOffset)
  Q_PROPERTY( double hsg_offset READ getHsgOffset WRITE setHsgOffset)
  Q_PROPERTY( double rig_floor_offset READ getRigFloorOffset WRITE setRigFloorOffset)
  Q_PROPERTY( double azimuth_low READ getAzimuthLow WRITE setAzimuthLow)
  Q_PROPERTY( double azimuth_high READ getAzimuthHigh WRITE setAzimuthHigh)
  Q_PROPERTY( double inclination_low READ getInclinationLow WRITE setInclinationLow)
  Q_PROPERTY( double inclination_high READ getInclinationHigh WRITE setInclinationHigh)
  Q_PROPERTY( double tf_grav_low READ getTfGravLow WRITE setTfGravLow)
  Q_PROPERTY( double tf_grav_high READ getTfGravHigh WRITE setTfGravHigh)
  Q_PROPERTY( double tf_mag_low READ getTfMagLow WRITE setTfMagLow)
  Q_PROPERTY( double tf_mag_high READ getTfMagHigh WRITE setTfMagHigh)
  Q_PROPERTY( double dip_calc_low READ getDipCalcLow WRITE setDipCalcLow)
  Q_PROPERTY( double dip_calc_high READ getDipCalcHigh WRITE setDipCalcHigh)
  Q_PROPERTY( double dip_meas_low READ getDipMeasLow WRITE setDipMeasLow)
  Q_PROPERTY( double dip_meas_high READ getDipMeasHigh WRITE setDipMeasHigh)
  Q_PROPERTY( double g_total_low READ getGTotalLow WRITE setGTotalLow)
  Q_PROPERTY( double g_total_high READ getGTotalHigh WRITE setGTotalHigh)
  Q_PROPERTY( int bt_calc_low READ getBtCalcLow WRITE setBtCalcLow)
  Q_PROPERTY( int bt_calc_high READ getBtCalcHigh WRITE setBtCalcHigh)
  Q_PROPERTY( int bt_meas_low READ getBtMeasLow WRITE setBtMeasLow)
  Q_PROPERTY( int bt_meas_high READ getBtMeasHigh WRITE setBtMeasHigh)
  Q_PROPERTY( QDateTime initialis_time READ getInitialisTime WRITE setInitialisTime)
  Q_PROPERTY( QDateTime read_time READ getReadTime WRITE setReadTime)
  Q_PROPERTY( double svss_log_period READ getSvssLogPeriod WRITE setSvssLogPeriod)
  Q_PROPERTY( double moderate_x_avg READ getModerateXAvg WRITE setModerateXAvg)
  Q_PROPERTY( double moderate_z_avg READ getModerateZAvg WRITE setModerateZAvg)
  Q_PROPERTY( double high_x_avg READ getHighXAvg WRITE setHighXAvg)
  Q_PROPERTY( double high_z_avg READ getHighZAvg WRITE setHighZAvg)
  Q_PROPERTY( double excessive_x_avg READ getExcessiveXAvg WRITE setExcessiveXAvg)
  Q_PROPERTY( double excessive_z_avg READ getExcessiveZAvg WRITE setExcessiveZAvg)
  Q_PROPERTY( double moderate_x_shock READ getModerateXShock WRITE setModerateXShock)
  Q_PROPERTY( double moderate_z_shock READ getModerateZShock WRITE setModerateZShock)
  Q_PROPERTY( double high_x_shock READ getHighXShock WRITE setHighXShock)
  Q_PROPERTY( double high_z_shock READ getHighZShock WRITE setHighZShock)
  Q_PROPERTY( double excessive_x_shock READ getExcessiveXShock WRITE setExcessiveXShock)
  Q_PROPERTY( double excessive_z_shock READ getExcessiveZShock WRITE setExcessiveZShock)
  Q_PROPERTY( double data_rate1 READ getDataRate1 WRITE setDataRate1)
  Q_PROPERTY( double data_rate2 READ getDataRate2 WRITE setDataRate2)
  Q_PROPERTY( double data_rate3 READ getDataRate3 WRITE setDataRate3)
  Q_PROPERTY( QString pcd_tool_mode READ getPcdToolMode WRITE setPcdToolMode)
  Q_PROPERTY( int wait_period READ getWaitPeriod WRITE setWaitPeriod)
  Q_PROPERTY( int alarm_period READ getAlarmPeriod WRITE setAlarmPeriod)
  Q_PROPERTY( int runin_period READ getRuninPeriod WRITE setRuninPeriod)
  Q_PROPERTY( double tf_crossover READ getTfCrossover WRITE setTfCrossover)

public:
  PCD();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  double getDistFrom() const;
  void setDistFrom(double value);

  QString getSurveyType() const;
  void setSurveyType(const QString &value);

  QString getProbeVariant() const;
  void setProbeVariant(const QString &value);

  QString getHocSN() const;
  void setHocSN(const QString &value);

  QString getProbeSN() const;
  void setProbeSN(const QString &value);

  QString getAnalogBoardSN() const;
  void setAnalogBoardSN(const QString &value);

  QDateTime getBatteryDate() const;
  void setBatteryDate(const QDateTime &value);

  QString getGxAccelSN() const;
  void setGxAccelSN(const QString &value);

  QString getGyAccelSN() const;
  void setGyAccelSN(const QString &value);

  QString getGzAccelSN() const;
  void setGzAccelSN(const QString &value);

  QString getProbeSoftware() const;
  void setProbeSoftware(const QString &value);

  QString getPicVersion() const;
  void setPicVersion(const QString &value);

  int getMagneticFieldStrength() const;
  void setMagneticFieldStrength(int value);

  double getMagneticDipAngle() const;
  void setMagneticDipAngle(double value);

  double getGravityFieldStrength() const;
  void setGravityFieldStrength(double value);

  double getTotalCorrection() const;
  void setTotalCorrection(double value);

  QString getNorthReference() const;
  void setNorthReference(const QString &value);

  QString getMagneticChecksum() const;
  void setMagneticChecksum(const QString &value);

  double getTotalOffset() const;
  void setTotalOffset(double value);

  double getHsgOffset() const;
  void setHsgOffset(double value);

  double getRigFloorOffset() const;
  void setRigFloorOffset(double value);

  double getAzimuthLow() const;
  void setAzimuthLow(double value);

  double getAzimuthHigh() const;
  void setAzimuthHigh(double value);

  double getInclinationLow() const;
  void setInclinationLow(double value);

  double getInclinationHigh() const;
  void setInclinationHigh(double value);

  double getTfGravLow() const;
  void setTfGravLow(double value);

  double getTfGravHigh() const;
  void setTfGravHigh(double value);

  double getTfMagLow() const;
  void setTfMagLow(double value);

  double getTfMagHigh() const;
  void setTfMagHigh(double value);

  double getDipCalcLow() const;
  void setDipCalcLow(double value);

  double getDipCalcHigh() const;
  void setDipCalcHigh(double value);

  double getDipMeasLow() const;
  void setDipMeasLow(double value);

  double getDipMeasHigh() const;
  void setDipMeasHigh(double value);

  double getGTotalLow() const;
  void setGTotalLow(double value);

  double getGTotalHigh() const;
  void setGTotalHigh(double value);

  int getBtCalcLow() const;
  void setBtCalcLow(int value);

  int getBtCalcHigh() const;
  void setBtCalcHigh(int value);

  int getBtMeasLow() const;
  void setBtMeasLow(int value);

  int getBtMeasHigh() const;
  void setBtMeasHigh(int value);

  QDateTime getInitialisTime() const;
  void setInitialisTime(const QDateTime &value);

  QDateTime getReadTime() const;
  void setReadTime(const QDateTime &value);

  double getSvssLogPeriod() const;
  void setSvssLogPeriod(double value);

  double getModerateXAvg() const;
  void setModerateXAvg(double value);

  double getModerateZAvg() const;
  void setModerateZAvg(double value);

  double getHighXAvg() const;
  void setHighXAvg(double value);

  double getHighZAvg() const;
  void setHighZAvg(double value);

  double getExcessiveXAvg() const;
  void setExcessiveXAvg(double value);

  double getExcessiveZAvg() const;
  void setExcessiveZAvg(double value);

  double getModerateXShock() const;
  void setModerateXShock(double value);

  double getModerateZShock() const;
  void setModerateZShock(double value);

  double getHighXShock() const;
  void setHighXShock(double value);

  double getHighZShock() const;
  void setHighZShock(double value);

  double getExcessiveXShock() const;
  void setExcessiveXShock(double value);

  double getExcessiveZShock() const;
  void setExcessiveZShock(double value);

  double getDataRate1() const;
  void setDataRate1(double value);

  double getDataRate2() const;
  void setDataRate2(double value);

  double getDataRate3() const;
  void setDataRate3(double value);

  QString getPcdToolMode() const;
  void setPcdToolMode(const QString &value);

  int getWaitPeriod() const;
  void setWaitPeriod(int value);

  int getAlarmPeriod() const;
  void setAlarmPeriod(int value);

  int getRuninPeriod() const;
  void setRuninPeriod(int value);

  double getTfCrossover() const;
  void setTfCrossover(double value);

private:
  int id = 0;
  int wellInfoId;
  int runInfoId;
  double distFrom;
  QString surveyType;
  QString probeVariant;
  QString hocSN;
  QString probeSN;
  QString analogBoardSN;
  QDateTime batteryDate;
  QString gxAccelSN;
  QString gyAccelSN;
  QString gzAccelSN;
  QString probeSoftware;
  QString picVersion;
  int magneticFieldStrength;
  double magneticDipAngle;
  double gravityFieldStrength;
  double totalCorrection;
  QString northReference;
  QString magneticChecksum;
  double totalOffset;
  double hsgOffset;
  double rigFloorOffset;

  double azimuthLow;
  double azimuthHigh;
  double inclinationLow;
  double inclinationHigh;
  double tfGravLow;
  double tfGravHigh;
  double tfMagLow;
  double tfMagHigh;
  double dipCalcLow;
  double dipCalcHigh;
  double dipMeasLow;
  double dipMeasHigh;
  double gTotalLow;
  double gTotalHigh;
  int btCalcLow;
  int btCalcHigh;
  int btMeasLow;
  int btMeasHigh;

  QDateTime initialisTime;
  QDateTime readTime;

  double svssLogPeriod;
  double moderateXAvg;
  double moderateZAvg;
  double highXAvg;
  double highZAvg;
  double excessiveXAvg;
  double excessiveZAvg;
  double moderateXShock;
  double moderateZShock;
  double highXShock;
  double highZShock;
  double excessiveXShock;
  double excessiveZShock;

  double dataRate1;
  double dataRate2;
  double dataRate3;
  QString pcdToolMode;
  int waitPeriod;
  int alarmPeriod;
  int runinPeriod;
  double tfCrossover;


};

#endif // PCD_H
