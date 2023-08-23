#include "leitura.hpp"

void readPrincipal() {
    vector<string> filenames = {"dataset/Semana_Machado_Assis.txt", "dataset/DomCasmurro.txt"};
    
    string line;
    string palavraLinha;
    bool decisao = false;
    int count = 0, contExpressoes = 0, NumStopWords = 0, Num_StopWords = 0;
    int cont = 0, linhai = 1, supremeCont = 0, tamanhoPalavra = 0;
    int aux = 0, contPalavras = 0;

    palavra_q word;
    palavra_q wordParagrados;

    unordered_map<string, palavra_q> mapPrintGeral; 
    unordered_map<string, bool>stopWords; 
    unordered_map<char, bool>pontos; 
    preencheMapPontos(pontos); 

    
    bool mudou = false;

    readStopWords(stopWords);

    for (int i=0; i<filenames.size(); i++) {
        string filename = filenames[i];
        ifstream input_file(filename, ios::in);

        if (!input_file.is_open()) {
            cout << "Nao foi possivel abrir o arquivo" << filename << " " << endl;
            return;
        }

        

        while (getline(input_file, line)) {
            while (getline(input_file, line, '\n')) { 
                cont++;
                for (auto &c : line) {
                    c = tolower(c); 
                }

                line = converterAcentuadasParaMinusculas(line);
                line = tiraReticencia(line);
                istringstream ln(line);

                if (line.size() > 1) {
                    decisao = false;

                    while (ln >> palavraLinha) { 
                        if (!temNumero(palavraLinha)) { 
                            
                            NumStopWords++;            
                            supremeCont++;             
                            if (Pontuacao(&palavraLinha, &contExpressoes, Num_StopWords)) {
                                mudou = true; 
                                NumStopWords = 0; 
                                Num_StopWords = 0; 
                            }

                            palavraLinha = removePontuacao(palavraLinha, pontos); 
                            
                            auto it2 = stopWords.find(palavraLinha); 
                            if (it2 == stopWords.end()) { 
                                
                                Num_StopWords++; 
                                if (palavraLinha != "" && caractere_estranho(palavraLinha)) {

                                    inserePrintGeral(mapPrintGeral, palavraLinha, word, cont, supremeCont, contPalavras);

                                }
                            }
                        }
                    }

                    line.clear();
                } else {
                    NumStopWords = 0;
                    Num_StopWords = 0;
                    decisao = true;
                    supremeCont = 0;  
                    linhai = cont + 1; 
                }
            }
        }
        if (!(decisao)) { 
            contExpressoes = contExpressoes + 1;
            contExpressoes = 0;
            decisao = true;
            linhai = cont + 1;
            supremeCont = 0;
        }
    }
    cout << "Cont Palavras:" << contPalavras << endl << endl;
    calcula_heap(mapPrintGeral);
}



void  inserePrintGeral(unordered_map<string, palavra_q> &mapPrintGeral, string palavraLinha, palavra_q &wordParagrados, int cont, int supremeCont, int &contPalavras) {
    auto it = mapPrintGeral.find(palavraLinha); 

    if (it != mapPrintGeral.end()) {
        it->second.quantidade++; 
    } else {
        mapPrintGeral.insert({ palavraLinha, wordParagrados }); 
        contPalavras++;
    }
}

void readStopWords(unordered_map<string, bool> &stopWords) {
    string filename("dataset/stopwords.csv");
    ifstream input_file(filename, ios::in | ios::binary);
    string line;

    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            if (line.size() >= 1) {
                for (auto &c : line) {
                    c = tolower(c);
                }

                stopWords.insert({ line,true });
            }
        }
    }
}

void preencheMapPontos(unordered_map<char, bool> &pontos) {
    pontos.insert({
        {'-', false},
        {'.', false},
        {',', false},
        {';', false},
        {'"', false},
        {'/', false},
        {'(', false},
        {')', false},
        {'[', false},
        {']', false},
        {'+', false},
        {'-', false},
        {'=', false},
        {'*', false},
        {':', false},
        {'|', false},
        {'§', false},
        {'ª', false},
        {'°', false},
        {'º', false},
        {'“', false},
        {'”', false},
        {'?', false},
        {':', false},
        });
}

bool caractere_estranho(string s) {
    auto acentos = {"^" ,"--", " — ", " —", "—", "”", "-", "——", "“", "-”"};
    auto acentos_2 = {'"','-', '\xE2', '\x9D','\x80', '\x9C', '\x94'};

    for (auto a : acentos) {
        if (s.find(a) != s.npos) {
            return false;
        }
    }
    for (auto a : acentos_2) {
        if (s.find(a) != s.npos) {
            return false;
        }
    }

    return true;
}


bool isPonto(char c, unordered_map<char, bool>pontos) { 
    auto it = pontos.find(c);
    if (it != pontos.end()) return true;
    return false;
}

string removePontuacao(string num, unordered_map<char, bool>pontos) { 
   string palavraSemPonto;
   for (char c : num) {
        if (!isPonto(c, pontos)) {
            palavraSemPonto += c;
        }
    }
    return palavraSemPonto;
}

string tiraReticencia(string linha) {
    string retiBug = ". . .";
    size_t pos = linha.find(retiBug);
    if (pos != std::string::npos)
        linha.erase(pos, retiBug.length());

    string reti = "...";
    size_t pos2 = linha.find(reti);
    if (pos2 != std::string::npos)
        linha.erase(pos2, reti.length());

    string reti2 = "..";
    size_t pos3 = linha.find(reti2);
    if (pos3 != std::string::npos)
        linha.erase(pos3, reti2.length());

    return linha;
}


bool temNumero(string palavra) {
    for (int i = 0;i < palavra.size();i++) {
        if (isdigit(palavra[i])) return true;
    }

    return false;
}


bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWords) { 
    bool encontrar = false;

    char ponto = '.', exclamacao = '!', interrogacao = '?';

    size_t pos1 = (*num).find(ponto);
    if (pos1 != std::string::npos) {  
        if (!ispunct((*num)[pos1 - 1])) {
            *contExpressoes = *contExpressoes + 1;
            (*num).erase(pos1, 1);
            encontrar = true;
        }
    }
    size_t pos2 = (*num).find(exclamacao);
    if (pos2 != std::string::npos) {  
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos2, 1);
        encontrar = true;
    }
    size_t pos3 = (*num).find(interrogacao);
    if (pos3 != std::string::npos) {  
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos3, 1);
        encontrar = true;
    }

    return encontrar;
}

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line) {

    for (auto itE = map.begin();itE != map.end();++itE) {
        auto itS = line.find(itE->first);
        if (itS != string::npos) {
            itE->second.push_back(cont);
        }
    }
}

string converterAcentuadasParaMinusculas(string num) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙÕÂÊÎÔÛ";
    string minuscula = "áàãéèíìóòúùõâêîôû";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(num.begin(), num.end(), maiuscula[i], minuscula[i]);
    }
    return num;
}

void calcula_heap(unordered_map<string, palavra_q> &mapPrintGeral) {
    vector<pair<string, int>> min_heap;
    bool verdade = false;
    int cont = 0;

    for (auto& x : mapPrintGeral) {
        if (min_heap.size() < K) {
            min_heap.push_back({x.first, x.second.quantidade});
            faz_a_heap(min_heap);
            cont ++;
        }
        else {
            if (x.second.quantidade > min_heap[0].second) {
                min_heap[0].second = x.second.quantidade;
                min_heap[0].first = x.first;
                faz_a_heap(min_heap);
            }
        }
    }
    imprimir(min_heap);
}


void faz_a_heap(vector<pair<string, int>> &min_heap) {
   int size = min_heap.size();

    for (int i = (size / 2) - 1; i >= 0; --i) {
        int menor = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && min_heap[left].second < min_heap[menor].second) {
            menor = left;
        }

        if (right < size && min_heap[right].second < min_heap[menor].second) {
            menor = right;
        }

        if (menor != i) {
            swap(min_heap[i].second, min_heap[menor].second);
            swap(min_heap[i].first, min_heap[menor].first);
        }
    }
}

void imprimir(vector<pair<string, int>> &min_heap) {
    int size = min_heap.size();

    for (int i = 0; i < size; ++i) {
        cout << "Palavra " << i << ": " << min_heap[i].first << " - " << min_heap[i].second << endl;
    }
}