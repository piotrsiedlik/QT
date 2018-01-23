#ifndef WYKRES_H
#define WYKRES_H

#include <QDialog>

namespace Ui {
class wykres;
}

class wykres : public QDialog
{
    Q_OBJECT

public:
    explicit wykres(QWidget *parent = 0);
    ~wykres();

private:
    Ui::wykres *ui;
};

#endif // WYKRES_H
