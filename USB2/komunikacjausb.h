#ifndef KOMUNIKACJAUSB_H
#define KOMUNIKACJAUSB_H
#include <libusb.h>
#include <QString>

class komunikacjaUSB
{
public:
    komunikacjaUSB();
    void znajdzUrzadzenia();
    QString wyswietlurzadzenia();
    QString ID[20][4];
    int getLurz()
    {
        int l=lurz;
        return l;
    }
private:
    ssize_t lurz;

};

#endif // KOMUNIKACJAUSB_H
