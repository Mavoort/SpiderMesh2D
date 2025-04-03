#ifndef MESHSCENE_H
#define MESHSCENE_H

#include "spidermesh.h"
#include <QGraphicsScene>
#include <QObject>
#include <QPoint>
#include <QPointF>

class MeshScene : public QGraphicsScene {
	Q_OBJECT
  public:
	explicit MeshScene(QObject* parent = nullptr);

  private:
	SpiderMesh mesh;

  public slots:
	void addPoint(QPointF point);
	// void deletePoint(QPointF point);
	// void addLine(QPointF pointA, QPointF pointB);
	// void addLine(int idx_A, int idx_B);
};

#endif // MESHSCENE_H
