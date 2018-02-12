#include "oknoglowne.h"
#include <QApplication>
#include <komunikacjausb.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OknoGlowne w;
    w.show();
    komunikacjaUSB U1;
    U1.znajdzUrzadzenia();
    return a.exec();
}
