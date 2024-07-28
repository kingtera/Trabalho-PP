#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM_MAX_NOME     50
#define TAM_MAX_OBJ      30
#define TAM_MAX_PROF     50
#define TAM_MAX_STATUS   15
#define TAM_MAX_PRODUTOS 3
#define TAM_LIN_STRUCT   15
#define VALOR_CRITERIO1  1
#define VALOR_CRITERIO2  5
#define VALOR_CRITERIO3  15
#define VALOR_CRITERIO4  15
#define DESCONHECIDOS    1
#define VISITANTES       5
#define LEADS            10
#define CLIENTES         15
#define PROMOTORES       36

void atribuiStatus(char sigla, char aux[TAM_MAX_STATUS]){
    switch(sigla){
        case 'D':
        strcpy(aux,"DESCONHECIDO");
        break;

        case 'V':
        strcpy(aux,"VISITANTE");
        break;

        case 'L':
        strcpy(aux,"LEAD");
        break;

        case 'C':
        strcpy(aux,"CLIENTE");
        break;

        case 'P':
        strcpy(aux,"PROMOTOR");
        break;
    }
}

char classificaSiglaConsumidor(int pontos){
    if(pontos >= DESCONHECIDOS && pontos < VISITANTES){
        return 'D';
    }
    if(pontos >= VISITANTES && pontos < LEADS){
        return 'V';
    }
    if(pontos >= LEADS && pontos < CLIENTES){
        return 'L';
    }
    if(pontos >= CLIENTES && pontos < PROMOTORES){
        return 'C';
    }
    if(pontos == PROMOTORES) {
        return 'P';
    } else {
        return 'D';
    }
}

int calculaPontuacao(int c1, int c2, int c3, int c4) {
    return c1 + c2 + c3 + c4;
}

typedef struct Data {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct InfoCompras {
    int     produtosConsumidos[TAM_MAX_PRODUTOS];
    float   frequenciaMes;
    float   valorMedioGasto;
}InfoCompras;

typedef struct CRM {
    int         pontuacao;
    int         assinaNewsletter;  //c1  1
    int         acompanhaBlog;     //c2  5
    InfoCompras criteriosCompra;   //c3 e c4 | 15 e 15
}CRM;

typedef struct Perfil {
    char        nome[TAM_MAX_NOME];
    Data        aniversario;
    int         idade;
    char        profissao[TAM_MAX_PROF];
    char        objetivos[TAM_MAX_OBJ];
    InfoCompras ticket;
    CRM         customerReport;
    char        status[TAM_MAX_STATUS];
}Perfil;

int imprimeMenu(){
    int op;

    printf("\n_______________________________________________");
    printf("\n Bem-vindo ao qualificador de consumidores \n");
    printf("_______________________________________________");

    printf("\n 1-Cadastrar ");
    printf("\n 2-Consultar ");
    printf("\n 3-Imprimir cadastros pela inicial");
    printf("\n 4-Imprimir todos os cadastros");
    printf("\n 5-Sair");
    printf("\n Digite a op��o que voc� deseja realizar: ");
    scanf("%d", &op);

    system("cls");

    return op;
}

void cadastra(){
    FILE   *arquivo;
    Perfil customer;
    int    criterio1 = 0;  //ASSINA NEWSLETTER -> VALOR: 1
    int    criterio2 = 0;  //ACOMPANHA O BLOG  -> VALOR: 5
    int    criterio3 = 0;  //FREQ DE COMPRA    -> VALOR: 15
    int    criterio4 = 0;  //VALOR MEDIO GASTO -> VALOR: 15

    setlocale(LC_ALL, "Portuguese");

    fflush(stdin);

    arquivo = fopen("arq.txt", "a");

    //VERIFICA SE O ARQUIVO FOI CRIADO CORRETAMENTE
    if(arquivo == NULL){
        printf("\nArquivo n�o pode ser aberto.");
        exit(1);
    }

    printf("\nDigite a seguir o perfil:");

    printf("\nNome: ");
    gets(customer.nome);

    printf("\nAnivers�rio: ");
    printf("\n  Dia: ");
    scanf(" %d", &customer.aniversario.dia);

    printf("\n  M�s[n�mero]: ");
    scanf(" %d", &customer.aniversario.mes);

    printf("\n  Ano: ");
    scanf(" %d", &customer.aniversario.ano);

    printf("\nIdade: ");
    scanf(" %d", &customer.idade);

    printf("\nProfiss�o: ");
    fflush(stdin);
    gets(customer.profissao);

    printf("\nObjetivos: ");
    gets(customer.objetivos);

    int contador = 0;
    int numeroItem;

    printf("====================\n");
    printf("   NOSSO CAT�LOGO   \n");
    printf("     1. Camisetas   \n");
    printf("     2. T�nis       \n");
    printf("     3. Eventos     \n");
    printf("====================\n");

    printf("\nQual item %s compra?", customer.nome);
    printf("\n[Digite 0 (zero) para sair]");

    do {
        printf("\nDigite o n�mero do item de acordo com nosso cat�logo: ");
        fflush(stdin);
        scanf("%d", &numeroItem);

        //VERIFICA SE O ITEM DIGITADO EXISTE
        if(numeroItem > 3){
            while(numeroItem > 3){
                printf("\nItem n�o encontrado. Digite novamente: ");
                fflush(stdin);
                scanf("%d", &numeroItem);
            }
        }

        //SAI DO LOOP
        if(numeroItem == 0){
            break;
        } else {
            customer.ticket.produtosConsumidos[contador] = numeroItem;
        }

        //ARRUMA A LISTA DE PROD. CONSUMIDOS (POSICOES NAO PREENCHIDAS COM PRODUTOS SAO SUBSTITUIDAS POR ZERO)
        for(int i = 0; i < 3; i++){
            if(customer.ticket.produtosConsumidos[i] > 3){
                customer.ticket.produtosConsumidos[i] = 0;
            }
        }

        contador++;
    }while(contador < 3);

    printf("\n%s consome os seguintes itens: ", customer.nome);

    for(int i = 0; i < 3; i++){
        printf("%d ", customer.ticket.produtosConsumidos[i]);
    }

    printf("\n");
    printf("\nQual a frequ�ncia que %s compra por m�s? ", customer.nome);
    fflush(stdin);
    scanf("%f", &customer.ticket.frequenciaMes);

    printf("\nQual o valor m�dio gasto por %s? ", customer.nome);
    fflush(stdin);
    scanf("%f", &customer.ticket.valorMedioGasto);

    printf("\n");
    printf("Digite 1 para Sim e 2 para N�o");
    printf("\n%s � assinante da NewsLetter? ", customer.nome);
    scanf("%d", &customer.customerReport.assinaNewsletter);

    printf("\n%s acompanha o Blog? ", customer.nome);
    fflush(stdin);
    scanf("%d", &customer.customerReport.acompanhaBlog);


    if(customer.customerReport.assinaNewsletter == 1){
        criterio1 = VALOR_CRITERIO1;
    }
    if(customer.customerReport.acompanhaBlog == 1){
        criterio2 = VALOR_CRITERIO2;
    }
    if(customer.ticket.frequenciaMes >= 5.0){
        criterio3 = VALOR_CRITERIO3;
    }
    if(customer.ticket.valorMedioGasto >= 500.00){
        criterio4 = VALOR_CRITERIO4;
    }

    customer.customerReport.pontuacao = calculaPontuacao(criterio1, criterio2, criterio3, criterio4);

    //DEFINE O STATUS DO CONSUMIDOR
    char sigla = classificaSiglaConsumidor(customer.customerReport.pontuacao);

    atribuiStatus(sigla, customer.status);

    //GRAVANDO NO ARQUIVO
    fprintf(arquivo,"\n=============================\n");
    fprintf(arquivo," %s\n", customer.nome);
    fprintf(arquivo,"   Anivers�rio: %d/%d/%d\n", customer.aniversario.dia, customer.aniversario.mes, customer.aniversario.ano);
    fprintf(arquivo,"   Idade: %d\n", customer.idade);
    fprintf(arquivo,"   Profiss�o: %s\n", customer.profissao);
    fprintf(arquivo,"   Objetivos: %s\n", customer.objetivos);
    fprintf(arquivo,"   Itens consumidos: [ %d, %d, %d ]\n", customer.ticket.produtosConsumidos[0], customer.ticket.produtosConsumidos[1], customer.ticket.produtosConsumidos[2]);
    fprintf(arquivo,"   Frequ�ncia de Compra(/m�s): %.2f\n", customer.ticket.frequenciaMes);
    fprintf(arquivo,"   Valor M�dio: R$%.2f\n", customer.ticket.valorMedioGasto);
    fprintf(arquivo,"________________________________\n");
    fprintf(arquivo,"   %s possui os seguintes scores:\n", customer.nome);
    fprintf(arquivo,"   Assina NewsLetter [1-SIM | 2-N�O]: %d\n", customer.customerReport.assinaNewsletter);
    fprintf(arquivo,"   Acompanha Blog [1-SIM | 2-N�O]: %d\n", customer.customerReport.acompanhaBlog);
    fprintf(arquivo,"   Frequencia de compra (/m�s): %.2f\n", customer.ticket.frequenciaMes);
    fprintf(arquivo,"   Ticket M�dio: R$%.2f\n", customer.ticket.valorMedioGasto);
    fprintf(arquivo,"   PONTUA��O FINAL > %d\n", customer.customerReport.pontuacao);
    fprintf(arquivo,"   CLASSIFICA��O > %s\n", customer.status);
    fprintf(arquivo,"=============================\n");

    fclose(arquivo);

    printf("\nConsumidor cadastrado!");
    printf("\nVoc� ser� redirecionado para o menu..\n");
    system("PAUSE");
    system("cls");

    menu();
}

void perguntaSeDesejaRepetirConsulta(){
    int repetir = 0;
    printf("\nDeseja realizar de novo?");
    printf("\n[1-SIM | 2-N�O]\n");
    fflush(stdin);
    scanf("%d", &repetir);

    if(repetir == 1){
        system("cls");
        consulta();
    } else {
        printf("\nOk, voc� ser� redirecionado para o menu..\n");
        printf("\n");
        system("PAUSE");
        system("cls");
        menu();
    }
}

void consulta(){
    FILE    *arquivo;
    char    nome[TAM_MAX_NOME];
    char    linhaStruct[70];

    printf("\n[CONSULTAS S�O FEITAS APENAS PELO NOME]");
    printf("\nQual consumidor voc� quer buscar? ");
    fflush(stdin);
    gets(nome);

    arquivo = fopen("arq.txt", "r");

    if(arquivo == NULL){
        printf("Ocorreu um ERRO!");
    }


    char auxIdentificaFimArquivo;
    int  auxContadorDeLinha = 1;
    char auxLinha[70];
    char *auxPonteiro;

    while(auxIdentificaFimArquivo != EOF){
        auxIdentificaFimArquivo = fgetc(arquivo);
        fgets(linhaStruct, sizeof(linhaStruct), arquivo);
        auxPonteiro = strstr(linhaStruct, nome);

        if(auxPonteiro != NULL){
            printf("\nNome encontrado!");

            printf("\n%s", nome);

            for(auxContadorDeLinha; auxContadorDeLinha <= TAM_LIN_STRUCT; auxContadorDeLinha++){
                fgets(auxLinha,sizeof(auxLinha),arquivo);
                printf("%s", auxLinha);
            }

            printf("\n");
            break;
        }
        else if(auxIdentificaFimArquivo == EOF){
            system("cls");
            fclose(arquivo);
            printf("\nO nome '%s' n�o foi encontrado.", nome);
            perguntaSeDesejaRepetirConsulta();
            return;
        }
    }
    fclose(arquivo);

    perguntaSeDesejaRepetirConsulta();
}

void perguntaSeDesejaRepetirImpressao(){
    int repetir = 0;
    printf("\nDeseja realizar de novo?");
    printf("\n[1-SIM | 2-N�O]\n");
    fflush(stdin);
    scanf("%d", &repetir);

    if(repetir == 1){
        system("cls");
        imprimePelaInicial();
    } else {
        printf("\nOk, voc� ser� redirecionado para o menu..\n");
        printf("\n");
        system("PAUSE");
        system("cls");
        menu();
    }
}

void imprimePelaInicial(){
    FILE    *arquivo;
    char    inicialPrimeiroNome[] = " ";
    char    inicial[] = " ";
    char    linhaStruct[70];
    char    auxLinha[70];
    char    auxIdentificaFimArquivo;
    char    *auxPonteiroInicial;
    int     auxContadorDeLinha = 0;

    printf("\nEsta fun��o imprime todos os consumidores que come�am com a inicial digitada.");
    printf("\nObs: caso n�o apare�a nada, fique tranquilo. Isso quer dizer que n�o foi encontrado nenhum nome com a inicial digitada.");
    printf("\nQual inicial voc� deseja procurar? ");
    fflush(stdin);
    gets(inicial);
    strupr(inicial);
    printf("\nImprimindo os nomes que come�am com '%s'..", inicial);
    printf("\n");

    arquivo = fopen("arq.txt", "r");

    if(arquivo == NULL){
        printf("Ocorreu um ERRO!");
    }

    while(auxIdentificaFimArquivo != EOF){
        auxIdentificaFimArquivo = fgetc(arquivo);
        if(auxIdentificaFimArquivo == EOF){
            break;
        }

        fgets(linhaStruct, sizeof(linhaStruct), arquivo);

        strncpy(inicialPrimeiroNome, linhaStruct, 2);

        auxPonteiroInicial = strstr(inicialPrimeiroNome, inicial);

        if(auxPonteiroInicial != NULL){
            printf("\n%s", linhaStruct);

            for(auxContadorDeLinha; auxContadorDeLinha <= TAM_LIN_STRUCT; auxContadorDeLinha++){
                fgets(auxLinha,sizeof(auxLinha),arquivo);
                printf("%s", auxLinha);
            }

            auxContadorDeLinha = 0;
        }
    }
    fclose(arquivo);

    printf("\n");
    perguntaSeDesejaRepetirImpressao();
}

void executaFuncoesDoMenu(int opcao){
    switch(opcao)
    {
        case 1:
        printf("\nFun��o Cadastro Aberta\n");
        cadastra();
        break;

        case 2:
        printf("\nFun��o Consulta Aberta\n");
        consulta();
        break;

        case 3:
        printf("\nFun��o Imprime Aberta\n");
        imprimePelaInicial();
        break;

        case 4:
        imprimeTudo();
        break;

        case 5:
        printf("\nVoc� saiu do programa\n");
        break;


        default:
        printf("\nOp��o Inv�lida!");
        printf("\nDigite novamente.");
        int auxOpcao = imprimeMenu();
        executaFuncoesDoMenu(auxOpcao);
    }
}

void imprimeTudo(){
    FILE *arquivo;
    char auxIdentificaFimArquivo;
    char linhaStruct[70];

    arquivo = fopen("arq.txt", "r");

    if(arquivo == NULL){
        printf("Ocorreu um ERRO!");
    }

    while(auxIdentificaFimArquivo != EOF){
        auxIdentificaFimArquivo = fgetc(arquivo);

        if(auxIdentificaFimArquivo == EOF){
            break;
        }

        fgets(linhaStruct, sizeof(linhaStruct), arquivo);
        printf("%s", linhaStruct);
    }

    printf("\n");
    printf("\nRedirecionando para o menu..\n");
    printf("\n");
    system("PAUSE");
    system("cls");
    menu();
}

void menu(){
    int opcao = imprimeMenu();
    executaFuncoesDoMenu(opcao);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    menu();

    system("PAUSE");
    return 0;
}
