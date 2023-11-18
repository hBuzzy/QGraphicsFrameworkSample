#include "scene.h"

#include <src/scene_items/itemsfactory.h>

#include <QByteArray>
#include <QDataStream>
#include <QGraphicsSceneDragDropEvent>
#include <QIODevice>

#include "qmimedata.h"
#include "src/dragitem/dragitem.h"

Scene::Scene(QObject *parent) : QGraphicsScene{parent} {
  setSceneRect(QRectF(0, 0, 400, 500));
}

// Поворачиваем выделенные объекты
void Scene::RotateSelectedItems() {
  int angle = 45;

  for (auto &item : selectedItems()) {
    item->setRotation(item->rotation() + angle);
  }
}

// Масштабируем выделенные объекты
void Scene::ScaleSelectedItems(qreal scaleFactor) {
  for (auto &item : selectedItems()) {
    item->setScale(item->scale() + scaleFactor);
  }
}

// Удаляем выделенные объекты
void Scene::RemoveSelectedItems() {
  for (auto &item : selectedItems()) {
    removeItem(item);
  }
}

// Сбрасываем масштаб для выделенных объектов
void Scene::ResetSelectedItemsScale() {
  int defaultScale = 1;

  for (auto &item : selectedItems()) {
    item->setScale(defaultScale);
  }
}

// Обработка события входа перетаскиваемого объекта
void Scene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  // Проверяем есть ли в mime необходимый нам формат данных и либо игнорируем,
  // либо принимаем событие
  if (event->mimeData()->hasFormat(DragItem::kMimeFormat)) {
    event->acceptProposedAction();
  } else {
    event->ignore();
  }
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasFormat(DragItem::kMimeFormat)) {
    event->accept();
  }
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event) {
  if (event->mimeData()->hasFormat(DragItem::kMimeFormat)) {
    /*
     *Если формат mime нам подходит, то считываем необходимые данные (тип
     *фигуры), которые Вносили в DragItem
     */
    QByteArray itemData = event->mimeData()->data(DragItem::kMimeFormat);
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);

    ItemsFactory::ItemsType itemType;
    // Записываем значение переданного типа из потока.
    dataStream >> itemType;

    // Создаем объект согласно типу и размещаем его относительно положения мыши
    // в момент отпускания левой кнопки мыши
    SceneItem *item = ItemsFactory::Create(itemType);
    item->setPos(event->scenePos());

    // Добавляем объект на сцену
    addItem(item);

    event->acceptProposedAction();
  } else {
    event->ignore();
  }
}
