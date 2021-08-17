#ifndef WELLINFOGENERAL_H
#define WELLINFOGENERAL_H

#include <QObject>

#include "../../common/base/baseentity.h"

class WellInfoGeneral : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( QString well_id READ getWellId WRITE setWellId)
  Q_PROPERTY( QString well_name READ getWellName WRITE setWellName)
  Q_PROPERTY( QString customer_name READ getCustomerName WRITE setCustomerName)
  Q_PROPERTY( QString platform READ getPlatform WRITE setPlatform)
  Q_PROPERTY( QString rig_name READ getRigName WRITE setRigName)
  Q_PROPERTY( QString field_name READ getFieldName WRITE setFieldName)
  Q_PROPERTY( QString country READ getCountry WRITE setCountry)
  Q_PROPERTY( QDateTime well_start_time READ getWellStartTime WRITE setWellStartTime)
  Q_PROPERTY( QDateTime well_end_time READ getWellEndTime WRITE setWellEndTime)
  Q_PROPERTY( QDateTime well_spud_time READ getWellSpudTime WRITE setWellSpudTime)
  Q_PROPERTY( QString well_type READ getWellType WRITE setWellType)
  Q_PROPERTY( double start_depth READ getStartDepth WRITE setStartDepth)
  Q_PROPERTY( double end_depth READ getEndDepth WRITE setEndDepth)
  Q_PROPERTY( double rig_cost READ getRigCost WRITE setRigCost)
  Q_PROPERTY( QString api_sn_uwi READ getApiSnUwi WRITE setApiSnUwi)
  Q_PROPERTY( QString doe_number READ getDoeNumber WRITE setDoeNumber)
  Q_PROPERTY( QString contractor READ getContractor WRITE setContractor)
  Q_PROPERTY( QString dir_contractor READ getDirContractor WRITE setDirContractor)
  Q_PROPERTY( QString job_number READ getJobNumber WRITE setJobNumber)
  Q_PROPERTY( QString job_ticker_number READ getJobTickerNumber WRITE setJobTickerNumber)
  Q_PROPERTY( QString halliburton_district READ getHalliburtonDistrict WRITE setHalliburtonDistrict)
  Q_PROPERTY( QString unit_number READ getUnitNumber WRITE setUnitNumber)
  Q_PROPERTY( QString lease_name READ getLeaseName WRITE setLeaseName)
  Q_PROPERTY( QString section READ getSection WRITE setSection)
  Q_PROPERTY( QString township READ getTownship WRITE setTownship)
  Q_PROPERTY( QString range READ getRange WRITE setRange)
  Q_PROPERTY( QString pad READ getPad WRITE setPad)
  Q_PROPERTY( QString slot READ getSlot WRITE setSlot)
  Q_PROPERTY( QString block READ getBlock WRITE setBlock)
  Q_PROPERTY( QString sub_block READ getSubBlock WRITE setSubBlock)
  Q_PROPERTY( int sidetrack_monitoring_on READ getSidetrackMonitoringOn WRITE setSidetrackMonitoringOn)
  Q_PROPERTY( int time_zone READ getTimeZone WRITE setTimeZone)
public:

  WellInfoGeneral();

  int getId() const;
  void setId(int value);

  QString getWellId() const;
  void setWellId(const QString &value);

  QString getWellName() const;
  void setWellName(const QString &value);

  QString getCustomerName() const;
  void setCustomerName(const QString &value);

  QString getPlatform() const;
  void setPlatform(const QString &value);

  QString getRigName() const;
  void setRigName(const QString &value);

  QString getFieldName() const;
  void setFieldName(const QString &value);

  QString getCountry() const;
  void setCountry(const QString &value);

  QDateTime getWellStartTime() const;
  void setWellStartTime(const QDateTime &value);

  QDateTime getWellEndTime() const;
  void setWellEndTime(const QDateTime &value);

  QDateTime getWellSpudTime() const;
  void setWellSpudTime(const QDateTime &value);

  QString getWellType() const;
  void setWellType(const QString &value);

  double getStartDepth() const;
  void setStartDepth(double value);

  double getEndDepth() const;
  void setEndDepth(double value);

  double getRigCost() const;
  void setRigCost(double value);

  QString getApiSnUwi() const;
  void setApiSnUwi(const QString &value);

  QString getDoeNumber() const;
  void setDoeNumber(const QString &value);

  QString getContractor() const;
  void setContractor(const QString &value);

  QString getDirContractor() const;
  void setDirContractor(const QString &value);

  QString getJobNumber() const;
  void setJobNumber(const QString &value);

  QString getJobTickerNumber() const;
  void setJobTickerNumber(const QString &value);

  QString getHalliburtonDistrict() const;
  void setHalliburtonDistrict(const QString &value);

  QString getUnitNumber() const;
  void setUnitNumber(const QString &value);

  QString getLeaseName() const;
  void setLeaseName(const QString &value);

  QString getSection() const;
  void setSection(const QString &value);

  QString getTownship() const;
  void setTownship(const QString &value);

  QString getRange() const;
  void setRange(const QString &value);

  QString getPad() const;
  void setPad(const QString &value);

  QString getSlot() const;
  void setSlot(const QString &value);

  QString getBlock() const;
  void setBlock(const QString &value);

  QString getSubBlock() const;
  void setSubBlock(const QString &value);

  int getSidetrackMonitoringOn() const;
  void setSidetrackMonitoringOn(int value);

  int getTimeZone() const;
  void setTimeZone(int value);

private:
  int id = 0;
  QString wellId;
  QString wellName;
  QString customerName;
  QString platform;
  QString rigName;
  QString fieldName;
  QString country;
  QDateTime wellStartTime;
  QDateTime wellEndTime;
  QDateTime wellSpudTime;
  QString wellType;
  double startDepth = 0.0;
  double endDepth = 0.0;
  double rigCost = 0.0;
  QString apiSnUwi;
  QString doeNumber;
  QString contractor;
  QString dirContractor;
  QString jobNumber;
  QString jobTickerNumber;
  QString halliburtonDistrict;
  QString unitNumber;
  QString leaseName;
  QString section;
  QString township;
  QString range;
  QString pad;
  QString slot;
  QString block;
  QString subBlock;
  int sidetrackMonitoringOn = 0;
  int timeZone = 0;
};

#endif // WELLINFOGENERAL_H
