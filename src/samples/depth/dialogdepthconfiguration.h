#ifndef DIALOGDEPTHCONFIGURATION_H
#define DIALOGDEPTHCONFIGURATION_H

#include <QDialog>

namespace Ui {
  class DialogDepthConfiguration;
}

class DialogDepthConfiguration : public QDialog
{
  Q_OBJECT

public:
  explicit DialogDepthConfiguration(QWidget *parent = nullptr);
  ~DialogDepthConfiguration();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::DialogDepthConfiguration *ui;
};

#endif // DIALOGDEPTHCONFIGURATION_H
