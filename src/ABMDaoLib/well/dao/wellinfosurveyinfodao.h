#ifndef WELLINFOSURVEYINFODAO_H
#define WELLINFOSURVEYINFODAO_H

#include "../entity/wellinfosurveyinfo.h"
#include "../../common/mysql/SqlUtils.h"

/**
 * @brief The SQL_PAGE struct 分页查询返回结构体
 */
struct WellInfoSurveyInfoPage
{
  int pageNum;
  int pageSize;
  int totalPage;
  QList<QSharedPointer<WellInfoSurveyInfo>> dataList;
};


class WellInfoSurveyInfoDao
{
public:
  WellInfoSurveyInfoDao();
  //新增井信息 SurveyInfo 信息
  bool add(QSharedPointer<WellInfoSurveyInfo> entity);
  //修改井信息 SurveyInfo 信息
  bool updateById(QSharedPointer<WellInfoSurveyInfo> entity);
  //批量查询井信息 SurveyInfo 集合
  QList<QSharedPointer<WellInfoSurveyInfo> > findList(QVector<SqlCondition> &conditions);
  //分页查询井信息 SurveyInfo 集合
  WellInfoSurveyInfoPage findPage(QVector<SqlCondition> &conditions, const int pageSize, const int pageNum);
  //根据id查询
  QSharedPointer<WellInfoSurveyInfo> findById(int id);
  //根据wellInfoId查询
  QSharedPointer<WellInfoSurveyInfo> findByWellInfoId(int wellInfoId);

private:
  QString m_tableName = "u_well_survey_info";
};

#endif // WELLINFOSURVEYINFODAO_H
