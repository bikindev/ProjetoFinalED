/*
    dado_atleta.h -> arquivo de cabeçalho para definição da classe dadoAtleta
    
    GCC216 - Estrutura de Dados, 2022

    Desenvolvido por: Grupo 26
    Patrícia Souza Couto
    Vitor Moreira dos Santos
    Vitor Pereira Resende
*/
#pragma once
#include <cstring>
#include <iostream>

namespace A{

    class dadoAtleta{
    public:
        dadoAtleta();
        dadoAtleta(unsigned& i, std::string& n, std::string& c, std::string& s, std::string& e, std::string& noc);
        void exibe();
        void trocaValores(dadoAtleta& a2, dadoAtleta& aux);
        void transforma(dadoAtleta& a);
    private:
        unsigned id;
        char name[50];
        char city[15];
        char sport[50];
        char event[50];
        char mNoc[4]; // 3 caracteres (o 4o é para o caractere nulo \0)
    };

    dadoAtleta::dadoAtleta(){
    id = 0;
    strcpy(name, "--");
    strcpy(city, "--");
    strcpy(sport, "--");
    strcpy(event, "--");
    strcpy(mNoc, "--");
    }

    dadoAtleta::dadoAtleta(unsigned& i, std::string& n, std::string& c, std::string& s, std::string& e, std::string& noc){
        // inicializa um novo elemento com os dados inseridos pelo usuário
        // e pelo id caluclado pelo programa, visto que é sequencial, começando em 0
        id = i;
        strcpy(name, n.c_str());
        strcpy(city, c.c_str());
        strcpy(sport, s.c_str());
        strcpy(event, e.c_str());
        strcpy(mNoc, noc.c_str());
    }

    void dadoAtleta::exibe(){
        // imprime os atributos de um registro
        printf("Id: %d\nNome: %s\nCidade: %s\nEsporte: %s\nEvento: %s\nComitê Olímpico: %s\n", id, name, city, sport, event, mNoc);
    }

    void dadoAtleta::trocaValores(dadoAtleta& a2, dadoAtleta& aux){
        // troca os atributos entre dois registros, exceto o atributo id, que é sequencial e indica a posição
        // copia os dados de atleta1 para auxiliar
        // em seguida, copia de atleta2 para atleta1
        // e de auxiliar para atleta2
        strcpy(aux.name, name);
        strcpy(aux.city, city);
        strcpy(aux.sport, sport);
        strcpy(aux.event, event);
        strcpy(aux.mNoc, mNoc);

        strcpy(name, a2.name);
        strcpy(city, a2.city);
        strcpy(sport, a2.sport);
        strcpy(event, a2.event);
        strcpy(mNoc, a2.mNoc);

        strcpy(a2.name, aux.name);
        strcpy(a2.city, aux.city);
        strcpy(a2.sport,aux.sport);
        strcpy(a2.event,aux.event);
        strcpy(a2.mNoc, aux.mNoc);
    }

    void dadoAtleta::transforma(dadoAtleta& a){
        // copia os atributos de um registro para o proximo
        // o próximo registro, que recebe a cópia, tem id = id anterior + 1
        // para manter a sequência ordenada de id no arquivo
        id = a.id + 1;
        strcpy(name, a.name);
        strcpy(city, a.city);
        strcpy(sport, a.sport);
        strcpy(event, a.event);
        strcpy(mNoc, a.mNoc);
    }
    
} // namespace A
