#ifndef HCIM_H
#define HCIM_H

#include "../../common/base/baseentity.h"

class HCIM : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( QString sw_version READ getSWVersion WRITE setSWVersion)
  Q_PROPERTY( QString hcim_type READ getHCIMType WRITE setHCIMType)
  Q_PROPERTY( QString hsc_memory_type READ getHSCMemoryType WRITE setHSCMemoryType)
  Q_PROPERTY( QString sub_sn READ getSubSN WRITE setSubSN)
  Q_PROPERTY( QString battery_sn READ getBatterySN WRITE setBatterySN)
  Q_PROPERTY( QString hanger_sn READ getHangerSN WRITE setHangerSN)
  Q_PROPERTY( QDateTime initialzation READ getInitialzation WRITE setInitialzation)
  Q_PROPERTY( QDateTime read_time READ getReadTime WRITE setReadTime)
  Q_PROPERTY( double current_usage READ getCurrentUsage WRITE setCurrentUsage)
  Q_PROPERTY( double smi_current_usage READ getSMICurrentUsage WRITE setSMICurrentUsage)
  Q_PROPERTY( QString azimuthal_refe READ getAzimuthalRefe WRITE setAzimuthalRefe)
  Q_PROPERTY( QString ecmb_board_name READ getECMBBoardName WRITE setECMBBoardName)
  Q_PROPERTY( QString ecmb_ip_address READ getECMBIpAddress WRITE setECMBIpAddress)

public:
  HCIM();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  QString getSWVersion() const;
  void setSWVersion(const QString &value);

  QString getHCIMType() const;
  void setHCIMType(const QString &value);

  QString getHSCMemoryType() const;
  void setHSCMemoryType(const QString &value);

  QString getSubSN() const;
  void setSubSN(const QString &value);

  QString getBatterySN() const;
  void setBatterySN(const QString &value);

  QString getHangerSN() const;
  void setHangerSN(const QString &value);

  QDateTime getInitialzation() const;
  void setInitialzation(const QDateTime &value);

  QDateTime getReadTime() const;
  void setReadTime(const QDateTime &value);

  double getCurrentUsage() const;
  void setCurrentUsage(double value);

  double getSMICurrentUsage() const;
  void setSMICurrentUsage(double value);

  QString getAzimuthalRefe() const;
  void setAzimuthalRefe(const QString &value);

  QString getECMBBoardName() const;
  void setECMBBoardName(const QString &value);

  QString getECMBIpAddress() const;
  void setECMBIpAddress(const QString &value);

private:
  int id = 0;
  int wellInfoId;
  int runInfoId;
  QString SWVersion;
  QString HCIMType;
  QString HSCMemoryType;
  QString subSN;
  QString batterySN;
  QString hangerSN;
  QDateTime initialzation;
  QDateTime readTime;
  double currentUsage;
  double SMICurrentUsage;
  QString azimuthalRefe;
  QString ECMBBoardName;
  QString ECMBIpAddress;

};

#endif // HCIM_H
