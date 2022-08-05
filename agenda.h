#ifndef AGENDA_H
#define AGENDA_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QtSql>
#include <QFileInfo>
#include <QDir>
#include <editcontatos.h>
#include <selectlist.h>
#include <editeventos.h>



QT_BEGIN_NAMESPACE
namespace Ui { class agenda; }
QT_END_NAMESPACE

class agenda : public QMainWindow
{
    Q_OBJECT

public:
    agenda(QWidget *parent = nullptr);
    ~agenda();

public:
    QString homeDir = qApp->applicationDirPath();
    QString db_dir = homeDir + "/db_agenda.db";
    QStringList contatosDoEvento; //array com os nomes dos participantes do evento, para visualização.
    QStringList idContatosDoEvento; //array com os ids dos participantes do evento, para busca em BD.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    void pegaContatos();
    void pegaEventos();



private slots:
    void on_btnCadastrarContato_clicked();

    void on_listaContatos_cellClicked(int row, int column);

    void on_btnCadastrarEvento_clicked();

    void on_btnSelectParticipantes_clicked();

    void on_listaEventos_cellClicked(int row, int column);

    void on_participantesEvento_itemClicked(QListWidgetItem *item);

private:
    Ui::agenda *ui;
};
#endif // AGENDA_H
