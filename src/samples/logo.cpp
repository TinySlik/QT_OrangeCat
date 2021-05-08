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


#include "logo.h"
#include <qmath.h>

Logo::Logo()
    : m_count(0) {
    m_data.resize(6 * 6);

    add(QVector3D(0.5, -0.5, 0), QVector3D(0, 0, -1));
    add(QVector3D(-0.5, -0.5, 0), QVector3D(0, 0, -1));
    add(QVector3D(0.5, 0.5, 0), QVector3D(0, 0, -1));
    add(QVector3D(-0.5, 0.5, 0), QVector3D(0, 0, -1));
    add(QVector3D(0.5, 0.5, 0), QVector3D(0, 0, -1));
    add(QVector3D(-0.5, -0.5, 0), QVector3D(0, 0, -1));

//    const GLfloat x1 = +0.06f;
//    const GLfloat y1 = -0.14f;
//    const GLfloat x2 = +0.14f;
//    const GLfloat y2 = -0.06f;
//    const GLfloat x3 = +0.08f;
//    const GLfloat y3 = +0.00f;
//    const GLfloat x4 = +0.30f;
//    const GLfloat y4 = +0.22f;

//    quad(x1, y1, x2, y2, y2, x2, y1, x1);
//    quad(x3, y3, x4, y4, y4, x4, y3, x3);

//    extrude(x1, y1, x2, y2);
//    extrude(x2, y2, y2, x2);
//    extrude(y2, x2, y1, x1);
//    extrude(y1, x1, x1, y1);
//    extrude(x3, y3, x4, y4);
//    extrude(x4, y4, y4, x4);
//    extrude(y4, x4, y3, x3);

    const int NumSectors = 100;

//    for (int i = 0; i < NumSectors; ++i) {
//        GLfloat angle = (i * 2 * M_PI) / NumSectors;
//        GLfloat angleSin = qSin(angle);
//        GLfloat angleCos = qCos(angle);
//        const GLfloat x5 = 0.30f * angleSin;
//        const GLfloat y5 = 0.30f * angleCos;
//        const GLfloat x6 = 0.20f * angleSin;
//        const GLfloat y6 = 0.20f * angleCos;

//        angle = ((i + 1) * 2 * M_PI) / NumSectors;
//        angleSin = qSin(angle);
//        angleCos = qCos(angle);
//        const GLfloat x7 = 0.20f * angleSin;
//        const GLfloat y7 = 0.20f * angleCos;
//        const GLfloat x8 = 0.30f * angleSin;
//        const GLfloat y8 = 0.30f * angleCos;

//        quad(x5, y5, x6, y6, x7, y7, x8, y8);

//        extrude(x6, y6, x7, y7);
//        extrude(x8, y8, x5, y5);
//    }
}

void Logo::add(const QVector3D &v, const QVector3D &n) {
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

// void Logo::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
// {
//    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

//    add(QVector3D(x1, y1, -0.05f), n);
//    add(QVector3D(x4, y4, -0.05f), n);
//    add(QVector3D(x2, y2, -0.05f), n);

//    add(QVector3D(x3, y3, -0.05f), n);
//    add(QVector3D(x2, y2, -0.05f), n);
//    add(QVector3D(x4, y4, -0.05f), n);

//    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

//    add(QVector3D(x4, y4, 0.05f), n);
//    add(QVector3D(x1, y1, 0.05f), n);
//    add(QVector3D(x2, y2, 0.05f), n);

//    add(QVector3D(x2, y2, 0.05f), n);
//    add(QVector3D(x3, y3, 0.05f), n);
//    add(QVector3D(x4, y4, 0.05f), n);
//}

// void Logo::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
// {
//    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

//    add(QVector3D(x1, y1, +0.05f), n);
//    add(QVector3D(x1, y1, -0.05f), n);
//    add(QVector3D(x2, y2, +0.05f), n);

//    add(QVector3D(x2, y2, -0.05f), n);
//    add(QVector3D(x2, y2, +0.05f), n);
//    add(QVector3D(x1, y1, -0.05f), n);
//}
