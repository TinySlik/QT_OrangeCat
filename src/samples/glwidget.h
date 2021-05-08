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


#ifndef OIL_SRC_GLWIDGET_H_
#define OIL_SRC_GLWIDGET_H_

#include <vector>
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

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core {
  Q_OBJECT

 public:
  explicit GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  static bool isTransparent() { return m_transparent; }
  static void setTransparent(bool t) { m_transparent = t; }

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void reset();
  void getData();

 public slots:
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void cleanup();

 signals:
  void xRotationChanged(int angle);
  void yRotationChanged(int angle);
  void zRotationChanged(int angle);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  QTimer timer;
  void setupVertexAttribs();

  bool m_core;
  int m_xRot;
  int m_yRot;
  int m_zRot;
  QPoint m_lastPos;
  Logo m_logo;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_logoVbo;
  std::shared_ptr<QOpenGLShaderProgram> m_program;
  int m_projMatrixLoc;
  int m_mvMatrixLoc;
  int m_time_;
  int m_normalMatrixLoc;
  int m_lightPosLoc;
  QMatrix4x4 m_proj;
  QMatrix4x4 m_camera;
  QMatrix4x4 m_world;
  std::vector<float> m_tex_buf;
  float * m_tex_buf_render_head;
  static bool m_transparent;
  std::shared_ptr<MemoryMapped::File> m_fileMMap;

  QOpenGLVertexArrayObject m_Cvao;
  std::shared_ptr<QOpenGLBuffer> m_CvertexBuffer;
  std::shared_ptr<QOpenGLBuffer> m_CindexBuffer;
  std::shared_ptr<QOpenGLShaderProgram> m_CcomputeProgram;
  std::shared_ptr<QOpenGLShaderProgram> m_CrenderProgram;
  std::shared_ptr<QOpenGLTexture> m_Ctexture;
  float roll;
  float m_speed;
  float m_lineThickness;
  float m_TestFrequency;
  bool m_ComputeShaderSwitch;
  int m_TestSwitch;
  int m_DisplaySwitch;
};

#endif  // OIL_SRC_GLWIDGET_H_
