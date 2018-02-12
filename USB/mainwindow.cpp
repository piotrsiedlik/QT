#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <libusb.h>
#include <QList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    libusb_device **dev;
    libusb_context *contex =NULL; //nie tworzę sterownika
    int Urzadzenia;
    int deb;
    QList <int> bus;
    deb=libusb_init(&contex);
    if(deb<0) exit(1);
    Urzadzenia= libusb_get_device_list(contex,&dev);
    ui->textBrowser->append(QString::number(Urzadzenia));
    print_devs(dev);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::print_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0, j = 0;
    uint8_t path[8];

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
        ui->textBrowser->append("failed to get device descriptor");
            return;
        }

        ui->textBrowser->append("id: "+
            QString::number(desc.idVendor)+", idProduct: "+QString::number(desc.idProduct)+", bus :"+
            QString::number(libusb_get_bus_number(dev))+", device: "+QString::number(libusb_get_device_address(dev)));


        ui->textBrowser->append("\n\n");
    }

}
MainWindow::connection()
{

}
