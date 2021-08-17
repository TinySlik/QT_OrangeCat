#ifndef RUNINFOGENERAL_H
#define RUNINFOGENERAL_H

#include "../../common/base/baseentity.h"

class RunInfoGeneral : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( QString run READ getRun WRITE setRun)
  Q_PROPERTY( QString ss_insite_versuib READ getSsInsiteVersuib WRITE setSsInsiteVersuib)
  Q_PROPERTY( QString iabc_rig_bha_number READ getIabcRigBhaNumber WRITE setIabcRigBhaNumber)
  Q_PROPERTY( double hydrostatic_offset READ getHydrostaticOffset WRITE setHydrostaticOffset)
  Q_PROPERTY( int bha_type READ getBhaType WRITE setBhaType)
  Q_PROPERTY( QString services READ getServices WRITE setServices)
  Q_PROPERTY( int drill_or_wipe READ getDrillOrWipe WRITE setDrillOrWipe)
  Q_PROPERTY( double total_depth_attempted READ getTotalDepthAttempted WRITE setTotalDepthAttempted)
  Q_PROPERTY( double depth_logged READ getDepthLogged WRITE setDepthLogged)
  Q_PROPERTY( double depth_wiped READ getDepthWiped WRITE setDepthWiped)
  Q_PROPERTY( double run_depth_range_start READ getRunDepthRangeStart WRITE setRunDepthRangeStart)
  Q_PROPERTY( double run_depth_range_end READ getRunDepthRangeEnd WRITE setRunDepthRangeEnd)
  Q_PROPERTY( QDateTime run_time_range_start READ getRunTimeRangeStart WRITE setRunTimeRangeStart)
  Q_PROPERTY( QDateTime run_time_range_end READ getRunTimeRangeEnd WRITE setRunTimeRangeEnd)
  Q_PROPERTY( QDateTime drilling_time_range_start READ getDrillingTimeRangeStart WRITE setDrillingTimeRangeStart)
  Q_PROPERTY( QDateTime drilling_time_range_end READ getDrillingTimeRangeEnd WRITE setDrillingTimeRangeEnd)
  Q_PROPERTY( QDateTime log_time_range_start READ getLogTimeRangeStart WRITE setLogTimeRangeStart)
  Q_PROPERTY( QDateTime log_time_range_end READ getLogTimeRangeEnd WRITE setLogTimeRangeEnd)
  Q_PROPERTY( QString mwd_engineers READ getMwdEngineers WRITE setMwdEngineers)
  Q_PROPERTY( QString directional_drillers READ getDirectionalDrillers WRITE setDirectionalDrillers)
  Q_PROPERTY( QString sdl_engineers READ getSdlEngineers WRITE setSdlEngineers)
  Q_PROPERTY( QString adt_engineers READ getAdtEngineers WRITE setAdtEngineers)
  Q_PROPERTY( QString customer_rep READ getCustomerRep WRITE setCustomerRep)
  Q_PROPERTY( QString customer_geo READ getCustomerGeo WRITE setCustomerGeo)
  Q_PROPERTY( QString res_contact_spec READ getResContactSpec WRITE setResContactSpec)
  Q_PROPERTY( QString other_engineers READ getOtherEngineers WRITE setOtherEngineers)

public:
  RunInfoGeneral();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  QString getRun() const;
  void setRun(const QString &value);

  QString getSsInsiteVersuib() const;
  void setSsInsiteVersuib(const QString &value);

  QString getIabcRigBhaNumber() const;
  void setIabcRigBhaNumber(const QString &value);

  double getHydrostaticOffset() const;
  void setHydrostaticOffset(double value);

  int getBhaType() const;
  void setBhaType(int value);

  QString getServices() const;
  void setServices(const QString &value);

  int getDrillOrWipe() const;
  void setDrillOrWipe(int value);

  double getTotalDepthAttempted() const;
  void setTotalDepthAttempted(double value);

  double getDepthLogged() const;
  void setDepthLogged(double value);

  double getDepthWiped() const;
  void setDepthWiped(double value);

  double getRunDepthRangeStart() const;
  void setRunDepthRangeStart(double value);

  double getRunDepthRangeEnd() const;
  void setRunDepthRangeEnd(double value);

  QDateTime getRunTimeRangeStart() const;
  void setRunTimeRangeStart(const QDateTime &value);

  QDateTime getRunTimeRangeEnd() const;
  void setRunTimeRangeEnd(const QDateTime &value);

  QDateTime getDrillingTimeRangeStart() const;
  void setDrillingTimeRangeStart(const QDateTime &value);

  QDateTime getDrillingTimeRangeEnd() const;
  void setDrillingTimeRangeEnd(const QDateTime &value);

  QDateTime getLogTimeRangeStart() const;
  void setLogTimeRangeStart(const QDateTime &value);

  QDateTime getLogTimeRangeEnd() const;
  void setLogTimeRangeEnd(const QDateTime &value);

  QString getMwdEngineers() const;
  void setMwdEngineers(const QString &value);

  QString getDirectionalDrillers() const;
  void setDirectionalDrillers(const QString &value);

  QString getSdlEngineers() const;
  void setSdlEngineers(const QString &value);

  QString getAdtEngineers() const;
  void setAdtEngineers(const QString &value);

  QString getCustomerRep() const;
  void setCustomerRep(const QString &value);

  QString getCustomerGeo() const;
  void setCustomerGeo(const QString &value);

  QString getResContactSpec() const;
  void setResContactSpec(const QString &value);

  QString getOtherEngineers() const;
  void setOtherEngineers(const QString &value);

private:
  int id = 0;
  int wellInfoId;
  QString run;
  QString ssInsiteVersuib;
  QString iabcRigBhaNumber;
  double hydrostaticOffset;
  int bhaType;
  QString services;
  int drillOrWipe;
  double totalDepthAttempted;
  double depthLogged;
  double depthWiped;
  double runDepthRangeStart;
  double runDepthRangeEnd;
  QDateTime runTimeRangeStart;
  QDateTime runTimeRangeEnd;
  QDateTime drillingTimeRangeStart;
  QDateTime drillingTimeRangeEnd;
  QDateTime logTimeRangeStart;
  QDateTime logTimeRangeEnd;
  QString mwdEngineers;
  QString directionalDrillers;
  QString sdlEngineers;
  QString adtEngineers;
  QString customerRep;
  QString customerGeo;
  QString resContactSpec;
  QString otherEngineers;

};

#endif // RUNINFOGENERAL_H
