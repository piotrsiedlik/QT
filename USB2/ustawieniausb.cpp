#include "ustawieniausb.h"
#include "ui_ustawieniausb.h"
#include "komunikacjausb.h"

UstawieniaUSB::UstawieniaUSB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UstawieniaUSB)
{
    ui->setupUi(this);
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
    }


}

void UstawieniaUSB::on_pbZnajdz_clicked()
{
    komunikacjaUSB urzadzenia;
    urzadzenia.znajdzUrzadzenia();
    wyswiettbUstawienia(urzadzenia.wyswietlurzadzenia(),urzadzenia.ID,urzadzenia.getLurz());
}
