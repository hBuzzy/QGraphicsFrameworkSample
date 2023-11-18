#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QAbstractGraphicsShapeItem>
#include <QBrush>
#include <QPen>

class SceneItem : public QAbstractGraphicsShapeItem {
 public:
  explicit SceneItem(QRectF rect, QPen pen, QBrush brush);
  SceneItem(SceneItem const &sceneItem);

 public:
  QPainterPath shape() const;
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

 private:
  void DrawBorder(QPainter *painter);

 private:
  const QColor kSelectedPenColor_ = Qt::white;
  const Qt::PenStyle kSelectedPenStyle_ = Qt::DashLine;

  QRectF geometry_;
  QPen selectedPenFront_;
  QPen selectedPenBack_;
};

#endif  // SCENEITEM_H
