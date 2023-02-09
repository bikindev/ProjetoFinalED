/*
    converteArquivo.cpp - aplicação para conversão de um arquivo csv para um arquivo binário

    GCC216 - Estrutura de Dados, 2022

    Desenvolvido por: Grupo 26
    Patrícia Souza Couto
    Vitor Moreira dos Santos
    Vitor Pereira Resende
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include "dado_atleta.h"

using namespace A;
using namespace std;

int main(){
    ifstream arqCSV("data_athlete_event.csv");
    ofstream arqBIN("data_athlete_event.dat");

    if(arqBIN){
        if (arqCSV){
            string linha; // string que recebe uma linha inteira do arquivo csv
            int contador = 0; // contador para controle de leitura

            // cada linha que a string linha lê de arqCSV é tratada como um arquivo
            // pelo tipo istringstream da biblioteca sstream
            // assim, cada linha é lida por outras variáveis que serão atribuidas a um objeto
            // a ser armazenado no arquivo de saída arqBIN
            // essa leitura é feita pela função getline com as delimitações adequadas
            while (getline(arqCSV, linha)){
                istringstream arqLinha(linha);

                // a primeira linha do arquivo csv, com o título das colunas, é ignorada (contador == 0)
                if (contador > 0){
                    unsigned id;
                    string i, name, city, sport, event, noc;
                    string n1, n2;
                    char caractere;

                    getline(arqLinha, i, ',');

                    // se um dado está entre aspas
                    // ele não pode ser separado pelas vírgulas internas a ele
                    // char caractere auxilia nesse controle
                    arqLinha >> caractere;
                    // PARA LER O NOME:
                    if (caractere == '"'){
                        // elimina as aspas ao redor do dado
                        // e mantem apenas um par de aspas onde há dois pares
                        getline(arqLinha, n1, '"');
                        getline(arqLinha, n2, '"');
                        getline(arqLinha, name, '"');
                        // concatenação de string para formar o nome inteiro
                        name = n1 + n2 + name; 
                        // lê o próximo caratere, que é uma vírgula
                        // para que não seja armazenado indevidamente em uma variável
                        arqLinha >> caractere; 
                    }
                    else {
                        getline(arqLinha, name, ',');
                        // concatena as duas variáveis 
                        // para 'name' não ficar sem a primeira letra que foi lida por caractere
                        name = caractere + name;
                    }
                    
                    getline(arqLinha, city, ',');
                    getline(arqLinha, sport, ',');

                    // PARA LER O EVENTO:
                    arqLinha >> caractere;
                    if (caractere == '"'){
                        getline(arqLinha, event, '"');
                        arqLinha >> caractere;
                    }
                    else {
                        getline(arqLinha, event, ',');
                        event = caractere + event; 
                    }


                    getline(arqLinha, noc, ',');

                    // converte string i para int id
                    // chama o construtor e grava o registro no arquivo binário
                    id = stoi(i);
                    dadoAtleta atleta(id, name, city, sport, event, noc);
                    
                    arqBIN.write((char*) &atleta, sizeof(dadoAtleta));
                }
                contador++;
            }
        }
        else {
            cerr<<"O arquivo csv não pode ser aberto."<<endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        cerr<<"O arquivo binário não pode ser aberto."<<endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
