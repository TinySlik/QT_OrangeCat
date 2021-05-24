/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef OIL_SRC_DATAPROCESSWIDGET_H_
#define OIL_SRC_DATAPROCESSWIDGET_H_

#include <vector>
#include <deque>
#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QTimer>

#include "logo.h"
#include "memorymapped.h"
#define MAX_PAINT_BUF_SIZE (4096)

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class DataProcessWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core {
  Q_OBJECT

 public:
  explicit DataProcessWidget(QWidget *parent = nullptr);
  ~DataProcessWidget() override;

  static bool isTransparent() { return m_transparent; }
  static void setTransparent(bool t) { m_transparent = t; }

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void reset(size_t size);

  void getData();

 public slots:

 signals:
  void TitelChanged(const QString &title);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  void resetBuf(int size);
  bool resetComputeShader(int level);
  QTimer timer;

  bool m_core;
  QOpenGLVertexArrayObject m_vao;
  QMatrix4x4 m_proj;
  std::vector<float> m_tex_buf;
  float * m_tex_buf_render_head;
  std::vector<float> m_tex_tmp;
  std::deque <uchar> m_code_step1_tmp;
  size_t m_code_step1_tmp_cur_head;
  size_t m_decode_step2_tmp_cur_head;
  std::string m_code_step1_tmp_str;
  static bool m_transparent;
  std::shared_ptr<MemoryMapped::File> m_fileMMap;

  QOpenGLVertexArrayObject m_Cvao;
  std::shared_ptr<QOpenGLBuffer> m_CvertexBuffer;
  std::shared_ptr<QOpenGLBuffer> m_CindexBuffer;
  std::shared_ptr<QOpenGLShaderProgram> m_CcomputeProgram;
  std::shared_ptr<QOpenGLShaderProgram> m_CrenderProgram;
  std::shared_ptr<QOpenGLTexture> m_Ctexture;
  float m_roll;
  float m_speed;
  float m_lineThickness;
  float m_TestFrequency;
  bool m_ComputeShaderSwitch;
  int m_TestSwitch;
  int m_DisplaySwitch;
  size_t m_file_find_index;
  int m_fft_level;
  bool m_reset_buf_tag;
  int buffer_size;
  bool m_reset_computeshader_tag;
  int  m_match_alpha;
  int m_matchClockFrequency;

  QVector3D   m_position;
  QVector3D   m_scale;
  QVector3D   m_rotation;
  float m_angle;

  float m_max_cut_filter;
  float m_min_cut_filter;

  float m_fft_display_scale;
};

#endif  // OIL_SRC_DATAPROCESSWIDGET_H_
