#include "itemsfactory.h"

ItemsFactory::ItemsFactory() {}

// Крайне примитивная реализация фабричного метода для выделения одного места,
// ответственного за создание фигур
SceneItem *ItemsFactory::Create(ItemsType type) {
  if (type == ItemsType::kBorder) {
    return new SceneItem(QRectF(0, 0, 70, 40), QPen(Qt::black, 1),
                         QBrush(Qt::green, Qt::SolidPattern));
  } else {
    return new SceneItem(QRectF(0, 0, 20, 20), QPen(),
                         QBrush(Qt::BDiagPattern));
  }
}
