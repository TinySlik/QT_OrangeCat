#ifndef WELLINFOLOCATION_H
#define WELLINFOLOCATION_H

#include "../../common/base/baseentity.h"

class WellInfoLocation : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY(int id READ getId WRITE setId)
  Q_PROPERTY(int well_info_id READ getWellInfoId WRITE setWellInfoId)

  Q_PROPERTY(int geog_latitude_deg READ getGeogLatitudeDeg WRITE setGeogLatitudeDeg)
  Q_PROPERTY(int geog_latitude_min READ getGeogLatitudeMin WRITE setGeogLatitudeMin)
  Q_PROPERTY(double geog_latitude_sec READ getGeogLatitudeSec WRITE setGeogLatitudeSec)
  Q_PROPERTY(QString geog_latitude_dire READ getGeogLatitudeDire WRITE setGeogLatitudeDire)

  Q_PROPERTY(int geog_longitude_deg READ getGeogLongitudeDeg WRITE setGeogLongitudeDeg)
  Q_PROPERTY(int geog_longitude_min READ getGeogLongitudeMin WRITE setGeogLongitudeMin)
  Q_PROPERTY(double geog_longitude_sec READ getGeogLongitudeSec WRITE setGeogLongitudeSec)
  Q_PROPERTY(QString geog_longitude_dire READ getGeogLongitudeDire WRITE setGeogLongitudeDire)

  Q_PROPERTY(QString geog_sys_desc READ getGeogSysDesc WRITE setGeogSysDesc)
  Q_PROPERTY(QString geog_sys_proj_method READ getGeogSysProjMethod WRITE setGeogSysProjMethod)
  Q_PROPERTY(QString geog_sys_reference READ getGeogSysReference WRITE setGeogSysReference)
  Q_PROPERTY(QString geog_sys_grid_system READ getGeogSysGridSystem WRITE setGeogSysGridSystem)
  Q_PROPERTY(QString geog_sys_group READ getGeogSysGroup WRITE setGeogSysGroup)

  Q_PROPERTY(double cart_northing READ getCartNorthing WRITE setCartNorthing)
  Q_PROPERTY(double cart_easting READ getCartEasting WRITE setCartEasting)
  Q_PROPERTY(QString cart_sys_desc READ getCartSysDesc WRITE setCartSysDesc)
  Q_PROPERTY(QString cart_sys_proj_method READ getCartSysProjMethod WRITE setCartSysProjMethod)
  Q_PROPERTY(QString cart_sys_reference READ getCartSysReference WRITE setCartSysReference)
  Q_PROPERTY(QString cart_sys_grid_system READ getCartSysGridSystem WRITE setCartSysGridSystem)
  Q_PROPERTY(QString cart_sys_group READ getCartSysGroup WRITE setCartSysGroup)
  Q_PROPERTY(double cart_sys_central_meridian READ getCartSysCentralMeridian WRITE setCartSysCentralMeridian)

  Q_PROPERTY(double wellhead_offset_north_south READ getWellheadOffsetNorthSouth WRITE setWellheadOffsetNorthSouth)
  Q_PROPERTY(double wellhead_offset_east_west READ getWellheadOffsetEastWest WRITE setWellheadOffsetEastWest)

  Q_PROPERTY(double vertical_section_offset_north_south READ getVerticalSectionOffsetNorthSouth WRITE setVerticalSectionOffsetNorthSouth)
  Q_PROPERTY(double vertical_section_offset_east_west READ getVerticalSectionOffsetEastWest WRITE setVerticalSectionOffsetEastWest)

  Q_PROPERTY(double wellhead_distance_north_south READ getWellheadDistanceNorthSouth WRITE setWellheadDistanceNorthSouth)
  Q_PROPERTY(double wellhead_distance_east_west READ getWellheadDistanceEastWest WRITE setWellheadDistanceEastWest)
  Q_PROPERTY(QString wellhead_distance_north_south_format READ getWellheadDistanceNorthSouthFormat WRITE setWellheadDistanceNorthSouthFormat)
  Q_PROPERTY(QString wellhead_distance_east_west_format READ getWellheadDistanceEastWestFormat WRITE setWellheadDistanceEastWestFormat)
public:
  WellInfoLocation();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getGeogLatitudeDeg() const;
  void setGeogLatitudeDeg(int value);

  int getGeogLatitudeMin() const;
  void setGeogLatitudeMin(int value);

  double getGeogLatitudeSec() const;
  void setGeogLatitudeSec(double value);

  QString getGeogLatitudeDire() const;
  void setGeogLatitudeDire(const QString &value);

  int getGeogLongitudeDeg() const;
  void setGeogLongitudeDeg(int value);

  int getGeogLongitudeMin() const;
  void setGeogLongitudeMin(int value);

  double getGeogLongitudeSec() const;
  void setGeogLongitudeSec(double value);

  QString getGeogLongitudeDire() const;
  void setGeogLongitudeDire(const QString &value);

  QString getGeogSysDesc() const;
  void setGeogSysDesc(const QString &value);

  QString getGeogSysProjMethod() const;
  void setGeogSysProjMethod(const QString &value);

  QString getGeogSysReference() const;
  void setGeogSysReference(const QString &value);

  QString getGeogSysGridSystem() const;
  void setGeogSysGridSystem(const QString &value);

  QString getGeogSysGroup() const;
  void setGeogSysGroup(const QString &value);

  double getCartNorthing() const;
  void setCartNorthing(double value);

  double getCartEasting() const;
  void setCartEasting(double value);

  QString getCartSysDesc() const;
  void setCartSysDesc(const QString &value);

  QString getCartSysProjMethod() const;
  void setCartSysProjMethod(const QString &value);

  QString getCartSysReference() const;
  void setCartSysReference(const QString &value);

  double getCartSysCentralMeridian() const;
  void setCartSysCentralMeridian(double value);

  double getWellheadOffsetNorthSouth() const;
  void setWellheadOffsetNorthSouth(double value);

  double getWellheadOffsetEastWest() const;
  void setWellheadOffsetEastWest(double value);

  double getVerticalSectionOffsetNorthSouth() const;
  void setVerticalSectionOffsetNorthSouth(double value);

  double getVerticalSectionOffsetEastWest() const;
  void setVerticalSectionOffsetEastWest(double value);

  double getWellheadDistanceNorthSouth() const;
  void setWellheadDistanceNorthSouth(double value);

  double getWellheadDistanceEastWest() const;
  void setWellheadDistanceEastWest(double value);

  QString getWellheadDistanceNorthSouthFormat() const;
  void setWellheadDistanceNorthSouthFormat(const QString &value);

  QString getWellheadDistanceEastWestFormat() const;
  void setWellheadDistanceEastWestFormat(const QString &value);

  QString getCartSysGridSystem() const;
  void setCartSysGridSystem(const QString &value);

  QString getCartSysGroup() const;
  void setCartSysGroup(const QString &value);

private:
  int id = 0;
  int wellInfoId;

  int geogLatitudeDeg;
  int geogLatitudeMin;
  double geogLatitudeSec;
  QString geogLatitudeDire;

  int geogLongitudeDeg;
  int geogLongitudeMin;
  double geogLongitudeSec;
  QString geogLongitudeDire;

  QString geogSysDesc;
  QString geogSysProjMethod;
  QString geogSysReference;
  QString geogSysGridSystem;
  QString geogSysGroup;

  double cartNorthing;
  double cartEasting;
  QString cartSysDesc;
  QString cartSysProjMethod;
  QString cartSysReference;
  QString cartSysGridSystem;
  QString cartSysGroup;
  double cartSysCentralMeridian;

  double wellheadOffsetNorthSouth;
  double wellheadOffsetEastWest;

  double verticalSectionOffsetNorthSouth;
  double verticalSectionOffsetEastWest;

  double wellheadDistanceNorthSouth;
  double wellheadDistanceEastWest;
  QString wellheadDistanceNorthSouthFormat;
  QString wellheadDistanceEastWestFormat;

};

#endif // WELLINFOLOCATION_H

