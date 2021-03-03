#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

void reseta_variaveis(){
    palavra_secreta = "";
    chutou.clear();
    chutes_errados.clear();
}

void saudacao(){
    cout << "*********************" << endl;
    cout << "*********************" << endl;
    cout << "*****           *****" << endl;
    cout << "*****   FORCA   *****" << endl;
    cout << "*****           *****" << endl;
    cout << "*********************" << endl;
    cout << "*********************" << endl;
}

bool letra_existe(char letra, string palavra){
    //for(int i = 0; i < palavra.size(); i++){
    //    if(letra == palavra[i]){
    //        return true;
    //    }
    //}
    for(char letra_da_palavra : palavra){
        if(letra == letra_da_palavra){
            return true;
        }
    }
    return false;
}

bool nao_acertou(string palavra, std::map<char, bool> letras){
    for(char letra : palavra){
        if(!letras[letra]){
            return true;
        }
    }
    return false;
}

bool nao_enforcou(std::vector<char> erros){
    return erros.size() < 5;
}

void exibir_palavra_secreta(string palavra, std::map<char, bool> chutou){
    cout << endl << "Palavra secreta: ";
    for(char letra : palavra){
        if(chutou[letra]){
            cout << letra << " ";
        } else {
            cout << "_ ";
        }
    }
}

void exibir_chutes_errados(vector<char> chutes_errados){
    cout << endl << "Chutes errados: ";
    for(char letra : chutes_errados){
        cout << letra << " ";
    }
}

void resolve_chute(){
    cout << endl << "Chute uma letra: ";
    char chute;
    cin >> chute;
    chutou[chute] = true;
    if(letra_existe(chute, palavra_secreta)){
        cout << "Essa letra existe na palavra!" << endl;
    } else {
        cout << "Essa letra nao existe na palavra!" << endl;
        chutes_errados.push_back(chute);
    }
}

void finaliza_jogo(){
    if(!nao_acertou(palavra_secreta, chutou)){
        cout << endl << "Parabens! Voce ganhou!" << endl;
    }

    if(!nao_enforcou(chutes_errados)){
        cout << endl << "Tente novamente!" << endl;
    }

    cout << "A palavra era '" << palavra_secreta << "' !" << endl;
}

vector<string> le_arquivo(){
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open()){
        int quant_palavras;
        arquivo >> quant_palavras;
        vector<string> lista_de_palavras;
        
        for(int i = 0; i < quant_palavras; i++){
            string minha_palavra;
            arquivo >> minha_palavra;
            lista_de_palavras.push_back(minha_palavra);
        }
        arquivo.close();
        return lista_de_palavras;
    } else {
        cout << "Banco de palavras nao encontrado." << endl;
        exit(0);
    }
};

void sorteia_palavra(){
    vector<string> lista = le_arquivo();
    srand(time(NULL)); // defines the seed of random numbers being seconds since 1970
    int indice_sorteado = rand() % lista.size();
    palavra_secreta = lista[indice_sorteado];
}

void exibe_lista(){
    ifstream arquivo;
    arquivo.open("palavras.txt");
    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(0);
    }

    cout << "Essa e a lista de palavras: " << endl;

    int linhas;
    arquivo >> linhas;
    for(int i = 0; i < linhas; i++){
        string linha;
        arquivo >> linha;
        cout << linha << ", ";
    }
    cout << endl;
    arquivo.close();
}

vector<string> cria_nova_lista(){
    ifstream arquivo;
    vector<string> lista_de_palavras;
    int numero_de_palavras;

    arquivo.open("palavras.txt");
    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(0);
    }

    arquivo >> numero_de_palavras;
    for(int i = 0; i < numero_de_palavras; i++){
        string palavra;
        arquivo >> palavra;
        lista_de_palavras.push_back(palavra);
    }

    string nova_palavra;
    cout << "Digite uma nova palavra: ";
    cin >> nova_palavra;
    lista_de_palavras.push_back(nova_palavra);
    arquivo.close();
    return lista_de_palavras;
}

void salva_arquivo(){
    ofstream arquivo;
    vector<string> lista_de_palavras = cria_nova_lista();
    arquivo.open("palavras.txt");
    
    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(0);
    }
    
    arquivo << lista_de_palavras.size() << endl;
    for(string palavra : lista_de_palavras){
        arquivo << palavra << endl;
    }
    cout << "Palavra adicionada." << endl;
    arquivo.close(); 
}

void jogar(){
    saudacao();
    sorteia_palavra();
    while(nao_acertou(palavra_secreta, chutou) && nao_enforcou(chutes_errados)){
        exibir_palavra_secreta(palavra_secreta, chutou);
        exibir_chutes_errados(chutes_errados);
        resolve_chute();
    }
    finaliza_jogo();
}

int main(){

    int resposta;
    while(resposta != 4){
        cout << endl << "Voce gostaria de exibir a lista de palavras (1), adicionar uma nova palavra (2), jogar (3) ou sair (4)? ";
        cin >> resposta;

        switch(resposta){
            case 1:
                exibe_lista();
                break;
            case 2:
                salva_arquivo();
                break;
            case 3:
                reseta_variaveis();
                jogar();
                break;
            case 4:
                break;
            default:
                cout << "Voce nao digitou 1, 2, 3 ou 4. Tente novamente." << endl;
                exit(0);
        }
    }
}