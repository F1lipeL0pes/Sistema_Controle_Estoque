#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

/*Projeto de Extensão de Beatriz Krebs, Filipe Eduardo e Jhonata Adriano*/

const int tamanho_arquivo = 300;

int verificou = 0;
int contador = 0;

typedef struct{
    int codProd, quantAtualProd, quantAdequada;
    char nomeProd[50], categoria[50], unidadeMedida[3];
}Produto;
Produto produto[300];

void salvar(){
    FILE *Banco = fopen("Banco.tsv", "w+");
    remove("Banco.tsv");
    fprintf(Banco, "Nome\tCódigo\tCategoria\tUnidade de Medida\tQuantidade Atual\tQuantidade Adequada");
    for(int i = 0; i < contador; i++){
        fprintf(Banco, "\n%s\t%d\t%s\t%s\t%d\t%d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
    }
    fclose(Banco);
}

void inicializacao(){
    FILE *Banco = fopen("Banco.tsv", "r+");
    int linha1 = 0;
    char linha[256];

    if(Banco == NULL){
        Banco = fopen("Banco.tsv", "w+");
        fprintf(Banco, "Nome\tCódigo\tCategoria\tUnidade de Medida\tQuantidade Atual\tQuantidade Adequada");
        fclose(Banco);
    }
    else{
        while (fgets(linha, sizeof(linha), Banco) != NULL) {
            char *token = strtok(linha, "\t");
            if(linha1 != 0){
                if (token != NULL) {
                    strcpy(produto[contador].nomeProd, token);
                }

                token = strtok(NULL, "\t");
                if (token != NULL) {
                    produto[contador].codProd = atoi(token);
                }

                token = strtok(NULL, "\t");
                if (token != NULL) {
                    strcpy(produto[contador].categoria, token);
                }

                token = strtok(NULL, "\t");
                if (token != NULL) {
                    strcpy(produto[contador].unidadeMedida, token);
                }

                token = strtok(NULL, "\t");
                if (token != NULL) {
                    produto[contador].quantAtualProd = atoi(token);
                }

                token = strtok(NULL, "\t");
                if (token != NULL) {
                    produto[contador].quantAdequada = atoi(token);
                }
                contador++;
            }
            linha1++;
        }
    }
    int temQuantidade = 0;
    for (int i = 0; i < contador; i++){
        if (produto[i].quantAtualProd < produto[i].quantAdequada){
            printf("Quantidade de %s abaixo da adequada!\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d\n", produto[i].nomeProd, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
            temQuantidade++;
        }
    }
    verificou++;
    if(temQuantidade != 0){
        printf("\n");
        system("pause");
        system("cls");
    }
}

void cadastro(int indice){
    FILE *Banco = fopen("Banco.tsv", "a+");
    int codigo;
    if(Banco == NULL){
        printf("\nERRO!");
    }
    else
    {
        printf("Digite o nome do produto: ");
        fflush(stdin);
        fgets(produto[indice].nomeProd, sizeof(produto[indice].nomeProd), stdin);
        while (strlen(produto[indice].nomeProd) < 3){
            printf("Digite um nome válido com pelo menos 3 caracteres: ");
            fflush(stdin);
            fgets(produto[indice].nomeProd, sizeof(produto[indice].nomeProd), stdin);
        }
        produto[indice].nomeProd[strcspn(produto[indice].nomeProd, "\n")] = 0;
        for (int i = 0; i < sizeof(produto[indice].nomeProd); i++){
            produto[indice].nomeProd[i] = toupper(produto[indice].nomeProd[i]);
        }

        printf("Digite o código do produto: ");
        scanf("%d", &codigo);
        while(codigo < 1){
            fflush(stdin);
            printf("Digite um código válido maior que 0: ");
            scanf("%d", &codigo);
        }
        for(int i = 0; i < contador; i++){
            while(codigo == produto[i].codProd || codigo < 1){
                fflush(stdin);
                printf("Código inadequado: ");
                scanf("%d", &codigo);
            }
        }
        produto[indice].codProd = codigo;

        printf("Digite a categoria: ");
        fflush(stdin);
        fgets(produto[indice].categoria, sizeof(produto[indice].categoria), stdin);
        while (strlen(produto[indice].categoria) < 3){
            printf("Digite uma categoria válida com pelo menos 3 caracteres: ");
            fflush(stdin);
            fgets(produto[indice].categoria, sizeof(produto[indice].categoria), stdin);
        }
        produto[indice].categoria[strcspn(produto[indice].categoria, "\n")] = 0;
        for (int i = 0; i < strlen(produto[indice].categoria); i++){
            produto[indice].categoria[i] = toupper(produto[indice].categoria[i]);
        }

        printf("Digite a unidade de medida (Kg, g, L, mL, Un [unidade]): ");
        fflush(stdin);
        fgets(produto[indice].unidadeMedida, sizeof(produto[indice].unidadeMedida), stdin);
        produto[indice].unidadeMedida[strcspn(produto[indice].unidadeMedida, "\n")] = 0;
        for (int i = 0; i < strlen(produto[indice].unidadeMedida); i++){
            produto[indice].unidadeMedida[i] = toupper(produto[indice].unidadeMedida[i]);
        }
        fflush(stdin);

        printf("Digite a quantidade atual: ");
        scanf("%d", &produto[indice].quantAtualProd);
        while(produto[indice].quantAtualProd < 0){
            fflush(stdin);
            printf("Digite uma quantidade válida: ");
            scanf("%d", &produto[indice].quantAtualProd);
        }

        printf("Digite a quantidade adequada do produto: ");
        scanf("%d", &produto[indice].quantAdequada);
        while(produto[indice].quantAdequada < 0){
            fflush(stdin);
            printf("Digite uma quantidade válida: ");
            scanf("%d", &produto[indice].quantAdequada);
        }

        fprintf(Banco, "\n%s\t%d\t%s\t%s\t%d\t%d", produto[indice].nomeProd, produto[indice].codProd, produto[indice].categoria, produto[indice].unidadeMedida, produto[indice].quantAtualProd, produto[indice].quantAdequada);
        printf("\nProduto cadastrado!");
        fclose(Banco);
        system("pause");
        system("cls");
        contador++;
    }
}

void alteracao_dados(){
    int codigo, resp, codExiste = 0;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    while (codigo < 1){
        fflush(stdin);
        printf("Código Inválido! Digite novamente: ");
        scanf("%d", &codigo);
    }
    for(int i = 0; i < contador; i++){
        if(codigo == produto[i].codProd){
            codExiste++;
        }
    }
    if (codExiste != 0){
        for(int i = 0; i < contador; i++){
            if(codigo == produto[i].codProd){
                while(1){
                    char nome[30], categoria[30], unidadeMedida[3];
                    float valor_custo;
                    int codigo, quant_atual, quant_adequada;
                    printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
                    printf("\n1- Nome\n2- Código\n3- Categoria\n4- Unidade de Medida\n5- Quantidade Adequada\n6- Sair");
                    printf("\nDigite o que deseja fazer: ");
                    scanf("%d", &resp);
                    while(resp < 1 || resp > 6){
                        fflush(stdin);
                        printf("Digite uma variável adequada: ");
                        scanf("%d", &resp);
                    }
                    fflush(stdin);
                    if (resp == 1){
                        printf("Digite o novo nome: ");
                        fgets(nome, sizeof(nome), stdin);
                        while(strlen(nome) < 3){
                            printf("Digite um nome adequado com pelo menos 3 caracteres: ");
                            fflush(stdin);
                            fgets(nome, sizeof(nome), stdin);
                        }
                        nome[strcspn(nome, "\n")] = 0;
                        for (int j = 0; j < strlen(nome); j++){
                            nome[j] = toupper(nome[j]);
                        }
                        fflush(stdin);
                        strcpy(produto[i].nomeProd, nome);
                    }
                    else if (resp == 2){
                        printf("Digite o novo código: ");
                        scanf("%d", &codigo);
                        while (codigo <= 0){
                            fflush(stdin);
                            printf("Digite um código válido: ");
                            scanf("%d", &codigo);
                        }
                        for(int i = 0; i < contador; i++){
                            while(codigo == produto[i].codProd){
                                fflush(stdin);
                                printf("Código já utilizado! Digite outro: ");
                                scanf("%d", &codigo);
                            }
                        }
                        produto[i].codProd = codigo;
                    }
                    else if (resp == 3){
                        printf("Digite a nova categoria: ");
                        fgets(categoria, sizeof(categoria), stdin);
                        while(strlen(categoria) < 3){
                            printf("Digite uma categoria válida com pelo menos 3 caracteres: ");
                            fflush(stdin);
                            fgets(categoria, sizeof(categoria), stdin);
                        }
                        categoria[strcspn(categoria, "\n")] = 0;
                        for (int j = 0; j < strlen(categoria); j++){
                            categoria[j] = toupper(categoria[j]);
                        }
                        fflush(stdin);
                        strcpy(produto[i].categoria, categoria);
                    }
                    else if (resp == 4){
                        printf("Digite a nova unidade de medida: ");
                        fgets(unidadeMedida, sizeof(unidadeMedida), stdin);
                        unidadeMedida[strcspn(categoria, "\n")] = 0;
                        for (int j = 0; j < strlen(unidadeMedida); j++){
                            unidadeMedida[j] = toupper(unidadeMedida[j]);
                        }
                        fflush(stdin);
                        strcpy(produto[i].unidadeMedida, unidadeMedida);
                    }
                    else if (resp == 5){
                        printf("Digite a quantidade adequada: ");
                        scanf("%d", &quant_adequada);
                        while(quant_adequada < 0){
                            fflush(stdin);
                            printf("Digite uma quantidade válida: ");
                            scanf("%d", &quant_adequada);
                        }
                        produto[i].quantAdequada = quant_adequada;
                    }
                    else
                        break;
                }
            }
        }
        salvar();
    }
    else{
        printf("Código não encontrado!");
    }
    printf("\n");
    system("pause");
    system("cls");
}

void excluir_dados(){
    int codigo, codExiste = 0, resp, indice;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    while (codigo < 1){
        fflush(stdin);
        printf("Código Inválido! Digite novamente: ");
        scanf("%d", &codigo);
    }
    for(int i = 0; i < contador; i++){
        if(codigo == produto[i].codProd){
            codExiste++;
            indice = i;
        }
    }
    if(codExiste != 0){
        for(int i = 0; i < contador; i++){
            if (codigo == produto[i].codProd){
                printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
                printf("\nDeseja mesmo apagar esse produto?\n1- Sim\n2- Não\nResposta: ");
                scanf("%d", &resp);
                while(resp < 1 || resp > 2){
                    fflush(stdin);
                    printf("Digite uma resposta válida: ");
                    scanf("%d", &resp);
                }
                if (resp == 1){
                    for(int i = indice; i < contador-1; i++){
                        strcpy(produto[i+1].nomeProd, produto[i].nomeProd);
                        strcpy(produto[i+1].categoria, produto[i].categoria);
                        strcpy(produto[i+1].unidadeMedida, produto[i].unidadeMedida);
                        produto[i].codProd = produto[i+1].codProd;
                        produto[i].quantAdequada = produto[i+1].quantAdequada;
                        produto[i].quantAtualProd = produto[i+1].quantAtualProd;
                    }
                    contador--;
                    salvar();
                    printf("Produto excluído!");
                }
                else{
                    printf("Produto não excluído!");
                    break;
                }
            }
        }
    }
    else{
        printf("Código não encontrado!");
    }
    printf("\n");
    system("pause");
    system("cls");
}

void controle(){
    int codigo, codExiste = 0, indice, quantEstoque, limiteEstoque, aumento, compQuantAdequada;
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    while (codigo < 1){
        fflush(stdin);
        printf("Código Inválido! Digite novamente: ");
        scanf("%d", &codigo);
    }
    for(int i = 0; i < contador; i++){
        if(codigo == produto[i].codProd){
            codExiste++;
            indice = i;
        }
    }
    if(codExiste != 0){
        for(int i = 0; i < contador; i++){
            if (codigo == produto[i].codProd){
                printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
                printf("\nDigite a nova quantidade em estoque: ");
                scanf("%d", &quantEstoque);
                while(quantEstoque < 0){
                    fflush(stdin);
                    printf("Digite uma quantidade válida: ");
                    scanf("%d", &quantEstoque);
                }
                aumento = quantEstoque - produto[i].quantAtualProd;
                if (aumento < 0){
                    aumento*= -1;
                    printf("O produto %s teve um decremento de %d %s", produto[i].nomeProd, aumento, produto[i].unidadeMedida);
                }
                else{
                    printf("O produto %s teve um aumento de %d %s", produto[i].nomeProd, aumento, produto[i].unidadeMedida);
                }
                produto[i].quantAtualProd = quantEstoque;
                compQuantAdequada = produto[i].quantAdequada - produto[i].quantAtualProd;
                if (produto[i].quantAtualProd == produto[i].quantAdequada)
                    printf("\nO produto %s atingiu a quantidade adequada", produto[i].nomeProd);
                else if (produto[i].quantAtualProd > produto[i].quantAdequada){
                    compQuantAdequada*= -1;
                    printf("\nO produto %s passou da quantidade adequada em estoque em %d %s", produto[i].nomeProd, compQuantAdequada, produto[i].unidadeMedida);
                }
                else
                    printf("\nRestam %d %s de %s para atingir a quantidade adequada de %d unidades", compQuantAdequada, produto[i].unidadeMedida, produto[i].nomeProd, produto[i].quantAdequada);
                salvar();
            }
        }
    }
    else{
        printf("Código não encontrado!");
    }
    printf("\n");
    system("pause");
    system("cls");
}

void relatorio(){
    char categoria[50], linha2[256], nome[30];
    int resp;

    printf("1- Relatório Geral"
           "\n2- Relatório por Categoria"
           "\n3- Relatório por Nome");

    printf("\nDigite a ação: ");
    scanf("%d", &resp);
    while(resp < 1 || resp > 3){
        printf("Digite uma resposta válida: ");
        scanf("%d", &resp);
    }
    system("cls");
    if(resp == 1){
        printf("Relatórios de Produtos:\n");
        for(int i = 0; i < contador; i++){
            printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria, produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
        }
    }
    else if(resp == 2){
        printf("Digite a categoria: ");
        fflush(stdin);
        scanf("%s", categoria);
        for (int i = 0; i < strlen(categoria); i++){
            categoria[i] = toupper(categoria[i]);
        }

        for(int i = 0; i < contador; i++){
            if(strstr(produto[i].categoria, categoria) != NULL){
                printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria,produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
            }
        }
    }
    else{
        printf("Digite o nome: ");
        fflush(stdin);
        scanf("%s", nome);
        for (int i = 0; i < strlen(nome); i++){
            nome[i] = toupper(nome[i]);
        }

        for(int i = 0; i < contador; i++){
            if(strstr(produto[i].nomeProd, nome) != NULL){
                printf("\nNome: %s\tCódigo: %d\tCategoria: %s\tUnidade de Medida: %s\tQuantidade Atual: %d\tQuantidade Adequada: %d", produto[i].nomeProd, produto[i].codProd, produto[i].categoria,produto[i].unidadeMedida, produto[i].quantAtualProd, produto[i].quantAdequada);
            }
        }

    }
    printf("\n");
    system("pause");
    system("cls");
}

int main()
{
    system("chcp 1252 > nul");
    setlocale(LC_ALL, "Portuguese");
    char linha[tamanho_arquivo];
    int contStruct = -1;
    if (verificou == 0)
        inicializacao();
    int resp;
    do{
        printf("Bem-Vindo!\n");
        printf("\n1 - Cadastro de Produtos"
               "\n2 - Alteração de Dados de Produtos"
               "\n3 - Excluir Dados"
               "\n4 - Controle de Entrada e Saída"
               "\n5 - Relatórios de Produtos"
               "\n6 - Sair"
               "\n\nDigite a ação a ser realizada: ");
               scanf("%d", &resp);
               while (resp < 1 || resp > 6){
                    fflush(stdin);
                    printf("Ação não reconhecida! Digite novamente: ");
                    scanf("%d",&resp);
               }
               system("cls");
               switch(resp){
                    case 1:
                        cadastro(contador);
                        break;

                    case 2:
                        alteracao_dados();
                        break;

                    case 3:
                        excluir_dados();
                        break;

                    case 4:
                        controle();
                        break;

                    case 5:
                        relatorio();
                        break;
               }
    }while(resp != 6);
    printf("Tchau!");
    return 0;
}
