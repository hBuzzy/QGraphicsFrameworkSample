#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <src/scene/scene.h>
#include <src/scene_items/itemsfactory.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void AddNewItem();
  void AddNewOwnItem();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private:
  void SetConnections();
  void SetUi();
  void AddItemToList(ItemsFactory::ItemsType itemType);

 private:
  Ui::MainWindow *ui_;
  Scene *scene_;
  int rotationAngle_ = 45;
  qreal itemScaleFactor_ = 0.1;
};
#endif  // MAINWINDOW_H
