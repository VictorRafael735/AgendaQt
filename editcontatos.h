#ifndef EDITCONTATOS_H
#define EDITCONTATOS_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class EditContatos;
}

class EditContatos : public QDialog
{
    Q_OBJECT

public:
    explicit EditContatos(QWidget *parent = nullptr, int id = 0, QString nome = NULL, QString telefone=NULL, QString email=NULL);
    ~EditContatos();

private slots:
    void on_btnExcluirContato_clicked();

    void on_btnEditarContato_clicked();

private:
    Ui::EditContatos *ui;
};

#endif // EDITCONTATOS_H
