#include "ustawieniausb.h"
#include "ui_ustawieniausb.h"

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
