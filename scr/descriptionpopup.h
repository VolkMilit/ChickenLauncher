#ifndef DESCRIPTIONPOPUP_H
#define DESCRIPTIONPOPUP_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextStream>

class descriptionpopup : public QDialog
{
    Q_OBJECT
public:
    explicit descriptionpopup(QWidget* parent = nullptr);
    virtual ~descriptionpopup();

protected:
    void showFullDescription(QString wadName, QString text);

private:
    QPlainTextEdit *pte;
    QPushButton *button;
};

#endif // DESCRIPTIONPOPUP_H
