#ifndef DIALOGSETUPDRAWWORKS_H
#define DIALOGSETUPDRAWWORKS_H

#include <QDialog>

namespace Ui {
  class DialogSetupDrawworks;
}

class DialogSetupDrawworks : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSetupDrawworks(QWidget *parent = nullptr);
  ~DialogSetupDrawworks();

private slots:
  void on_pushButton_3_clicked();

private:
  Ui::DialogSetupDrawworks *ui;
};

#endif // DIALOGSETUPDRAWWORKS_H
