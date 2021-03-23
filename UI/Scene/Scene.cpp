#include <cassert>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include <QPixmap>
#include <QWheelEvent>

#include "Utils/ImageUtils.h"

#include "DeclareMetatype.h"

#include "Scene.h"

namespace {

constexpr double SCALE_UP_FACTOR = 1.1;
constexpr double SCALE_DOWN_FACTOR = 0.9;

}

class Scene::Impl
{
public:
	void SetImage(const cv::Mat& image, bool isNew = false)
	{
		m_image = image.clone();
		if(isNew)
			m_origImage = image.clone();
	}

	const cv::Mat& GetImage() const
	{
		return m_image;
	}

	cv::Mat GetImage()
	{
		return m_image.clone();
	}

	const cv::Mat& GetOrigImage() const
	{
		return m_origImage;
	}

	cv::Mat GetOrigImage()
	{
		return m_origImage.clone();
	}

	QGraphicsScene& Scene()
	{
		return m_scene;
	}

private:
	cv::Mat m_image;
	cv::Mat m_origImage;

	QGraphicsScene m_scene;
};

Scene::Scene(QWidget* parent)
	: QGraphicsView(parent)
	, m_impl(std::make_unique<Impl>())
{
	m_impl->Scene().setParent((parent));
	setScene(&m_impl->Scene());
}

Scene::~Scene() = default;

//.....................................................................................

void Scene::SetImage(const cv::Mat& image,  bool isNew /*= false*/)
{
	m_impl->SetImage(image, isNew);
	UpdateImage();
}

//.....................................................................................

const cv::Mat& Scene::GetImage() const
{
	return m_impl->GetImage();
}

//.....................................................................................

cv::Mat Scene::GetImage()
{
	return m_impl->GetImage();
}

//.....................................................................................

const cv::Mat& Scene::GetOrigImage() const
{
	return m_impl->GetOrigImage();
}

//.....................................................................................

cv::Mat Scene::GetOrigImage()
{
	return m_impl->GetOrigImage();
}

//.....................................................................................

void Scene::SetBefore()
{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(Utils::cvMat2QPixmap(m_impl->GetOrigImage()));

	m_impl->Scene().clear();
	m_impl->Scene().addItem(item);

	m_impl->Scene().update();
	update();
}

//.....................................................................................

void Scene::SetAfter()
{
	UpdateImage();
}

//.....................................................................................

//.....................................................................................

void Scene::wheelEvent(QWheelEvent* event)
{
	static double factor;

	factor = (event->angleDelta().y() > 0) ? SCALE_UP_FACTOR : SCALE_DOWN_FACTOR;

	const QPointF viewportPos = underMouse() ? mapFromGlobal(QCursor::pos()) : QPointF();
	const QPointF scenePos = mapToScene(viewportPos.toPoint());

	scale(factor, factor);

	if(!viewportPos.isNull())
	{
		centerOn(scenePos);
		QPointF viewportDelta = viewportPos - QPointF(viewport()->width() / 2., viewport()->height() / 2.);
		QPointF viewportCenter = mapFromScene(scenePos) - viewportDelta;
		centerOn(mapToScene(viewportCenter.toPoint()));
	}

	update();
}

//.....................................................................................

void Scene::UpdateImage()
{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(Utils::cvMat2QPixmap(m_impl->GetImage()));

	m_impl->Scene().clear();
	m_impl->Scene().addItem(item);

	m_impl->Scene().update();
	update();
}
