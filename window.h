#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include "Serial.h"
#include "Map.h"



class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);
	~Window();
private slots:
	void enableDisconnectButton();
	void enableScanButton();
	void connect();
	void disconnect();
	void scan();
	pointList getData();
signals:
	void portConnected();
private:
	Ui::WindowClass ui;
	Serial port;
	Map* map;

};


#endif // WINDOW_H
