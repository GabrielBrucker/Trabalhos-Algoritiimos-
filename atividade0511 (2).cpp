// Atividade da aula 05/11 - Algoritmos B
// Leitura, listagem e pesquisa de telefones

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct {
    string numeroCelular;
    string dadosSessao;
} Telefone;

// Metodo split fornecido na atividade, adaptado para usar strings com seguranca.
string *split(string frase, string delimitador = " ") {
    static string vetor[3];
    int inicio = 0;
    int fim = frase.find(delimitador);
    int i = 0;

    while (fim != -1 && i < 2) {
        vetor[i] = frase.substr(inicio, fim - inicio);
        inicio = fim + delimitador.size();
        fim = frase.find(delimitador, inicio);
        i++;
    }
    vetor[i] = frase.substr(inicio);

    return vetor;
}

// Carrega a base de telefonia para um vetor de Telefone.
vector<Telefone> carregarBase() {
    vector<Telefone> listaSessoes;
    ifstream arquivo("telephony_sessions.txt");
    string linha;

    if (!arquivo.is_open()) {
        cout << "Nao foi possivel abrir telephony_sessions.txt\n";
        return listaSessoes;
    }

    while (getline(arquivo, linha)) {
        int posicao = linha.find(";");
        if (posicao != -1) {
            string *dados = split(linha, ";");

            Telefone telefone;
            telefone.numeroCelular = dados[0];
            telefone.dadosSessao = dados[1];
            listaSessoes.push_back(telefone);
        }
    }

    arquivo.close();
    return listaSessoes;
}

// Lista os celulares e mostra a quantidade.
void listarTelefones(vector<Telefone> listaSessoes) {
    cout << "\nLISTA DE TELEFONES\n";
    int quantidade = listaSessoes.size();
    for (int i = 0; i < quantidade; i++) {
        cout << listaSessoes[i].numeroCelular << "\n";
    }
    cout << "Quantidade: " << listaSessoes.size() << "\n";
}

// Pesquisa o telefone e apresenta os dados da sessao.
void pesquisarTelefone(vector<Telefone> listaSessoes) {
    string numero;
    bool encontrou = false;

    cout << "Digite o numero do celular: ";
    cin >> numero;

    int quantidade = listaSessoes.size();
    for (int i = 0; i < quantidade; i++) {
        if (listaSessoes[i].numeroCelular == numero) {
            cout << "\nTelefone: " << listaSessoes[i].numeroCelular << "\n";
            cout << "Dados da sessao: " << listaSessoes[i].dadosSessao << "\n";
            encontrou = true;
        }
    }

    if (encontrou == false) {
        cout << "Telefone nao encontrado.\n";
    }
}

int main() {
    vector<Telefone> listaSessoes;
    char opcao;

    listaSessoes = carregarBase();
    if (listaSessoes.size() == 0) {
        cout << "A base esta vazia ou o arquivo nao foi encontrado.\n";
        return 1;
    }

    do {
        cout << "\nMENU\n";
        cout << "1 - Listar telefones\n";
        cout << "2 - Pesquisar telefone e dados de sessao\n";
        cout << "3 - Finalizar\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case '1':
                listarTelefones(listaSessoes);
                break;
            case '2':
                pesquisarTelefone(listaSessoes);
                break;
            case '3':
                cout << "Obrigado por usar o sistema\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != '3');

    return 0;
}
