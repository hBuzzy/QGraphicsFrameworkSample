#ifndef DRAGITEM_H
#define DRAGITEM_H

#include <src/scene_items/itemsfactory.h>

#include <QGraphicsItem>
#include <QListWidget>
#include <QWidget>

class DragItem : public QWidget, public QListWidgetItem {
  Q_OBJECT
 public:
  explicit DragItem(ItemsFactory::ItemsType type, QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event);

 public:
  SceneItem *GetGraphicsItem() const;
  ItemsFactory::ItemsType GetType() const;

 public:
  static const inline QString kMimeFormat = "application/x-dnditemdata";

 private:
  SceneItem *graphicsItem_;
  ItemsFactory::ItemsType type_;
};

#endif  // DRAGITEM_H
