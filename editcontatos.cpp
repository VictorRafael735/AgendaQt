#include "editcontatos.h"
#include "ui_editcontatos.h"

EditContatos::EditContatos(QWidget *parent, int id, QString nome, QString telefone, QString email) :
    QDialog(parent),
    ui(new Ui::EditContatos)
{
    ui->setupUi(this);
    ui->idContato->setText(QString::number(id));
    ui->idContato->setVisible(false);
    ui->editNome->setText(nome);
    ui->editTelefone->setText(telefone);
    ui->editEmail->setText(email);
}

EditContatos::~EditContatos()
{
    delete ui;
}

void EditContatos::on_btnExcluirContato_clicked()
{
    QString id = ui->idContato->text();
    QString deleteQuery = "DELETE FROM tb_contatos WHERE id='"+id+"'";
    QMessageBox::StandardButton resposta= QMessageBox::question(this, "Aviso", "Deseja excluir o contato?", QMessageBox::Yes | QMessageBox::No);
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


void EditContatos::on_btnEditarContato_clicked()
{
    QString nome = ui->editNome->text();
    QString telefone = ui->editTelefone->text();
    QString email = ui->editEmail->text();
    QString id = ui->idContato->text();
    if(nome == "" || telefone == "" || email == ""){
        QMessageBox::warning(this, "Erro", "Os campos não podem estar vazios");
        return;
    }
    QSqlQuery query;
    QString updateQuery = "UPDATE tb_contatos SET nome ='"+nome+"', telefone = '"+telefone+"', email = '"+email+"' WHERE id = '"+id+"'";
    query.prepare(updateQuery);
    if(query.exec()){
        close();
    }else{
        qDebug() << "Falha ao atualizar os dados";
    }



}

