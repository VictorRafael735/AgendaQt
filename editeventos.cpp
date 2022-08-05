#include "editeventos.h"
#include "ui_editeventos.h"

EditEventos::EditEventos(QWidget *parent, int id, QString nomeEvento, QString dataEvento) :
    QDialog(parent),
    ui(new Ui::EditEventos)
{
    ui->setupUi(this);
    ui->idEvento->setText(QString::number(id));
    ui->idEvento->setVisible(false);
    ui->editNomeEvento->setText(nomeEvento);
    ui->editDataEvento->setDateTime(QDateTime::fromString(dataEvento));

}

EditEventos::~EditEventos()
{
    delete ui;
}

void EditEventos::on_btnExcluirEvento_clicked()
{
    QString id = ui->idEvento->text();
    QString deleteQuery = "DELETE FROM tb_eventos WHERE id='"+id+"'";
    QMessageBox::StandardButton resposta= QMessageBox::question(this, "Aviso", "Deseja excluir o evento?", QMessageBox::Yes | QMessageBox::No);
    if(resposta == QMessageBox::Yes){
        QSqlQuery query;
        query.prepare(deleteQuery);
        if(query.exec()){
            close();
        }else{
            qDebug() << "Falha ao deletar o registro";
        }

    }
}


void EditEventos::on_btnEditarEvento_clicked()
{
    QString nomeEvento = ui->editNomeEvento->text();
    QString dataEvento = ui->editDataEvento->text();
    QString id = ui->idEvento->text();
    if(nomeEvento == "" || dataEvento == ""){
        QMessageBox::warning(this, "Erro", "Os campos não podem estar vazios");
        return;
    }
    QSqlQuery query;
    QString updateQuery = "UPDATE tb_eventos SET nome_evento ='"+nomeEvento+"', data_evento = '"+dataEvento+"' WHERE id = '"+id+"'";
    query.prepare(updateQuery);
    if(query.exec()){
        close();
    }else{
        qDebug() << "Falha ao atualizar os dados";
    }
}

