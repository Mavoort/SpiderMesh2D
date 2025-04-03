#ifndef MESHVIEW_H
#define MESHVIEW_H

#include "meshscene.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

class MeshView : public QGraphicsView {
	Q_OBJECT
  public:
    MeshView(QWidget* parent);

  protected:
    void mousePressEvent(QMouseEvent *event) override;

  private:
	MeshScene* scene = nullptr;
	QGraphicsEllipseItem* ellipseItem = nullptr;
};

#endif // MESHVIEW_H
