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


#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include "ui_downloadwidget.h"

#include <QFrame>
#include <QTime>

QT_BEGIN_NAMESPACE
class QWebEngineDownloadItem;
QT_END_NAMESPACE

// Displays one ongoing or finished download (QWebEngineDownloadItem).
class DownloadWidget final : public QFrame, public Ui::DownloadWidget
{
    Q_OBJECT
public:
    // Precondition: The QWebEngineDownloadItem has been accepted.
    explicit DownloadWidget(QWebEngineDownloadItem *download, QWidget *parent = nullptr);

signals:
    // This signal is emitted when the user indicates that they want to remove
    // this download from the downloads list.
    void removeClicked(DownloadWidget *self);

private slots:
    void updateWidget();

private:
    QString withUnit(qreal bytes);

    QWebEngineDownloadItem *m_download;
    QTime m_timeAdded;
};

#endif // DOWNLOADWIDGET_H
