#include "wellinfo.h"

WellInfo::WellInfo()
{

}

QSharedPointer<WellInfoDistances> WellInfo::distances() const
{
  return m_distances;
}

void WellInfo::setDistances(const QSharedPointer<WellInfoDistances> &distances)
{
  m_distances = distances;
}

QSharedPointer<WellInfoFormation> WellInfo::formation() const
{
  return m_formation;
}

void WellInfo::setFormation(const QSharedPointer<WellInfoFormation> &formation)
{
  m_formation = formation;
}

QSharedPointer<WellInfoGeneral> WellInfo::general() const
{
  return m_general;
}

void WellInfo::setGeneral(const QSharedPointer<WellInfoGeneral> &general)
{
  m_general = general;
}

QSharedPointer<WellInfoLocation> WellInfo::location() const
{
  return m_location;
}

void WellInfo::setLocation(const QSharedPointer<WellInfoLocation> &location)
{
  m_location = location;
}

QSharedPointer<WellInfoMatchedSystemsTracking> WellInfo::matchedSystemsTracking() const
{
  return m_matchedSystemsTracking;
}

void WellInfo::setMatchedSystemsTracking(const QSharedPointer<WellInfoMatchedSystemsTracking> &matchedSystemsTracking)
{
  m_matchedSystemsTracking = matchedSystemsTracking;
}

QSharedPointer<WellInfoPersonnel> WellInfo::personnel() const
{
  return m_personnel;
}

void WellInfo::setPersonnel(const QSharedPointer<WellInfoPersonnel> &personnel)
{
  m_personnel = personnel;
}

QSharedPointer<WellInfoSurveyInfo> WellInfo::surveyInfo() const
{
  return m_surveyInfo;
}

void WellInfo::setSurveyInfo(const QSharedPointer<WellInfoSurveyInfo> &surveyInfo)
{
  m_surveyInfo = surveyInfo;
}
