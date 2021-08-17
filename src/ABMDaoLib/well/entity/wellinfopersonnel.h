#ifndef WELLINFOPERSONNEL_H
#define WELLINFOPERSONNEL_H

#include "../../common/base/baseentity.h"

class WellInfoPersonnel : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY(int id READ getId WRITE setId)
  Q_PROPERTY(int well_info_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY(int count_off_loc_as_wday READ getCountOffLocAsWDay WRITE setCountOffLocAsWDay)
  Q_PROPERTY(QString personnel_dd READ getPersonnelDD WRITE setPersonnelDD)
  Q_PROPERTY(QString personnel_mwd READ getPersonnelMWD WRITE setPersonnelMWD)
  Q_PROPERTY(QString personnel_sdl READ getPersonnelSDL WRITE setPersonnelSDL)
  Q_PROPERTY(QString personnel_adt READ getPersonnelADT WRITE setPersonnelADT)
  Q_PROPERTY(QString personnel_customer_rep READ getPersonnelCustomerRep WRITE setPersonnelCustomerRep)
  Q_PROPERTY(QString personnel_geologist READ getPersonnelGeologist WRITE setPersonnelGeologist)
  Q_PROPERTY(QString personnel_rcs READ getPersonnelRCS WRITE setPersonnelRCS)
  Q_PROPERTY(QString personnel_other READ getPersonnelOther WRITE setPersonnelOther)
  Q_PROPERTY(QString contacts_dd READ getContactsDD WRITE setContactsDD)
  Q_PROPERTY(QString contacts_mwd READ getContactsMWD WRITE setContactsMWD)
  Q_PROPERTY(QString contacts_sdl_adt READ getContactsSDLADT WRITE setContactsSDLADT)
  Q_PROPERTY(QString contacts_rcs READ getContactsRCS WRITE setContactsRCS)
  Q_PROPERTY(QString contacts_rig READ getContactsRig WRITE setContactsRig)

public:
  WellInfoPersonnel();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  QString getPersonnelDD() const;
  void setPersonnelDD(const QString &value);

  QString getPersonnelMWD() const;
  void setPersonnelMWD(const QString &value);

  QString getPersonnelSDL() const;
  void setPersonnelSDL(const QString &value);

  QString getPersonnelADT() const;
  void setPersonnelADT(const QString &value);

  QString getPersonnelCustomerRep() const;
  void setPersonnelCustomerRep(const QString &value);

  QString getPersonnelGeologist() const;
  void setPersonnelGeologist(const QString &value);

  QString getPersonnelRCS() const;
  void setPersonnelRCS(const QString &value);

  QString getPersonnelOther() const;
  void setPersonnelOther(const QString &value);

  QString getContactsDD() const;
  void setContactsDD(const QString &value);

  QString getContactsMWD() const;
  void setContactsMWD(const QString &value);

  QString getContactsSDLADT() const;
  void setContactsSDLADT(const QString &value);

  QString getContactsRCS() const;
  void setContactsRCS(const QString &value);

  QString getContactsRig() const;
  void setContactsRig(const QString &value);

  int getCountOffLocAsWDay() const;
  void setCountOffLocAsWDay(int value);

private:
  int id = 0;
  int wellInfoId;
  int countOffLocAsWDay;
  QString personnelDD;
  QString personnelMWD;
  QString personnelSDL;
  QString personnelADT;
  QString personnelCustomerRep;
  QString personnelGeologist;
  QString personnelRCS;
  QString personnelOther;

  QString contactsDD;
  QString contactsMWD;
  QString contactsSDLADT;
  QString contactsRCS;
  QString contactsRig;


};

#endif // WELLINFOPERSONNEL_H
