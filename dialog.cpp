#include "dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

dialog::dialog(QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    //setCaption("Add new profile");

    btn_ok = new QPushButton("Ok", this);
    btn_cancel = new QPushButton("Cancel", this);
    le_profile = new QLineEdit(this);
    leLayout = new QHBoxLayout();
    btnLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    le_profile->setFocus();

    connect(btn_ok, SIGNAL(clicked()), this, SLOT(btn_ok_clicked()));
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));

    leLayout->addWidget(le_profile);
    btnLayout->addWidget(btn_ok);
    btnLayout->addWidget(btn_cancel);

    mainLayout->addLayout(leLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
}

void dialog::btn_ok_clicked()
{
    MainWindow mw;
    mw.newProfile(le_profile->text());
}
