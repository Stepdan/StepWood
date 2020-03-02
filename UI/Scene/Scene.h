#pragma once

#include <memory>

#include <QGraphicsView>
#include <QGraphicsScene>

class Scene : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void wheelEvent(QWheelEvent* event) override;

public:
    void SetImage(const QImage& image);

private:
    QGraphicsScene m_scene;
};
