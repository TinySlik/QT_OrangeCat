#ifndef WELLINFOFORMATION_H
#define WELLINFOFORMATION_H

#include "../../common/base/baseentity.h"

class WellInfoFormation : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( double depth READ getDepth WRITE setDepth)
  Q_PROPERTY( QString formation_name READ getFormationName WRITE setFormationName)
  Q_PROPERTY( int lithology_type READ getLithologyType WRITE setLithologyType)
  Q_PROPERTY( double dip READ getDip WRITE setDip)
  Q_PROPERTY( double dip_direction READ getDipDirection WRITE setDipDirection)
  Q_PROPERTY( QString formation_description READ getFormationDescription WRITE setFormationDescription)
  Q_PROPERTY( int period READ getPeriod WRITE setPeriod)
  Q_PROPERTY( QString epoch READ getEpoch WRITE setEpoch)

public:
  WellInfoFormation();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  double getDepth() const;
  void setDepth(double value);

  QString getFormationName() const;
  void setFormationName(const QString &value);

  int getLithologyType() const;
  void setLithologyType(int value);

  double getDip() const;
  void setDip(double value);

  double getDipDirection() const;
  void setDipDirection(double value);

  QString getFormationDescription() const;
  void setFormationDescription(const QString &value);

  int getPeriod() const;
  void setPeriod(int value);

  QString getEpoch() const;
  void setEpoch(const QString &value);

private:
  int id = 0;
  int wellInfoId;
  double depth;
  QString formationName;
  int lithologyType;
  double dip;
  double dipDirection;
  QString formationDescription;
  int period;
  QString epoch;
};

#endif // WELLINFOFORMATION_H
