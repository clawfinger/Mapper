
#include "window.h" 

//

Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	map = new Map(this);																			//Adding Map widged to central layout
	map->setData(this->getData());
	ui.mapLayout->addWidget(map, 0, 0);
	QObject::connect(ui.connectButton, SIGNAL(clicked()), this, SLOT(connect()));						//Buttons logic connections
	QObject::connect(this, SIGNAL(portConnected()), this, SLOT(enableDisconnectButton()));
	QObject::connect(this, SIGNAL(portConnected()), this, SLOT(enableScanButton()));
	QObject::connect(ui.scanButton, SIGNAL(clicked()), this, SLOT(scan()));
	QObject::connect(ui.disconnectButton, SIGNAL(clicked()), this, SLOT(disconnect()));
}

Window::~Window()
{

}

void Window::enableDisconnectButton()											//Slots and signals
{
	ui.disconnectButton->setEnabled(true);
}

void Window::enableScanButton()
{
	ui.scanButton->setEnabled(true);
}

void Window::connect()
{
	this->port.connect("COM3", 9600);
	if(this->port.connected == true)
		emit portConnected();
}
void Window::disconnect()
{
	this->port.disconnect();
	ui.disconnectButton->setEnabled(false);
	ui.scanButton->setEnabled(false);
}
void Window::scan()
{
	this->port.gatherData();	
	for( auto x : port.getData())
	{
		std::cout << x.first << '\t' << x.second << std::endl;
	}
	map->setData(this->getData());
	map->repaint();
}

pointList Window::getData()
{
	return port.getData();
}