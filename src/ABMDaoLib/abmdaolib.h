#ifndef ABMDAOLIB_H
#define ABMDAOLIB_H

#include "ABMDaoLib_global.h"

#include "config/config.h"
#include "common/mysql/SqlUtils.h"

#include "config/dao/currentdatadao.h"

#include "well/dao/wellinfogeneraldao.h"
#include "well/dao/wellinfodistancesdao.h"
#include "well/dao/wellinfolocationdao.h"
#include "well/dao/wellinfosurveyinfodao.h"
#include "well/dao/wellinfopersonneldao.h"
#include "well/dao/wellinfoformationdao.h"
#include "well/dao/wellinfomatchedsystemstrackingdao.h"
#include "well/dao/welldao.h"

#include "runinfo/dao/runinfogeneraldao.h"
#include "runinfo/dao/runinforeliabilitydao.h"
#include "runinfo/dao/runinfomwdstatsdao.h"
#include "runinfo/dao/runinfomudstatsdao.h"
#include "runinfo/dao/runinfodrillstatsdao.h"
#include "runinfo/dao/runinfomatchedsystemstrackingdao.h"
#include "runinfo/dao/runinfodesdao.h"


#include "toolParam/dao/toolparametersdao.h"
#include "toolParam/dao/abidao.h"
#include "toolParam/dao/dgrdao.h"
#include "toolParam/dao/hcimdao.h"
#include "toolParam/dao/pcddao.h"
#include "toolParam/dao/pospulserdao.h"

#include <memory>

class ABMDAOLIB_EXPORT ABMDaoLib
{
public:
  static ABMDaoLib *getInstance();
  ~ABMDaoLib();

  ABMDaoLib();
  //配置参数
  QSharedPointer<Config> getConfig();
  //数据库工具类
  QSharedPointer<SqlUtils> getSqlUtils() const;
  void setSqlUtils(const QSharedPointer<SqlUtils> &sqlUtils);
  //配置：当前数据
  QSharedPointer<CurrentDataDao> getCurrentDataDao();
  //**json 读写接口**/
  std::shared_ptr<WellDaoJsonInterface> getJsonInterface();

  //*****************************井信息******************************

  QSharedPointer<WellInfoGeneralDao> getWellInfoGeneralDao();

  QSharedPointer<WellInfoDistancesDao> getWellInfoDistancesDao();

  QSharedPointer<WellInfoLocationDao> getWellInfoLocationDao();

  QSharedPointer<WellInfoSurveyInfoDao> getWellInfoSurveyInfoDao();

  QSharedPointer<WellInfoPersonnelDao> getWellInfoPersonnelDao();

  QSharedPointer<WellInfoFormationDao> getWellInfoFormationDao();

  QSharedPointer<WellInfoMatchedSystemsTrackingDao> getWellInfoMatchedSystemsTrackingDao();

  //*****************************运行号信息******************************

  QSharedPointer<RunInfoGeneralDao> getRunInfoGeneralDao();

  QSharedPointer<RunInfoReliabilityDao> getRunInfoReliabilityDao();

  QSharedPointer<RunInfoMWDStatsDao> getRunInfoMWDStatsDao();

  QSharedPointer<RunInfoMudStatsDao> getRunInfoMudStatsDao();

  QSharedPointer<RunInfoDrillStatsDao> getRunInfoDrillStatsDao();

  QSharedPointer<RunInfoMatchedSystemsTrackingDao> getRunInfoMatchedSystemsTrackingDao();

  QSharedPointer<RunInfoDesDao> getRunInfoDesDao();

  //*****************************仪器******************************
  QSharedPointer<ToolParametersDao> getToolParametersDao();

  QSharedPointer<ABIDao> getAbiDao() ;

  QSharedPointer<DGRDao> getDgrDao() ;

  QSharedPointer<HCIMDao> getHcimDao() ;

  QSharedPointer<PCDDao> getPcdDao() ;

  QSharedPointer<PosPulserDao> getPosPulserDao();

private:
  QSharedPointer<Config> m_config;//配置参数

  QSharedPointer<SqlUtils> m_sqlUtils;//数据库工具类
  //数据库交互类
  //配置 当前数据
  QSharedPointer<CurrentDataDao> m_currentDataDao;
  //井信息
  QSharedPointer<WellInfoGeneralDao> m_wellInfoGeneralDao;
  QSharedPointer<WellInfoDistancesDao> m_wellInfoDistancesDao;
  QSharedPointer<WellInfoLocationDao> m_wellInfoLocationDao;
  QSharedPointer<WellInfoSurveyInfoDao> m_wellInfoSurveyInfoDao;
  QSharedPointer<WellInfoPersonnelDao> m_wellInfoPersonnelDao;
  QSharedPointer<WellInfoFormationDao> m_wellInfoFormationDao;
  QSharedPointer<WellInfoMatchedSystemsTrackingDao> m_wellInfoMatchedSystemsTrackingDao;
  //运行号信息
  QSharedPointer<RunInfoGeneralDao> m_runInfoGeneralDao;
  QSharedPointer<RunInfoReliabilityDao> m_runInfoReliabilityDao;
  QSharedPointer<RunInfoMWDStatsDao> m_runInfoMWDStatsDao;
  QSharedPointer<RunInfoMudStatsDao> m_runInfoMudStatsDao;
  QSharedPointer<RunInfoDrillStatsDao> m_runInfoDrillStatsDao;
  QSharedPointer<RunInfoMatchedSystemsTrackingDao> m_runInfoMatchedSystemsTrackingDao;
  QSharedPointer<RunInfoDesDao> m_runInfoDesDao;
  //仪器
  QSharedPointer<ToolParametersDao> m_toolParametersDao;
  QSharedPointer<ABIDao> m_abiDao;
  QSharedPointer<DGRDao> m_dgrDao;
  QSharedPointer<HCIMDao> m_hcimDao;
  QSharedPointer<PCDDao> m_pcdDao;
  QSharedPointer<PosPulserDao> m_posPulserDao;

};

#endif // ABMDAOLIB_H
