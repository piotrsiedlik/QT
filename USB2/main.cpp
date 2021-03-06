#include "oknoglowne.h"
#include <QApplication>
#include "komunikacjausb.h"
#include "ustawieniausb.h"
#include <QMessageBox>
#include <QErrorMessage>
#include<QObject>
#include "ui_oknoglowne.h"
#include "ui_ustawieniausb.h"
#include <QDebug>

libusb_device **urzadzenia;
komunikacjaUSB u;
unsigned char buforx,bufory;

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
    int u=libusb_init(&ctx)
            ;
    QErrorMessage Err;
    if(u<0)
    {
        Err.showMessage("1Błąd inicjacji");
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
void komunikacjaUSB::transfer(int czujnik,komunikacjaUSB u)
{
    libusb_device *dev;
    //libusb_device **devs;
    libusb_device_handle *dev_handle;
    libusb_context *ctx =NULL;
    struct libusb_device_descriptor desc;
    int r;
    ssize_t cnt;
    QErrorMessage Err;
    libusb_set_debug(ctx,3);
    cnt=libusb_get_device_descriptor(dev, &desc);
    if(cnt<0)
    {
        {
            Err.showMessage("Błąd pobrania listy urządzeń");
            qDebug() << "Błąd pobrania listy urządzeń";
            exit(1);
        }
    }
    dev_handle=libusb_open_device_with_vid_pid(ctx,IDint[czujnik][0],IDint[czujnik][1] );
    //dev_handle=libusb_open_device_with_vid_pid(ctx,7247,0052);
    if(libusb_kernel_driver_active(dev_handle, 0) == 1)
        {
                    qDebug()<<"Kernel Driver Active"<<endl;
                    if(libusb_detach_kernel_driver(dev_handle, 0) == 0)
                        qDebug()<<"Kernel Driver Detached!";
        }
    if(dev_handle == NULL)
    {
        Err.showMessage("Nie można się połączyć z urządzeniem: "+QString::number(czujnik));
        qDebug() << "Nie można się połączyć z urządzeniem: ";
        exit(1);
    }    
    unsigned char data[10];
    int sprawdz;   
    r=libusb_claim_interface(dev_handle,0);
    if(r<0)
    {
        Err.showMessage("Nie można się połączyć z urządzeniem");
        qDebug() << "Nie można się połączyć z urządzeniem"+QString::number(r);
        exit(0);
    }    
    QString str;
    int rr=libusb_interrupt_transfer(dev_handle,0x81 ,data,10,&sprawdz,10);
    for(int j=0;j<sprawdz;j++)
    {
    str.append(data[j]);
    }
    buforx=data[3];
    bufory=data[4];
    if(libusb_attach_kernel_driver(dev_handle,0)==1)
    {
        qDebug()<<"driver on";
    }
    else
    {
        qDebug()<<"driver off";
    }
    r = libusb_release_interface(dev_handle, 0);
    qDebug()<<"KONIEC";
}
OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);

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

    for(int j=0;j<500;j++)
    {
    u.transfer(u.getCzujnik1index(),u);
   // if(u.Dane1x.isEmpty()) ui->tbError->append("Pusty");
        //else
    u.Dane1x=buforx;
    u.Dane1y=bufory;
    ui->tbError->append(QString::number(u.Dane1x));
    qDebug()<<"start:"<<u.Dane1x;

    }

    //qDebug()<<u.Dane1.last();

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

}
void OknoGlowne::wys(QString tekst)
{
    ui->tbError->append(tekst);
}
void UstawieniaUSB ::on_cbCzujnik1_currentIndexChanged(int index)
{
    u.setCzujnik1index(index);
    ui->tbUstawienia->append(QString::number(u.getCzujnik1index()));
}
