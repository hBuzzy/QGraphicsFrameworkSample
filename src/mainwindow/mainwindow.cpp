#include "mainwindow.h"

#include <qgraphicsitem.h>
#include <src/dragitem/dragitem.h>

#include <QGraphicsItem>
#include <QKeyEvent>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  SetUi();
  SetConnections();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::AddNewItem() {
  // Рисуем эллипс, вписанный в прямоугольник стандартным методом
  QGraphicsItem *figure = scene_->addEllipse(
      QRectF(0, 0, 70, 40),  // Геометрия фигуры
      QPen(Qt::black),       // Цвет контура фигуры
      QBrush(Qt::blue, Qt::SolidPattern));  // Цвет заливки фигуры

  // Включам возможность претаскивать объект по сцене
  figure->setFlag(QGraphicsItem::ItemIsMovable, true);
  // Включам возможность выделять объект на сцене
  figure->setFlag(QGraphicsItem::ItemIsSelectable, true);

  // Эквивалентная запись флагов, установленных выше
  figure->setFlags(QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsSelectable);
}

void MainWindow::AddNewOwnItem() {
  // Создаем свою фигуру класса SceneItem
  scene_->addItem(ItemsFactory::Create(ItemsFactory::ItemsType::kBorder));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    auto selectedItems = scene_->selectedItems();
    // Если есть выделенные объекты на сцене, берем первый из них
    if (!selectedItems.isEmpty()) {
      auto item = selectedItems[0];

      // Выводим все столкновения объекта item на сцене с помощью метода сцены
      qDebug() << "Метод сцены: " << scene_->collidingItems(item)
               << Qt::endl
               // Для выбранного объекта выводим все столкновения c помощью
               // метода объекта
               << "Метод объекта: " << item->collidingItems();

      // Проверяем сталкивается ли объект item с item2
      // item->collidesWithItem(item2)
    }
  }
}

void MainWindow::SetConnections() {
  connect(ui_->newItemButon, &QPushButton::clicked, this,
          &MainWindow::AddNewItem);

  connect(ui_->newOwnItemButton, &QPushButton::clicked, this,
          &MainWindow::AddNewOwnItem);

  connect(ui_->rotateButton, &QPushButton::clicked, scene_,
          &Scene::RotateSelectedItems);

  // Увеличиваем масштаб объектов на itemScaleFactor_
  connect(ui_->zoomInButton, &QPushButton::clicked, this,
          [=]() { scene_->ScaleSelectedItems(itemScaleFactor_); });

  // Уменьшаем масштаб объектов на itemScaleFactor_
  connect(ui_->zoomOutButton, &QPushButton::clicked, this,
          [=]() { scene_->ScaleSelectedItems(-itemScaleFactor_); });

  // Сбрасываем масштаб выделенных объектов
  connect(ui_->resetZoomButton, &QPushButton::clicked, scene_,
          &Scene::ResetSelectedItemsScale);

  // Удаляем выделенные объекты по нажатию кнопки
  connect(ui_->removeButton, &QPushButton::clicked, scene_,
          &Scene::RemoveSelectedItems);

  // Изменяем масштаб всего представления(QGraphicsView)
  connect(ui_->graphicsViewScaleButton, &QPushButton::clicked, this, [=]() {
    double scaleFactor = ui_->graphicsViewScaleFactor->value();
    ui_->graphicsView->scale(scaleFactor, scaleFactor);
  });

  // Поворачиваем представление по нажатию кнопки (QGraphicsView)
  connect(ui_->graphicsViewRotateButton, &QPushButton::clicked, this,
          [=]() { ui_->graphicsView->rotate(rotationAngle_); });
}

void MainWindow::SetUi() {
  // Создаем модель сцены, где будут храниться все объекты
  scene_ = new Scene();

  // Связываяем графичское представление с моделью
  ui_->graphicsView->setScene(scene_);

  // Заполняем пол объектов (Класс ItemsWidget).
  AddItemToList(ItemsFactory::ItemsType::kBorder);
  AddItemToList(ItemsFactory::ItemsType::kCoin);
}

void MainWindow::AddItemToList(ItemsFactory::ItemsType itemType) {
  DragItem *item = new DragItem(itemType);
  ui_->listWidget->addItem(item);  // Добавляем объект в список
  /*Задаем его представление в виде виджета
   *Можно отделить представление в отдельный класс и передавать его
   *Вторым параметром
   */
  ui_->listWidget->setItemWidget(item, item);
}
