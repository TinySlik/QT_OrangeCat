#ifndef DEPTHWINDOW_H
#define DEPTHWINDOW_H

#include <QMainWindow>
#include <QTimer>

typedef enum {
  SLIP_IN_SLIPS = 0,
  SLIP_OUT_OF_SLIPS = 1
} SLIP_STATUS;

typedef enum {
  BOTTOM_ON = 0,
  BOTTOM_OFF = 1
} BOTTOM_STATUS;

typedef enum {
  INTERNAL_IDLE = 0,
  INTERNAL_DRILLING = 1,
  INTERNAL_TRIP_IN = 2,
  INTERNAL_TRIP_OUT = 3,
  INTERNAL_CIRCULATING = 4
} INTERNAL_STATUS;

namespace Ui {
  class DepthWindow;
}

class DepthWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit DepthWindow(QWidget *parent = nullptr);
  ~DepthWindow();
  void InitStatus(const SLIP_STATUS slip = SLIP_IN_SLIPS, const BOTTOM_STATUS bottom = BOTTOM_OFF, INTERNAL_STATUS activity = INTERNAL_DRILLING);
  void CreateMainMenu();
public Q_SLOTS:
  void CreateDepthConfigDialog();
  void CreateActivatyDialog();
  void CreateDepthCalibrationDialog();
  void CreateDepthCtrlDialog();
  void updateFromDao();

private:
  Ui::DepthWindow *ui;
  QTimer m_timer;
};

#endif // DEPTHWINDOW_H
