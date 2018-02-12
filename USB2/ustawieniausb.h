#ifndef USTAWIENIAUSB_H
#define USTAWIENIAUSB_H

#include <QDialog>

namespace Ui {
class UstawieniaUSB;
}

class UstawieniaUSB : public QDialog
{
    Q_OBJECT

public:
    explicit UstawieniaUSB(QWidget *parent = 0);
    void wyswiettbUstawienia(QString tekst,QString tablica[20][4],int liczbau);
    ~UstawieniaUSB();

private slots:
    void on_pbZnajdz_clicked();


private:
    Ui::UstawieniaUSB *ui;
};

#endif // USTAWIENIAUSB_H
