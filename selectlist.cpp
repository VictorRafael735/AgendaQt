#include "selectlist.h"
#include "ui_selectlist.h"

SelectList::SelectList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectList)
{
    ui->setupUi(this);
    ui->contatosSelected->setSelectionMode(QAbstractItemView::MultiSelection);
    QSqlQuery query;
    QString selectQuery = "SELECT * FROM tb_contatos ORDER BY nome asc";
    query.prepare(selectQuery);
    if(query.exec()){
        while(query.next()){
            nomes.append(query.value(1).toString());
        }
    }else{
        qDebug() << "Falha ao recuperar os registros";
    }

    ui->contatosSelected->addItems(nomes);
}

SelectList::~SelectList()
{
    delete ui;
}

QStringList SelectList::retornaSelecionados(){
    return nomesSelecionados;
}

QStringList SelectList::retornaParticipantes(){
    return participantes;
}

void SelectList::on_btnConfirmar_clicked()
{
    QList<QListWidgetItem*> lista = ui->contatosSelected->selectedItems();
    for(int i = 0;i < lista.length(); i++){
        nomesSelecionados.append("'" + lista.at(i)->text() + "'");
    }
    qDebug() << nomesSelecionados;
    QString nomes = nomesSelecionados.join(",");
    QSqlQuery query;
    QString selectQuery = "SELECT id FROM tb_contatos WHERE nome IN ("+nomes+")";
    query.prepare(selectQuery);
    if(query.exec()){
        while(query.next()){

            participantes.append(query.value(0).toString());
        }

        qDebug() << participantes;
    }else{
        qDebug() << "Falha na query";
    }
    close();
}

