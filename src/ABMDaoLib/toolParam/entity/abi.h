#ifndef ABI_H
#define ABI_H

#include "../../common/base/baseentity.h"

class ABI : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( double dist_from READ getDistFrom WRITE setDistFrom)
  Q_PROPERTY( QString sw_version READ getSWVersion WRITE setSWVersion)
  Q_PROPERTY( QString receiver_sn READ getReceiverSN WRITE setReceiverSN)
  Q_PROPERTY( QString receiver_version READ getReceiverVersion WRITE setReceiverVersion)
  Q_PROPERTY( QString receiver_tx_sn READ getReceiverTXSN WRITE setReceiverTXSN)
  Q_PROPERTY( QString receiver_gm_sn READ getReceiverGMSN WRITE setReceiverB1SN)
  Q_PROPERTY( QString receiver_b1_sn READ getReceiverB1SN WRITE setReceiverB1SN)
  Q_PROPERTY( QString receiver_b2_sn READ getReceiverB2SN WRITE setReceiverB2SN)
  Q_PROPERTY( QString transmitter_sn READ getTransmitterSN WRITE setTransmitterSN)
  Q_PROPERTY( QString transmitter_version READ getTransmitterVersion WRITE setTransmitterVersion)
  Q_PROPERTY( QString inserter_sn READ getInserterSN WRITE setInserterSN)
  Q_PROPERTY( QString inserter_pre_amp_sn READ getInserterPreAMPSN WRITE setInserterPreAMPSN)
  Q_PROPERTY( QString inserter_rx_sn READ getInserterRXSN WRITE setInserterRXSN)
  Q_PROPERTY( QString inserter_rtc_sn READ getInserterRTCSN WRITE setInserterRTCSN)
  Q_PROPERTY( double ivss_moderate_avg READ getIVSSModerateAvg WRITE setIVSSExcessiveAvg)
  Q_PROPERTY( double ivss_moderate_shock READ getIVSSModerateShock WRITE setIVSSModerateShock)
  Q_PROPERTY( double ivss_high_avg READ getIVSSHighAvg WRITE setIVSSExcessiveAvg)
  Q_PROPERTY( double ivss_high_shock READ getIVSSHighShock WRITE setIVSSHighShock)
  Q_PROPERTY( double ivss_excessive_avg READ getIVSSExcessiveAvg WRITE setIVSSExcessiveAvg)
  Q_PROPERTY( double ivss_excessive_shock READ getIVSSExcessiveShock WRITE setIVSSExcessiveShock)

public:
  ABI();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  double getDistFrom() const;
  void setDistFrom(double value);

  QString getSWVersion() const;
  void setSWVersion(const QString &value);

  QString getReceiverSN() const;
  void setReceiverSN(const QString &value);

  QString getReceiverVersion() const;
  void setReceiverVersion(const QString &value);

  QString getReceiverTXSN() const;
  void setReceiverTXSN(const QString &value);

  QString getReceiverGMSN() const;
  void setReceiverGMSN(const QString &value);

  QString getReceiverB1SN() const;
  void setReceiverB1SN(const QString &value);

  QString getReceiverB2SN() const;
  void setReceiverB2SN(const QString &value);

  QString getTransmitterSN() const;
  void setTransmitterSN(const QString &value);

  QString getTransmitterVersion() const;
  void setTransmitterVersion(const QString &value);

  QString getInserterSN() const;
  void setInserterSN(const QString &value);

  QString getInserterPreAMPSN() const;
  void setInserterPreAMPSN(const QString &value);

  QString getInserterRXSN() const;
  void setInserterRXSN(const QString &value);

  QString getInserterRTCSN() const;
  void setInserterRTCSN(const QString &value);

  double getIVSSModerateAvg() const;
  void setIVSSModerateAvg(double value);

  double getIVSSModerateShock() const;
  void setIVSSModerateShock(double value);

  double getIVSSHighAvg() const;
  void setIVSSHighAvg(double value);

  double getIVSSHighShock() const;
  void setIVSSHighShock(double value);

  double getIVSSExcessiveAvg() const;
  void setIVSSExcessiveAvg(double value);

  double getIVSSExcessiveShock() const;
  void setIVSSExcessiveShock(double value);

private:
  int id = 0;
  int runInfoId;
  int wellInfoId;
  double distFrom = 0;
  QString SWVersion;        //软件版本
  //接收钻铤
  QString receiverSN;       //编号
  QString receiverVersion;  //版本号
  QString receiverTXSN;     //发射模块编号
  QString receiverGMSN;     //伽玛模块编号
  QString receiverB1SN;     //电池模块1编号
  QString receiverB2SN;     //电池模块2编号

  //发射钻铤
  QString transmitterSN;    //编号
  QString transmitterVersion;  //版本号

  //插入体
  QString inserterSN;       //编号
  QString inserterPreAMPSN; //前置放大编号
  QString inserterRXSN;     //接收主控编号
  QString inserterRTCSN;    //RTC电池编号

  double IVSSModerateAvg;
  double IVSSModerateShock;
  double IVSSHighAvg;
  double IVSSHighShock;
  double IVSSExcessiveAvg;
  double IVSSExcessiveShock;

};

#endif // ABI_H
