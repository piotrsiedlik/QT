#include "wykres.h"
#include "ui_wykres.h"

wykres::wykres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wykres)
{
    ui->setupUi(this);
}

wykres::~wykres()
{
    delete ui;
}
