#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include "ustawieniausb.h"

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
