#include "komunikacjausb.h"
#include "ustawieniausb.h"
#include <QMessageBox>
#include <QErrorMessage>

komunikacjaUSB::komunikacjaUSB()
{

}
void komunikacjaUSB::znajdzUrzadzenia()
{
    libusb_device **urzadzenia;
    //libusb_device_handle *devhandle;
    libusb_context *ctx=NULL;
    int u=libusb_init(&ctx);
    QErrorMessage Err;
    if(u<0)
    {
        Err.showMessage("Błąd inicjacji");
        exit(1);
    }
    libusb_set_debug(ctx,3);
    lurz =libusb_get_device_list(ctx,&urzadzenia);
    if(lurz<0)
    {
      Err.showMessage("Nie znaleziono urządzeń");
    }
    libusb_device *dev;
    int i = 0;
    while ((dev = urzadzenia[i++]) != NULL)
    {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0)
        {
            ID[0][0]="ERROR";
            return;
        }
            ID[i][0]=QString::number(desc.idVendor);//0 vendor
            ID[i][1]=QString::number(desc.idProduct);//1 idProduct
            ID[i][2]=QString::number(libusb_get_bus_number(dev));//2 bus nr
            ID[i][3]=QString::number(libusb_get_device_address(dev));//3 adress
     }

}
QString komunikacjaUSB::wyswietlurzadzenia()
{
    QString tekst;
    tekst="Liczba urządzeń: "+QString::number(lurz);
    return tekst;
}


