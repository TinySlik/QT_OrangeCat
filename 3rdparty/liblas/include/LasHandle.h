#ifndef LASHANDLE_H
#define LASHANDLE_H

#include "CommonLas.h"
#include "memorymapped.h"
#include "windllsupport.h"
#include <vector>
#include <memory>
#include <string>

#define PRECISION_SHOW 8

enum TIME_DEPTH_DATA{
    TIME_DATA,
    DEPTH_DATA,
    V_DEPTH_DATA
};

class CLASS_DECLSPEC LasManager {
 public:
  using DATA = std::shared_ptr<std::vector<unsigned char>>;

  explicit LasManager();

  /**
   * @brief readHeatMapData   读取FSK解码数据
   * @param fileName          文件名
   * @return
   */
  static std::vector<DATA> readDecodeData(const std::string &fileName);

  /**
   * @brief readTimeDepthData 读取FSK波形数据
   * @param fileName          文件名
   * @return
   */
  static std::vector<DATA> readWaveData(const std::string &fileName);

  /**
   * @brief saveDecodeData    保存解码las文件
   * @param data            数据
   * @param fileName          保存文件名,默认弹框选择文件名
   * @return
   */
  static bool saveDecodeData(DATA data, const std::string &fileName);

  /**
   * @brief saveWaveData      保存波形las文件
   * @param data            数据
   * @param fileName          保存文件名,默认弹框选择文件名
   * @return
   */
  static bool saveWaveData(DATA data, const std::string &fileName);

  static void writeWaveHead(const std::string &fileName);
};

#endif // LASHANDLE_H
