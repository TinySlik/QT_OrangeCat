#include "LasParser.h"
#include <QMessageBox>

LasParser::LasParser(QObject *parent) : QObject(parent)
{

}

void LasParser::clearLas()
{
  m_data.clear();
  m_infos.clear();
}

void LasParser::createPresetLas()
{
  Las::LasInfo infoW(Las::Info_W);
  Las::LasInfo infoC(Las::Info_C);
  Las::LasInfo infoP1(Las::Info_P);
  Las::LasInfo infoP2(Las::Info_P);

  infoW.addField(Las::LasField("STRT",Las::LasUnit_M, 3440.0000           , "START DEPTH"));
  infoW.addField(Las::LasField("STOP",Las::LasUnit_M, 3486.3000           , "STOP DEPTH"));
  infoW.addField(Las::LasField("STEP",Las::LasUnit_M,             0.1000  ,"STEP DEPTH                            "));
  infoW.addField(Las::LasField("NULL", Las::LasUnit_Null,-999.2500  ,"NULL VALUE                            "));
  infoW.addField(Las::LasField("WELL", Las::LasUnit_Null, "","WELL NAME                             "));
  infoW.addField(Las::LasField("COMP", Las::LasUnit_Null, "","COMPANY                               "));
  infoW.addField(Las::LasField("RIG",  Las::LasUnit_Null,"","RIG NAME                              "));
  infoW.addField(Las::LasField("FLD",  Las::LasUnit_Null,"","FIELD NAME                            "));
  infoW.addField(Las::LasField("CNTY", Las::LasUnit_Null, "","COUNTY NAME                           "));
  infoW.addField(Las::LasField("PROV", Las::LasUnit_Null, "","PROVINCE                              "));
  infoW.addField(Las::LasField("STAT", Las::LasUnit_Null, "","STATE NAME                            "));
  infoW.addField(Las::LasField("CTRY", Las::LasUnit_Null, "","COUNTRY NAME                          "));
  infoW.addField(Las::LasField("SRVC", Las::LasUnit_Null, "","CONTRACTOR                            "));
  infoW.addField(Las::LasField("LEAS", Las::LasUnit_Null, "","LEASE NAME                            "));
  infoW.addField(Las::LasField("DCON", Las::LasUnit_Null, "","DIRECTNL CONTR                        "));
  infoW.addField(Las::LasField("SECT", Las::LasUnit_Null, "","SECTION                               "));
  infoW.addField(Las::LasField("TOWN", Las::LasUnit_Null, "","TOWNSHIP                              "));
  infoW.addField(Las::LasField("RANG", Las::LasUnit_Null, "","RANGE                                 "));
  infoW.addField(Las::LasField("SON",  Las::LasUnit_Null,"","JOB NUMBER                            "));
  infoW.addField(Las::LasField("UWI",  Las::LasUnit_Null,"","UNIQUE WELL IDENTIFIER                "));
  infoW.addField(Las::LasField("API",  Las::LasUnit_Null,"","API NUMBER                            "));
  infoW.addField(Las::LasField("DOE",  Las::LasUnit_Null,"","DOE NUMBER                            "));
  infoW.addField(Las::LasField("UNIT.",Las::LasUnit_Null,  "","LOGGING EQUIPMENT ID                  "));
  infoW.addField(Las::LasField("COLG", Las::LasUnit_Null,"","COMPANY LOGO                          "));
  infoW.addField(Las::LasField("CULG", Las::LasUnit_Null,"","CUSTOMER LOGO                         "));
  infoW.addField(Las::LasField("REGN", Las::LasUnit_Null,"","REGION                                "));
  infoW.addField(Las::LasField("BASE", Las::LasUnit_Null,"","LOGGING EQUIPMENT BASE LOCATION       "));
  infoW.addField(Las::LasField("JOBN", Las::LasUnit_Null,"","JOB TICKET NUMB                       "));
  infoW.addField(Las::LasField("MWDS", Las::LasUnit_Null,"","MWD SHOP                              "));
  infoW.addField(Las::LasField("SPUD", Las::LasUnit_Null,QDate(16,4,25)  ,"SPUD DATE                             "));
  infoW.addField(Las::LasField("GCDE", Las::LasUnit_Null,"","GEO COORD DESC                        "));
  infoW.addField(Las::LasField("GPMT", Las::LasUnit_Null,"","GEO PROJ METHOD                       "));
  infoW.addField(Las::LasField("GREF", Las::LasUnit_Null,"","GEO REFERENCE                         "));
  infoW.addField(Las::LasField("GGSY", Las::LasUnit_Null,"","GEO GRID SYS                          "));
  infoW.addField(Las::LasField("LLGR", Las::LasUnit_Null,"","LLGROUP                               "));
  infoW.addField(Las::LasField("CCDE", Las::LasUnit_Null,"","CART COORD DESC                       "));
  infoW.addField(Las::LasField("CPJM", Las::LasUnit_Null,"","CART PROJ METHD                       "));
  infoW.addField(Las::LasField("CREF", Las::LasUnit_Null,"","CART REFERENCE                        "));
  infoW.addField(Las::LasField("CGSY", Las::LasUnit_Null,"","CART GRID SYS                         "));
  infoW.addField(Las::LasField("XYGR", Las::LasUnit_Null,"","XYGROUP                               "));
  infoW.addField(Las::LasField("MDS", Las::LasUnit_Null,"Operator Entered","MAG DATA SOURCE                       "));
  infoW.addField(Las::LasField("MMDL",Las::LasUnit_Null,"","MAGNETIC MODEL                        "));
  infoW.addField(Las::LasField("DFWT",Las::LasUnit_Null,"","DIST FWL TEXT                         "));
  infoW.addField(Las::LasField("DFST",Las::LasUnit_Null,"","DIST FSL TEXT                         "));
  infoW.addField(Las::LasField("PDAT",Las::LasUnit_Null,"","PERMANENT DATUM                       "));
  infoW.addField(Las::LasField("DMF ",Las::LasUnit_Null,"","DRILL MEAS FROM                       "));
  infoW.addField(Las::LasField("STIM",Las::LasUnit_Null, QDateTime(QDate(16,4,25),QTime(0,32,0)),"START TIME                            "));
  infoW.addField(Las::LasField("DATE",Las::LasUnit_Null, QDateTime(QDate(16,4,25),QTime(0,32,0)),"END TIME                              "));
  infoW.addField(Las::LasField("DMOD",Las::LasUnit_Null, "   Drill Model  ","DRILL MOD DESC                        "));
  infoW.addField(Las::LasField("SVYD",Las::LasUnit_Null, "        Survey  ","SURVEY DESC                           "));
  infoW.addField(Las::LasField("ILTD",Las::LasUnit_Null, "     Lithology  ","INTERP LTH DESC                       "));
  infoW.addField(Las::LasField("FTOP",Las::LasUnit_Null, "Formation Tops  ","FORM TOPS DESC                        "));
  infoW.addField(Las::LasField("LOC", Las::LasUnit_Null,"","LOCATION                              "));
  infoW.addField(Las::LasField("LMF", Las::LasUnit_Null,"","LOG MEASURED FROM                     "));
  infoW.addField(Las::LasField("RCST",Las::LasUnit_da, 0.000000  ,"RIG COST                              "));
  infoW.addField(Las::LasField("AGAP",Las::LasUnit_m,0.000000  ,"AIR GAP                               "));
  infoW.addField(Las::LasField("CMER",Las::LasUnit_deg,0.000000  ,"CENTRL MERIDIAN                       "));
  infoW.addField(Las::LasField("VSNS",Las::LasUnit_m,0.000000  ,"VERT SEC N/S                          "));
  infoW.addField(Las::LasField("VSEW",Las::LasUnit_m,0.000000  ,"VERT SEC E/W                          "));
  infoW.addField(Las::LasField("LATI",Las::LasUnit_deg,0.000000  ,"LATITUDE                              "));
  infoW.addField(Las::LasField("LONG",Las::LasUnit_deg,0.000000  ,"LONGITUDE                             "));
  infoW.addField(Las::LasField("TVDS",Las::LasUnit_m, 0.000000  ,"TVDSS CORRECTN                        "));
  infoW.addField(Las::LasField("EGL", Las::LasUnit_m,0.000000  ,"GROUND ELEVATION                      "));
  infoW.addField(Las::LasField("WDMS",Las::LasUnit_m, 0.000000  ,"WD ELEV                               "));
  infoW.addField(Las::LasField("WHNS",Las::LasUnit_m, 0.000000  ,"WELL HEAD N/S                         "));
  infoW.addField(Las::LasField("WHEW",Las::LasUnit_m, 0.000000  ,"WELL HEAD E/W                         "));
  infoW.addField(Las::LasField("UTMX",Las::LasUnit_m, 0.000000  ,"UTM X                                 "));
  infoW.addField(Las::LasField("UTMY",Las::LasUnit_m, 0.000000  ,"UTM Y                                 "));
  infoW.addField(Las::LasField("DFWL",Las::LasUnit_m, 0.000000  ,"DISTANCE FWL                          "));
  infoW.addField(Las::LasField("DFSL",Las::LasUnit_m, 0.000000  ,"DISTANCE FSL                          "));
  infoW.addField(Las::LasField("EPD", Las::LasUnit_m,0.000000  ,"ELEVATION                             "));
  infoW.addField(Las::LasField("APD", Las::LasUnit_m,0.000000  ,"DEPTH ABOVE PD                        "));
  infoW.addField(Las::LasField("STRD",Las::LasUnit_m, 0.000000  ,"START DEPTH                           "));
  infoW.addField(Las::LasField("TDD", Las::LasUnit_m,0.000000  ,"TOTAL DEPTH (DRILLER)                 "));
  infoW.addField(Las::LasField("VSDR",Las::LasUnit_deg,0.000000  ,"VERT SEC DIRECT                       "));
  infoW.addField(Las::LasField("MFLD",Las::LasUnit_nT,57301.000000  ,"MAGNETIC FIELD                        "));
  infoW.addField(Las::LasField("MDIP",Las::LasUnit_deg,65.669998  ,"MAGNETIC DIP                          "));
  infoW.addField(Las::LasField("GVFD",Las::LasUnit_g,1.000000  ,"GRAVITY FIELD                         "));
  infoW.addField(Las::LasField("MDEC",Las::LasUnit_deg,0.000000  ,"MAGNETIC DECL                         "));
  infoW.addField(Las::LasField("GRDC",Las::LasUnit_deg,0.000000  ,"GRID CORRECTION                       "));
  infoW.addField(Las::LasField("AZTC",Las::LasUnit_deg,0.000000  ,"AZM TOTAL CORR                        "));
  infoW.addField(Las::LasField("EKB",Las::LasUnit_m,0.000000  ,"KB ELEVATION                          "));
  infoW.addField(Las::LasField("EDF",Las::LasUnit_m,0.000000  ,"DF ELEVATION                          "));
  infoW.addField(Las::LasField("TDL",Las::LasUnit_m,0.000000  ,"TOTAL DEPTH (LOGGER)                  "));
  infoW.addField(Las::LasField("WTYP",Las::LasUnit_Null,0  ,"WELL TYPE                             "));
  infoW.addField(Las::LasField("VSC", Las::LasUnit_Null, 0  ,"VS TO CLOSURE                         "));
  infoW.addField(Las::LasField("MAGU",Las::LasUnit_Null,2047380  ,"MAGUTM CHECKSUM                       "));
  infoW.addField(Las::LasField("NREF",Las::LasUnit_Null,0  ,"NORTH REFERENCE                       "));
  infoW.addField(Las::LasField("HPTY",Las::LasUnit_Null,  0  ,"HOLE POS TYPE                         "));

  infoP1.addField(Las::LasField("RUN",Las::LasUnit_Null,100 , "Run Number                      "));
  infoP1.addField(Las::LasField("TCS",Las::LasUnit_hr,0.000000 , "Time Ciculation Ended           "));
  infoP1.addField(Las::LasField("BS", Las::LasUnit_mm,0.000000 , "Bit Size                        "));
  infoP1.addField(Las::LasField("ROP",Las::LasUnit_mhr,0.000000 , "ROP Max                         "));
  infoP1.addField(Las::LasField("ROP",Las::LasUnit_mhr,0.000000 , "ROP Min                         "));
  infoP1.addField(Las::LasField("ROP",Las::LasUnit_mhr,0.000000 , "ROP Avg                         "));
  infoP1.addField(Las::LasField("RMB",Las::LasUnit_ohmm,0.000000 , "Rm @ Max Temp                   "));
  infoP1.addField(Las::LasField("MCST",Las::LasUnit_degC,-0.000000 , "Mud Cake Sample Temperature     "));
  infoP1.addField(Las::LasField("RMCS",Las::LasUnit_ohmm,0.000000 , "Mud Cake Resistivity            "));
  infoP1.addField(Las::LasField("RMFT",Las::LasUnit_degC,-0.000000 , "Mud Filtrate Sample Temperature "));
  infoP1.addField(Las::LasField("RMFS",Las::LasUnit_ohmm,0.000000 , "Mud Filtrate Resistivity        "));
  infoP1.addField(Las::LasField("MST",Las::LasUnit_degC,-0.000000 , "Mud Sample Temperature          "));
  infoP1.addField(Las::LasField("RMS",Las::LasUnit_ohmm,0.000000 , "Mud Resistivity                 "));
  infoP1.addField(Las::LasField("DFL",Las::LasUnit_m3pm,0.000000 , "Fluid Loss                      "));
  infoP1.addField(Las::LasField("PH",Las::LasUnit_pH,0.000000 , "Mud pH                          "));
  infoP1.addField(Las::LasField("DFV",Las::LasUnit_spl,0.000000 , "Mud Viscosity                   "));
  infoP1.addField(Las::LasField("ORT",Las::LasUnit_hr,0.000000 , "Time Operating                  "));
  infoP1.addField(Las::LasField("TLAT", Las::LasUnit_Null,QDateTime(QDate(16,4,25),QTime(0,32,0)), "Log End Time                    "));
  infoP1.addField(Las::LasField("TLAB", Las::LasUnit_Null,QDateTime(QDate(16,4,25),QTime(0,32,0)), "Log Start Time                  "));
  infoP1.addField(Las::LasField("ETIM", Las::LasUnit_Null,QDateTime(QDate(16,4,25),QTime(0,32,0)), "End Time                        "));
  infoP1.addField(Las::LasField("STIM", Las::LasUnit_Null,QDateTime(QDate(16,4,25),QTime(0,32,0)), "Start Time                      "));
  infoP1.addField(Las::LasField("EDEP",Las::LasUnit_m, 0.000000 , "End Depth                       "));
  infoP1.addField(Las::LasField("STRD",Las::LasUnit_m, 0.000000 , "Start Depth                     "));
  infoP1.addField(Las::LasField("TDL", Las::LasUnit_m,0.000000 , "Tot Depth Loggd                 "));
  infoP1.addField(Las::LasField("DFD",Las::LasUnit_kgm3,0.000000 , "Mud Density                     "));

  infoP2.addField(Las::LasField("SP1",Las::LasUnit_sec , 12.000000, "Sample Period 1"));
  infoP2.addField(Las::LasField("DFB",Las::LasUnit_ft  , 33.005249, "Dist From Bit  "));
  infoP2.addField(Las::LasField("SNIN",Las::LasUnit_Null    ,         1, "SN Insert      "));
  infoP2.addField(Las::LasField("DFB",Las::LasUnit_ft  , 40.748032, "Dist From Bit  "));
  infoP2.addField(Las::LasField("SP1",Las::LasUnit_sec , 12.000000, "Sample Period 1"));
  infoP2.addField(Las::LasField("SNTX",Las::LasUnit_Null,      1501, "SN Trans Insert"));
  infoP2.addField(Las::LasField("SNIN",Las::LasUnit_Null,1, "SN Insert      "));
  infoP2.addField(Las::LasField("DFB",Las::LasUnit_ft  , 58.530186, "Dist From Bit  "));
  infoP2.addField(Las::LasField("SNIN",Las::LasUnit_Null ,    "PDR590", "SN Insert      "));
  infoP2.addField(Las::LasField("OTY",Las::LasUnit_Null ,"Jet Oil II", "Oil Type       "));

  infoC.addField(Las::LasField("DEPT",Las::LasUnit_M ,"00 000 000 000","DGR Depth                "));
  infoC.addField(Las::LasField("DGR",Las::LasUnit_api,"00 000 000 000","DGR Combined Gamma Ray   "));
  infoC.addField(Las::LasField("Cnts",Las::LasUnit_cnts,"00 000 000 000","EWR Deep Cnts Phase Ang  "));
  infoC.addField(Las::LasField("DPS",Las::LasUnit_deg ,"00 000 000 000","EWR Deep Phase Ang       "));
  infoC.addField(Las::LasField("EDP",Las::LasUnit_ohmm,"00 000 000 000","EWR Deep Phase Res       "));
  infoC.addField(Las::LasField("CntsPhaseAn1",Las::LasUnit_cnts ,"00 000 000 000","EWR Shallow Cnts Phase An"));
  infoC.addField(Las::LasField("EWRPhaseAng",Las::LasUnit_deg   ,"00 000 000 000","EWR Shallow EWR Phase Ang"));
  infoC.addField(Las::LasField("EWRPhaseRes",Las::LasUnit_ohmm  ,"00 000 000 000","EWR Shallow EWR Phase Res"));

  m_infos[Las::Info_W].append(infoW);
  m_infos[Las::Info_P].append(infoP1);
  m_infos[Las::Info_P].append(infoP2);
  m_infos[Las::Info_C].append(infoC);
}

void LasParser::setDataHead(const QStringList &head)
{
  m_data.setHead(head);
}

void LasParser::addData(const QVector<double> &data)
{
  m_data.addData(data);
}

void LasParser::addMultiData(const QVector<QVector<double> > &datas)
{
  m_data.addMultiData(datas);
}

void LasParser::addInfo(const Las::LasInfo &info)
{
  m_infos[info.type].append(info);
}

void LasParser::addInfoField(const Las::LasInfoType &section, const Las::LasField &field)
{
  int count = m_infos[section].count();
  for(int i = 0; i < count; ++i){
    m_infos[section][i].addField(field);
  }
}

void LasParser::deleteInfo(const Las::LasInfoType &section)
{
  m_infos.remove(section);
}

void LasParser::deleteInfoField(const Las::LasInfoType &section, const QString &field)
{
  int count = m_infos[section].count();
  for(int i = 0; i < count; ++i){
    m_infos[section][i].deleteField(field);
  }
}

void LasParser::changeInfoField(const Las::LasInfoType &section, const QString &field, const Las::LasUnit &unit, const QVariant &value, const QString &description)
{
  int count = m_infos[section].count();
  for(int i = 0; i < count; ++i){
    m_infos[section][i].changeField(field,unit,value,description);
  }
}

void LasParser::changeInfoFieldValue(const Las::LasInfoType &section, const QString &field, const QVariant &value)
{
  int count = m_infos[section].count();
  for(int i = 0; i < count; ++i){
    m_infos[section][i].changeValue(field,value);
  }
}

QList<Las::LasInfoType> LasParser::getInfoSectionKeys() const
{
  return m_infos.keys();
}

QList<Las::LasField> LasParser::getInfoSectionFields(const Las::LasInfoType &section) const
{
  QList<Las::LasField> list;

  int count = m_infos[section].count();
  for(int i = 0; i < count; ++i) {
    list.append(m_infos[section][i].fields.toList());
  }

  return list;
}

QList<Las::LasInfo> LasParser::getInfoSections() const
{
  QList<Las::LasInfo> list;

  foreach (Las::LasInfoType key, m_infos.keys()) {
    list.append(m_infos[key]);
  }

  return list;
}

QList<QVector<QVector<double> > > LasParser::getDatas()
{
  return m_data.datas;
}

bool LasParser::exportFile(const QString fileName)
{
  if(fileName.isEmpty()){
    QMessageBox::information(nullptr,"export result","export fail");
    return false;
  }

  QFile file(fileName);
  if(!file.open(QFile::WriteOnly | QFile::Append)){return false;}

  file.write(this->toString().toLatin1());
  file.close();

  return true;
}

bool LasParser::importFile(const QString fileName)
{
  if(fileName.isEmpty()){
    QMessageBox::information(nullptr,"import result","import fail");
    return false;
  }

  QFile file(fileName);
  if(!file.open(QFile::ReadOnly)){return false;}

  QString fileStr    = file.readAll();
  importString(fileStr);

  file.close();

  return true;
}

void LasParser::importString(const QString &str)
{
  clearLas();
  QStringList spList =  str.split('~', QString::SkipEmptyParts);

  foreach (QString var, spList) {
    parseStr(var.remove('\r').replace('\t',' '));
  }
}

void LasParser::parseStr(const QString &str)
{
  if(str.startsWith('V')) {
    parseVersionHead(str);
  } else if(str.startsWith('W')) {
    parseInfo(Las::Info_W,str);
  } else if(str.startsWith('P')) {
    parseInfo(Las::Info_P,str);
  } else if(str.startsWith('C')) {
    parseInfo(Las::Info_C,str);
  } else if(str.startsWith('O')) {
    parseInfo(Las::Info_O,str);
  } else if(str.startsWith('A')) {
    parseData(str);
  }
}

void LasParser::parseVersionHead(const QString &str)
{
  Las::LasField vers;
  Las::LasField wrap;

  QStringList list = str.split('\n', QString::SkipEmptyParts);
  list.removeFirst();

  foreach (QString var, list) {
    if(!var.startsWith("#")){
      Las::LasField field = Las::LasField::parseStr(var);
      if(field.field == "VERS") {
        vers = field;
      } else if(field.field == "WRAP") {
        wrap = field;
      }
    }
  }

  m_head = Las::LasV(vers, wrap);
}

void LasParser::parseInfo(const Las::LasInfoType &type, const QString &str)
{
  QStringList list = str.split('\n', QString::SkipEmptyParts);
  list.removeFirst();

  Las::LasInfo info(type);
  foreach (QString var, list) {
    if(!var.startsWith("#")){
      info.addField(Las::LasField::parseStr(var));
    }
  }

  addInfo(info);
}

void LasParser::parseData(const QString &str)
{
  QStringList list = str.split('\n', QString::SkipEmptyParts);
  QString headStr = list.takeFirst();
  QStringList headList = headStr.split(' ', QString::SkipEmptyParts);
  headList.removeFirst();
  m_data.setHead(headList);

  foreach (QString var, list) {
    QVector<double> datas;
    QStringList dataList = var.split(' ',QString::SkipEmptyParts);
    foreach (QString dataStr, dataList) {
      datas.append(dataStr.toDouble());
    }

    addData(datas);
  }
}
