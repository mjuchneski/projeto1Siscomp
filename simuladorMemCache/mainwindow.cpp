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
        bool estado = true;



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


        for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
            qDebug()<< "entrou no laço 1 ";
            int linhaAtual = line.toInt();
            int linhaCache = ui->tableCache->item(i,1)->text().toInt();

            if (i <= ui->editCapacidadeCache->text().toInt()-1){
                if (estado){
                    if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                        qDebug()<< "verificou se esta vazio, cache vazia";
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));
                        ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                        ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));
                        vet[i] = linhaAtual;
                        qDebug()<< vet << "miss cache vazia, insere "<< linhaAtual << "no final";
                        break;//i = ui->editCapacidadeCache->text().toInt();
                    }//end if linha vazia
                    else if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                             qDebug()<< "Verificou se é hit cache vazia";
                             hit ++;
                             ui->editHit->setText(QString::number(hit));
                             qDebug()<< vet << "hit, cache vazia "<< linhaAtual << "";
                             break;//i = ui->editCapacidadeCache->text().toInt();
                    }//end if hit cache vazia

                }//end if estado
                if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                        estado = false;
                }
            }//if chegou no final

            if (i == ui->editCapacidadeCache->text().toInt()-1){
                if (!estado){
                qDebug()<<"Estado da cache = "<< estado;

                for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {
                    bool verificador = false;

                    int valorAtual = line.toInt();
                    int valorCache = 0;
                    for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                        //qDebug()<< m;
                        valorCache = ui->tableCache->item(m,1)->text().toInt();
                        if ( valorAtual == valorCache){
                            verificador = true;
                            qDebug() << "é igual?"<< verificador;
                            break;
                        }//if encontra hit
                    }//for encontra hit

                    if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                        hit ++;
                        ui->editHit->setText(QString::number(hit));
                        qDebug()<< vet<< "hit cache cheia"<< linhaAtual << "";
                        break;
                    }//end if hit cheio
                    else if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                        miss ++;
                        ui->editMiss->setText(QString::number(miss));

                        int indiceReal = 0;
                        while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                            if (ui->tableCache->item(indiceReal,1)->text().toInt() == vet[0]){
                                break;
                            }
                            indiceReal+=1;
                        }

                        ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));

                        vet.pop_front();//remove da cabeça
                        vet.push_back(linhaAtual);//insere na cauda
                        qDebug()<< vet<< "miss cache cheia, insere "<< linhaAtual << "no final";
                        break;
                    }// if miss cheio
                }//for cache cheia
              }//if estado cheio
          }//if for cache cheio





        }//for cache vazia






        /*QString cauda = line;
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

                            int indiceReal = 0;
                            while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                                if (ui->tableCache->item(indiceReal,1)->text().toInt() == vet[0]){

                                    break;
                                }
                                indiceReal+=1;
                            }
                            ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
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
             //} //end for
             //}



        }// end while
        arquivo.close();


            //---------------------ASSOCIATIVO + LRU-------------------

        //
        //colocar as mesmas condiçoes do LFU de saber se esta cheio ou vazio antes de começar a comparar hit e miss
        //

    if (ui->radioAssociativo->isChecked() && ui->radioLRU->isChecked()){
       QVector<int> vetLRU;
       bool estado = true;

       vetLRU.resize(ui->editCapacidadeCache->text().toInt());
       qDebug()<< vetLRU;
       QFile arquivo(abrirArquivo);
       if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
           QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
       }//end if
       QTextStream entrada(&arquivo);

       while (!arquivo.atEnd()) {
       QString line = arquivo.readLine();//faz a leitura de uma linha
        qDebug()<< "leu linha";
       for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {
           qDebug()<< "entrou no laço 1 ";
           int linhaAtual = line.toInt();
           int linhaCache = ui->tableCache->item(i,1)->text().toInt();

           if (i <= ui->editCapacidadeCache->text().toInt()-1){
               if (estado){
                   if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                    qDebug()<< "verificou se esta vazio, cache vazia";
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(QString::number(linhaAtual)));

                    for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                        qDebug()<< "reordenou cache vazia";
                        if(j < ui->editCapacidadeCache->text().toInt()-1){
                            vetLRU[j] = vetLRU[j+1];
                        }
                    }
                    vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;
                    qDebug()<< vetLRU<< "miss cache vazia, insere "<< linhaAtual << "no final";
                    break;//i = ui->editCapacidadeCache->text().toInt();

                   }//end if linha vazia
                   else if (ui->tableCache->item(i,0)->text() == "1" && linhaCache == linhaAtual) {//verifica se é hit
                            qDebug()<< "Verificou se é hit cache vazia";
                            hit ++;
                            ui->editHit->setText(QString::number(hit));

                            for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                                if(j < ui->editCapacidadeCache->text().toInt()-1){
                                vetLRU[j] = vetLRU[j+1];
                                }//if
                            }//for
                            vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;
                            qDebug()<< "reordenou o hit cache vazia";
                            qDebug()<< vetLRU<< "hit, move "<< linhaAtual << "pro final";
                            break;//i = ui->editCapacidadeCache->text().toInt();
                   }//end if hit cache vazia

               }//end if estado
               if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                       estado = false;
               }
           }//if chegou no final

           if (i == ui->editCapacidadeCache->text().toInt()-1){
               if (!estado){
               qDebug()<<"Estado da cache = "<< estado;

               for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {
                   bool verificador = false;

                   int valorAtual = line.toInt();
                   int valorCache = 0;
                   for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                       //qDebug()<< m;
                       valorCache = ui->tableCache->item(m,1)->text().toInt();
                       if ( valorAtual == valorCache){
                           verificador = true;
                           qDebug() << "é igual?"<< verificador;
                           break;
                       }//if encontra hit
                   }//for encontra hit

                   if (valorCache == valorAtual && verificador == true){// verifica hit na cache cheia
                       hit ++;
                       ui->editHit->setText(QString::number(hit));
                       vetLRU.move(j,ui->editCapacidadeCache->text().toInt()-1);
                       /*for(int j = 0; j < ui->editCapacidadeCache->text().toInt(); j++){
                           if(j < ui->editCapacidadeCache->text().toInt()-1){
                           vetLRU[j] = vetLRU[j+1];
                           }//if
                       }//for*/
                       //vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;

                       qDebug()<< vetLRU<< "hit cache cheia, move "<< linhaAtual << "pro final";
                       break;
                   }//end if hit cheio
                   else if (valorCache != valorAtual  && verificador == false) {//miss cache cheia
                       miss ++;
                       ui->editMiss->setText(QString::number(miss));

                       int indiceReal = 0;
                       while (indiceReal < ui->editCapacidadeCache->text().toInt()) {
                           if (ui->tableCache->item(indiceReal,1)->text().toInt() == vetLRU[0]){

                               break;
                           }
                           indiceReal+=1;
                       }

                       ui->tableCache->setItem(indiceReal,1, new QTableWidgetItem(QString::number(linhaAtual)));

                       for(int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                           if(k < ui->editCapacidadeCache->text().toInt()-1){
                               vetLRU[k] = vetLRU[k+1];
                           }
                       }
                       vetLRU[ui->editCapacidadeCache->text().toInt()-1] = linhaAtual;
                       qDebug()<< vetLRU<< "miss cache cheia, insere "<< linhaAtual << "no final";
                       break;
                   }// if miss cheio
               }//for cache cheia
             }//if estado cheio
         }//if for cache cheio
       }//for cache vazia

     }//while
       arquivo.close();

    }//if radio

//-----------------------LFU---------------------
    if (ui->radioAssociativo->isChecked() && ui->radioLFU->isChecked()){


        int contHit[ui->editCapacidadeCache->text().toInt()][ui->editCapacidadeCache->text().toInt()];
        bool estado = true;
        for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
             contHit[k][0] = 0;
             contHit[k][1] = 0;
             qDebug() << contHit[k][0]<< "|" << contHit[k][1];
         }


        qDebug() << "contHit zerado";


        QFile arquivo(abrirArquivo);
        if (!arquivo.open(QFile::ReadOnly|QFile::Text)){// faz a abertura do arquivo no modo de leitura
            QMessageBox::warning(this,"Alerta","O arquivo não foi aberto");
        }//end if
        QTextStream entrada(&arquivo);

        while (!arquivo.atEnd()) {
        QString line = arquivo.readLine();//faz a leitura de uma linha
        qDebug()<<"linha da vez"<<line;

            for (int i = 0;i < ui->editCapacidadeCache->text().toInt();i++) {

                if (i <= ui->editCapacidadeCache->text().toInt()-1){
                    if (estado){
                        qDebug()<<"Estado da cache = "<< estado;
                    if(ui->tableCache->item(i,0)->text() == "0"){//verifica se a linha é vazia
                    miss ++;
                    ui->editMiss->setText(QString::number(miss));
                    ui->tableCache->setItem(i,0, new QTableWidgetItem("1"));
                    ui->tableCache->setItem(i,1, new QTableWidgetItem(line));

                    contHit[i][0] = line.toInt();
                    contHit[i][1] = 0;

                    qDebug() << "substituição por miss em cache vazia / estado da cache";
                    for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                        qDebug() << contHit[k][0] << "|" << contHit[k][1];
                    }
                    break;
                    //i = ui->editCapacidadeCache->text().toInt();

                        // ----------verifica se ja existe na cache----------
                    } else if (ui->tableCache->item(i,0)->text() == "1" && ui->tableCache->item(i,1)->text() == line) {//verifica se é hit

                        hit ++;
                        ui->editHit->setText(QString::number(hit));
                        qDebug()<<"hit";

                        contHit[i][1] ++;
                        qDebug() << "Hit, incremento de contador/ estado da cache";
                         for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                            qDebug() << contHit[k][0] << "|" << contHit[k][1];
                         }
                         break;
                        //i = ui->editCapacidadeCache->text().toInt();

                         }

                }
                if (i >= ui->editCapacidadeCache->text().toInt()-1) {
                        estado = false;
                }

            }//else {

                    if (i == ui->editCapacidadeCache->text().toInt()-1){
                        if (!estado){
                        qDebug()<<"Estado da cache = "<< estado;
                        //qDebug()<<"linha da vez"<< line;
                        for (int j = 0;j <= ui->editCapacidadeCache->text().toInt(); j++) {


                            bool verificador = false;

                            int valorAtual = line.toInt();
                            int valorCache = 0;
                            for(int m = 0; m <= ui->editCapacidadeCache->text().toInt() -1; m++){
                                qDebug()<< m;
                                valorCache = ui->tableCache->item(m,1)->text().toInt();
                                if ( valorAtual == valorCache){
                                    verificador = true;
                                    qDebug() << "é igual?"<< verificador;
                                    break;
                                }
                            }
                            qDebug() << "Encontrou igual? "<< verificador;
                            valorAtual = line.toInt();
                            valorCache = ui->tableCache->item(j,1)->text().toInt();
                            if (valorCache == valorAtual && verificador == true){
                                hit ++;
                                ui->editHit->setText(QString::number(hit));
                                qDebug()<<"hit";
                                contHit[j][1] ++;
                                qDebug() << "Hit cache cheia, incremento de contador/ estado da cache";
                                for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                                   qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                }//for debug
                                break;
                            }//if igual
                            else if (valorCache != valorAtual  && verificador == false) {
                                //encontra a instrução com menor numero de hit
                                int menor = contHit[0][1];
                                int posicaoMenor = 0;

                                for (int l = 0; l <= ui->editCapacidadeCache->text().toInt(); l++) {
                                    if (contHit[l][1] < menor){
                                        menor = contHit[l][1];
                                        posicaoMenor = l;
                                    }
                                }
                                qDebug() << "menor qtd de hit" << menor;
                                qDebug() << "valor a ser substituido"<< contHit[posicaoMenor][0] << "posição do menor" << posicaoMenor;

                                //incrementa miss e substitui na cache
                                miss ++;
                                ui->editMiss->setText(QString::number(miss));
                                ui->tableCache->setItem(posicaoMenor,1, new QTableWidgetItem(line));//cache recebe o endereço novo na posição salva no vetor
                                contHit[posicaoMenor][0] = line.toInt();
                                contHit[posicaoMenor][1] = 0;

                                qDebug() << "substituição por miss em cache cheia/estado da cache";
                                 for (int k = 0; k < ui->editCapacidadeCache->text().toInt(); k++){
                                    qDebug() << contHit[k][0] << "|" << contHit[k][1];
                                 }
                                break;
                            }//if diferente
                        }//for cheio
                    }//estado false
                }//if cheio



            }//for


        }//while
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


