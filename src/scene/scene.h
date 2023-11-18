#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Scene : public QGraphicsScene {
  // Q_OBJECT
 public:
  explicit Scene(QObject *parent = nullptr);

 public slots:
  void RotateSelectedItems();
  void ScaleSelectedItems(qreal scaleFactor);
  void RemoveSelectedItems();
  void ResetSelectedItemsScale();

 protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
  void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
  void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif  // SCENE_H
