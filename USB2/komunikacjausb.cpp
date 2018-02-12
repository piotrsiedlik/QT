#include "komunikacjausb.h"
#include <QMessageBox>
#include <QErrorMessage>

komunikacjaUSB::komunikacjaUSB()
{

}
void komunikacjaUSB::znajdzUrzadzenia()
{
    libusb_device **urzadzenia;
    libusb_device_handle *devhandle;
    libusb_context *ctx=NULL;
    int u=libusb_init(&ctx);
    QErrorMessage Err;
    if(u<0)
    {
        Err.showMessage("Błąd inicjacji");
        exit(1);
    }
    libusb_set_debug(ctx,3);
    ssize_t lurz;
    lurz=libusb_get_device_list(ctx,&urzadzenia);
    if(lurz<0)
    {
      Err.showMessage("Nie znaleziono urządzeń");
    }
}
