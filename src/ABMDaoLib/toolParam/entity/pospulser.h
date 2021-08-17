#ifndef POSPULSER_H
#define POSPULSER_H

#include "../../common/base/baseentity.h"

class PosPulser : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( QString hochos_sn READ getHochosSN WRITE setHochosSN)
  Q_PROPERTY( QString pulser_sn READ getPulserSN WRITE setPulserSN)
  Q_PROPERTY( QString nmdc_sn READ getNmdcSN WRITE setNmdcSN)
  Q_PROPERTY( double stator_angle READ getStatorAngle WRITE setStatorAngle)
  Q_PROPERTY( double impeller_angle READ getImpellerAngle WRITE setImpellerAngle)
  Q_PROPERTY( double orifice_size READ getOrificeSize WRITE setOrificeSize)
  Q_PROPERTY( double standoff_size READ getStandoffSize WRITE setStandoffSize)
  Q_PROPERTY( QString pulser_name READ getPulserName WRITE setPulserName)
  Q_PROPERTY( QString oil_type READ getOilType WRITE setOilType)


public:
  PosPulser();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  QString getHochosSN() const;
  void setHochosSN(const QString &value);

  QString getPulserSN() const;
  void setPulserSN(const QString &value);

  QString getNmdcSN() const;
  void setNmdcSN(const QString &value);

  double getStatorAngle() const;
  void setStatorAngle(double value);

  double getImpellerAngle() const;
  void setImpellerAngle(double value);

  double getOrificeSize() const;
  void setOrificeSize(double value);

  double getStandoffSize() const;
  void setStandoffSize(double value);

  QString getPulserName() const;
  void setPulserName(const QString &value);

  QString getOilType() const;
  void setOilType(const QString &value);

private:
  int id = 0;
  int runInfoId;
  int wellInfoId;
  QString hochosSN;
  QString pulserSN;
  QString nmdcSN;
  double statorAngle;
  double impellerAngle;
  double orificeSize;
  double standoffSize;
  QString pulserName;
  QString oilType;

};

#endif // POSPULSER_H
