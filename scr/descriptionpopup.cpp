#include "descriptionpopup.h"

descriptionpopup::descriptionpopup(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    this->setModal(true);
    this->resize(500, 600);
}

void descriptionpopup::showFullDescription(QString wadName, QString text)
{
    this->setWindowTitle(wadName);

    QPlainTextEdit *pte = new QPlainTextEdit();
    pte->setReadOnly(true);
    pte->appendPlainText(text);

    QPushButton *button = new QPushButton();
    button->setText("Close dialog");
    connect(button, SIGNAL(click()), this, SLOT(on_close_button_clicked()));

    this->layout()->addWidget(pte);
    this->layout()->addWidget(button);
}

void descriptionpopup::on_close_button_clicked()
{
    this->hide();
}
