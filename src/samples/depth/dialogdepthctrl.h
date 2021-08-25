#ifndef DIALOGDEPTHCTRL_H
#define DIALOGDEPTHCTRL_H

#include <QDialog>
#include "depthwindow.h"

namespace Ui {
  class DialogDepthCtrl;
}

class DialogDepthCtrl : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDepthCtrl(QWidget *parent = nullptr);
  ~DialogDepthCtrl();

  void Accept();
signals:
  void acceptSig();

private slots:
  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

private:
  Ui::DialogDepthCtrl *ui;
  friend DepthWindow;
};

#endif // DIALOGDEPTHCTRL_H
