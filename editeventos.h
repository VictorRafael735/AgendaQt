#ifndef EDITEVENTOS_H
#define EDITEVENTOS_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class EditEventos;
}

class EditEventos : public QDialog
{
    Q_OBJECT

public:
    explicit EditEventos(QWidget *parent = nullptr, int id = 0, QString nomeEvento = NULL, QString dataEvento=NULL);
    ~EditEventos();

private slots:
    void on_btnExcluirEvento_clicked();

    void on_btnEditarEvento_clicked();

private:
    Ui::EditEventos *ui;
};

#endif // EDITEVENTOS_H
