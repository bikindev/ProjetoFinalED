/*
    manipulaArquivo.cpp - aplicação para manipulação de arquivo binário

    GCC216 - Estrutura de Dados, 2022

    Desenvolvido por: Grupo 26
    Patrícia Souza Couto
    Vitor Moreira dos Santos
    Vitor Pereira Resende
*/

#include <iostream>
#include <fstream>
#include "dado_atleta.h"

using namespace A;
using namespace std;

int main(){
    // ------- MENU -------- //
    cout<<"Selecione a função que deseja executar:\n\n";
    cout<<"1 - Adicionar um novo elemento ao final do arquivo\n";
    cout<<"2 - Adicionar um novo elemento na posição desejada\n";
    cout<<"3 - Alterar os dados de um registro\n";
    cout<<"4 - Trocar a posição de dois registros\n";
    cout<<"5 - Visualizar os registros entre duas posições\n";
    cout<<"6 - Visualizar todos os registros\n";
    cout<<"7 - Sair da aplicação\n\n";

    fstream BASEDADOS("data_athlete_event.dat");
    char escolha, continua;
    cin >> escolha;

    if (BASEDADOS and escolha != '7'){
        unsigned id;
        string name, city, sport, event, noc;
        unsigned numRegistros, posRelativa, posAbsoluta1, posAbsoluta2, contador;
        bool sentinela;
        dadoAtleta* novoAtleta = NULL;
        dadoAtleta atleta1, atleta2, auxiliar;

        do {
            switch (escolha) { 
            case '1': // adiciona um novo elemento ao final do arquivo
                cout<<"Insira os dados do novo registro: \n";
                cin.ignore();
                cout<<"Nome: "; getline(cin, name, '\n');
                cout<<"Cidade: "; getline(cin, city, '\n');
                cout<<"Esporte: "; getline(cin, sport, '\n');
                cout<<"Evento: "; getline(cin, event, '\n'); 
                cout<<"Comitê Olímpico: "; getline(cin, noc, '\n'); 
                cout<<endl;

                // cria novo registro
                // numRegistros é a quantidade de atletas registrados
                // id é sequencial e começa em zero, então numRegistros atual = id+1
                // um novo registro será adicionado na posição id+1
                // então novo registro receberá id = numRegistros atual 
                BASEDADOS.seekp(0, BASEDADOS.end);
                numRegistros = BASEDADOS.tellp() / sizeof(dadoAtleta);
                novoAtleta = new dadoAtleta(numRegistros, name, city, sport, event, noc);

                // grava novo registro no arquivo
                // e desaloca a memória ocupada pelo objeto novoAtleta
                BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));
                delete novoAtleta;

                break;

            case '2': // adiciona um novo elemento na posição relativa desejada
                // estabele a posição onde será adicionado um novo registro (posAbsoluta1)
                // estabele posição do último registro, de onde vai começar a alteração (posAbsoluta2)
                // cria um registro "vazio" no final do arquivo
                cout<<"Insira a posição onde deseja inserir o novo registro: "; cin>>posRelativa;
                posAbsoluta1 = (posRelativa-1) * sizeof(dadoAtleta);

                BASEDADOS.seekp(0, BASEDADOS.end);
                posAbsoluta2 = BASEDADOS.tellp();
                posAbsoluta2 -= sizeof(dadoAtleta);

                novoAtleta = new dadoAtleta;
                BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));
                delete novoAtleta;

                // copia os atributos de posAboluta2 para (posAbsoluta2 + 1 registro)
                // incrementando id para manter a sequência ordenada de id
                // enquanto a posição onde será inserido o novo registro for menor ou igual do que posição onde ocorre a cópia
                // continua copiando os dados de um registro para o próximo e incrementando id
                
                sentinela = true;
                while ((sentinela) and (posAbsoluta1 <= posAbsoluta2)){
                    BASEDADOS.seekg(posAbsoluta2); // posiciona cabeça de leitura
                    BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));

                    posAbsoluta2 += sizeof(dadoAtleta); 
                    BASEDADOS.seekp(posAbsoluta2); // posiciona cabeça de escrita
                    atleta2.transforma(atleta1); // copia os dados de atleta1 para a proxima posição (atleta2)
                    BASEDADOS.write((char*) &atleta2, sizeof(dadoAtleta));
                
                    // altera o valor de posAbsoluta2 para posicionar a cabeça de leitura novamente
                    // função sizeof() não pode conter valores negativos, então
                    // se posAbsoluta2 for do tamanho de apenas um registro (id = 0)
                    // finaliza a decrementação do tamanho de 2 registros
                    // e seta sentinela = false para sair do laço de repetição
                    if (posAbsoluta2 != sizeof(dadoAtleta))    
                        posAbsoluta2 -= (2*sizeof(dadoAtleta));
                    else
                        sentinela = false;
                }

                // recebe os novos dados e atribui a um registro na posição desejada
                // sem alterar o id (posRelativa - 1)
                cout<<"Insira os dados do novo registro: \n";
                id = posRelativa - 1;
                cout<<"NOVO ID: "<<id<<endl;
                cin.ignore();
                cout<<"Nome: "; getline(cin, name, '\n');
                cout<<"Cidade: "; getline(cin, city, '\n'); 
                cout<<"Esporte: "; getline(cin, sport, '\n'); 
                cout<<"Evento: "; getline(cin, event, '\n');
                cout<<"Comitê Olímpico: "; getline(cin, noc, '\n'); 
                cout<<endl;

                novoAtleta = new dadoAtleta(id, name, city, sport, event, noc);  
                
                // se o status da sentinela foi alterado a posição da cabeça de escrita será zero
                // se não, é preciso mover a posição um registro a frente, pois ela se encontra na posição onde supostamente faria a próxima leitura
                if (sentinela == false)
                    posAbsoluta2 = 0;
                else 
                    posAbsoluta2 += (1*sizeof(dadoAtleta));
                
                BASEDADOS.seekp(posAbsoluta2);
                BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));

                break;

            case '3': // altera os dados do registro de uma posição
                // posiciona o arquivo na posição desejada (id)
                // faz a leitura e impressão dos dados atuais do registro 
                // (para o usuário conferir os dados que serão alterados)
                // e altera esses dados com os novos dados inseridos
                cout<<"Insira a chave ID do registro que deseja alterar: ";
                
                BASEDADOS.seekg(0,BASEDADOS.end);
                numRegistros = BASEDADOS.tellg() / sizeof(dadoAtleta);
                id = numRegistros; // inicializado com esse valor apenas para entrar dentro do laço de repetição
                
                // usuário deve inserir um id válido (ou seja, id < número de registros)
                // laço se repete até que ele insira um valor válido
                while (id >= numRegistros){   
                    cin>>id; 

                    // condição satisfeita apenas se o id for válido
                    if (id < numRegistros){
                        cout<<endl;
                        novoAtleta = new dadoAtleta;
                        posAbsoluta1 = sizeof(dadoAtleta) * id;
                        BASEDADOS.seekg(posAbsoluta1);
                        BASEDADOS.read((char*) novoAtleta, sizeof(dadoAtleta));
                        novoAtleta->exibe(); // imprime os dados do registro
                        delete novoAtleta;

                        cout<<"\nTem certeza de que deseja alterar os dados desse registro? [S/n] "; cin>>continua;

                        if (continua == 'S'){
                            cout<<"Insira os novos dados do registro:\n";
                            cin.ignore();
                            cout<<"Nome: "; getline(cin, name, '\n');
                            cout<<"Cidade: "; getline(cin, city, '\n');
                            cout<<"Esporte: "; getline(cin, sport, '\n');
                            cout<<"Evento: "; getline(cin, event, '\n');
                            cout<<"Comitê Olímpico: "; getline(cin, noc, '\n'); 
                            cout<<endl;

                            novoAtleta = new dadoAtleta(id, name, city, sport, event, noc);
                            BASEDADOS.seekp(posAbsoluta1);
                            BASEDADOS.write((char*) novoAtleta, sizeof(dadoAtleta));

                            delete novoAtleta;
                        }
                    }
                    else {
                        cout<<"Insira uma chave válida: ";
                    }
                }
                
                break;

            case '4': // troca dois registros de posição
                // posRelativa recebe as posições desejadas
                // imprime os dados do registro de cada posição (para verificação do usuário)
                // troca os valores entre os dois registros, com exceção de id
                // e grava as alterações no arquivo
                cout<<"Insira as duas posições que deseja trocar:\n"; 
                cout<<"Primeira posição: "; cin>>posRelativa;

                posAbsoluta1 = (posRelativa-1)*sizeof(dadoAtleta);
                BASEDADOS.seekg(posAbsoluta1);
                BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
                atleta1.exibe();
                cout<<endl;

                cout<<"Segunda posição: "; cin>>posRelativa;
                posAbsoluta2 = (posRelativa-1)*sizeof(dadoAtleta);
                BASEDADOS.seekg(posAbsoluta2);
                BASEDADOS.read((char*) &atleta2, sizeof(dadoAtleta));
                atleta2.exibe();
                cout<<endl;

                // troca os valores entre os registros atleta1 e atelta2
                atleta1.trocaValores(atleta2, auxiliar);

                BASEDADOS.seekp(posAbsoluta1);
                BASEDADOS.write((char*) &atleta1, sizeof(dadoAtleta));
                BASEDADOS.seekp(posAbsoluta2);
                BASEDADOS.write((char*) &atleta2, sizeof(dadoAtleta));

                cout<<"Troca realizada!\n\n";

                break;

            case '5': // visualiza os registros entre duas posições
                // calcula o número de registros entre as duas posições
                // inicia a impressão dos dados a partir da primeira posição
                // até que o número de registros calculado seja impresso
                cout<<"Insira as duas posições desejadas: \n"; 

                // número de registros total
                // utilizado para verificar se as posições inseridas são válidas
                // ambas as posições não podem ser maior do que o número de registros do arquivo
                BASEDADOS.seekg(0, BASEDADOS.end);
                numRegistros = BASEDADOS.tellg() / sizeof(dadoAtleta);

                cout<<"Primeira posição: "; cin>>posRelativa;
                if (posRelativa > numRegistros) {
                    numRegistros = 0;
                    cerr<<"Registro inexistente!"<<endl;
                }
                else {
                    posAbsoluta1 = (posRelativa-1)*sizeof(dadoAtleta);

                    // no caso de ser maior que o numRegistros, a segunda posição recebe a posição do último registro como seu valor
                    cout<<"Segunda posição: "; cin>>posRelativa;
                    if (posRelativa > numRegistros) {
                        posRelativa = numRegistros;
                    }
                    cout<<endl;
                    posAbsoluta2 = (posRelativa-1)*sizeof(dadoAtleta);

                    // se as duas posições são iguais, deve ser impresso exatamente um registro indicado por elas
                    if (posAbsoluta1 == posAbsoluta2) {
                        numRegistros = 1;
                    }
                    else {
                        numRegistros = (posAbsoluta2 - posAbsoluta1) / sizeof(dadoAtleta);
                    }
                    BASEDADOS.seekg(posAbsoluta1);
                }
                
                contador = 0;
                while ((numRegistros > 0) and (contador <= numRegistros)) {
                    BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
                    atleta1.exibe();
                    cout<<endl;
                    contador++;
                    // se as duas posições são iguais, incrementa o contador de novo
                    // para sair do laço de repetição com apenas uma impressão
                    if (numRegistros == 1) contador++;
                }

                break;

            case '6': // imprime todos os registros
                // calcula o total de registros no arquivo
                // inicia a impressão dos dados a partir da primeira posição do arquivo
                // até que o número de registros totais seja impresso
                BASEDADOS.seekg(0, BASEDADOS.end);
                numRegistros = BASEDADOS.tellg() / sizeof(dadoAtleta);
                BASEDADOS.seekg(0, BASEDADOS.beg);

                contador = 0;
                while (contador < numRegistros){
                    BASEDADOS.read((char*) &atleta1, sizeof(dadoAtleta));
                    atleta1.exibe();
                    cout<<endl;
                    contador++;
                }

                break;

            case '7': // encerra a aplicação 
                break;
            
            default:
                cout << "Opção inválida!" << endl;
                break;
            }
        cout<<"Selecione a função que deseja executar: "; cin>>escolha;

        } while (escolha != '7');
    }
    else {
        cerr<<"Não foi possível abrir o arquivo"<<endl;
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
