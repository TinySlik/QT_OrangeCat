#ifndef LASDEFINE_H
#define LASDEFINE_H

#define LAS_DATA_MAX_SIZE 4096

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QDebug>

namespace Las {

enum LasUnit{
  LasUnit_m,
  LasUnit_M,
  LasUnit_da, // $/da
  LasUnit_deg,
  LasUnit_nT,
  LasUnit_g,
  LasUnit_hr,
  LasUnit_mm,
  LasUnit_mhr,
  LasUnit_ohmm,
  LasUnit_degC,
  LasUnit_m3pm,
  LasUnit_pH,
  LasUnit_spl,
  LasUnit_kgm3, // kg/m3
  LasUnit_sec,
  LasUnit_ft,
  LasUnit_api,
  LasUnit_cnts,
  LasUnit_Null
};

static QMap<LasUnit, QString> s_unitStr{{LasUnit_m,"m"},{LasUnit_M,"M"},
                                        {LasUnit_da,"$/da"},{LasUnit_deg ,"deg"},
                                        {LasUnit_nT,"nT"},{LasUnit_hr ,"hr"},
                                        {LasUnit_mm,"mm"},{LasUnit_mhr,"m/hr"},
                                        {LasUnit_ohmm,"ohmm"},{LasUnit_degC,"degC"},
                                        {LasUnit_m3pm,"m3pm"},{LasUnit_pH,"pH"},
                                        {LasUnit_spl,"spl"},{LasUnit_kgm3,"kgm3"},
                                        {LasUnit_sec,"sec"},{LasUnit_ft,"ft"},
                                        {LasUnit_api,"api"},{LasUnit_cnts,"cnts"},
                                        {LasUnit_Null,""}};

enum LasInfoType{
  Info_V,
  Info_W, //Well Information Block
  Info_C, //Curve Information Block
  Info_P, //Parameter Information Block
  Info_O, //Other
  Info_A
};

struct LasField{
  QString   field;
  LasUnit   unit;
  QVariant  value;
  QString   description;


  LasField(){}

  LasField(const QString &_field, const LasUnit _unit = LasUnit_Null,
           const QVariant &_value = QString(),const QString &_description = QString())
    :field(_field), unit(_unit), value(_value), description(_description){}

  static LasField parseStr(const QString &str) {
    QString fieldStr = str.section('.',0,0).remove(' ');
    QString unitStr;
    QString valueStr;
    QString desStr;
    QString tempStr1 = str.section('.',1);
    QString tempStr2 = tempStr1.section(':',0,0);
    desStr   = tempStr1.section(':',1);

    QStringList list = tempStr2.split(' ',QString::SkipEmptyParts);

    if(tempStr2.startsWith(' ')) {
      if(list.size() > 0) {
        valueStr = list.join(' ');
      }
    } else {
      unitStr  = list.takeFirst();
      if(list.size() > 0) {
        valueStr = list.join(' ');
      }
    }

    return LasField(fieldStr,s_unitStr.key(unitStr),valueStr,desStr);
  }

  QString toString() const{
    QString unitStr;
    QString valueStr;

    unitStr = s_unitStr[unit];
    unitStr.insert(0,'.');

    switch (value.type()) {
    case QVariant::Type::String:{
      valueStr = value.toString();
      break;
    }
    case QVariant::Type::DateTime: {
      valueStr = value.toDateTime().toString("HH.mm.ss dd-MM-yy");
      break;
    }
    case QVariant::Type::Time: {
      valueStr = value.toTime().toString("HH.mm.ss");
      break;
    }
    case QVariant::Type::Date: {
      valueStr = value.toDate().toString("dd-MM-yy");
      break;
    }
    default: {
      valueStr = QString::number(value.toDouble());
      break;
    }
    }

    return QString(" %1%2%3: %4\n").arg(field,-20).arg(unitStr,10).arg(valueStr,20).arg(description,-40);
  }
};

/** 这里将las文件当成3部分
 *
 * 1.版本号头
 * ~Version Information
 *  VERS.                  2.0:   CWLS log ASCII Standard -VERSION 2.0
 *  WRAP.                   NO:   One line per depth step

 * 2.井相关信息
 * ~Well Information Block
 * #MNEM.UNIT     VALUE/NAME     DESCRIPTION
 * #---------     -----------    ---------------------------
 *  STRT.M              3440.0000: START DEPTH
 *  STOP.M              3486.3000: STOP DEPTH
 * ...............
 * ~Parameter Information Block
 * #MNEM.UNIT       Value        Description
 * #---------     -----------    ---------------------------
 *  RUN .                     100:  Run Number
 *  TCS .hr              0.000000:  Time Ciculation Ended
 * ...............

 * 3.数据
 * ~A   DEPT       DGR    CntsPhaseAng    DPS       EDP    CntsPhaseAn1 EWRPhaseAng EWRPhaseRes
 *    3440.0000 -999.2500    -999.2500 -999.2500 -999.2500    -999.2500   -999.2500 -999.2500
 *    3440.1000 -999.2500    -999.2500 -999.2500 -999.2500    -999.2500   -999.2500 -999.2500
 *    3440.2000 -999.2500    -999.2500 -999.2500 -999.2500    -999.2500   -999.2500 -999.2500
*/


struct LasV{
  LasField vers;
  LasField wrap;

  LasV(){
    vers = LasField("VERS",Las::LasUnit_Null, "2.0", "CWLS log ASCII Standard -VERSION 2.0");
    wrap = LasField("WRAP", Las::LasUnit_Null,"NO", "CWLS log ASCII Standard -VERSION 2.0");
  }

  LasV(const LasField &_vers, const LasField &_wrap) : vers(_vers), wrap(_wrap){}

  LasV(const QString &_vers, const QString &_versDes, const QString &_wrap, const QString &_wrapDes){
    vers = LasField("VERS",Las::LasUnit_Null, _vers, _versDes);
    wrap = LasField("WRAP", Las::LasUnit_Null,_wrap, _wrapDes);
  }

  QString toString() const{
    QString str = "~Version Information\n";
    str.append(vers.toString());
    str.append(wrap.toString());

    return str;
  }
};


struct LasInfo{
  QVector<LasField> fields;
  LasInfoType type;

  LasInfo(const LasInfoType &_type = Info_W):type(_type){}

  void addField(const LasField &field){
    fields.append(field);
  }

  void deleteField(const QString &_key){
    int count = fields.count();

    for(int i = 0; i < count; ++i) {
      if(fields[i].field == _key) {
        fields.removeAt(i);
      }
    }
  }

  void changeField(const QString &_key, const LasUnit &_unit,
                   const QVariant &_value,const QString &_description) {
    int count = fields.count();

    for(int i = 0; i < count; ++i) {
      if(fields[i].field == _key) {
        fields[i].unit = _unit;
        fields[i].value = _value;
        fields[i].description = _description;
      }
    }
  }

  void changeValue(const QString &_key, const QVariant &_value){
    int count = fields.count();

    for(int i = 0; i < count; ++i) {
      if(fields[i].field == _key) {
        fields[i].value = _value;
      }
    }
  }

  QString toString() const{
    QString str;
    QString key1 = "MNEM";
    QString key2 = ".UNIT";
    QString key3 = "VALUE";
    QString key4 = "Description";

    switch (type) {
      case Info_W:{
        str = "~Well Information Block\n";
        key3 = "VALUE/NAME";
        break;
      }
      case Info_C:{
        str = "~Curve Information Block\n";
        key3 = "API CODE";
        key4 = "Curve Description";
        break;
      }
      case Info_P:{
        str = "~Parameter Information Block\n";
        break;
      }
      case Info_O:{
        str = "~Other\n";
        break;
      }
    }

    QString delimiter1(key1.size(),'-');
    QString delimiter2(key2.size(),'-');
    QString delimiter3(key3.size(),'-');
    QString delimiter4(key4.size(),'-');

    QString head = QString("#%1%2%3  %4\n#%5%6%7  %8\n").arg(key1,-20).arg(key2,10).arg(key3,20).arg(key4,-40)
                                    .arg(delimiter1,-20).arg(delimiter2,10).arg(delimiter3,20).arg(delimiter4,-40);

    str.append(head);
    foreach (LasField var, fields) {
      str.append(var.toString());
    }

    return str;
  }
};

struct LasData{
  QStringList head;
  QList<QVector<QVector<double>> > datas;

  LasData(){
    datas.append(QVector<QVector<double>>());
  }

  LasData(const QStringList &_head): head(_head){
    datas.append(QVector<QVector<double>>());
  }

  void setHead(const QStringList &_head) {
    head = _head;
  }

  void clear() {
    head.clear();
    datas.clear();
    datas.append(QVector<QVector<double>>());
  }

  void addData(const QVector<double> &data) {
    datas.last().append(data);
    if(datas.last().size() >= LAS_DATA_MAX_SIZE) {
      datas.append(QVector<QVector<double>>());
    }
  }

  void addMultiData(const QVector<QVector<double>> &_datas){
    int existDataSize = datas.last().size();
    int newDataSize   = _datas.size();

    if(existDataSize + newDataSize >= LAS_DATA_MAX_SIZE) {
      int addSize = LAS_DATA_MAX_SIZE-existDataSize;
      datas.last().append(_datas.mid(0, addSize));
      datas.append(QVector<QVector<double>>());
      addMultiData(_datas.mid(addSize));
    } else {
      datas.last().append(_datas);
    }
  }

  QString toString() const {
    QString str = "~A ";
    foreach (QString var, head) {
      str.append(QString("%1").arg(var,-15));
    }
    str.append('\n');

    int listSize = datas.size();
    for(int i = 0; i < listSize; ++i){
      int onceVecSize = datas[i].size();
      for(int j = 0; j < onceVecSize; ++j){
        QString lineDataStr = "   ";
        foreach (double var, datas[i][j]) {
          lineDataStr.append(QString("%1").arg(var,-15));
        }
        lineDataStr.append('\n');
        str.append(lineDataStr);
      }
    }

    return str;
  }

};




}

#endif // LASDEFINE_H
