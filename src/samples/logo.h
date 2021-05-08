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

#ifndef OIL_SRC_LOGO_H_
#define OIL_SRC_LOGO_H_

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Logo {
 public:
  Logo();
  const GLfloat *constData() const { return m_data.constData(); }
  int count() const { return m_count; }
  int vertexCount() const { return m_count / 6; }

 private:
//    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
//    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
  void add(const QVector3D &v, const QVector3D &n);

  QVector<GLfloat> m_data;
  int m_count;
};

#endif  // OIL_SRC_LOGO_H_
