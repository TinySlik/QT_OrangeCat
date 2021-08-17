#ifndef RUNINFODES_H
#define RUNINFODES_H

#include "../../common/base/baseentity.h"

class RunInfoDes : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( int question_1 READ getQuestion1 WRITE setQuestion1)
  Q_PROPERTY( int question_2 READ getQuestion2 WRITE setQuestion2)
  Q_PROPERTY( int question_3 READ getQuestion3 WRITE setQuestion3)
  Q_PROPERTY( int question_4 READ getQuestion4 WRITE setQuestion4)
  Q_PROPERTY( int question_5 READ getQuestion5 WRITE setQuestion5)
  Q_PROPERTY( int question_5a READ getQuestion5a WRITE setQuestion5a)
  Q_PROPERTY( int question_5b READ getQuestion5b WRITE setQuestion5b)
  Q_PROPERTY( int question_5c READ getQuestion5c WRITE setQuestion5c)

public:
  RunInfoDes();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  int getQuestion1() const;
  void setQuestion1(int value);

  int getQuestion2() const;
  void setQuestion2(int value);

  int getQuestion3() const;
  void setQuestion3(int value);

  int getQuestion4() const;
  void setQuestion4(int value);

  int getQuestion5() const;
  void setQuestion5(int value);

  int getQuestion5a() const;
  void setQuestion5a(int value);

  int getQuestion5b() const;
  void setQuestion5b(int value);

  int getQuestion5c() const;
  void setQuestion5c(int value);

private:
  int id = 0;
  int runInfoId;
  int question1;
  int question2;
  int question3;
  int question4;
  int question5;
  int question5a;
  int question5b;
  int question5c;
};

#endif // RUNINFODES_H
