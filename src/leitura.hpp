#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <locale>

#define endl '\n'
#define K 20

using namespace std;

typedef struct palavra {
    int quantidade = 1;
}palavra_q;

void readPrincipal();

void preencheMapPontos(unordered_map<char, bool> &pontos);
void readStopWords(unordered_map<string, bool> &stopWords);

void inserePrintGeral(unordered_map<string, palavra_q> &mapPrintGeral, string palavraLinha, palavra_q &wordParagrados, int cont, int supremeConte, int &contPalavras);

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line);
string tiraReticencia(string linha);
string removePontuacao(string num, unordered_map<char, bool>pontos);
string converterAcentuadasParaMinusculas(string num);
bool temNumero(string palavra);
bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWord);
bool isPonto(char c, unordered_map<char, bool>pontos);

void calcula_heap(unordered_map<string, palavra_q> &mapPrintGeral);
void faz_a_heap(vector<pair<string, int>> &min_heap);
void imprimir(vector<pair<string, int>> &min_heap);

bool caractere_estranho(string s);

#endif