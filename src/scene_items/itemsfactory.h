#ifndef ITEMSFACTORY_H
#define ITEMSFACTORY_H

#include <QObject>
#include <QRectF>

#include "src/scene_items/sceneitem.h"

class ItemsFactory : public QObject {
 public:
  enum ItemsType { kBorder = 0, kPlayer = 1, kCoin = 2 };
  Q_ENUM(ItemsType)

 private:
  ItemsFactory();

 public:
  static SceneItem* Create(ItemsType type);
};

#endif  // ITEMSFACTORY_H
