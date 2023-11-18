#include "sceneitem.h"

#include <QPainter>

SceneItem::SceneItem(QRectF rect, QPen pen, QBrush brush)
    : QAbstractGraphicsShapeItem() {
  geometry_ = rect;
  setPen(pen);
  setBrush(brush);

  // Цвета контура при выдилении
  selectedPenBack_ = QPen(kSelectedPenColor_, pen.width(), Qt::SolidLine);
  selectedPenFront_ = QPen(pen.color(), pen.width(), kSelectedPenStyle_);

  // Деем возможность выделять и перемещать объект на сцене
  setFlags(ItemIsMovable | ItemIsSelectable);
}

SceneItem::SceneItem(SceneItem const &sceneItem)
    : QAbstractGraphicsShapeItem() {
  SceneItem(sceneItem.boundingRect(), sceneItem.pen(), sceneItem.brush());
}

// Берется при расчете коллизий, если не переопределена, то
// Возвразается boundingRect
QPainterPath SceneItem::shape() const {
  QPainterPath path;
  path.addRect(boundingRect());
  return path;
}

// Область отрисовки фигуры, принято добавлять к области половину толщины пера
QRectF SceneItem::boundingRect() const {
  int divider = 2;
  qreal penThickness = pen().widthF();

  return QRectF(-penThickness / divider, -penThickness / divider,
                geometry_.width() + penThickness,
                geometry_.height() + penThickness);
}

void SceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setPen(pen());
  painter->setBrush(brush());
  painter->drawRect(geometry_);

  // Создаем свою обводку фигуры при выдилении объекта
  if (isSelected()) {
    painter->setPen(selectedPenBack_);
    DrawBorder(painter);

    painter->setPen(selectedPenFront_);
    DrawBorder(painter);
  }
}

// Рисуем обводку
void SceneItem::DrawBorder(QPainter *painter) {
  painter->drawLine(geometry_.topLeft(), geometry_.topRight());
  painter->drawLine(geometry_.topLeft(), geometry_.bottomLeft());
  painter->drawLine(geometry_.bottomRight(), geometry_.topRight());
  painter->drawLine(geometry_.bottomRight(), geometry_.bottomLeft());
}
