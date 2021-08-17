#ifndef WELLINFO_H
#define WELLINFO_H


#include "wellinfodistances.h"
#include "wellinfoformation.h"
#include "wellinfogeneral.h"
#include "wellinfolocation.h"
#include "wellinfomatchedsystemstracking.h"
#include "wellinfopersonnel.h"
#include "wellinfosurveyinfo.h"

class WellInfo
{
public:
  WellInfo();

  QSharedPointer<WellInfoDistances> distances() const;
  void setDistances(const QSharedPointer<WellInfoDistances> &distances);

  QSharedPointer<WellInfoFormation> formation() const;
  void setFormation(const QSharedPointer<WellInfoFormation> &formation);

  QSharedPointer<WellInfoGeneral> general() const;
  void setGeneral(const QSharedPointer<WellInfoGeneral> &general);

  QSharedPointer<WellInfoLocation> location() const;
  void setLocation(const QSharedPointer<WellInfoLocation> &location);

  QSharedPointer<WellInfoMatchedSystemsTracking> matchedSystemsTracking() const;
  void setMatchedSystemsTracking(const QSharedPointer<WellInfoMatchedSystemsTracking> &matchedSystemsTracking);

  QSharedPointer<WellInfoPersonnel> personnel() const;
  void setPersonnel(const QSharedPointer<WellInfoPersonnel> &personnel);

  QSharedPointer<WellInfoSurveyInfo> surveyInfo() const;
  void setSurveyInfo(const QSharedPointer<WellInfoSurveyInfo> &surveyInfo);

private:
  QSharedPointer<WellInfoDistances> m_distances;
  QSharedPointer<WellInfoFormation> m_formation;
  QSharedPointer<WellInfoGeneral> m_general;
  QSharedPointer<WellInfoLocation> m_location;
  QSharedPointer<WellInfoMatchedSystemsTracking> m_matchedSystemsTracking;
  QSharedPointer<WellInfoPersonnel> m_personnel;
  QSharedPointer<WellInfoSurveyInfo> m_surveyInfo;
};

#endif // WELLINFO_H
