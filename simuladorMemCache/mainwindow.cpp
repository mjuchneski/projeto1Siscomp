#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QRandomGenerator>

QFile arquivo;
QString abrirArquivo;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*Abertura do arquivo*/
    QString filtro = "Todos os Arquivos(*.*) ;; Texto (*.txt)";// filtro para mostrar apenas os arquivos txt
    //faz a abertura da cx de dialogo
    abrirArquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivos","C:/Users/Higo Alves/Documents/GitHub/projeto1Siscomp/",filtro);

    /*Manipulação do arquivo*/
    QFile arquivo(abrirArquivo);//faz a criação do arquivo
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
        QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
    }
    QTextStream entrada(&arquivo);

    QString texto = entrada.readAll();// faz a leitura do arquivo e retorna uma string
    ui->plainTextEdit->setPlainText(texto);// passa o conteudo do texto para o plaintext
    arquivo.close();
}




void MainWindow::on_radioDireto_clicked()
{
    ui->radioFIFO->hide();
    ui->radioLFU->hide();
    ui->radioLRU->hide();
    ui->radioRANDOM->hide();
}

void MainWindow::on_radioAssociativo_clicked()
{
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}

void MainWindow::on_radioAssociativoConjunto_clicked()
{
    ui->radioFIFO->show();
    ui->radioLFU->show();
    ui->radioLRU->show();
    ui->radioRANDOM->show();
}

void MainWindow::on_btnInserir_clicked()
{
    ui->tableCache->setRowCount(ui->editCapacidadeCache->text().toInt());
    ui->tableCache->setColumnCount(3);
    ui->tableCache->verticalHeader()->setVisible(false);
    ui->tableCache->setEditTriggers(QAbstractItemView::NoEditTriggers);


        for (int i = 0 ; i < ui->editCapacidadeCache->text().toInt(); i++) {
            ui->tableCache->setItem(i,0,new QTableWidgetItem("0"));//preenche a linha validade na tabela da cache
            ui->tableCache->setItem(i,1,new QTableWidgetItem(""));
        }//end for
}


void MainWindow::on_btnRodar_clicked()
{

    int hit = 0, miss = 0;
    ui->editMiss->setText(QString::number(miss));
    ui->editHit->setText(QString::number(hit));
//------------Mapeamento Direto-----------------
    if(ui->radioDireto->isChecked() == true){
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha
            int tam = ui->editCapacidadeCache->text().toInt();
            int row = line.toInt() % tam;
            if(ui->tableCache->item(row,0)->text() == "0"){// verifica se a validade é 0
                ui->tableCache->setItem(row,1, new QTableWidgetItem(line));
                ui->tableCache->setItem(row,0, new QTableWidgetItem("1"));
                qDebug() << "miss";
                miss ++;
                ui->editMiss->setText(QString::number(miss));
                } else if (ui->tableCache->item(row,0)->text() == "1" && ui->tableCache->item(row,1)->text() == line) {
                            hit ++;
                            qDebug() << "hit";
                            ui->editHit->setText(QString::number(hit));
                        } else if (ui->tableCache->item(row,0)->text() == "1" && ui->tableCache->item(row,1)->text() != line) {
                                    ui->tableCache->setItem(row,1, new QTableWidgetItem(line));
                                    ui->tableCache->setItem(row,0, new QTableWidgetItem("1"));
                                    qDebug() << "miss";
                                    miss ++;
                                    ui->editMiss->setText(QString::number(miss));
                                }


            /*if (  i >= ui->editCapacidadeCache->text().toInt()-1) {
                qDebug()<< "nivel 1";
                int tam = ui->editCapacidadeCache->text().toInt();
                int posicao = line.toInt() % tam;
                qDebug()<< "linha" << line;
                qDebug()<< "tamanho" << tam;
                qDebug()<< "resto" << posicao;
                    if(ui->tableCache->item(posicao,0)->text() == "0" ){
                        qDebug()<< "nivel 2";
                        ui->tableCache->setItem(posicao,1, new QTableWidgetItem(line));
                        qDebug() << "miss direto cache menor que mem principal";
                        qDebug() << "valor resto "<< posicao;
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));
                    } else if (ui->tableCache->item(posicao,0)->text() == "1" && ui->tableCache->item(posicao,1)->text() != line) {
                        qDebug()<< "nivel 3";
                        ui->tableCache->setItem(posicao,1, new QTableWidgetItem(line));
                        qDebug() << "miss direto cache menor que mem principal";
                        qDebug() << "valor resto "<< posicao;
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));
                            }
                    else if(ui->tableCache->item(posicao,0)->text() == "1" && ui->tableCache->item(posicao,1)->text() == line){
                            qDebug()<< "nivel 4";
                            hit ++;
                            qDebug() << "hit direto cache menor que mem principal";
                            qDebug() <<"valor resto "<< posicao;
                            ui->editHit->setText(QString::number(hit));
                            }
            }
            i ++;*/

        }   //end while
            arquivo.close();
    }//end if

//----------------Mapeamento Associativo + algoritmo RANDOM--------------------
    if (ui->radioAssociativo->isChecked() && ui->radioRANDOM->isChecked()){
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if

        QTextStream entrada(&arquivo);
        while (!arquivo.atEnd()) {
            QString line = arquivo.readLine();//faz a leitura de uma linha

            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
                // ----------verifica se ja existe na cache----------
                if (ui->tableCache->item(i,0)->text()== "1" && ui->tableCache->item(i,1)->text() == line) {
                    hit ++;
                    ui->editHit->setText(QString::number(hit));
                    i = ui->editCapacidadeCache->text().toInt();
                }else if(ui->tableCache->item(i,0)->text() == "0"){
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));
                    i = ui->editCapacidadeCache->text().toInt();
                } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,0)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                    int tamanhoRandom = ui->editCapacidadeCache->text().toInt();
                    int random = QRandomGenerator::global()->bounded(tamanhoRandom);
                    ui->tableCache->setItem(random,1, new QTableWidgetItem(line));
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                }
            }//end for
        }//end while






        }//end while
        arquivo.close();
    }//end if



    /*QString concatena = "";
    int row = 0, posicaoDaVirgula = 0;
    QFile arquivo(abrirArquivo);
    if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
        QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
    }
    QTextStream entrada(&arquivo);
    while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha
        for (int c = 0;c < line.length();c++) {//encontra a posição da virgula
            if (line[c] == ","){
                posicaoDaVirgula = c;
            }
        }
        concatena = "";
        for (int i = 0; i < posicaoDaVirgula; i++) {//concatena os dados antes da virgula
            concatena = concatena + line[i];
        }
        ui->tableCache->setItem(row, 0, new QTableWidgetItem(concatena));//adiciona na celula

        concatena = "";

        for (int j = posicaoDaVirgula; j < line.length(); j++) {//concatena os dados depois da virgula
            concatena = concatena + line[j+1];
        }
        ui->tableCache->setItem(row, 1, new QTableWidgetItem(concatena));//adiciona na celula
        row++;

    }*/


