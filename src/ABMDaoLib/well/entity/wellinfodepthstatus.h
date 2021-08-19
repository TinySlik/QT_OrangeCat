#ifndef WELLINFODEPTHSTATUS_H
#define WELLINFODEPTHSTATUS_H

#include <QObject>

#include "../../common/base/baseentity.h"

#define CUSTOM_PROPERTY_TINI(yu, type, target) yu:\
  Q_PROPERTY(type target READ get##target WRITE set##target)\
  type target;\
  public:\
  inline type get##target() const {return target;} \
  inline void set##target(type value){target = value;}

struct WellInfoDepthStatus : public BaseEntity
{
  Q_OBJECT
  // test
  CUSTOM_PROPERTY_TINI(public, int, id)
  CUSTOM_PROPERTY_TINI(public, QString, well_id)
  CUSTOM_PROPERTY_TINI(public, QString, well_name)
  CUSTOM_PROPERTY_TINI(public, QString, customer_name)
  CUSTOM_PROPERTY_TINI(public, QString, platform)
  CUSTOM_PROPERTY_TINI(public, QString, rig_name)
  CUSTOM_PROPERTY_TINI(public, QString, field_name)
  CUSTOM_PROPERTY_TINI(public, QString, country)
  CUSTOM_PROPERTY_TINI(public, QDateTime, well_start_time)
  CUSTOM_PROPERTY_TINI(public, QDateTime, well_end_time)
  CUSTOM_PROPERTY_TINI(public, QDateTime, well_spud_time)
  CUSTOM_PROPERTY_TINI(public, QString, well_type)
  CUSTOM_PROPERTY_TINI(public, double, start_depth)
  CUSTOM_PROPERTY_TINI(public, double, end_depth)
  CUSTOM_PROPERTY_TINI(public, double, rig_cost)
  CUSTOM_PROPERTY_TINI(public, QString, api_sn_uwi)
  CUSTOM_PROPERTY_TINI(public, QString, doe_number)
  CUSTOM_PROPERTY_TINI(public, QString, contractor)
  CUSTOM_PROPERTY_TINI(public, QString, dir_contractor)
  CUSTOM_PROPERTY_TINI(public, QString, job_number)
  CUSTOM_PROPERTY_TINI(public, QString, job_ticker_number)
  CUSTOM_PROPERTY_TINI(public, QString, halliburton_district)
  CUSTOM_PROPERTY_TINI(public, QString, unit_number)
  CUSTOM_PROPERTY_TINI(public, QString, lease_name)
  CUSTOM_PROPERTY_TINI(public, QString, section)
  CUSTOM_PROPERTY_TINI(public, QString, township)
  CUSTOM_PROPERTY_TINI(public, QString, range)
  CUSTOM_PROPERTY_TINI(public, QString, pad)
  CUSTOM_PROPERTY_TINI(public, QString, slot)
  CUSTOM_PROPERTY_TINI(public, QString, block)
  CUSTOM_PROPERTY_TINI(public, QString, sub_block)
public:

  WellInfoDepthStatus();
};

#undef CUSTOM_PROPERTY_TINI

#endif // WELLINFODEPTHSTATUS_H
