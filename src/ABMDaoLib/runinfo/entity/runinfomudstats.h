#ifndef RUNINFOMUDSTATS_H
#define RUNINFOMUDSTATS_H

#include "../../common/base/baseentity.h"

class RunInfoMudStats : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( int mud_type READ getMudType WRITE setMudType)
  Q_PROPERTY( int ruid_type READ getRuidType WRITE setRuidType)
  Q_PROPERTY( int description READ getDescription WRITE setDescription)
  Q_PROPERTY( double density_avg READ getDensityAvg WRITE setDensityAvg)
  Q_PROPERTY( double density_min READ getDensityMin WRITE setDensityMin)
  Q_PROPERTY( double density_max READ getDensityMax WRITE setDensityMax)
  Q_PROPERTY( double solids READ getSolids WRITE setSolids)
  Q_PROPERTY( double sand READ getSand WRITE setSand)
  Q_PROPERTY( double mud_chlorides READ getMudChlorides WRITE setMudChlorides)
  Q_PROPERTY( double viscosity READ getViscosity WRITE setViscosity)
  Q_PROPERTY( double plastic_visc READ getPlasticVisc WRITE setPlasticVisc)
  Q_PROPERTY( double yield_point READ getYieldPoint WRITE setYieldPoint)
  Q_PROPERTY( double flow_avg READ getFlowAvg WRITE setFlowAvg)
  Q_PROPERTY( double flow_min READ getFlowMin WRITE setFlowMin)
  Q_PROPERTY( double flow_max READ getFlowMax WRITE setFlowMax)
  Q_PROPERTY( double annular_velocity READ getAnnularVelocity WRITE setAnnularVelocity)
  Q_PROPERTY( double max_ann_velocity READ getMaxAnnVelocity WRITE setMaxAnnVelocity)
  Q_PROPERTY( double critical_velocity READ getCriticalVelocity WRITE setCriticalVelocity)
  Q_PROPERTY( double max_crit_velocity READ getMaxCritVelocity WRITE setMaxCritVelocity)
  Q_PROPERTY( double bit_press_loss READ getBitPressLoss WRITE setBitPressLoss)
  Q_PROPERTY( double api_filtrate READ getApiFiltrate WRITE setApiFiltrate)
  Q_PROPERTY( double ph READ getPh WRITE setPh)
  Q_PROPERTY( double oil READ getOil WRITE setOil)
  Q_PROPERTY( double owr READ getOwr WRITE setOwr)
  Q_PROPERTY( double rm READ getRm WRITE setRm)
  Q_PROPERTY( double rm_temp READ getRmTemp WRITE setRmTemp)
  Q_PROPERTY( double rmf READ getRmf WRITE setRmf)
  Q_PROPERTY( double rmf_temp READ getRmfTemp WRITE setRmfTemp)
  Q_PROPERTY( double rmc READ getRmc WRITE setRmc)
  Q_PROPERTY( double rmc_temp READ getRmcTemp WRITE setRmcTemp)
  Q_PROPERTY( double rm_max_temp READ getRmMaxTemp WRITE setRmMaxTemp)
  Q_PROPERTY( QString max_temp_sensor READ getMaxTempSensor WRITE setMaxTempSensor)
  Q_PROPERTY( double max_tool_temp READ getMaxToolTemp WRITE setMaxToolTemp)
  Q_PROPERTY( QString gas_type READ getGasType WRITE setGasType)
  Q_PROPERTY( double combined_ecd READ getCombinedEcd WRITE setCombinedEcd)
  Q_PROPERTY( double gas_flow_avg READ getGasFlowAvg WRITE setGasFlowAvg)
  Q_PROPERTY( double gas_flow_min READ getGasFlowMin WRITE setGasFlowMin)
  Q_PROPERTY( double gas_flow_max READ getGasFlowMax WRITE setGasFlowMax)
  Q_PROPERTY( int foam READ getFoam WRITE setFoam)

public:
  RunInfoMudStats();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  int getMudType() const;
  void setMudType(int value);

  int getRuidType() const;
  void setRuidType(int value);

  int getDescription() const;
  void setDescription(int value);

  double getDensityAvg() const;
  void setDensityAvg(double value);

  double getDensityMin() const;
  void setDensityMin(double value);

  double getDensityMax() const;
  void setDensityMax(double value);

  double getSolids() const;
  void setSolids(double value);

  double getSand() const;
  void setSand(double value);

  double getMudChlorides() const;
  void setMudChlorides(double value);

  double getFlowAvg() const;
  void setFlowAvg(double value);

  double getFlowMin() const;
  void setFlowMin(double value);

  double getFlowMax() const;
  void setFlowMax(double value);

  double getAnnularVelocity() const;
  void setAnnularVelocity(double value);

  double getMaxAnnVelocity() const;
  void setMaxAnnVelocity(double value);

  double getCriticalVelocity() const;
  void setCriticalVelocity(double value);

  double getMaxCritVelocity() const;
  void setMaxCritVelocity(double value);

  double getBitPressLoss() const;
  void setBitPressLoss(double value);

  double getApiFiltrate() const;
  void setApiFiltrate(double value);

  double getPh() const;
  void setPh(double value);

  double getOil() const;
  void setOil(double value);

  double getOwr() const;
  void setOwr(double value);

  double getRm() const;
  void setRm(double value);

  double getRmTemp() const;
  void setRmTemp(double value);

  double getRmf() const;
  void setRmf(double value);

  double getRmfTemp() const;
  void setRmfTemp(double value);

  double getRmc() const;
  void setRmc(double value);

  double getRmcTemp() const;
  void setRmcTemp(double value);

  double getRmMaxTemp() const;
  void setRmMaxTemp(double value);

  QString getMaxTempSensor() const;
  void setMaxTempSensor(const QString &value);

  double getMaxToolTemp() const;
  void setMaxToolTemp(double value);

  QString getGasType() const;
  void setGasType(const QString &value);

  double getCombinedEcd() const;
  void setCombinedEcd(double value);

  double getGasFlowAvg() const;
  void setGasFlowAvg(double value);

  double getGasFlowMin() const;
  void setGasFlowMin(double value);

  double getGasFlowMax() const;
  void setGasFlowMax(double value);

  int getFoam() const;
  void setFoam(const int &value);

  double getViscosity() const;
  void setViscosity(double value);

  double getPlasticVisc() const;
  void setPlasticVisc(double value);

  double getYieldPoint() const;
  void setYieldPoint(double value);

private:
  int id = 0;
  int runInfoId;
  int mudType;
  int ruidType;
  int description;
  double densityAvg;
  double densityMin;
  double densityMax;
  double solids;
  double sand;
  double mudChlorides;

  double viscosity;
  double plasticVisc;
  double yieldPoint;

  double flowAvg;
  double flowMin;
  double flowMax;
  double annularVelocity;
  double maxAnnVelocity;
  double criticalVelocity;
  double maxCritVelocity;
  double bitPressLoss;

  double apiFiltrate;
  double ph;
  double oil;
  double owr;
  double rm;
  double rmTemp;
  double rmf;
  double rmfTemp;
  double rmc;
  double rmcTemp;
  double rmMaxTemp;
  QString maxTempSensor;
  double maxToolTemp;

  QString gasType;
  double combinedEcd;
  double gasFlowAvg;
  double gasFlowMin;
  double gasFlowMax;
  int foam;
};

#endif // RUNINFOMUDSTATS_H
