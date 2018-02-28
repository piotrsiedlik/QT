#ifndef KOMUNIKACJAUSB_H
#define KOMUNIKACJAUSB_H
#include <libusb.h>
#include <QString>
#include <QList>

class komunikacjaUSB
{
public:
    komunikacjaUSB();
    void znajdzUrzadzenia();
    QString wyswietlurzadzenia();
    QString ID[20][4];
    uint16_t IDint[20][4];
    int Dane1x;
    int Dane1y;
    int getLurz()
    {
        int l=lurz;
        return l;
    }
    int getCzujnik1index()
    {return Czujnik1index;}
    void setCzujnik1index(int indeks)
    {
        Czujnik1index=indeks;
    }
public slots:
    void transfer(int czujnik, komunikacjaUSB u);
private:
    ssize_t lurz;
    int Czujnik1index;
};

#endif // KOMUNIKACJAUSB_H
