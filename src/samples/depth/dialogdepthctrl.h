#ifndef DIALOGDEPTHCTRL_H
#define DIALOGDEPTHCTRL_H

#include <QDialog>

namespace Ui {
  class DialogDepthCtrl;
}

class DialogDepthCtrl : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDepthCtrl(QWidget *parent = nullptr);
  ~DialogDepthCtrl();

private:
  Ui::DialogDepthCtrl *ui;
};

#endif // DIALOGDEPTHCTRL_H
