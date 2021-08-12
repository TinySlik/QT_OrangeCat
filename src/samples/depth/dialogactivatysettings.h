#ifndef DIALOGACTIVATYSETTINGS_H
#define DIALOGACTIVATYSETTINGS_H

#include <QDialog>

namespace Ui {
  class DialogActivatySettings;
}

class DialogActivatySettings : public QDialog
{
  Q_OBJECT

public:
  explicit DialogActivatySettings(QWidget *parent = nullptr);
  ~DialogActivatySettings();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::DialogActivatySettings *ui;
};

#endif // DIALOGACTIVATYSETTINGS_H
