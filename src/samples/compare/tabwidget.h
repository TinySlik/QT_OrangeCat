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

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QWebEnginePage>

QT_BEGIN_NAMESPACE
class QUrl;
QT_END_NAMESPACE

class WebView;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    TabWidget(QWebEngineProfile *profile, QWidget *parent = nullptr);

    WebView *currentWebView() const;

signals:
    // current tab/page signals
    void linkHovered(const QString &link);
    void loadProgress(int progress);
    void titleChanged(const QString &title);
    void urlChanged(const QUrl &url);
    void favIconChanged(const QIcon &icon);
    void webActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
    void devToolsRequested(QWebEnginePage *source);

public slots:
    // current tab/page slots
    void setUrl(const QUrl &url);
    void triggerWebPageAction(QWebEnginePage::WebAction action);

    WebView *createTab();
    WebView *createBackgroundTab();
    void closeTab(int index);
    void nextTab();
    void previousTab();

private slots:
    void handleCurrentChanged(int index);
    void handleContextMenuRequested(const QPoint &pos);
    void cloneTab(int index);
    void closeOtherTabs(int index);
    void reloadAllTabs();
    void reloadTab(int index);

private:
    WebView *webView(int index) const;
    void setupView(WebView *webView);

    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H
