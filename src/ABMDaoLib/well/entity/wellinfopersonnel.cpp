#include "wellinfopersonnel.h"

WellInfoPersonnel::WellInfoPersonnel()
{

}

int WellInfoPersonnel::getId() const
{
    return id;
}

void WellInfoPersonnel::setId(int value)
{
    id = value;
}

int WellInfoPersonnel::getWellInfoId() const
{
    return wellInfoId;
}

void WellInfoPersonnel::setWellInfoId(int value)
{
    wellInfoId = value;
}

QString WellInfoPersonnel::getPersonnelDD() const
{
    return personnelDD;
}

void WellInfoPersonnel::setPersonnelDD(const QString &value)
{
    personnelDD = value;
}

QString WellInfoPersonnel::getPersonnelMWD() const
{
    return personnelMWD;
}

void WellInfoPersonnel::setPersonnelMWD(const QString &value)
{
    personnelMWD = value;
}

QString WellInfoPersonnel::getPersonnelSDL() const
{
    return personnelSDL;
}

void WellInfoPersonnel::setPersonnelSDL(const QString &value)
{
    personnelSDL = value;
}

QString WellInfoPersonnel::getPersonnelADT() const
{
    return personnelADT;
}

void WellInfoPersonnel::setPersonnelADT(const QString &value)
{
    personnelADT = value;
}

QString WellInfoPersonnel::getPersonnelCustomerRep() const
{
    return personnelCustomerRep;
}

void WellInfoPersonnel::setPersonnelCustomerRep(const QString &value)
{
    personnelCustomerRep = value;
}

QString WellInfoPersonnel::getPersonnelGeologist() const
{
    return personnelGeologist;
}

void WellInfoPersonnel::setPersonnelGeologist(const QString &value)
{
    personnelGeologist = value;
}

QString WellInfoPersonnel::getPersonnelRCS() const
{
    return personnelRCS;
}

void WellInfoPersonnel::setPersonnelRCS(const QString &value)
{
    personnelRCS = value;
}

QString WellInfoPersonnel::getPersonnelOther() const
{
    return personnelOther;
}

void WellInfoPersonnel::setPersonnelOther(const QString &value)
{
    personnelOther = value;
}

QString WellInfoPersonnel::getContactsDD() const
{
    return contactsDD;
}

void WellInfoPersonnel::setContactsDD(const QString &value)
{
    contactsDD = value;
}

QString WellInfoPersonnel::getContactsMWD() const
{
    return contactsMWD;
}

void WellInfoPersonnel::setContactsMWD(const QString &value)
{
    contactsMWD = value;
}

QString WellInfoPersonnel::getContactsSDLADT() const
{
    return contactsSDLADT;
}

void WellInfoPersonnel::setContactsSDLADT(const QString &value)
{
    contactsSDLADT = value;
}

QString WellInfoPersonnel::getContactsRCS() const
{
    return contactsRCS;
}

void WellInfoPersonnel::setContactsRCS(const QString &value)
{
    contactsRCS = value;
}

QString WellInfoPersonnel::getContactsRig() const
{
    return contactsRig;
}

void WellInfoPersonnel::setContactsRig(const QString &value)
{
    contactsRig = value;
}

int WellInfoPersonnel::getCountOffLocAsWDay() const
{
  return countOffLocAsWDay;
}

void WellInfoPersonnel::setCountOffLocAsWDay(int value)
{
  countOffLocAsWDay = value;
}
