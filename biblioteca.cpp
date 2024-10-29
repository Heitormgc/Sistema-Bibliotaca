#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimo
{
    char data_emp[10], data_dev[10], usuarios[255];
};

struct livros
{
    int codigo, paginas;
    char area[255], titulo[255], autores[30], editora[255];
    struct emprestimo emp;
};

int opc_princ, cod, pos;
char opc;
struct livros liv;

FILE *arquivo, *arquivoAux;

int main()
{
    do
    {
        cout << "Sitema de Biblioteca" << endl;
        cout << "1- Cadastro:" << endl;
        cout << "2- Emprestimo:" << endl;
        cout << "3- Devolução:" << endl;
        cout << "4- Consulta de Livros:" << endl;
        cout << "5- Livros Disponíveis:" << endl;
        cout << "6- Alteração:" << endl;
        cout << "7- Exclusão:" << endl;
        cout << "8- Listagem geral de livros" << endl;
        cout << "9- Sair:" << endl;

        switch (opc_princ)
        {
        case 1:
            cout << "Deseja cadastrar um livro(S ou N)?";
            cin >> opc;
            while (opc == 'S' || opc == 's')
            {
                cout << "Digite o codigo de catalogalçao do livro";
                cin >> liv.codigo;
                cout << "Agora digite a área de atuação deste livro";
                cin.get(liv.area, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite o título do livro";
                cin.get(liv.titulo, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite a editora do livro";
                cin.get(liv.editora, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Digite os autor(es) do livro";
                cin.get(liv.autores, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Número de páginas";
                cin >> liv.paginas;

                arquivo = fopen("dados.dat", "ab");
                if (arquivo == NULL)
                {
                    arquivo = fopen("dados.dat", "wb");
                }
                if (fwrite(&liv, sizeof(struct livros), 1, arquivo) == 1)
                {
                    cout << "Livro cadstrado com sucesso!";
                }
                else
                {
                    cout << "Não foi possível cadastrar livro";
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();

                cout << "Deseja cadastrar um livro (S ou N?";
                cin >> opc;
            }

            break;
        case 2:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL)
            {
                cout << "Digite o codigo do livro";
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                pos = -1;
                while (!feof(arquivo))
                {
                    fread(&liv, sizeof(struct livros), 1, arquivo);
                    pos++;
                    if (cod == liv.codigo)
                    {
                        fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                        cout << "Data de emprestimo ";
                        cin.get(liv.emp.data_emp, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Data de devolução: ";
                        cin.get(liv.emp.data_dev, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Usuário: ";
                        cin.get(liv.emp.usuarios, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        fwrite(&liv, sizeof(struct livros), 1, arquivo);
                        break;
                    }
                }
                fclose(arquivo);
            }
            else
            {
                cout << "Erro ao abrir o banco de dados";
                cin.ignore();
                cin.get();
            }
            break;
        case 3:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL)
            {
                cout << "Digite o codigo do livro";
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                pos = -1;
                while (!feof(arquivo))
                {
                    fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                    strcpy(liv.emp.data_emp, "");
                    strcpy(liv.emp.data_dev, "");
                    strcpy(liv.emp.usuarios, "");
                    fwrite(&liv, sizeof(struct livros), 1, arquivo);
                    break;
                }
                fclose(arquivo);
            }
            else
            {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 4:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL)
            {
                cout << "Digite o codigo do livro";
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while (!feof(arquivo))
                {
                    fread(&liv, sizeof(struct livros), 1, arquivo);
                    if (cod == liv.codigo)
                    {
                        cout << "Código: " << liv.codigo << endl;
                        cout << "Área: " << liv.area << endl;
                        cout << "Título: " << liv.titulo << endl;
                        cout << "Autor(es): " << liv.autores << endl;
                        cout << "Editora: " << liv.editora << endl;
                        cout << "Nº páginas: " << liv.paginas << endl;
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);
            }
            else
            {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 5:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL)
            {
                fread(&liv, sizeof(struct livros), 1, arquivo);
                while (!feof(arquivo))
                {
                    if (strcmp(liv.emp.data_emp, "") == 0)
                    {
                        cout << "Código: " << liv.codigo << endl;
                        cout << "Área: " << liv.area << endl;
                        cout << "Título: " << liv.titulo << endl;
                        cout << "Autor(es): " << liv.autores << endl;
                        cout << "Editora: " << liv.editora << endl;
                        cout << "Nº páginas: " << liv.paginas << endl;
                        cin.get();
                        break;
                    }
                    fread(&liv, sizeof(struct livros), 1, arquivo);
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();
            }
            else
            {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 6:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL)
            {

                cout << "Digite o código do livro que deseja alterar";
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                pos = -1;
                while (!feof(arquivo))
                {
                    fread(&liv, sizeof(struct livros), 1, arquivo);
                    pos++;
                    if (cod == liv.codigo)
                    {
                        cout << "Área:";
                        cin.get(liv.area, 30);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Título: ";
                        cin.get(liv.titulo, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Autores: ";
                        cin.get(liv.autores, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Editora:";
                        cin.get(liv.editora, 50);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Número de páginas:";
                        cin >> liv.paginas;

                        fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                        if (fwrite(&liv, sizeof(struct livros), 1, arquivo) == 1)
                        {
                            cout << "Livro alterado com sucesso!";
                        }
                        else
                        {
                            cout << "Erro ao alterar livro";
                        }

                        cin.ignore();
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);
            }
            else
            {
                cout << "Erro ao abrir banco de dados";
                cin.ignore();
                cin.get();
            }
            break;
        case 7:
            cout << "Digite o código do livro";
            cin >> cod;
            arquivo = fopen("dados.dat", "rb");
            arquivoAux = fopen("dados.aux", "wb");

            fread(&liv, sizeof(struct livros), 1, arquivo);
            while (!feof(arquivo))
            {
                if (cod != liv.codigo)
                {
                    fwrite(&liv, sizeof(struct livros), 1, arquivoAux);
                }
                fread(&liv, sizeof(struct livros), 1, arquivo);
            }

            fclose(arquivo);
            fclose(arquivoAux);
            remove("dados.dat");
            rename("dados.aux", "dados.dat");
            break;
        case 8:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL)
            {
                fread(&liv, sizeof(struct livros), 1, arquivo);
                while (!feof(arquivo))
                {
                    cout << "Código: " << liv.codigo << endl;
                    cout << "Área: " << liv.area << endl;
                    cout << "Título: " << liv.titulo << endl;
                    cout << "Autor(es): " << liv.autores << endl;
                    cout << "Editora: " << liv.editora << endl;
                    cout << "Nº páginas: " << liv.paginas << endl;
                    cin.get();
                    break;
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();
            }
            else
            {
                cout << "Erro ao abrir o banco de dados!";
                cin.ignore();
                cin.get();
            }
            break;
        case 9:
            cout << "Obrigado por usar nosso sistema";
        default:
            break;
        }
        cout << "\e[2J" << "\e[o;oH";
    } while (opc_princ != 9);

}