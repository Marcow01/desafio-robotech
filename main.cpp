#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
using namespace std;

vector<vector<int>> lerarquivo(string caminho){

    ifstream arquivo(caminho);
    string linha;
    vector<vector<int>> matriz;

    if(!arquivo.is_open()){
        cout << "arquivo nao encontrado" << endl;
        return matriz;
    }

    while (getline(arquivo, linha)) {
        vector<int> linhaMatriz;
        for (char ch : linha) {
            linhaMatriz.push_back(ch - '0');
        }
        matriz.push_back(linhaMatriz);
    }

    arquivo.close();
    return matriz;
}

tuple<int, int> posicaoinicial(vector<vector<int>> matriz){
    for(int x = 0; x < matriz.size(); x++){
        for(int y = 0; y < matriz[x].size(); y++){
            if(matriz[x][y] == 2){
                //cout << "x: " << x << endl;
                //cout << "y: " << y << endl;
                return make_tuple(x, y);
            }
        }
    }
}

void exibirtabuleiro(vector<vector<int>> matriz, ofstream& resultado){\
    for (vector<int> linha : matriz) {
        for (int elemento : linha) {
            resultado << elemento << " ";
            //cout << elemento << " ";
        }

        resultado << endl;
    }

    resultado << endl;
}

int iteracoes = 1;

bool dfs(int x, int y, int linhas, int colunas, vector<vector<int>>& matriz, vector<vector<bool>>& posicoesvisitadas, ofstream& resultado) {
    if (x < 0 || x >= linhas || y < 0 || y >= colunas || matriz[x][y] == 1 || posicoesvisitadas[x][y]) {
        return false;
    }

    resultado << "i = " << iteracoes << ";" << " pos = [" << x + 1 << ", " << y + 1 << "];" << endl;

    iteracoes++;
    if (matriz[x][y] == 3) return true;
    posicoesvisitadas[x][y] = true;

    if (dfs(x, y + 1, linhas, colunas, matriz, posicoesvisitadas, resultado)) return true;
    if (dfs(x, y - 1, linhas, colunas, matriz, posicoesvisitadas, resultado)) return true;
    if (dfs(x + 1, y, linhas, colunas, matriz, posicoesvisitadas, resultado)) return true;
    if (dfs(x - 1, y, linhas, colunas, matriz, posicoesvisitadas, resultado)) return true;


    return false;
}

int main(){
    int x, y;

    cout << "exemplo de caminho: " << R"(C:\Users\User\Downloads\arquivo.txt)" << endl;
    cout << endl;
    cout << "digite o caminho do arquivo: ";
    string caminho;
    cin >> caminho;

    for(int i = 0; i < caminho.length(); i++){
        if(caminho[i] == '\\'){
            caminho[i] = '/';
        }
    }

    //string caminho = "C:/Users/marco/Downloads/maze_05.txt"; //caso prefira apenas colocar o caminho do arquivo no cÃ³digo

    vector<vector<int>> matriz = lerarquivo(caminho);
    tie(x, y) = posicaoinicial(matriz);

    int linhas = matriz.size();
    int colunas = matriz[0].size();

    ofstream resultado;
    resultado.open("resultados.txt");
    exibirtabuleiro(matriz, resultado);

    vector<vector<bool>> posicoesvisitadas(linhas, vector<bool>(colunas, false));
    bool sucesso = dfs(x, y, linhas, colunas, matriz, posicoesvisitadas, resultado);

    resultado.close();

    if(!sucesso){
        cout << endl;
        cout << "nao achou a saida :(" << endl;
    }
    else{
        cout << endl;
        cout << "saida encontrada!" << endl;
        cout << "confira o arquivo resultados.txt" << endl;
    }

    return 0;
}
