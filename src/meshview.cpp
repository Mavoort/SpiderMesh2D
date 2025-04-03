#include "meshview.h"
#include "meshscene.h"

MeshView::MeshView(QWidget* parent)
    : QGraphicsView(parent)
{
	scene = new MeshScene(this);
	setScene(scene);

	// Optional: Set scene rect to control the scrollable area
	scene->setSceneRect(0, 0, 400, 300);
}

void MeshView::mousePressEvent(QMouseEvent *event) {
	if (event->button() != Qt::LeftButton)
		return;

	// Convert view coordinates to scene coordinatess
	auto scenePos = mapToScene(event->pos());

	// insert point into the scene
	scene->addPoint(scenePos);

	// Call base class implementation to draw on screen
	QGraphicsView::mousePressEvent(event);
}
