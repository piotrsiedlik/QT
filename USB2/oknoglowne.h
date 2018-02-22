#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H

#include <QMainWindow>

namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGlowne(QWidget *parent = 0);
    ~OknoGlowne();
    void wys(QString tekst);
signals:
    void start();

private slots:
    void on_pbZamknij_clicked();

    void on_pbUstawieniaUSB_clicked();

    void on_pbStart_clicked();

private:
    Ui::OknoGlowne *ui;
};

#endif // OKNOGLOWNE_H
