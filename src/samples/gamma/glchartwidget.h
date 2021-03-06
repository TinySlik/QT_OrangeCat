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


#ifndef OIL_SRC_DISPLAYWIDGET_H_
#define OIL_SRC_DISPLAYWIDGET_H_

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
#include <QtSvg>
#include "parameterserver.h"

#include "memorymapped.h"
#define MAX_PAINT_BUF_SIZE (32768)

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
class DisplayWidget :public QOpenGLWidget ,protected QOpenGLFunctions_4_3_Core {
  Q_OBJECT

 public:
  explicit DisplayWidget(QWidget *parent = nullptr);
  ~DisplayWidget() override;

  static bool isTransparent() { return m_transparent; }
  static void setTransparent(bool t) { m_transparent = t; }

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void reset(size_t size);

  void getData(std::shared_ptr<std::vector<float>> data = nullptr);
  std::string getParamIndexStr();

 signals:
  void TitelChanged(const QString &title);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  bool mousePressedTag_;
  int  mouseX_;
  int  mouseY_;
  bool ctrlPressed_;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  void resetBuf(int size);
  QTimer timer;

  bool m_core;
  QOpenGLVertexArrayObject m_vao;
  QMatrix4x4 m_proj;
  std::vector<float> m_tex_buf;
  float *m_tex_buf_render_head;
  std::shared_ptr<std::vector<float>> m_tex_tmp_ptr;
  std::deque <uchar> m_code_step1_tmp;
  int code_step1_trust_count;
  size_t m_code_step1_tmp_cur_head;
  size_t m_decode_step2_tmp_cur_head;
  std::string m_code_step1_tmp_str;
  static bool m_transparent;
  std::shared_ptr<MemoryMapped::File> m_fileMMap;
  std::vector<GLfloat> verts_;

  QOpenGLVertexArrayObject m_Cvao;
  std::shared_ptr<QOpenGLBuffer> m_CvertexBuffer;
  std::shared_ptr<QOpenGLBuffer> m_CindexBuffer;
  std::shared_ptr<QOpenGLShaderProgram> m_CrenderProgram;
  std::shared_ptr<QOpenGLTexture> m_Ctexture;
  std::shared_ptr<QSvgRenderer> m_SVGRender;

  float m_lineThickness;
  int m_TestSwitch;
  int m_DisplaySwitch;
  size_t m_file_find_index;
  size_t _file_find_index_set_tmp;
  bool m_reset_buf_tag;
  int buffer_size;
  int m_samplingSpeed;

  QVector3D   m_position;
  QVector3D   m_scale;
  QVector3D   m_rotation;
  float m_angle;
  uint32_t    m_color;
  uint32_t    m_backgroundColor;

  bool m_decoder_unsigned;
};

#endif  // OIL_SRC_DISPLAYWIDGET_H_
