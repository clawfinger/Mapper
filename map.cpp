#include "stdafx.h"
#include "map.h"

void Map::paintEvent(QPaintEvent* event)
{
	QPalette Pal(palette());									//Creating background
	Pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(Pal);
	QPainter painter(this);
	painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
	painter.setWindow(-250, -250, 500, 500);					//Setting window
	painter.drawPoint(0, 0);
	Draw(painter, array);
}

void Map::Draw(QPainter& p, std::list<std::pair<float, float>> arr)						//If array is not empty drawing all scanned points
{

	QPen pen(Qt::red, 3);
	p.setPen(pen);
	if(arr.size())
	{
		for(auto x : arr)
		{
			p.drawPoint(x.first, x.second);
		}
	}
}
void Map::setData(std::list<std::pair<float, float>> arr)								//Copying array
{
	array = arr;
}