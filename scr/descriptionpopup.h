#ifndef DESCRIPTIONPOPUP_H
#define DESCRIPTIONPOPUP_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QPlainTextEdit>

class descriptionpopup : public QDialog
{
    Q_OBJECT
public:
    explicit descriptionpopup(QWidget* parent = nullptr);

//protected:
    void showFullDescription(QString wadName, QString text);

private slots:
    void on_close_button_clicked();
};

#endif // DESCRIPTIONPOPUP_H
