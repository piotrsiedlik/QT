#include "oknoglowne.h"
#include <QApplication>
#include "komunikacjausb.h"
#include "ustawieniausb.h"
#include <QMessageBox>
#include <QErrorMessage>
#include<QObject>
#include "ui_oknoglowne.h"
#include "ui_ustawieniausb.h"

libusb_device **urzadzenia;
komunikacjaUSB u;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OknoGlowne w;
    w.show();
    return a.exec();
}
//komunikacja usb
komunikacjaUSB::komunikacjaUSB()
{
}
void komunikacjaUSB::znajdzUrzadzenia()
{

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
            IDint[i][0]=desc.idVendor;//0 vendor
            IDint[i][1]=desc.idProduct;//1 idProduct
            IDint[i][2]=libusb_get_bus_number(dev);//2 bus nr
            IDint[i][3]=libusb_get_device_address(dev);//3 adress
     }
    libusb_free_device_list(urzadzenia,1);
}
QString komunikacjaUSB::wyswietlurzadzenia()
{
    QString tekst;
    tekst="Liczba urządzeń: "+QString::number(lurz);
    return tekst;
}
void komunikacjaUSB::transfer(int czujnik)
{
    libusb_device *dev;
    libusb_device **devs;
    libusb_device_handle *dev_handle;
    libusb_context *ctx =NULL;
    struct libusb_device_descriptor desc;
    int r;
    ssize_t cnt;
    QErrorMessage Err;
    if(r<0)
    {
        Err.showMessage("Błąd inicjacji");
        exit(1);
    }
    libusb_set_debug(ctx,3);
    cnt=libusb_get_device_descriptor(dev, &desc);
    if(cnt<0)
    {
        {
            Err.showMessage("Błąd pobrania listy urządzeń");
            exit(1);
        }
    }
    dev_handle=libusb_open_device_with_vid_pid(ctx,IDint[czujnik][0],IDint[czujnik][1] );
    if(dev_handle == NULL)
    {
        Err.showMessage("Nie można się połączyć z urządzeniem: "+QString::number(czujnik));
        exit(1);
    }
    libusb_free_device_list(devs,1);
    unsigned char *data=new unsigned char[10];
    int sprawdz;
    r=libusb_claim_interface(dev_handle,0);
    if(r<0)
    {
        Err.showMessage("Nie można się połączyć z urządzeniem");
        exit(0);
    }
    r=libusb_bulk_transfer(dev_handle,1|LIBUSB_ENDPOINT_IN,data,10,&sprawdz,0);
    if(r==0&&sprawdz==10)
    {
        Err.showMessage("Jest git");
    }
    else
    {
        Err.showMessage("Wystąpił błąd podczas transmisji");
    }
    r = libusb_release_interface(dev_handle, 0);
    delete[] data;
}
OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
    //connect(ui->pbStart,SIGNAL(clicked(bool)),)

}

OknoGlowne::~OknoGlowne()
{
    delete ui;
}

void OknoGlowne::on_pbZamknij_clicked()
{
    close();
}

void OknoGlowne::on_pbUstawieniaUSB_clicked()
{
    UstawieniaUSB Noweokno;
    Noweokno.setModal(true);
    Noweokno.exec();
}

void OknoGlowne::on_pbStart_clicked()
{
    u.transfer(u.getCzujnik1index());
}
UstawieniaUSB::UstawieniaUSB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UstawieniaUSB)
{
    ui->setupUi(this);
    u.znajdzUrzadzenia();
    wyswiettbUstawienia(u.wyswietlurzadzenia(),u.ID,u.getLurz());
}

UstawieniaUSB::~UstawieniaUSB()
{
    delete ui;
}
void UstawieniaUSB::wyswiettbUstawienia(QString tekst,QString tablica[20][4],int liczbau)
{
    ui->tbUstawienia->clear();
    ui->tbUstawienia->append(tekst);
    for(int i=0;i<liczbau;i++)
    {
        ui->tbUstawienia->append(QString::number(i)+": Vendor: "+tablica[i][0]+" Id Produktu: "+tablica[i][1]+" Bus: "+tablica[i][2]+" Adres: "+tablica[i][3]) ;
        ui->cbCzujnik1->addItem(QString::number(i));
    }


}

void UstawieniaUSB::on_pbZnajdz_clicked()
{

    u.znajdzUrzadzenia();
    wyswiettbUstawienia(u.wyswietlurzadzenia(),u.ID,u.getLurz());
}

void UstawieniaUSB::on_cbCzujnik1_highlighted(int index)
{
    u.setCzujnik1index(index);
}
