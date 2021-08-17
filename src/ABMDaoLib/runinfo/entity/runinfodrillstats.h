#ifndef RUNINFODRILLSTATS_H
#define RUNINFODRILLSTATS_H

#include "../../common/base/baseentity.h"

class RunInfoDrillStats : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( double start_inc READ getStartInc WRITE setStartInc)
  Q_PROPERTY( double inc_min READ getIncMin WRITE setIncMin)
  Q_PROPERTY( double inc_min_depth READ getIncMinDepth WRITE setIncMinDepth)
  Q_PROPERTY( double inc_max READ getIncMax WRITE setIncMax)
  Q_PROPERTY( double inc_max_depth READ getIncMaxDepth WRITE setIncMaxDepth)
  Q_PROPERTY( double final_inc READ getFinalInc WRITE setFinalInc)
  Q_PROPERTY( double start_azimuth READ getStartAzimuth WRITE setStartAzimuth)
  Q_PROPERTY( double final_azimuth READ getFinalAzimuth WRITE setFinalAzimuth)
  Q_PROPERTY( double max_ori_dogleg READ getMaxOriDogleg WRITE setMaxOriDogleg)
  Q_PROPERTY( double avg_ori_dogleg READ getAvgOriDogleg WRITE setAvgOriDogleg)
  Q_PROPERTY( double max_rot_dogleg READ getMaxRotDogleg WRITE setMaxRotDogleg)
  Q_PROPERTY( double avg_rot_build READ getAvgRotBuild WRITE setAvgRotBuild)
  Q_PROPERTY( double avg_rot_walk READ getAvgRotWalk WRITE setAvgRotWalk)
  Q_PROPERTY( double max_dog_pushed READ getMaxDogPushed WRITE setMaxDogPushed)
  Q_PROPERTY( double max_dog_pulled READ getMaxDogPulled WRITE setMaxDogPulled)
  Q_PROPERTY( double operating_hours READ getOperatingHours WRITE setOperatingHours)
  Q_PROPERTY( double circulating_hours READ getCirculatingHours WRITE setCirculatingHours)
  Q_PROPERTY( double drilling_hours READ getDrillingHours WRITE setDrillingHours)
  Q_PROPERTY( double reaming_hours READ getReamingHours WRITE setReamingHours)
  Q_PROPERTY( double mwd_borehole_size READ getMwdBoreholeSize WRITE setMwdBoreholeSize)
  Q_PROPERTY( double hole_opened_to_size READ getHoleOpenedToSize WRITE setHoleOpenedToSize)
  Q_PROPERTY( QString mwd_position_relative READ getMwdPositionRelative WRITE setMwdPositionRelative)
  Q_PROPERTY( double spp_min READ getSppMin WRITE setSppMin)
  Q_PROPERTY( double spp_max READ getSppMax WRITE setSppMax)
  Q_PROPERTY( double spp READ getSpp WRITE setSpp)
  Q_PROPERTY( double max_op_press READ getMaxOpPress WRITE setMaxOpPress)
  Q_PROPERTY( double total_bit_rev READ getTotalBitRev WRITE setTotalBitRev)
  Q_PROPERTY( double wob READ getWob WRITE setWob)
  Q_PROPERTY( double wob_overpull READ getWobOverpull WRITE setWobOverpull)
  Q_PROPERTY( double wob_max READ getWobMax WRITE setWobMax)
  Q_PROPERTY( double rop READ getRop WRITE setRop)
  Q_PROPERTY( double rop_min READ getRopMin WRITE setRopMin)
  Q_PROPERTY( double rop_max READ getRopMax WRITE setRopMax)
  Q_PROPERTY( double rpm READ getRpm WRITE setRpm)
  Q_PROPERTY( double rpm_min READ getRpmMin WRITE setRpmMin)
  Q_PROPERTY( double rpm_max READ getRpmMax WRITE setRpmMax)
  Q_PROPERTY( double torque_avg READ getTorqueAvg WRITE setTorqueAvg)
  Q_PROPERTY( double torque_min READ getTorqueMin WRITE setTorqueMin)
  Q_PROPERTY( double torque_max READ getTorqueMax WRITE setTorqueMax)
  Q_PROPERTY( double bending_moment_avg READ getBendingMomentAvg WRITE setBendingMomentAvg)
  Q_PROPERTY( double bending_moment_min READ getBendingMomentMin WRITE setBendingMomentMin)
  Q_PROPERTY( double bending_moment_max READ getBendingMomentMax WRITE setBendingMomentMax)

public:
  RunInfoDrillStats();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  double getStartInc() const;
  void setStartInc(double value);

  double getIncMin() const;
  void setIncMin(double value);

  double getIncMinDepth() const;
  void setIncMinDepth(double value);

  double getIncMax() const;
  void setIncMax(double value);

  double getIncMaxDepth() const;
  void setIncMaxDepth(double value);

  double getFinalInc() const;
  void setFinalInc(double value);

  double getStartAzimuth() const;
  void setStartAzimuth(double value);

  double getFinalAzimuth() const;
  void setFinalAzimuth(double value);

  double getMaxOriDogleg() const;
  void setMaxOriDogleg(double value);

  double getAvgOriDogleg() const;
  void setAvgOriDogleg(double value);

  double getMaxRotDogleg() const;
  void setMaxRotDogleg(double value);

  double getAvgRotBuild() const;
  void setAvgRotBuild(double value);

  double getAvgRotWalk() const;
  void setAvgRotWalk(double value);

  double getMaxDogPushed() const;
  void setMaxDogPushed(double value);

  double getMaxDogPulled() const;
  void setMaxDogPulled(double value);

  double getOperatingHours() const;
  void setOperatingHours(double value);

  double getCirculatingHours() const;
  void setCirculatingHours(double value);

  double getDrillingHours() const;
  void setDrillingHours(double value);

  double getReamingHours() const;
  void setReamingHours(double value);

  double getMwdBoreholeSize() const;
  void setMwdBoreholeSize(double value);

  double getHoleOpenedToSize() const;
  void setHoleOpenedToSize(double value);

  QString getMwdPositionRelative() const;
  void setMwdPositionRelative(const QString &value);

  double getSppMin() const;
  void setSppMin(double value);

  double getSppMax() const;
  void setSppMax(double value);

  double getSpp() const;
  void setSpp(double value);

  double getMaxOpPress() const;
  void setMaxOpPress(double value);

  double getTotalBitRev() const;
  void setTotalBitRev(double value);

  double getWob() const;
  void setWob(double value);

  double getWobOverpull() const;
  void setWobOverpull(double value);

  double getWobMax() const;
  void setWobMax(double value);

  double getRop() const;
  void setRop(double value);

  double getRopMin() const;
  void setRopMin(double value);

  double getRopMax() const;
  void setRopMax(double value);

  double getRpm() const;
  void setRpm(double value);

  double getRpmMin() const;
  void setRpmMin(double value);

  double getRpmMax() const;
  void setRpmMax(double value);

  double getTorqueAvg() const;
  void setTorqueAvg(double value);

  double getTorqueMin() const;
  void setTorqueMin(double value);

  double getTorqueMax() const;
  void setTorqueMax(double value);

  double getBendingMomentAvg() const;
  void setBendingMomentAvg(double value);

  double getBendingMomentMin() const;
  void setBendingMomentMin(double value);

  double getBendingMomentMax() const;
  void setBendingMomentMax(double value);

private:
  int id = 0;
  int runInfoId;
  double startInc;
  double incMin;
  double incMinDepth;
  double incMax;
  double incMaxDepth;
  double finalInc;

  double startAzimuth;
  double finalAzimuth;

  double maxOriDogleg;
  double avgOriDogleg;
  double maxRotDogleg;
  double avgRotBuild;
  double avgRotWalk;
  double maxDogPushed;
  double maxDogPulled;

  double operatingHours;
  double circulatingHours;
  double drillingHours;
  double reamingHours;

  double mwdBoreholeSize;
  double holeOpenedToSize;
  QString mwdPositionRelative;

  double sppMin;
  double sppMax;
  double spp;

  double maxOpPress;
  double totalBitRev;

  double wob;
  double wobOverpull;
  double wobMax;

  double rop;
  double ropMin;
  double ropMax;

  double rpm;
  double rpmMin;
  double rpmMax;

  double torqueAvg;
  double torqueMin;
  double torqueMax;

  double bendingMomentAvg;
  double bendingMomentMin;
  double bendingMomentMax;


};

#endif // RUNINFODRILLSTATS_H
