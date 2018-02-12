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
    ~UstawieniaUSB();

private:
    Ui::UstawieniaUSB *ui;
};

#endif // USTAWIENIAUSB_H
