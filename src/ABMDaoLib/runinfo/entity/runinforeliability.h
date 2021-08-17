#ifndef RUNINFORELIABILITY_H
#define RUNINFORELIABILITY_H

#include "../../common/base/baseentity.h"

class RunInfoReliability : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( int jarring_occurred READ getJarringOccurred WRITE setJarringOccurred)
  Q_PROPERTY( int outside_of_spec READ getOutsideOfSpec WRITE setOutsideOfSpec)
  Q_PROPERTY( QString run_comments READ getRunComments WRITE setRunComments)
  Q_PROPERTY( QString mwd_transmission_method READ getMwdTransmssionMethod WRITE setMwdTransmssionMethod)
  Q_PROPERTY( double mwd_tool_od READ getMwdToolOd WRITE setMwdToolOd)
  Q_PROPERTY( int mwd_service_interrupt READ getMwdServiceInterrupt WRITE setMwdServiceInterrupt)
  Q_PROPERTY( int mwd_trip READ getMwdTrip WRITE setMwdTrip)
  Q_PROPERTY( double mwd_npt READ getMwdNPT WRITE setMwdNPT)
  Q_PROPERTY( int mwd_high_flow READ getMwdHighFlow WRITE setMwdHighFlow)
  Q_PROPERTY( int mwd_high_temp150 READ getMwdHighTemp150 WRITE setMwdHighTemp150)
  Q_PROPERTY( int mwd_high_pressure18k READ getMwdHighPressure18k WRITE setMwdHighPressure18k)
  Q_PROPERTY( QString mwd_geo_span_sn READ getMwdGeoSpanSn WRITE setMwdGeoSpanSn)
  Q_PROPERTY( QString mwd_virtual_string_number READ getMwdVirtualStringNumber WRITE setMwdVirtualStringNumber)
  Q_PROPERTY( int dd_directional_service READ getDdDirectionalService WRITE setDdDirectionalService)
  Q_PROPERTY( int dd_motor_type READ getDdMotorType WRITE setDdMotorType)
  Q_PROPERTY( int dd_service_interrupt READ getDdServiceInterrupt WRITE setDdServiceInterrupt)
  Q_PROPERTY( int dd_trip READ getDdTrip WRITE setDdTrip)
  Q_PROPERTY( double dd_npt READ getDdNpt WRITE setDdNpt)
  Q_PROPERTY( int sdl_service_inte READ getSdlServiceInterrupt WRITE setSdlServiceInterrupt)
  Q_PROPERTY( double sdl_npt READ getSdlNPT WRITE setSdlNPT)
  Q_PROPERTY( QString sdl_data_transfer_rigsite READ getSdlDataTransferRigsite WRITE setSdlDataTransferRigsite)
  Q_PROPERTY( QString sdl_data_transfer_to_town READ getSdlDataTransferToTown WRITE setSdlDataTransferToTown)
  Q_PROPERTY( QString sdl_add_on_services READ getSdlAddOnServices WRITE setSdlAddOnServices)

public:
  RunInfoReliability();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  int getJarringOccurred() const;
  void setJarringOccurred(int value);

  int getOutsideOfSpec() const;
  void setOutsideOfSpec(int value);

  QString getRunComments() const;
  void setRunComments(const QString &value);

  double getMwdToolOd() const;
  void setMwdToolOd(double value);

  int getMwdServiceInterrupt() const;
  void setMwdServiceInterrupt(int value);

  int getMwdTrip() const;
  void setMwdTrip(int value);

  int getMwdHighFlow() const;
  void setMwdHighFlow(int value);

  int getMwdHighTemp150() const;
  void setMwdHighTemp150(int value);

  int getMwdHighPressure18k() const;
  void setMwdHighPressure18k(int value);

  QString getMwdGeoSpanSn() const;
  void setMwdGeoSpanSn(const QString &value);

  QString getMwdVirtualStringNumber() const;
  void setMwdVirtualStringNumber(const QString &value);

  int getDdDirectionalService() const;
  void setDdDirectionalService(int value);

  int getDdMotorType() const;
  void setDdMotorType(int value);

  int getDdServiceInterrupt() const;
  void setDdServiceInterrupt(int value);

  int getDdTrip() const;
  void setDdTrip(int value);

  double getDdNpt() const;
  void setDdNpt(double value);

  QString getSdlDataTransferRigsite() const;
  void setSdlDataTransferRigsite(const QString &value);

  QString getSdlDataTransferToTown() const;
  void setSdlDataTransferToTown(const QString &value);

  QString getSdlAddOnServices() const;
  void setSdlAddOnServices(const QString &value);

  QString getMwdTransmssionMethod() const;
  void setMwdTransmssionMethod(const QString &value);

  double getMwdNPT() const;
  void setMwdNPT(double value);

  int getSdlServiceInterrupt() const;
  void setSdlServiceInterrupt(int value);

  double getSdlNPT() const;
  void setSdlNPT(double value);

private:
  int id = 0;
  int runInfoId;
  int jarringOccurred;
  int outsideOfSpec;
  QString runComments;
  QString mwdTransmssionMethod;
  double mwdToolOd;
  int mwdServiceInterrupt;
  int mwdTrip;
  double mwdNPT;
  int mwdHighFlow;
  int mwdHighTemp150;
  int mwdHighPressure18k;
  QString mwdGeoSpanSn;
  QString mwdVirtualStringNumber;
  int ddDirectionalService;
  int ddMotorType;
  int ddServiceInterrupt;
  int ddTrip;
  double ddNpt;
  int sdlServiceInterrupt;
  double sdlNPT;
  QString sdlDataTransferRigsite;
  QString sdlDataTransferToTown;
  QString sdlAddOnServices;

};

#endif // RUNINFORELIABILITY_H
