#ifndef WELLINFODISTANCES_H
#define WELLINFODISTANCES_H

#include "../../common/base/baseentity.h"

class WellInfoDistances : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( double drill_floor READ getDrillFloor WRITE setDrillFloor)
  Q_PROPERTY( double ground_level READ getGroundLevel WRITE setGroundLevel)
  Q_PROPERTY( double kelly_bushing READ getKellyBushing WRITE setKellyBushing)
  Q_PROPERTY( double water_depth READ getWaterDepth WRITE setWaterDepth)
  Q_PROPERTY( double air_gap READ getAirGap WRITE setAirGap)
  Q_PROPERTY( QString permanent_datum READ getPermanentDatum WRITE setPermanentDatum)
  Q_PROPERTY( double elevation_of_pd READ getElevationOfPd WRITE setElevationOfPd)
  Q_PROPERTY( QString log_measured_from READ getLogMeasuredFrom WRITE setLogMeasuredFrom)
  Q_PROPERTY( double height_abovePd READ getHeightAbovePd WRITE setHeightAbovePd)
  Q_PROPERTY( QString drilling_measured_from READ getDrillingMeasuredFrom WRITE setDrillingMeasuredFrom)
  Q_PROPERTY( double trav_block_weight READ getTravBlockWeight WRITE setTravBlockWeight)
  Q_PROPERTY( QString lines_strung READ getLinesStrung WRITE setLinesStrung)
  Q_PROPERTY( int mechanical_efficency READ getMechanicalEfficency WRITE setMechanicalEfficency)
  Q_PROPERTY( int tvdss_reference READ getTvdssReference WRITE setTvdssReference)

public:
  WellInfoDistances();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  double getDrillFloor() const;
  void setDrillFloor(double value);

  double getGroundLevel() const;
  void setGroundLevel(double value);

  double getKellyBushing() const;
  void setKellyBushing(double value);

  double getWaterDepth() const;
  void setWaterDepth(double value);

  double getAirGap() const;
  void setAirGap(double value);

  QString getPermanentDatum() const;
  void setPermanentDatum(const QString &value);

  double getElevationOfPd() const;
  void setElevationOfPd(double value);

  QString getLogMeasuredFrom() const;
  void setLogMeasuredFrom(const QString &value);

  double getHeightAbovePd() const;
  void setHeightAbovePd(double value);

  QString getDrillingMeasuredFrom() const;
  void setDrillingMeasuredFrom(const QString &value);

  QString getLinesStrung() const;
  void setLinesStrung(const QString &value);

  double getMechanicalEfficency() const;
  void setMechanicalEfficency(double value);

  double getTvdssReference() const;
  void setTvdssReference(double value);

  double getTravBlockWeight() const;
  void setTravBlockWeight(double value);

private:
  int id = 0;
  int wellInfoId;
  double drillFloor;
  double groundLevel;
  double kellyBushing;
  double waterDepth;
  double airGap;
  QString permanentDatum;
  double elevationOfPd;
  QString logMeasuredFrom;
  double heightAbovePd;
  QString drillingMeasuredFrom;
  double travBlockWeight;
  QString linesStrung;
  double mechanicalEfficency;
  double tvdssReference;

};

#endif // WELLINFODISTANCES_H
