#ifndef DIALOGDEPTHCONFIGURATION_H
#define DIALOGDEPTHCONFIGURATION_H

#include <QDialog>
#include <QLabel>
#include <vector>
#include <QMimeData>
#include <QListWidgetItem>
#include <QRadioButton>

namespace Ui {
  class DialogDepthConfiguration;
}

class CustomMimeData: public QMimeData {
  //todo
};

class DialogDepthConfiguration : public QDialog
{
  Q_OBJECT
  typedef struct {
    QRect rect;
    QLabel *label;
    QRadioButton *checked;
  } DROP_UNIT;

public:
  explicit DialogDepthConfiguration(QWidget *parent = nullptr);
  ~DialogDepthConfiguration();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragLeaveEvent(QDragLeaveEvent *event) override;

  void dropEvent(QDropEvent *event) override;

  void itemPressed(QListWidgetItem *item);

private:
  std::vector<DROP_UNIT> m_dropUnits;
  Ui::DialogDepthConfiguration *ui;

};

#endif // DIALOGDEPTHCONFIGURATION_H
