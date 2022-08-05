#include "agenda.h"
#include "ui_agenda.h"
agenda::agenda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::agenda)
{
    ui->setupUi(this);
    db.setDatabaseName(db_dir);
    !db.open() ? qDebug() << "Falha ao iniciar o banco" : qDebug() <<"Banco iniciado com sucesso";
    pegaContatos();
    pegaEventos();

}

agenda::~agenda()
{
    delete ui;
}

void agenda::pegaContatos(){
    QSqlQuery query;
    QString selectQuery = "SELECT * FROM tb_contatos ORDER BY nome asc";
    query.prepare(selectQuery);
    if(query.exec()){
        int cont = 0;
        ui->listaContatos->setColumnCount(4);
        while(query.next()){
            ui->listaContatos->insertRow(cont);
            for(int i =0; i<4; i++){
                ui->listaContatos->setItem(cont, i, new QTableWidgetItem(query.value(i).toString()));
            }
            ++cont;
        }
        ui->listaContatos->verticalHeader()->setVisible(false);
        QStringList headersContatos = {"Id","Nome", "Telefone", "Email"};
        ui->listaContatos->setColumnHidden(0, true);
        ui->listaContatos->setColumnWidth(1, 200);
        ui->listaContatos->setColumnWidth(2, 200);
        ui->listaContatos->setColumnWidth(3, 350);
        ui->listaContatos->setHorizontalHeaderLabels(headersContatos);
        while (cont < ui->listaContatos->rowCount()){
            ui->listaContatos->removeRow(cont);
        }
    }else{
        qDebug() << "Falha ao iniciar o banco de dados";
    }
}

void agenda::pegaEventos(){
    QSqlQuery query;
    QString selectQuery = "SELECT * FROM tb_eventos ORDER BY nome_evento asc";
    query.prepare(selectQuery);
    if(query.exec()){
        int cont = 0;
        ui->listaEventos->setColumnCount(3);
        while(query.next()){
            ui->listaEventos->insertRow(cont);
            for(int i =0; i<3; i++){
                ui->listaEventos->setItem(cont, i, new QTableWidgetItem(query.value(i).toString()));
            }
            ++cont;
        }
        ui->listaContatos->verticalHeader()->setVisible(false);
        QStringList headersContatos = {"Id","Evento", "Data"};
        ui->listaEventos->setColumnHidden(0, true);
        ui->listaEventos->setColumnWidth(1, 200);
        ui->listaEventos->setColumnWidth(2, 200);
        ui->listaEventos->setHorizontalHeaderLabels(headersContatos);
        while (cont < ui->listaEventos->rowCount()){
            ui->listaEventos->removeRow(cont);
        }
    }else{
        qDebug() << "Falha ao iniciar o banco de dados";
    }
}

void agenda::on_btnCadastrarContato_clicked()
{
    QString nome = ui->inNome->text();
    QString telefone = ui->inTelefone->text();
    QString email = ui->inEmail->text();

    if(nome == "" || telefone == "" || email == ""){
        QMessageBox::warning(this, "Erro", "Preencha todos os campos");
        ui->inNome->clear();
        ui->inTelefone->clear();
        ui->inEmail->clear();
        ui->inNome->setFocus();
        return;
    }

    if(!db.isOpen()){
        QMessageBox::warning(this, "Erro", "O banco de dados não foi inicializado corretamente");
        return;
    }

    QSqlQuery query;
    QString insertQuery = "INSERT INTO tb_contatos (nome, telefone, email) VALUES ('"+nome+"', '"+telefone+"', '"+email+"')";
    query.prepare(insertQuery);
    if (query.exec(insertQuery)){
        ui->statusbar->showMessage("Contato cadastrado com sucesso");
        QTimer::singleShot(2000, [&](){ ui->statusbar->showMessage("");});
        ui->inNome->clear();
        ui->inTelefone->clear();
        ui->inEmail->clear();
        ui->inNome->setFocus();
        ui->listaContatos->clear();
        pegaContatos();
    }else{
        qDebug() << "Falha ao inserir os dados";
    }
}


void agenda::on_listaContatos_cellClicked(int row, int column)
{
    column = 0;
    int id = ui->listaContatos->item(row, column)->text().toInt();
    QString nome = ui->listaContatos->item(row, 1)->text();
    QString telefone = ui->listaContatos->item(row, 2)->text();
    QString email = ui->listaContatos->item(row, 3)->text();
    EditContatos e(this, id, nome, telefone, email);
    e.exec();
    pegaContatos();
}

void agenda::on_btnSelectParticipantes_clicked()
{
    SelectList s;
    s.exec();
    if(s.close()){
        contatosDoEvento = s.retornaSelecionados();
        idContatosDoEvento = s.retornaParticipantes();
        qDebug() << contatosDoEvento;
        ui->participantesEvento->addItems(contatosDoEvento);
    }
}


void agenda::on_btnCadastrarEvento_clicked()
{
    qDebug() << idContatosDoEvento;
    QString nomeEvento = ui->inNomeEvento->text();
    QString data = ui->dataEvento->text();

    if(nomeEvento == "" || data == ""){
        QMessageBox::warning(this, "Erro", "Preencha todos os campos");
        ui->inNomeEvento->clear();
        ui->dataEvento->clear();
        ui->inNomeEvento->setFocus();
        return;
    }

    if(!db.isOpen()){
        QMessageBox::warning(this, "Erro", "O banco de dados não foi inicializado corretamente");
        return;
    }
    QString idContatos = idContatosDoEvento.join(",");
    QSqlQuery query;
    QString insertQuery = "INSERT INTO tb_eventos (nome_evento, data_evento, participanteId) VALUES ('"+nomeEvento+"', '"+data+"', '{"+idContatos+"}')";
    query.prepare(insertQuery);
    if (query.exec()){
        qDebug() << "Inseriu os ids";
        ui->statusbar->showMessage("Evento cadastrado com sucesso");
        QTimer::singleShot(2000, [&](){ ui->statusbar->showMessage("");});
        ui->inNomeEvento->clear();
        ui->dataEvento->clear();
        ui->participantesEvento->clear();
        ui->inNomeEvento->setFocus();

    }else{
        qDebug() << "Falha ao inserir os dados";
    }
    pegaEventos();
}



void agenda::on_listaEventos_cellClicked(int row, int column)
{
    column = 0;
    int id = ui->listaEventos->item(row, column)->text().toInt();
    QString nomeEvento = ui->listaEventos->item(row, 1)->text();
    QString dataEvento = ui->listaEventos->item(row, 2)->text();
    EditEventos e(this, id, nomeEvento, dataEvento);
    e.exec();
    pegaEventos();
}


void agenda::on_participantesEvento_itemClicked(QListWidgetItem *item)
{
    qDebug() << contatosDoEvento;
    contatosDoEvento.removeOne(item->text());
    qDebug() << contatosDoEvento;
    ui->participantesEvento->removeItemWidget(item);
    ui->participantesEvento->takeItem(ui->participantesEvento->currentRow());
}

