#ifndef DIALOGDEPTHCARDCONFIGRATION_H
#define DIALOGDEPTHCARDCONFIGRATION_H

#include <QDialog>

namespace Ui {
  class DialogDepthCardConfigration;
}

class DialogDepthCardConfigration : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDepthCardConfigration(QWidget *parent = nullptr);
  ~DialogDepthCardConfigration();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_checkBox_toggled(bool checked);

private:
  Ui::DialogDepthCardConfigration *ui;
};

#endif // DIALOGDEPTHCARDCONFIGRATION_H
