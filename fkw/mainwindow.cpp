#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include "wykres.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbWykres->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbZamknij_clicked()
{
    close();
}

void MainWindow::on_pbOblicz_clicked()
{
    ui->tbWynik->clear();
    QString wynik;

    if(ui->leA->text().isEmpty() || ui->leB->text().isEmpty() || ui->leC->text().isEmpty())
    {
        wynik.append("Wprowadź współczynniki równania");
        ui->tbWynik->setTextColor(QColor(255,0,0,255)) ;
        ui->tbWynik->append(wynik);
    }
    else
    {
        float a,b,c,delta,x1,x2;
        a=ui->leA->text().toFloat();
        b=ui->leB->text().toFloat();
        c=ui->leC->text().toFloat();
        delta=b*b-4*a*c;
        if(sqrt(delta)>0)
        {
            x1=(-b+sqrt(delta))/(2*a);
            x2=(-b-sqrt(delta))/(2*a);
            wynik="X1="+QString::number(x1)+ "\nX2="+QString::number(x2) ;
        }
        else if(sqrt(delta)==0)
        {
            x1=-b/(2*a);
            wynik="delta="+QString::number(sqrt(delta))+"\nX="+QString::number(x1);
        }
        else
        {
            float u,r;
            delta=delta*-1;
            r=-b/(2*a);
            u=sqrt(delta)/(2*a);
            wynik="delta="+QString::number(delta)+"\nX1="+QString::number(r)+"+"+QString::number(u)+"i"+"\nX2="+QString::number(r)+"-"+QString::number(u)+"i";
        }
        ui->tbWynik->setTextColor(QColor(0,0,0,255)) ;
        ui->tbWynik->append(wynik);
       ui->pbWykres->setVisible(1);
     }


}

void MainWindow::on_pbWykres_clicked()
{
    wykres okno2;
    okno2.setModal(true);
    okno2.exec();


}
