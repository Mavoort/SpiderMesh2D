#include "meshscene.h"
#include <qgraphicsview.h>

MeshScene::MeshScene(QObject* parent)
    : QGraphicsScene{ parent }
{
}

void MeshScene::addPoint(QPointF point)
{
	// add point to the mesh object
	mesh.addPoint(point.x(), point.y());

	// draw point using Qt6
	auto pen = QPen{};
	auto brush = QBrush{ Qt::red };
	addEllipse(point.x() - 10, point.y() - 10, 20, 20, pen, brush);
}
