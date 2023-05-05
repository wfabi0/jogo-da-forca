#include <iostream>
#include <sstream>
#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

/*

 * Para adicionar mais palavras mude o (MAX_WORDS)
 * E adicione as palavras no vetor (words)

*/

#define MAX_WORDS 10
#define MAX_ERRORS 10

using namespace std;

// Mostre sua situação na forca
void printForca(int errors)
{
    cout << "+------+" << endl;
    cout << "|      |" << endl;
    cout << "|      " << (errors >= 1 ? "O" : "") << endl;
    cout << "|     " << (errors >= 3 ? "/" : "") << (errors >= 2 ? "|" : "") << (errors >= 4 ? "\\" : "") << endl;
    cout << "|      " << (errors >= 5 ? "|" : "") << endl;
    cout << "|     " << (errors >= 6 ? "/ " : "") << (errors == 10 ? "\\" : "") << endl;
    cout << "|" << endl;
    cout << "+------+" << endl;
}

int main()
{
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    srand(time(nullptr));

    // Adicione mais palavras aqui. (Lembre-se de mudar o máximo de palavras em MAX_WORDS)
    const string words[MAX_WORDS] = {
        "peixe",
        "conhecimento",
        "livro",
        "advogado",
        "apartamento",
        "bicicleta",
        "lagosta",
        "semente",
        "congelar",
        "faculdade",
    };

    // Gerar palavra aleatória
    const string randomWord = words[rand() % MAX_WORDS];

    // Defina as variaveis e vetores do jogador
    const int lenWord = randomWord.size();
    int correctsWords = 0;
    vector<char> correctWords(lenWord);
    int errors = 0;
    vector<char> wrongWords(MAX_ERRORS);
    vector<char> saveWords;

    // Variavel auxiliar
    bool repeated = false;

    while (errors < MAX_ERRORS)
    {
        system("cls");

        // cout << randomWord << endl; // Mostre a palavra escolhida
        printForca(errors);

        if (repeated)
        {
            cout << "- Esta letra já foi utilizada." << endl
                 << endl;
            repeated = false;
        }
        cout << "Palavra: " << endl;
        for (int i = 0; i < lenWord; i++)
        {
            if (correctWords[i] != 0)
            {
                cout << correctWords[i] << " ";
            }
            else
            {
                cout << "_ ";
            }
        }
        cout << endl
             << endl;
        cout << "Erros: " << errors << "/" << MAX_ERRORS << "." << endl;
        for (int i = 0; i < wrongWords.size(); i++)
        {
            if (wrongWords[i] != 0)
            {
                cout << wrongWords[i] << " ";
            }
        }

        cout << endl
             << endl;

        char character;
        cin >> character;
        cin.ignore();
        character = tolower(character);

        bool resp = false;
        if (find(wrongWords.begin(), wrongWords.end(), character) != wrongWords.end())
        {
            repeated = true;
        }
        else
        {
            repeated = false;
            for (int i = 0; i < lenWord; i++)
            {
                if (correctWords[i] == character)
                {
                    repeated = true;
                    break;
                }
            }
            if (!repeated)
            {
                for (int i = 0; i < lenWord; i++)
                {
                    if (randomWord[i] == character)
                    {
                        correctWords[i] = character;
                        resp = true;
                        correctsWords++;
                    }
                }
                if (!resp)
                {
                    errors++;
                    wrongWords.push_back(character);
                }
            }
        }
        if (correctsWords == lenWord)
            break;
    }

    system("cls");
    printForca(errors);

    if (errors == MAX_ERRORS)
    {
        cout << endl
             << endl
             << "Você morreu! A palavra correta era: \"" << randomWord << "\"." << endl;
    }
    else
    {
        cout << endl
             << endl
             << "Você ganhou!!! Palavra descoberta: \"" << randomWord << "\"." << endl;
        cout << "Total de erros: " << errors << "/" << MAX_ERRORS << ".";
    }

    cout << endl
         << endl;

    system("pause");
    return 0;
}
