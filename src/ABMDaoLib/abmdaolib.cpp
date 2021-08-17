#include "abmdaolib.h"
#include "common/log/easylogging++.h"

#pragma execution_character_set("utf-8")
//初始化easilogging
INITIALIZE_EASYLOGGINGPP

ABMDaoLib *ABMDaoLib::getInstance()
{
    static ABMDaoLib *instance = nullptr;
    if (instance == nullptr)
    {
        instance = new ABMDaoLib();
    }
    return instance;
}

ABMDaoLib::~ABMDaoLib()
{

}

ABMDaoLib::ABMDaoLib()
{
  m_sqlUtils = QSharedPointer<SqlUtils>(new SqlUtils("abm100","root","123456"));
  m_sqlUtils->connectDatabase();
}

QSharedPointer<Config> ABMDaoLib::getConfig()
{
  if(m_config.isNull()){
    m_config = QSharedPointer<Config>(new Config());
  }
  return m_config;
}

QSharedPointer<SqlUtils> ABMDaoLib::getSqlUtils() const
{
  return m_sqlUtils;
}

void ABMDaoLib::setSqlUtils(const QSharedPointer<SqlUtils> &sqlUtils)
{
  m_sqlUtils = sqlUtils;
}


QSharedPointer<CurrentDataDao> ABMDaoLib::getCurrentDataDao()
{
  if(m_currentDataDao.isNull()){
    m_currentDataDao = QSharedPointer<CurrentDataDao>(new CurrentDataDao());
  }
  return m_currentDataDao;
}

QSharedPointer<WellInfoGeneralDao> ABMDaoLib::getWellInfoGeneralDao()
{
  if(m_wellInfoGeneralDao.isNull()){
    m_wellInfoGeneralDao = QSharedPointer<WellInfoGeneralDao>(new WellInfoGeneralDao());
  }
  return m_wellInfoGeneralDao;
}

QSharedPointer<WellInfoDistancesDao> ABMDaoLib::getWellInfoDistancesDao()
{
  if(m_wellInfoDistancesDao.isNull()){
    m_wellInfoDistancesDao = QSharedPointer<WellInfoDistancesDao>(new WellInfoDistancesDao());
  }
  return m_wellInfoDistancesDao;
}

QSharedPointer<WellInfoLocationDao> ABMDaoLib::getWellInfoLocationDao()
{
  if(m_wellInfoLocationDao.isNull()){
    m_wellInfoLocationDao = QSharedPointer<WellInfoLocationDao>(new WellInfoLocationDao());
  }
  return m_wellInfoLocationDao;
}

QSharedPointer<WellInfoSurveyInfoDao> ABMDaoLib::getWellInfoSurveyInfoDao()
{
  if(m_wellInfoSurveyInfoDao.isNull()){
    m_wellInfoSurveyInfoDao = QSharedPointer<WellInfoSurveyInfoDao>(new WellInfoSurveyInfoDao());
  }
  return m_wellInfoSurveyInfoDao;
}

QSharedPointer<WellInfoPersonnelDao> ABMDaoLib::getWellInfoPersonnelDao()
{
  if(m_wellInfoPersonnelDao.isNull()){
    m_wellInfoPersonnelDao = QSharedPointer<WellInfoPersonnelDao>(new WellInfoPersonnelDao());
  }
  return m_wellInfoPersonnelDao;
}

QSharedPointer<WellInfoFormationDao> ABMDaoLib::getWellInfoFormationDao()
{
  if(m_wellInfoFormationDao.isNull()){
    m_wellInfoFormationDao = QSharedPointer<WellInfoFormationDao>(new WellInfoFormationDao());
  }
  return m_wellInfoFormationDao;
}

QSharedPointer<WellInfoMatchedSystemsTrackingDao> ABMDaoLib::getWellInfoMatchedSystemsTrackingDao()
{
  if(m_wellInfoMatchedSystemsTrackingDao.isNull()){
    m_wellInfoMatchedSystemsTrackingDao = QSharedPointer<WellInfoMatchedSystemsTrackingDao>(new WellInfoMatchedSystemsTrackingDao());
  }
  return m_wellInfoMatchedSystemsTrackingDao;
}

QSharedPointer<RunInfoGeneralDao> ABMDaoLib::getRunInfoGeneralDao()
{
  if(m_runInfoGeneralDao.isNull()){
    m_runInfoGeneralDao = QSharedPointer<RunInfoGeneralDao>(new RunInfoGeneralDao());
  }
  return m_runInfoGeneralDao;
}

QSharedPointer<RunInfoReliabilityDao> ABMDaoLib::getRunInfoReliabilityDao()
{
  if(m_runInfoReliabilityDao.isNull()){
    m_runInfoReliabilityDao = QSharedPointer<RunInfoReliabilityDao>(new RunInfoReliabilityDao());
  }
  return m_runInfoReliabilityDao;
}

QSharedPointer<RunInfoMWDStatsDao> ABMDaoLib::getRunInfoMWDStatsDao()
{
  if(m_runInfoMWDStatsDao.isNull()){
    m_runInfoMWDStatsDao = QSharedPointer<RunInfoMWDStatsDao>(new RunInfoMWDStatsDao());
  }
  return m_runInfoMWDStatsDao;
}

QSharedPointer<RunInfoMudStatsDao> ABMDaoLib::getRunInfoMudStatsDao()
{
  if(m_runInfoMudStatsDao.isNull()){
    m_runInfoMudStatsDao = QSharedPointer<RunInfoMudStatsDao>(new RunInfoMudStatsDao());
  }
  return m_runInfoMudStatsDao;
}

QSharedPointer<RunInfoDrillStatsDao> ABMDaoLib::getRunInfoDrillStatsDao()
{
  if(m_runInfoDrillStatsDao.isNull()){
    m_runInfoDrillStatsDao = QSharedPointer<RunInfoDrillStatsDao>(new RunInfoDrillStatsDao());
  }
  return m_runInfoDrillStatsDao;
}

QSharedPointer<RunInfoMatchedSystemsTrackingDao> ABMDaoLib::getRunInfoMatchedSystemsTrackingDao()
{
  if(m_runInfoMatchedSystemsTrackingDao.isNull()){
    m_runInfoMatchedSystemsTrackingDao = QSharedPointer<RunInfoMatchedSystemsTrackingDao>(new RunInfoMatchedSystemsTrackingDao());
  }
  return m_runInfoMatchedSystemsTrackingDao;
}

QSharedPointer<RunInfoDesDao> ABMDaoLib::getRunInfoDesDao()
{
  if(m_runInfoDesDao.isNull()){
    m_runInfoDesDao = QSharedPointer<RunInfoDesDao>(new RunInfoDesDao());
  }
  return m_runInfoDesDao;
}

QSharedPointer<ToolParametersDao> ABMDaoLib::getToolParametersDao()
{
  if(m_toolParametersDao.isNull()){
    m_toolParametersDao = QSharedPointer<ToolParametersDao>(new ToolParametersDao());
  }
  return m_toolParametersDao;
}

QSharedPointer<ABIDao> ABMDaoLib::getAbiDao()
{
  if(m_abiDao.isNull()){
    m_abiDao = QSharedPointer<ABIDao>(new ABIDao());
  }
  return m_abiDao;
}


QSharedPointer<DGRDao> ABMDaoLib::getDgrDao()
{
  if(m_dgrDao.isNull()){
    m_dgrDao = QSharedPointer<DGRDao>(new DGRDao());
  }
  return m_dgrDao;
}

QSharedPointer<HCIMDao> ABMDaoLib::getHcimDao()
{
  if(m_hcimDao.isNull()){
    m_hcimDao = QSharedPointer<HCIMDao>(new HCIMDao());
  }
  return m_hcimDao;
}

QSharedPointer<PCDDao> ABMDaoLib::getPcdDao()
{
  if(m_pcdDao.isNull()){
    m_pcdDao = QSharedPointer<PCDDao>(new PCDDao());
  }
  return m_pcdDao;
}

QSharedPointer<PosPulserDao> ABMDaoLib::getPosPulserDao()
{
  if(m_posPulserDao.isNull()){
    m_posPulserDao = QSharedPointer<PosPulserDao>(new PosPulserDao());
  }
  return m_posPulserDao;
}

