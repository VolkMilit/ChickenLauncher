#include "descriptionpopup.h"

descriptionpopup::descriptionpopup(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    setModal(true);
    resize(500, 600);

    pte = new QPlainTextEdit();
    pte->setReadOnly(true);

    button = new QPushButton();
    button->setText("Close dialog");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(hide()));

    layout->addWidget(pte);
    layout->addWidget(button);
}

descriptionpopup::~descriptionpopup()
{
    delete pte;
    delete button;
}

void descriptionpopup::showFullDescription(QString wadName, QString text)
{
    setWindowTitle(wadName);
    pte->appendPlainText(text);
}
