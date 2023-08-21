#include "leitura.hpp"

void readPrincipal() {
    vector<string> filenames = {"dataset/Semana_Machado_Assis.txt", "dataset/DomCasmurro.txt"};
    
    string line;
    string palavraLinha;
    bool decisao = false;
    int count = 0, contExpressoes = 0, paragrafoQuantidade = 1, NumStopWords = 0, Num_StopWords = 0;
    int cont = 0, linhai = 1, supremeCont = 0, distancia = 0, contSentecas = 1, tamanhoPalavra = 0;
    int aux = 0, contPalavras = 0;;

    unordered_map<string, Sword> mapPrintGeral; // armazena todas as palavras do texto com todas as info
    unordered_map<string, bool>stopWords; // armazena as sw
    unordered_map<char, bool>pontos; // armazena os pts
    preencheMapPontos(pontos); 

    Sword word;
    Sword wordParagrados;

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
            while (getline(input_file, line, '\n')) { // pega linha por linha
                cont++;
                for (auto &c : line) {
                    c = tolower(c); // passa tudo pra minusculo
                }

                line = converterAcentuadasParaMinusculas(line);
                line = tiraReticencia(line);
                istringstream ln(line); // token

                if (line.size() > 1) {// onde comeca o paragrafo
                    decisao = false;

                    while (ln >> palavraLinha) { // analisa palavra por palavra ate o final da linha
                        if (!temNumero(palavraLinha)) { // verifica se tem numero na linha e se tiver n salva no map
                            
                            NumStopWords++;            //contador com stop words pega//
                            supremeCont++;             //posi da palavra no paragrafo

                            if (Pontuacao(&palavraLinha, &contExpressoes, Num_StopWords)) {
                                mudou = true; //pra falar q mudou de senteca
                                NumStopWords = 0; //numero de palavras por sentenca com sw
                                Num_StopWords = 0; //sem sw
                            }

                            palavraLinha = removePontuacao(palavraLinha, pontos); // palavrinha recebe a palavra sem pontuacao
                            
                            auto it2 = stopWords.find(palavraLinha); //"posicao" verifica se a palavrinha eh igual a alguma sw, se for igual retorna a posi da sw no map
                            if (it2 == stopWords.end()) { // se a  posicao do it2 for igual a posicao final do map, significa que a a palavinha n eh sw
                                
                                Num_StopWords++;      //contador sem stop words na sentenca
                                //adiciona palavra no map//
                                if (palavraLinha != "" && caractere_estranho(palavraLinha)) {

                                    inserePrintGeral(mapPrintGeral, palavraLinha, word, cont, supremeCont, paragrafoQuantidade, contSentecas, contPalavras);

                                }
                            }
                        }
                    }

                    line.clear();
                } else {// entra quando acabar o paragrafo, quuando a linha eh vazia
                    NumStopWords = 0;
                    Num_StopWords = 0;
                    decisao = true;
                    supremeCont = 0;
                    paragrafoQuantidade++; // cont de paragrafos 
                    linhai = cont + 1; // para que a linha incial do prox paragrafo n seja linha em branco
                }
            }
        }
        if (!(decisao)) { // caso o ultimo paragrafo n seja lido, dependendo da formatacao do arq
            contExpressoes = contExpressoes + 1;
            contExpressoes = 0;
            decisao = true;
            paragrafoQuantidade++;
            linhai = cont + 1;
            supremeCont = 0;
        }
    }
    cout << "Cont Palavras:" << contPalavras << endl << endl;
    calcula_heap(mapPrintGeral);
}



void  inserePrintGeral(unordered_map<string, Sword> &mapPrintGeral, string palavraLinha, Sword &wordParagrados, int cont, int supremeCont, int paragrafoQuantidade, int contSentencas, int &contPalavras) {
    auto it = mapPrintGeral.find(palavraLinha); //MAPA FINAL

    if (it != mapPrintGeral.end()) {//palavra existe*
        it->second.quantidade++; //incrementa valor
    } else {
        mapPrintGeral.insert({ palavraLinha, wordParagrados }); //insere se não existir
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


bool isPonto(char c, unordered_map<char, bool>pontos) { // recebe um char e ve se ele eh um ponto a partir da procura do map de pontos
    auto it = pontos.find(c);
    if (it != pontos.end()) return true;
    return false;
}

string removePontuacao(string num, unordered_map<char, bool>pontos) { // remove pontuacao e char estranho para n aparacer no output
   string palavraSemPonto;
   for (char c : num) {
        if (!isPonto(c, pontos)) {
            palavraSemPonto += c;
        }
    }
    return palavraSemPonto;
}

bool caractereDesejado(char c) {
    static const string caracteresDesejados = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúÁÉÍÓÚâêîôûÂÊÎÔÛàèìòùÀÈÌÒÙçÇãÃõÕ";

    return caracteresDesejados.find(c) != string::npos;
}

string tiraReticencia(string linha) {// retorna a linha sem reticencias
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


bool temNumero(string palavra) {// verifica se tem numero
    for (int i = 0;i < palavra.size();i++) {
        if (isdigit(palavra[i])) return true;
    }

    return false;
}


bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWords) { // verifica se terminou a sentenca de acordo com os delimitadores
    bool encontrar = false;

    char ponto = '.', exclamacao = '!', interrogacao = '?';

    size_t pos1 = (*num).find(ponto);
    if (pos1 != std::string::npos) {  // Verifica se o caractere foi encontrado
        if (!ispunct((*num)[pos1 - 1])) {
            *contExpressoes = *contExpressoes + 1;
            (*num).erase(pos1, 1);
            encontrar = true;
        }
    }
    size_t pos2 = (*num).find(exclamacao);
    if (pos2 != std::string::npos) {  // Verifica se o caractere foi encontrado
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos2, 1);
        encontrar = true;
    }
    size_t pos3 = (*num).find(interrogacao);
    if (pos3 != std::string::npos) {  // Verifica se o caractere foi encontrado
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos3, 1);
        encontrar = true;
    }

    return encontrar;
}

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line) { // verifica se tem exp na linha

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

void calcula_heap(unordered_map<string, Sword> &mapPrintGeral) {
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