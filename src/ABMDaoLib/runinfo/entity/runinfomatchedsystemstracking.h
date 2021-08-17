#ifndef RUNINFOMATCHEDSYSTEMSTRACKING_H
#define RUNINFOMATCHEDSYSTEMSTRACKING_H

#include "../../common/base/baseentity.h"

class RunInfoMatchedSystemsTracking : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int run_info_id READ getRunInfoId WRITE setRunInfoId)
  Q_PROPERTY( int question_1 READ getQuestion1 WRITE setQuestion1)
  Q_PROPERTY( int question_2 READ getQuestion2 WRITE setQuestion2)
  Q_PROPERTY( int question_3a READ getQuestion3a WRITE setQuestion3a)
  Q_PROPERTY( int question_3b READ getQuestion3b WRITE setQuestion3b)
  Q_PROPERTY( int question_4 READ getQuestion4 WRITE setQuestion4)

public:
  RunInfoMatchedSystemsTracking();

  int getId() const;
  void setId(int value);

  int getRunInfoId() const;
  void setRunInfoId(int value);

  int getQuestion1() const;
  void setQuestion1(int value);

  int getQuestion2() const;
  void setQuestion2(int value);

  int getQuestion3a() const;
  void setQuestion3a(int value);

  int getQuestion3b() const;
  void setQuestion3b(int value);

  int getQuestion4() const;
  void setQuestion4(int value);

private:
  int id = 0;
  int runInfoId;
  int question1;
  int question2;
  int question3a;
  int question3b;
  int question4;
};

#endif // RUNINFOMATCHEDSYSTEMSTRACKING_H
