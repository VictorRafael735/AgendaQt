#ifndef SELECTLIST_H
#define SELECTLIST_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <agenda.h>

namespace Ui {
class SelectList;
}

class SelectList : public QDialog
{
    Q_OBJECT

public:
    explicit SelectList(QWidget *parent = nullptr);
    QStringList nomes = {};
    QStringList nomesSelecionados = {};
    QStringList participantes = {};
    ~SelectList();
public:
    QStringList retornaSelecionados();
    QStringList retornaParticipantes();
private slots:

    void on_btnConfirmar_clicked();

private:
    Ui::SelectList *ui;
};

#endif // SELECTLIST_H
