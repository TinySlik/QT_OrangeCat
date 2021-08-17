#ifndef WELLINFOSURVEYINFO_H
#define WELLINFOSURVEYINFO_H

#include "../../common/base/baseentity.h"

class WellInfoSurveyInfo : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( double verical_section_direction READ getVericalSectionDirection WRITE setVericalSectionDirection)
  Q_PROPERTY( int calc_vartical_section READ getCalcVarticalSection WRITE setCalcVarticalSection)
  Q_PROPERTY( int hole_position_calc_method READ getHolePositionCalcMethod WRITE setHolePositionCalcMethod)
  Q_PROPERTY( double bulk_density READ getBulkDensity WRITE setBulkDensity)
  Q_PROPERTY( int gravity_refe_calc_environment READ getGravityRefeCalcEnvironment WRITE setGravityRefeCalcEnvironment)
  Q_PROPERTY( double gravity_field_strength READ getGravityFieldStrength WRITE setGravityFieldStrength)
  Q_PROPERTY( double magnetic_filed_strength READ getMagneticFiledStrength WRITE setMagneticFiledStrength)
  Q_PROPERTY( double magnetic_dip_angle READ getMagneticDipAngle WRITE setMagneticDipAngle)
  Q_PROPERTY( QString magnetic_model READ getMagneticModel WRITE setMagneticModel)
  Q_PROPERTY( QDateTime magnetic_data_date READ getMagneticDataDate WRITE setMagneticDataDate)
  Q_PROPERTY( QString magnetic_field_data_source READ getMagneticFieldDataSource WRITE setMagneticFieldDataSource)
  Q_PROPERTY( int north_reference READ getNorthReference WRITE setNorthReference)
  Q_PROPERTY( double total_correction READ getTotalCorrection WRITE setTotalCorrection)
  Q_PROPERTY( double mag_dedination READ getMagDedination WRITE setMagDedination)
  Q_PROPERTY( double grid_convergence READ getGridConvergence WRITE setGridConvergence)
  Q_PROPERTY( int checksum_insite_calculated READ getChecksumInsiteCalculated WRITE setChecksumInsiteCalculated)
  Q_PROPERTY( QString checksum_insite_magutm READ getChecksumInsiteMagutm WRITE setChecksumInsiteMagutm)
  Q_PROPERTY( int checksum_dos_calculated READ getChecksumDosCalculated WRITE setChecksumDosCalculated)


public:
  WellInfoSurveyInfo();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  double getVericalSectionDirection() const;
  void setVericalSectionDirection(double value);

  int getCalcVarticalSection() const;
  void setCalcVarticalSection(int value);

  int getHolePositionCalcMethod() const;
  void setHolePositionCalcMethod(int value);

  double getBulkDensity() const;
  void setBulkDensity(double value);

  int getGravityRefeCalcEnvironment() const;
  void setGravityRefeCalcEnvironment(int value);

  double getGravityFieldStrength() const;
  void setGravityFieldStrength(double value);

  double getMagneticFiledStrength() const;
  void setMagneticFiledStrength(double value);

  QString getMagneticModel() const;
  void setMagneticModel(const QString &value);

  QDateTime getMagneticDataDate() const;
  void setMagneticDataDate(const QDateTime &value);

  QString getMagneticFieldDataSource() const;
  void setMagneticFieldDataSource(const QString &value);

  int getNorthReference() const;
  void setNorthReference(int value);

  double getTotalCorrection() const;
  void setTotalCorrection(double value);

  double getMagDedination() const;
  void setMagDedination(double value);

  double getGridConvergence() const;
  void setGridConvergence(double value);

  int getChecksumInsiteCalculated() const;
  void setChecksumInsiteCalculated(int value);

  QString getChecksumInsiteMagutm() const;
  void setChecksumInsiteMagutm(const QString &value);

  int getChecksumDosCalculated() const;
  void setChecksumDosCalculated(int value);

  double getMagneticDipAngle() const;
  void setMagneticDipAngle(double value);

private:
  int id = 0;
  int wellInfoId;
  double vericalSectionDirection;
  int calcVarticalSection;
  int holePositionCalcMethod;
  double bulkDensity;
  int gravityRefeCalcEnvironment;
  double gravityFieldStrength;
  double magneticFiledStrength;
  double magneticDipAngle;
  QString magneticModel;
  QDateTime magneticDataDate;
  QString magneticFieldDataSource;
  int northReference;
  double totalCorrection;
  double magDedination;
  double gridConvergence;
  int checksumInsiteCalculated;
  QString checksumInsiteMagutm;
  int checksumDosCalculated;

};

#endif // WELLINFOSURVEYINFO_H

