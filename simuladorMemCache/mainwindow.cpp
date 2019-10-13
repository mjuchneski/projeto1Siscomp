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
int fifo = 0;
QVector<int> vet;
//QVector<int> vetLRU;



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
    fifo = 0;

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
                } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                    int tamanhoRandom = ui->editCapacidadeCache->text().toInt();
                    int random = QRandomGenerator::global()->bounded(tamanhoRandom);
                    ui->tableCache->setItem(random,1, new QTableWidgetItem(line));
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                }
            }//end for
        }//end while
        }//end if
        arquivo.close();

        //----------------Mapeamento Associativo + FIFO--------------------
    if (ui->radioAssociativo->isChecked() && ui->radioFIFO->isChecked()){
        fifo ++;

        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);
        vet.resize(ui->editCapacidadeCache->text().toInt());
        if (fifo -1 == 0){
            for (int i = 0; i < vet.size(); i++){
                vet[i]= ui->tableCache->item(i,1)->text().toInt();
            }
        }

        //qDebug()<< vet << "vetor preenchido com o que estava na cache";
        while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha
            QString cauda = line;
            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
                // ----------verifica se ja existe na cache----------
                if (ui->tableCache->item(i,0)->text()== "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit
                    hit ++;
                    ui->editHit->setText(QString::number(hit));
                    i = ui->editCapacidadeCache->text().toInt();
                }else if(ui->tableCache->item(i,0)->text() == "0"){//verifica a linha é vazia
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));
                    vet[i] = line.toInt();
                    //qDebug()<< vet[i];
                    i = ui->editCapacidadeCache->text().toInt();
                    //-----------FIFO----------
                    //verifica se a linha esta cheia, se a linha é diferente na cache e se a cache está cheia
                } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                            //qDebug()<< "Fifo";
                            miss ++;
                            ui->editMiss->setText(QString::number(miss));
                            ui->tableCache->setItem(vet[0],1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                            vet.pop_front();//remove da cabeça
                            vet.push_back(cauda.toInt());//insere na cauda
                            /*for (int c = 1; c <= vet.size(); c++) {
                               //qDebug()<< c;
                               if(c < vet.size()){
                                    vet[c-1] = vet[c];
                                    //qDebug()<< vet[c];
                               }
                               if(c >= vet.size()) {
                                    vet[c-1] = cauda.toInt();
                                   //qDebug()<< vet <<"cauda";
                                 }
                             }*/
                       }
             }//end for
             }
        }// end while
        arquivo.close();


            //---------------------ASSOCIATIVO + LRU-------------------

    if (ui->radioAssociativo->isChecked() && ui->radioLRU->isChecked()){
       QVector<int> vetLRU;

       vetLRU.resize(ui->editCapacidadeCache->text().toInt());
       qDebug()<< vetLRU;
       QFile arquivo(abrirArquivo);
       if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
           QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
       }//end if
       QTextStream entrada(&arquivo);

       while (!arquivo.atEnd()) {
       QString line = arquivo.readLine();//faz a leitura de uma linha

        for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
           // ----------verifica se ja existe na cache----------
           if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit
               hit ++;
               ui->editHit->setText(QString::number(hit));
               vetLRU.move(i, vetLRU.size()-1);// move o valor da posição atual para o fim do vetor
               qDebug()<< vetLRU<< "hit";
               i = ui->editCapacidadeCache->text().toInt();
           }else if(ui->tableCache->item(i,0)->text() == "0"){//verifica a linha é vazia
               miss ++;
               ui->editMiss->setText(QString::number(miss));
               ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
               ui->tableCache->setItem(i,1, new QTableWidgetItem(line));
               vetLRU.push_back(line.toInt());//insere na cauda
               vetLRU.pop_front();//remove da cabeça
               qDebug()<< vetLRU << "miss cache vazia";
               i = ui->editCapacidadeCache->text().toInt();
               //-----------LRU----------
               //verifica a validade, se a linha é diferente na cache e se a cache está cheia
           } else if (ui->tableCache->item(i,0)->text() == "1"  && ui->tableCache->item(i,1)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                   miss ++;
                   ui->editMiss->setText(QString::number(miss));
                   ui->tableCache->setItem(vetLRU[0],1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                   vetLRU.push_back(line.toInt());//insere na cauda
                   vetLRU.pop_front();//remove da cabeça
                   qDebug()<< vetLRU<<"miss cache cheia";
               }
        }

       }
       arquivo.close();

    }

//-----------------------LFU---------------------
    if (ui->radioAssociativo->isChecked() && ui->radioLFU->isChecked()){
        QVector<int> vetLFU;
        QVector<int> vetLFUHit;

        vetLFU.resize(ui->editCapacidadeCache->text().toInt());
        vetLFUHit.resize(ui->editCapacidadeCache->text().toInt());
        qDebug()<< vetLFU;
        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);

        while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha

            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
                // ----------verifica se ja existe na cache----------
                if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit
                    hit ++;
                    ui->editHit->setText(QString::number(hit));
                    qDebug()<<"hit";
                    vetLFUHit[i]++;
                    vetLFU.move(i, vetLFU.size()-1);// move o valor da posição atual para o fim do vetor
                    vetLFUHit.move(i, vetLFU.size()-1);
                    qDebug()<< vetLFU[i] << "Valor no vetor de posições";
                    qDebug()<< vetLFUHit[i] << "valor no vetor hit";

                    i = ui->editCapacidadeCache->text().toInt();
                } else if(ui->tableCache->item(i,0)->text() == "0"){//verifica a linha é vazia
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));


                    vetLFU.push_back(line.toInt());//insere na cauda
                    vetLFU.pop_front();//remove da cabeça
                    vetLFUHit.push_back(0);
                    vetLFUHit.pop_front();
                    qDebug()<< vetLFU << "miss cache vazia";
                    qDebug()<< vetLFU[i] << "Valor no vetor de posições";
                    qDebug()<< vetLFUHit[i] << "valor no vetor hit";
                    i = ui->editCapacidadeCache->text().toInt();
                    //-----------LFU----------
                    //verifica a validade, se a linha é diferente na cache e se a cache está cheia
                }else if (ui->tableCache->item(i,0)->text() == "1"  && ui->tableCache->item(i,1)->text() != line && i == ui->editCapacidadeCache->text().toInt()-1){
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    /*int menor = vetLFUHit[0];
                    int posicaoMenor = 0;
                    for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
                        if (vetLFUHit[i] < menor){
                            menor = vetLFUHit[i];
                            posicaoMenor = i;
                        }
                    }*/
                    ui->tableCache->setItem(vetLFU[0],1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                    vetLFUHit.push_back(0);
                    vetLFUHit.pop_front();
                    qDebug()<< vetLFU<<"miss cache cheia";
                    qDebug()<< vetLFU[i] << "Valor no vetor de posições";
                    qDebug()<< vetLFUHit[i] << "valor no vetor hit";
                }
            }
        }
        arquivo.close();
    }
}//end btn

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


