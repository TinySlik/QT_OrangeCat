#ifndef WELLINFOMATCHEDSYSTEMSTRACKING_H
#define WELLINFOMATCHEDSYSTEMSTRACKING_H

#include "../../common/base/baseentity.h"

class WellInfoMatchedSystemsTracking : public BaseEntity
{
  Q_OBJECT
  Q_PROPERTY( int id READ getId WRITE setId)
  Q_PROPERTY( int wellInfo_id READ getWellInfoId WRITE setWellInfoId)
  Q_PROPERTY( int question_1 READ getQuestion1 WRITE setQuestion1)
  Q_PROPERTY( int question_2 READ getQuestion2 WRITE setQuestion2)
  Q_PROPERTY( int question_3 READ getQuestion3 WRITE setQuestion3)
  Q_PROPERTY( int question_4 READ getQuestion4 WRITE setQuestion4)

public:
  WellInfoMatchedSystemsTracking();

  int getId() const;
  void setId(int value);

  int getWellInfoId() const;
  void setWellInfoId(int value);

  int getQuestion1() const;
  void setQuestion1(int value);

  int getQuestion2() const;
  void setQuestion2(int value);

  int getQuestion3() const;
  void setQuestion3(int value);

  int getQuestion4() const;
  void setQuestion4(int value);

private:
  int id = 0;
  int wellInfoId;
  int question1;
  int question2;
  int question3;
  int question4;
};

#endif // WELLINFOMATCHEDSYSTEMSTRACKING_H

