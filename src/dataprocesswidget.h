/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OIL_SRC_DATAPROCESSWIDGET_H_
#define OIL_SRC_DATAPROCESSWIDGET_H_

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

class DataProcessWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core {
  Q_OBJECT

 public:
  explicit DataProcessWidget(QWidget *parent = nullptr);
  ~DataProcessWidget();

  static bool isTransparent() { return m_transparent; }
  static void setTransparent(bool t) { m_transparent = t; }

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  void reset();
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
  QTimer timer;

  bool m_core;
  QOpenGLVertexArrayObject m_vao;
  QMatrix4x4 m_proj;
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
  size_t m_file_find_index;
};

#endif  // OIL_SRC_DATAPROCESSWIDGET_H_