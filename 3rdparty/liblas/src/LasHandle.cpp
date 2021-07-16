#include "LasHandle.h"

LasManager::LasManager() {
  //
}

std::vector<LasManager::DATA> LasManager::readDecodeData(const std::string &fileName) {
  return {};
}

std::vector<LasManager::DATA> LasManager::readWaveData(const std::string &fileName) {
  return {};
}


bool LasManager::saveDecodeData(LasManager::DATA data, const std::string &fileName) {
  return false;
}

bool LasManager::saveWaveData(LasManager::DATA data, const std::string &fileName) {
  return false;
}

void LasManager::writeWaveHead(const std::string &fileName) {
  //
}

//QVector<FlashFSKDecodeData> LasHandle::readDecodeData(const QString fileName)
//{
//    QVector<FlashFSKDecodeData > dataVector;

//    QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){return dataVector;}

//    QByteArray t ;
//    bool isReading = false;

//    while(!file.atEnd())
//    {
//        t = file.readLine();

//        if(isReading){//是否开始读数据
//            QString data(t);
//            //将数据中个间隔一个或多个空格替换为一个空格并去除首尾空格
//            data = data.replace(QRegExp("\\s{1,}"), " ").trimmed();
//            //根据空格分隔字符串
//            QStringList dataStrList = data.split(" ");
//            if(dataStrList.size() < 11){continue;}

//            //解析数据
//            FlashFSKDecodeData tempDecodeData;
//            tempDecodeData.time         = dataStrList[0].toInt();
//            tempDecodeData.gamma1       = dataStrList[1].toInt();
//            tempDecodeData.gamma2       = dataStrList[2].toInt();
//            tempDecodeData.gamma3       = dataStrList[3].toInt();
//            tempDecodeData.gamma4       = dataStrList[4].toInt();
//            tempDecodeData.wellAngle    = dataStrList[5].toDouble();
//            tempDecodeData.rotateSpeed = dataStrList[6].toInt();
//            tempDecodeData.powerSupply1 = dataStrList[7].toDouble();
//            tempDecodeData.flag         = dataStrList[8].toInt();
//            tempDecodeData.powerSupply2 = dataStrList[9].toDouble();
//            tempDecodeData.temperature  = dataStrList[10].toDouble();

//            dataVector.append(tempDecodeData);
//        }
//        else if(t.contains("~A")){
//            isReading = true;
//        }
//    }

//    file.close();

//    return dataVector;
//}

//QVector<FlashFSKWaveData> LasHandle::readWaveData(const QString fileName)
//{
//    QVector<FlashFSKWaveData> dataVector;

//    QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){return dataVector;}

//    QByteArray t ;
//    bool isReading = false;

//    while(!file.atEnd())
//    {
//        t = file.readLine();
//        if(isReading){//是否开始读数据
//            QString data(t);
//            //将数据中个间隔一个或多个空格替换为一个空格并去除首尾空格
//            data = data.replace(QRegExp("\\s{1,}"), " ").trimmed();
//            //根据空格分隔字符串
//            QStringList dataStrList = data.split(" ");
//            if(dataStrList.size() < 2){continue;}

//            //解析数据
//            FlashFSKWaveData tempWaveData;
//            tempWaveData.time = dataStrList.takeFirst().toInt();
//            int strListSize = dataStrList.size();
//            tempWaveData.values.resize(strListSize);

//            for(int i = 0; i < strListSize; ++i)
//            {
//                tempWaveData.values[i] = dataStrList[i].toDouble();
//            }

//            dataVector.append(tempWaveData);
//        }
//        else if(t.contains("~A")){
//            isReading = true;
//        }
//    }

//    file.close();

//    return dataVector;
//}

//bool LasHandle::saveDecodeData(const QVector<FlashFSKDecodeData> &values, const double gammaRatio, const QString fileName)
//{
//    if(fileName.isEmpty())
//    {
//        QMessageBox::information(nullptr,QStringLiteral("保存结果"),QStringLiteral("保存解码数据失败"));
//        return false;
//    }

//    QFile file(fileName);
//    if(!file.open(QFile::WriteOnly | QFile::Append)){return false;}
//    file.write(g_commonLasHead.toLatin1());

//    QStringList keyList;
//    keyList << "Time" << "Gamma1" << "Gamma2" << "Gamma3" << "Gamma4"
//            << "WellAngle" << "RotateSpeed" << "PowerSupply1" << "Flag" << "PowerSupply2" << "Temperature";
//    QString keyStr = QString("~A\t\t").append(keyList.join("\t")).append('\n');

//    file.write(keyStr.toLatin1());

//    foreach (FlashFSKDecodeData onceValue, values) {
//        QString lineStr = QString("\t\t%1\t\t%2\t\t%3\t\t%4\t\t%5\t\t%6\t\t%7\t\t\t%8\t\t\t%9\t\t%10\t\t\t%11\n")
//                                  .arg(onceValue.time).arg(onceValue.gamma1*gammaRatio).arg(onceValue.gamma2*gammaRatio)
//                                  .arg(onceValue.gamma3*gammaRatio).arg(onceValue.gamma4*gammaRatio).arg(onceValue.wellAngle).arg(onceValue.rotateSpeed)
//                                  .arg(onceValue.powerSupply1).arg(onceValue.flag).arg(onceValue.powerSupply2).arg(onceValue.temperature);
//        file.write(lineStr.toLatin1());
//    }

//    file.close();

//    return true;
//}

//bool LasHandle::saveWaveData(const QVector<FlashFSKWaveData> &values, const QString fileName)
//{
//    if(fileName.isEmpty())
//    {
//        QMessageBox::information(nullptr,QStringLiteral("保存结果"),QStringLiteral("保存波形数据失败"));
//        return false;
//    }

//    QFile file(fileName);
//    if(!file.open(QFile::WriteOnly | QFile::Append)){return false;}

//    writeWaveHead(file);

//    foreach (FlashFSKWaveData onceValue, values){
//        QString lineStr = QString("\t\t%1").arg(onceValue.time);
//        foreach (double var, onceValue.values) {
//            lineStr.append(QString("\t\t%1").arg(var));
//        }
//        lineStr.append('\n');

//        file.write(lineStr.toLatin1());
//    }

//    file.close();

//    return true;
//}

//void LasHandle::writeWaveHead(QFile &file)
//{
//  if(file.isOpen()){
//    file.write(g_commonLasHead.toLatin1());

//    QString keyStr = QString("~A\t%1").arg("Time",PRECISION_SHOW);

//    for(int i = 0; i < 2044; ++i)
//    {
//      keyStr.append(QString("\t%1").arg(QString("DATA%1").arg(i+1),PRECISION_SHOW));
//    }

//    keyStr.append('\n');
//    file.write(keyStr.toLatin1());
//  }
//}

