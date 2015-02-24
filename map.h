#ifndef MAP_H
#define MAP_H

//Custom painting widget 

#include <QWidget>
#include <QPainter>

class Map : public QWidget
{
	Q_OBJECT

private:
	std::list<std::pair<float, float>> array;
public:
	Map(QWidget* parent = nullptr):QWidget(parent)
	{
		setFixedSize(600,600);	

	};
	~Map(){};
	void paintEvent(QPaintEvent* event);
	void Draw(QPainter& p, std::list<std::pair<float, float>> array);
	void setData(std::list<std::pair<float, float>>);
};
#endif