#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLayout>
#include <QLineEdit>

class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;

class dialog : public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *btnLayout;
    QHBoxLayout *leLayout;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;
    QLineEdit *le_profile;

private slots:
    void btn_ok_clicked();

signals:

public slots:

};

#endif // DIALOG_H
