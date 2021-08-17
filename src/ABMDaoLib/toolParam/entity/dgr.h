#ifndef DGR_H
#define DGR_H

#include "../../common/base/baseentity.h"

class DGR : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( double dist_from READ getDistFrom WRITE setDistFrom)
  Q_PROPERTY( QString tool_size READ getToolSize WRITE setToolSize)
  Q_PROPERTY( double total_current_use READ getTotalCurrentUse WRITE setTotalCurrentUse)
  Q_PROPERTY( QString sub_sn READ getSubSN WRITE setSubSN)
  Q_PROPERTY( QString sw_version READ getSWVersion WRITE setSWVersion)
  Q_PROPERTY( double api_cali_fa_chan_a READ getApiCaliFaChanA WRITE setApiCaliFaChanA)
  Q_PROPERTY( double api_cali_fa_chan_b READ getApiCaliFaChanB WRITE setApiCaliFaChanB)
  Q_PROPERTY( double offset_chan_a READ getOffsetChanA WRITE setOffsetChanA)
  Q_PROPERTY( double offset_chan_b READ getOffsetChanB WRITE setOffsetChanB)
  Q_PROPERTY( int low_limit_chan_a READ getLowLimitChanA WRITE setLowLimitChanA)
  Q_PROPERTY( int low_limit_chan_b READ getLowLimitChanB WRITE setLowLimitChanB)
  Q_PROPERTY( int high_limit_chan_a READ getHighLimitChanA WRITE setHighLimitChanA)
  Q_PROPERTY( int high_limit_chan_b READ getHighLimitChanB WRITE setHighLimitChanB)
  Q_PROPERTY( int t_delay_first READ getTDelayFirst WRITE setTDelayFirst)
  Q_PROPERTY( int t_delay_second READ getTDelaySecond WRITE setTDelaySecond)
  Q_PROPERTY( int t_delay_third READ getTDelayThird WRITE setTDelayThird)
  Q_PROPERTY( int sample_period_first READ getSamplePeriodFirst WRITE setSamplePeriodFirst)
  Q_PROPERTY( int sample_period_second READ getSamplePeriodSecond WRITE setSamplePeriodSecond)
  Q_PROPERTY( int sample_period_third READ getSamplePeriodThird WRITE setSamplePeriodThird)


public:
  DGR();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  double getDistFrom() const;
  void setDistFrom(double value);

  QString getToolSize() const;
  void setToolSize(const QString &value);

  double getTotalCurrentUse() const;
  void setTotalCurrentUse(double value);

  QString getSubSN() const;
  void setSubSN(const QString &value);

  QString getSWVersion() const;
  void setSWVersion(const QString &value);

  double getApiCaliFaChanA() const;
  void setApiCaliFaChanA(double value);

  double getApiCaliFaChanB() const;
  void setApiCaliFaChanB(double value);

  double getOffsetChanA() const;
  void setOffsetChanA(double value);

  double getOffsetChanB() const;
  void setOffsetChanB(double value);

  int getLowLimitChanA() const;
  void setLowLimitChanA(int value);

  int getLowLimitChanB() const;
  void setLowLimitChanB(int value);

  int getHighLimitChanA() const;
  void setHighLimitChanA(int value);

  int getHighLimitChanB() const;
  void setHighLimitChanB(int value);

  int getTDelayFirst() const;
  void setTDelayFirst(int value);

  int getTDelaySecond() const;
  void setTDelaySecond(int value);

  int getTDelayThird() const;
  void setTDelayThird(int value);

  int getSamplePeriodFirst() const;
  void setSamplePeriodFirst(int value);

  int getSamplePeriodSecond() const;
  void setSamplePeriodSecond(int value);

  int getSamplePeriodThird() const;
  void setSamplePeriodThird(int value);

private:
  int id = 0;
  int wellInfoId;
  int runInfoId;
  double distFrom;
  QString toolSize;
  double totalCurrentUse;
  QString subSN;
  QString SWVersion;

  double apiCaliFaChanA;
  double apiCaliFaChanB;
  double offsetChanA;
  double offsetChanB;
  int lowLimitChanA;
  int lowLimitChanB;
  int highLimitChanA;
  int highLimitChanB;

  int tDelayFirst;
  int tDelaySecond;
  int tDelayThird;

  int samplePeriodFirst;
  int samplePeriodSecond;
  int samplePeriodThird;
};

#endif // DGR_H
