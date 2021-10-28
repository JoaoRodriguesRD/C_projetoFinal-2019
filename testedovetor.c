/* JOAO RODRIGUES DE MELO NETO  */

#include <stdio.h>
#include <string.h>
#define MAX_APOSTADORES 4
#define MAX_CARTOES 200
#define MIN_NUMEROS 6
#define MAX_NUMEROS 15


typedef struct
{
	int dia;
	int mes;
	int ano;
} tdata;

typedef struct
{
	int apostador[MAX_APOSTADORES];
	int quant; //quant max = MAX_APOSTADORES
	int quant_numeros; //min e max = 6 e 15
	int numeros[MAX_NUMEROS]; // nao permitir numeros duplicados
	int finalizado; // 0 - pode alterar , 1 - nao altera
} tbolaoum;

typedef struct
{
	int apostador[MAX_APOSTADORES];
	int quant; //quant max = MAX_APOSTADORES
	int quant_cartoes;
	int numeros[MAX_CARTOES][MIN_NUMEROS];
	int finalizado; // 0 - pode alterar , 1 - nao altera
} tbolaovarios;

typedef struct
{
	tdata data;
	tbolaoum bolaoU;
	tbolaovarios bolaoV;
} tbolao;

typedef struct
{
	char nome[51];
	char cpf[12];
	char telefone[12];
	char telefone2[12];
	int posicao; // posicao no vetor
//	char cadastro; //n- nenhum, u-bolao U v-bolao V
} tapostadores;

//
//Verifica se existe outro apostador com o mesmo CPF e retorna 1
//Recebe o vetor apost e o cpf digitado
int ja_existe(tapostadores apost[MAX_APOSTADORES], char cpf_provisorio[12])
{
	int i;
	for(i = 0; i < MAX_APOSTADORES; i++)
	{
		if(strcmp(apost[i].cpf, cpf_provisorio) == 0)
		{
			return 1;
		}
	}
	return 0;
}

//
//Cadastra apostador, retorna 'n' se for cancelado e retorna 's' se for cadastrado
//
char cadastrar_apostador(tapostadores apost[MAX_APOSTADORES], int **contador_apost)
{
	printf("-CADASTRAR APOSTADOR-\n");
	printf("Para cancelar o cadastro digite n na parte de cpf \n");
	int contador = **contador_apost;
	int i;
	char cpf_provisorio[12];
	do
	{
		printf("Digite um CPF valido\n");
		fflush(stdin);
		fgets(cpf_provisorio, 12, stdin);
//		scanf("%s",cpf_provisorio);
		if(cpf_provisorio[0] == 'n' || cpf_provisorio[0] == 'N')
			return 'n';

		if(ja_existe(apost, cpf_provisorio))
			printf("ja existe esse cpf cadastrado\n");

		if(cpf_provisorio[1] == '\0')
			printf("Tamanho insuficiente\n");

	}
	while(ja_existe(apost, cpf_provisorio) || cpf_provisorio[1] == '\0');

	for(i = 0; i < 12; i++)
	{
		apost[contador].cpf[i] = cpf_provisorio[i];
	}
	//printf("%s",apost[contador].cpf);

	do
	{
		printf("Digite o nome:\n");
		fflush(stdin);
		fgets(apost[contador].nome, 51, stdin);
//	scanf("%s",apost[contador].nome);
		if(apost[contador].nome[1] == '\0')
			printf("eh obrigatorio ter o nome!\n");
	}
	while(apost[contador].nome[1] == '\0');

	printf("Digite o telefone principal\n");
	printf("Se nao quiser, basta digitar enter\n");
//	scanf("%s",apost[contador].telefone);
	fflush(stdin);
	fgets(apost[contador].telefone, 12, stdin);

	printf("Digite o telefone secundario\n");
	printf("Se nao quiser, basta digitar 0 e dar enter\n");
//	scanf("%s",apost[contador].telefone2);
	fflush(stdin);
	fgets(apost[contador].telefone2, 12, stdin);

	printf("contador= %d\n", contador);
	return's';
}

//busca um apostador com o cpf cadastrado
//recebe o vetor apost e um cpf
//Retorna a posicao se for achado ou retorna -1 se nao encontrar
int buscar(tapostadores apost[MAX_APOSTADORES], char cpf_provisorio[12])
{
	int i;
	for(i = 0; i < MAX_APOSTADORES; i++)
	{
		if(strcmp(apost[i].cpf, cpf_provisorio) == 0)
		{
			return i;
		}
	}
	return -1;
}
//
//altera apostador cadastrado
//
void alterar_apostador(tapostadores apost[MAX_APOSTADORES])
{
	char cpf_provisorio[12];
	int local;
	do
	{
		printf("Digite o cpf do apostador que deseja alterar\n");
		printf("Se nao quiser alterar digite enter\n");
		fflush(stdin);
		fgets(cpf_provisorio, 12, stdin);
		if(cpf_provisorio[1] == '\0')
			return;
		local = buscar(apost, cpf_provisorio);
		if(local == -1)
			printf("Nao foi encontrado esse cpf\n");
	}
	while(local == -1);
	/*
		do{
		printf("Digite um novo nome:\n");
		scanf("%s",apost[local].nome);
		    if(strlen(apost[local].nome)==0)
		    	printf("Tamanho insuficiente\n");
		}while(strlen(apost[local].nome)==0);
	*/
	do
	{
		printf("Digite um novo nome:\n");
		fflush(stdin);
		fgets(apost[local].nome, 51, stdin);
//	scanf("%s",apost[contador].nome);
		if(apost[local].nome[1] == '\0')
			printf("eh obrigatorio ter o nome!\n");
	}
	while(apost[local].nome[1] == '\0');


	printf("Digite um novo telefone principal\n");
	printf("Se nao quiser, basta digitar 0 e dar enter\n");
	scanf("%s", apost[local].telefone);

	printf("Digite um novo telefone secundario\n");
	printf("Se nao quiser, basta digitar 0 e dar enter\n");
	scanf("%s", apost[local].telefone2);
	return;
}

//
//Excluir apostador
//recebe o vetor apost, exclui um apostador e arruma o vetor
void excluir_apostador(tapostadores apost[MAX_APOSTADORES], int **contador_apost)
{
	char cpf[12];
	int achado;
	char escolha = 'n';
	int local;
	int i;
	char nulo_51[51];
	char nulo_12[12];
	do
	{
		printf("Digite um cpf de alguem cadastrado para excluir\n");
		fflush(stdin);
		fgets(cpf, 12, stdin);
		achado = buscar(apost, cpf);
		if(achado == -1)
		{
			printf("Apostador nao encontrado\n");
			printf("Deseja continuar tentando? digite s\n");
			scanf(" %c", &escolha);
			if(escolha == 'n' || escolha == 'N')
				return;
		}
	}
	while(achado == -1);
	local = achado;
	printf("achado= %d\n", local);


	//apost[local].cpf[0] inicio
	//apost[local].cpf[11] fim

	for(i = achado; i < MAX_APOSTADORES; i++)
	{
		if(i == MAX_APOSTADORES - 1)
		{
			break;
		}
		strcpy(apost[i].nome, apost[i + 1].nome);
		strcpy(apost[i].cpf, apost[i + 1].cpf);
		strcpy(apost[i].telefone, apost[i + 1].telefone);
		strcpy(apost[i].telefone, apost[i + 1].telefone2);
	}
	i = (MAX_APOSTADORES - 1);
	//Ultimo elemento do vetor apost
	strcpy(apost[i].nome, nulo_51);
	strcpy(apost[i].cpf, nulo_12);
	strcpy(apost[i].telefone, nulo_12);
	strcpy(apost[i].telefone, nulo_12);


	**contador_apost = **contador_apost - 1 ;


	return;
}

//
// Menu dos apostadores
//
int menu_apostador(tapostadores apost[MAX_APOSTADORES], int *contador_apost)
{
	char cadastrado;
	int opcao;
	do
	{
		printf("-MENU DOS APOSTADORES-\n");
		printf("1- CADASTRAR APOSTADOR\n");
		printf("2- ALTERAR APOSTADOR\n");
		printf("3- EXCLUIR APOSTADOR\n");
		printf("0- SAIR\n");
		scanf("%d", &opcao);


		switch(opcao)
		{
		case 0:
			return 0;
			break;

		case 1:
			if(*contador_apost >= MAX_APOSTADORES)
			{
				printf("Cadastro impossivel, maximo atingido\n");
				continue;
			}
			cadastrado = cadastrar_apostador(apost, &contador_apost);
			if(cadastrado != 'n' && cadastrado != 'N')
				*contador_apost = *contador_apost + 1;
			break;

		case 2:
			alterar_apostador(apost);
			break;

		case 3:
			if(*contador_apost == 0)
			{
				printf("Impossivel excluir, sem pessoas cadastradas\n");
				continue;
			}

			excluir_apostador(apost, &contador_apost);
			break;


		}

	}
	while(opcao != 0);

	return opcao;

}

//
//Recebe um vetor de numeros e a quantidade de numeros do sorteio. Verifica se tem algum repetido
//retorna 1 se tiver, retorna 0 se nao tiver
int numero_repetido(int vetor[MAX_NUMEROS], int num)
{
	int i;
	int j;
	for (i = 0; i < num; i++)
	{
		for (j = i + 1; j < num; j++)
		{
			if (vetor[i] == vetor[j])
			{
				return 1;
			}
		}
	}
	return 0;
}



//
//Cadastra o bolao
//Recebe o bolao e o vetor de apostadores
void bolao_cadastrar(tbolao bolao[0], tapostadores apost[MAX_APOSTADORES])
{
	//printf("%d%d%d",(bolao.data.dia),(bolao.data.mes),(bolao.data.ano));
	int ano;
	int mes;
	int dia;
	char opcao;
	char opcao_tipo;
	int n;
	int i, j, k;
	char cpf_provisorio[12];
	int registrado = 0;
	int indice;
	int continua = 0;
	printf("Escreva a data do sorteio no formato[dia/mes/ano]\n");
	scanf("%d%d%d", &dia, &mes, &ano);
	if( bolao[0].data.dia != dia && bolao[0].data.mes != mes && bolao[0].data.ano != ano ) //Data diferente da armazenada!
	{
		do
		{
			printf("Quer cadastrar novo sorteio?  [s/n]\n");
			printf("OBS: as informacoes do sorteio anterior serao perdidas!\n");
			fflush(stdin);
			scanf(" %c", &opcao);
			if(opcao == 'n')
				return;
		}
		while(opcao != 's');

		bolao[0].bolaoU.quant = 0;
		bolao[0].bolaoV.quant = 0;
		bolao[0].bolaoU.finalizado = 0;
		bolao[0].bolaoV.finalizado = 0;

		do
		{
			printf("Digite o tipo de bolao que deseja cadastrar\n");
			printf("u - para bolao UM,\nv - para bolao VARIOS\n");
			scanf(" %c", &opcao_tipo);
		}
		while(opcao_tipo != 'u' && opcao_tipo != 'v');

		//	int vagas_cadastro;
		//	vagas_cadastro = MAX_APOSTADORES - bolao.bolaoU.quant;

		//////////////////////////////////////////////////////////////////////
		switch(opcao_tipo)
		{
		case 'u':
			printf("OPCAO u SELECIONADA\n");
			printf("bolao simples\n");
			do
			{
				printf("Digite a quantidade de apostadores\n");
				printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
				printf("0 - VOLTAR\n");
				printf("Quantidade de apostadores: ");
				scanf("%d", &n);
			}
			while(n > MAX_APOSTADORES || n < 0);
			if(n == 0)
			{
				printf("VOLTANDO ENTAO\n");
				return;
			}

			printf("Digite o CPF dos %d apostadores:\n", n);
			for(i = 0; i < n; i++)
			{
				printf("%d- \n", i + 1);
				fflush(stdin);
				fgets(cpf_provisorio, 12, stdin);
				if(ja_existe(apost, cpf_provisorio) == 0)
				{
					printf("Apostador nao cadastrado\n");
					continue;
				}
				indice = buscar(apost, cpf_provisorio);
				for(j = 0; j < MAX_APOSTADORES; j++)
				{
					if(indice == bolao[0].bolaoU.apostador[j])
					{
						printf("Apostador inserido anteriormente\n");
						continua = 1;
					}

				}

				if(continua)
				{
					continua = 0;
					continue;
				}

				registrado++;
				bolao[0].bolaoU.apostador[bolao[0].bolaoU.quant] = indice;

			}

			printf("Foram registrados %d apostadores para esse bolao\n", registrado);
			if(registrado == 0)
			{
				printf("Retornando ao menu...\n");
				return;
			}
			bolao[0].bolaoU.quant = bolao[0].bolaoU.quant + registrado;

			printf("Digite a quantidade de numeros no cartao\n");
			do
			{
				printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
				scanf("%d", &bolao[0].bolaoU.quant_numeros);
			}
			while(bolao[0].bolaoU.quant_numeros < MIN_NUMEROS || bolao[0].bolaoU.quant_numeros > MAX_NUMEROS);

			do
			{
				printf("Digite %d numeros:", bolao[0].bolaoU.quant_numeros);
				for(i = 0; i < bolao[0].bolaoU.quant_numeros; i++)
					scanf("%d", &bolao[0].bolaoU.numeros[i]);
				if(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros))
					printf("Nao pode ter sorteio com numero repetido!\n");
			}
			while(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros));

			printf("Bolao e apostadores cadastrados!\n");
			printf("Para adicionar mais apostadores vai na opcao ALTERAR no menu de apostas\n");



			break;
		case 'v':
			printf("OPCAO v SELECIONADA\n");
			printf("bolao com cartoes\n");
			do
			{
				printf("Digite a quantidade de apostadores\n");
				printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
				printf("0 - VOLTAR\n");
				printf("Quantidade de apostadores: ");
				scanf("%d", &n);
			}
			while(n > MAX_APOSTADORES || n < 0);
			if(n == 0)
			{
				printf("VOLTANDO\n");
				return;
			}
			printf("Digite o CPF dos %d apostadores:\n", n);
			for(i = 0; i < n; i++)
			{
				printf("%d- \n", i + 1);
				fflush(stdin);
				fgets(cpf_provisorio, 12, stdin);
				if(ja_existe(apost, cpf_provisorio) == 0)
				{
					printf("Apostador nao cadastrado\n");
					continue;
				}
				indice = buscar(apost, cpf_provisorio);
				for(j = 0; j < MAX_APOSTADORES; j++)
				{
					if(indice == bolao[0].bolaoV.apostador[j])
					{
						printf("Apostador inserido anteriormente\n");
						continua = 1;
					}

				}

				if(continua)
				{
					continua = 0;
					continue;
				}
				printf("registrado\n");
				registrado++;
				bolao[0].bolaoV.apostador[bolao[0].bolaoV.quant] = indice;

			}
			bolao[0].bolaoV.quant += registrado;
			printf("Foram registrados %d apostadores para esse bolao\n", registrado);
			if(registrado == 0)
			{
				printf("Retornando ao menu...\n");
				return;
			}
			int cartoes;
			int quantidade;
			do
			{
				printf("Digite o numero de cartoes\n");
				printf("Entre 1 e %d cartoes\n", MAX_CARTOES);
				scanf("%d", &cartoes);

			}
			while(cartoes < 1 || cartoes > MAX_CARTOES);
			for(i = 0; i < cartoes; i++)
			{
				printf("Cadastrar cartao %d\n", i + 1);

				printf("Digite a quantidade de numeros no cartao %d\n", i + 1);
				do
				{
					printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
					scanf("%d", &quantidade);
				}
				while(quantidade < MIN_NUMEROS || quantidade > MAX_NUMEROS);

				do
				{
					printf("Digite %d numeros do cartao %d :\n", quantidade, i + 1);
					printf("ATENCAO, SE DIGITAR MAIS QUE %d NUMEROS SO DEUS SABE O QUE VAI ACONTECER\n", quantidade);
					for(k = 0; k < quantidade; k++)
						scanf("%d", &bolao[0].bolaoV.numeros[i][k]);
					if(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade))
						printf("Nao pode ter sorteio com numero repetido!\n");
				}
				while(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade));
				printf("Cartao %d cadastrado!\n", i + 1);
			}
			printf("Todos os cartoes foram cadastrados!\n");
			break;

		}
	}
	else   //Data igual da armazenada!
	{
		if(bolao[0].bolaoU.quant != 0 && bolao[0].bolaoV.quant != 0)
		{
			printf("Boloes cadastrados para a data no sorteio\n");
			printf("Se quiser adicionar escolha a opcao alterar bolao\n");
			return;
		}
		if(bolao[0].bolaoU.quant == 0 && bolao[0].bolaoV.quant != 0)
		{

			do
			{
				printf("So tem como criar o bolao UM\n");
				printf("Deseja criar? [s/n]\n");
				scanf(" %c", &opcao);
				if(opcao == 'n')
					return;
			}
			while(opcao != 's');

			printf("bolao simples\n");

			do
			{
				printf("Digite a quantidade de apostadores\n");
				printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
				printf("0 - VOLTAR\n");
				printf("Quantidade de apostadores: ");
				scanf("%d", &n);
			}
			while(n > MAX_APOSTADORES || n < 0);
			if(n == 0)
			{
				printf("VOLTANDO ENTAO\n");
				return;
			}

			printf("Digite o CPF dos %d apostadores:\n", n);
			for(i = 0; i < n; i++)
			{
				printf("%d- \n", i + 1);
				fflush(stdin);
				fgets(cpf_provisorio, 12, stdin);
				if(ja_existe(apost, cpf_provisorio) == 0)
				{
					printf("Apostador nao cadastrado\n");
					continue;
				}
				indice = buscar(apost, cpf_provisorio);
				for(j = 0; j < MAX_APOSTADORES; j++)
				{
					if(indice == bolao[0].bolaoU.apostador[j])
					{
						printf("Apostador inserido anteriormente\n");
						continua = 1;
					}

				}

				if(continua)
				{
					continua = 0;
					continue;
				}

				registrado++;
				bolao[0].bolaoU.apostador[bolao[0].bolaoU.quant] = indice;

			}
			bolao[0].bolaoU.quant += registrado;
			printf("Foram registrados %d apostadores para esse bolao\n", registrado);
			if(registrado == 0)
			{
				printf("Retornando ao menu...\n");
				return;
			}

			printf("Digite a quantidade de numeros no cartao\n");
			do
			{
				printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
				scanf("%d", &bolao[0].bolaoU.quant_numeros);
			}
			while(bolao[0].bolaoU.quant_numeros < MIN_NUMEROS || bolao[0].bolaoU.quant_numeros > MAX_NUMEROS);

			do
			{
				printf("Digite %d numeros:", bolao[0].bolaoU.quant_numeros);
				for(i = 0; i < bolao[0].bolaoU.quant_numeros; i++)
					scanf("%d", &bolao[0].bolaoU.numeros[i]);
				if(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros))
					printf("Nao pode ter sorteio com numero repetido!\n");
			}
			while(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros));

			printf("Bolao e apostadores cadastrados!\n");
			printf("Para adicionar mais apostadores vai na opcao ALTERAR no menu de apostas\n");


		}
		if(bolao[0].bolaoU.quant != 0 && bolao[0].bolaoV.quant == 0)
		{
			do
			{
				printf("So tem como criar o bolao com cartoes\n");
				printf("Deseja criar? [s/n]\n");
				scanf(" %c", &opcao);
				if(opcao == 'n')
					return;
			}
			while(opcao != 's');
			printf("bolao com cartoes\n");
			do
			{
				printf("Digite a quantidade de apostadores\n");
				printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
				printf("0 - VOLTAR\n");
				printf("Quantidade de apostadores: ");
				scanf("%d", &n);
			}
			while(n > MAX_APOSTADORES || n < 0);
			if(n == 0)
			{
				printf("VOLTANDO\n");
				return;
			}
			printf("Digite o CPF dos %d apostadores:\n", n);
			for(i = 0; i < n; i++)
			{
				printf("%d- \n", i + 1);
				fflush(stdin);
				fgets(cpf_provisorio, 12, stdin);
				if(ja_existe(apost, cpf_provisorio) == 0)
				{
					printf("Apostador nao cadastrado\n");
					continue;
				}
				indice = buscar(apost, cpf_provisorio);
				for(j = 0; j < MAX_APOSTADORES; j++)
				{
					if(indice == bolao[0].bolaoV.apostador[j])
					{
						printf("Apostador inserido anteriormente\n");
						continua = 1;
					}

				}

				if(continua)
				{
					continua = 0;
					continue;
				}
				printf("registrado\n");
				registrado++;
				bolao[0].bolaoV.apostador[bolao[0].bolaoV.quant] = indice;

			}
			bolao[0].bolaoV.quant += registrado;
			printf("Foram registrados %d apostadores para esse bolao\n", registrado);
			if(registrado == 0)
			{
				printf("Retornando ao menu...\n");
				return;
			}
			int cartoes;
			int quantidade;
			do
			{
				printf("Digite o numero de cartoes\n");
				printf("Entre 1 e %d cartoes\n", MAX_CARTOES);
				scanf("%d", &cartoes);

			}
			while(cartoes < 1 || cartoes > MAX_CARTOES);
			for(i = 0; i < cartoes; i++)
			{
				printf("Cadastrar cartao %d\n", i + 1);

				printf("Digite a quantidade de numeros no cartao %d\n", i + 1);
				do
				{
					printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
					scanf("%d", &quantidade);
				}
				while(quantidade < MIN_NUMEROS || quantidade > MAX_NUMEROS);

				do
				{
					printf("Digite %d numeros do cartao %d :\n", quantidade, i + 1);
					printf("ATENCAO, SE DIGITAR MAIS QUE %d NUMEROS SO DEUS SABE O QUE VAI ACONTECER\n", quantidade);
					for(k = 0; k < quantidade; k++)
						scanf("%d", &bolao[0].bolaoV.numeros[i][k]);
					if(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade))
						printf("Nao pode ter sorteio com numero repetido!\n");
				}
				while(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade));
				printf("Cartao %d cadastrado!\n", i + 1);
			}
			printf("Todos os cartoes foram cadastrados!\n");
		}
		if(bolao[0].bolaoU.quant == 0 && bolao[0].bolaoV.quant == 0)
		{
			printf("Os dois tipos de apostas nao foram cadastradas\n");
			bolao[0].bolaoU.quant = 0;
			bolao[0].bolaoV.quant = 0;
			bolao[0].bolaoU.finalizado = 0;
			bolao[0].bolaoV.finalizado = 0;
			do
			{
				printf("Digite o tipo de bolao que deseja cadastrar\n");
				printf("u - para bolao UM,\nv - para bolao VARIOS\n");
				scanf(" %c", &opcao_tipo);
			}
			while(opcao_tipo != 'u' && opcao_tipo != 'v');

			//	int vagas_cadastro;
			//	vagas_cadastro = MAX_APOSTADORES - bolao.bolaoU.quant;

			//////////////////////////////////////////////////////////////////////
			switch(opcao_tipo)
			{
			case 'u':
				printf("OPCAO u SELECIONADA\n");
				printf("bolao simples\n");
				do
				{
					printf("Digite a quantidade de apostadores\n");
					printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
					printf("0 - VOLTAR\n");
					printf("Quantidade de apostadores: ");
					scanf("%d", &n);
				}
				while(n > MAX_APOSTADORES || n < 0);
				if(n == 0)
				{
					printf("VOLTANDO ENTAO\n");
					return;
				}

				printf("Digite o CPF dos %d apostadores:\n", n);
				for(i = 0; i < n; i++)
				{
					printf("%d- \n", i + 1);
					fflush(stdin);
					fgets(cpf_provisorio, 12, stdin);
					if(ja_existe(apost, cpf_provisorio) == 0)
					{
						printf("Apostador nao cadastrado\n");
						continue;
					}
					indice = buscar(apost, cpf_provisorio);
					for(j = 0; j < MAX_APOSTADORES; j++)
					{
						if(indice == bolao[0].bolaoU.apostador[j])
						{
							printf("Apostador inserido anteriormente\n");
							continua = 1;
						}

					}

					if(continua)
					{
						continua = 0;
						continue;
					}

					registrado++;
					bolao[0].bolaoU.apostador[bolao[0].bolaoU.quant] = indice;

				}
				bolao[0].bolaoU.quant += registrado;
				printf("Foram registrados %d apostadores para esse bolao\n", registrado);
				if(registrado == 0)
				{
					printf("Retornando ao menu...\n");
					return;
				}

				printf("Digite a quantidade de numeros no cartao\n");
				do
				{
					printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
					scanf("%d", &bolao[0].bolaoU.quant_numeros);
				}
				while(bolao[0].bolaoU.quant_numeros < MIN_NUMEROS || bolao[0].bolaoU.quant_numeros > MAX_NUMEROS);

				do
				{
					printf("Digite %d numeros:", bolao[0].bolaoU.quant_numeros);
					for(i = 0; i < bolao[0].bolaoU.quant_numeros; i++)
						scanf("%d", &bolao[0].bolaoU.numeros[i]);
					if(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros))
						printf("Nao pode ter sorteio com numero repetido!\n");
				}
				while(numero_repetido(bolao[0].bolaoU.numeros, bolao[0].bolaoU.quant_numeros));

				printf("Bolao e apostadores cadastrados!\n");
				printf("Para adicionar mais apostadores vai na opcao ALTERAR no menu de apostas\n");



				break;
			case 'v':
				printf("OPCAO v SELECIONADA\n");
				printf("bolao com cartoes\n");
				do
				{
					printf("Digite a quantidade de apostadores\n");
					printf("Entre 1 e %d apostadores!\n", MAX_APOSTADORES);
					printf("0 - VOLTAR\n");
					printf("Quantidade de apostadores: ");
					scanf("%d", &n);
				}
				while(n > MAX_APOSTADORES || n < 0);
				if(n == 0)
				{
					printf("VOLTANDO\n");
					return;
				}
				printf("Digite o CPF dos %d apostadores:\n", n);
				for(i = 0; i < n; i++)
				{
					printf("%d- \n", i + 1);
					fflush(stdin);
					fgets(cpf_provisorio, 12, stdin);
					if(ja_existe(apost, cpf_provisorio) == 0)
					{
						printf("Apostador nao cadastrado\n");
						continue;
					}
					indice = buscar(apost, cpf_provisorio);
					for(j = 0; j < MAX_APOSTADORES; j++)
					{
						if(indice == bolao[0].bolaoV.apostador[j])
						{
							printf("Apostador inserido anteriormente\n");
							continua = 1;
						}

					}

					if(continua)
					{
						continua = 0;
						continue;
					}
					printf("registrado\n");
					registrado++;
					bolao[0].bolaoV.apostador[bolao[0].bolaoV.quant] = indice;

				}
				bolao[0].bolaoV.quant += registrado;
				printf("Foram registrados %d apostadores para esse bolao\n", registrado);
				if(registrado == 0)
				{
					printf("Retornando ao menu...\n");
					return;
				}
				int cartoes;
				int quantidade;
				do
				{
					printf("Digite o numero de cartoes\n");
					printf("Entre 1 e %d cartoes\n", MAX_CARTOES);
					scanf("%d", &cartoes);

				}
				while(cartoes < 1 || cartoes > MAX_CARTOES);
				for(i = 0; i < cartoes; i++)
				{
					printf("Cadastrar cartao %d\n", i + 1);

					printf("Digite a quantidade de numeros no cartao %d\n", i + 1);
					do
					{
						printf("No minimo %d e no maximo %d: ", MIN_NUMEROS, MAX_NUMEROS);
						scanf("%d", &quantidade);
					}
					while(quantidade < MIN_NUMEROS || quantidade > MAX_NUMEROS);

					do
					{
						printf("Digite %d numeros do cartao %d :\n", quantidade, i + 1);
						printf("ATENCAO, SE DIGITAR MAIS QUE %d NUMEROS SO DEUS SABE O QUE VAI ACONTECER\n", quantidade);
						for(k = 0; k < quantidade; k++)
							scanf("%d", &bolao[0].bolaoV.numeros[i][k]);
						if(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade))
							printf("Nao pode ter sorteio com numero repetido!\n");
					}
					while(numero_repetido(bolao[0].bolaoV.numeros[i], quantidade));
					printf("Cartao %d cadastrado!\n", i + 1);
				}
				printf("Todos os cartoes foram cadastrados!\n");
				break;

			}
		}
	}
	bolao[0].data.dia = dia;
	bolao[0].data.mes = mes;
	bolao[0].data.ano = ano;

	return;
}

//
//altera um bolao
//Recebe o bolao e o vetor de apostadores
void bolao_alterar(tbolao bolao[0], tapostadores apost[MAX_APOSTADORES])
{
	char opcao;
	int vaga;
	int n;
	printf("MENU ALTERAR\n");
	do
	{
		printf("Escolha o tipo de bolao que deseja alterar\n");
		printf("u - bolao UM\n");
		printf("v - Bolao VARIOS\n");
		printf("0 - VOLTAR\n");
		scanf(" %c", &opcao);
		if(opcao == '0')
			return;
	}
	while(opcao != 'u' && opcao != 'v');

	switch(opcao)
	{
	case 'u':
		if(bolao[0].bolaoU.finalizado == 1)
		{
			printf("Bolao finalizado, nao pode alterar\n");
			return;
		}
		if(bolao[0].bolaoU.quant == 0)
		{
			printf("Nao tem apostadores para alterar, por favor cadastre\n");
			return;
		}
		if(bolao[0].bolaoU.quant == MAX_APOSTADORES)
		{
			printf("Impossivel cadastrar, esta lotado!\n");
		}
		vaga = MAX_APOSTADORES - bolao[0].bolaoU.quant;
		do
		{
			printf("voce pode adicionar no maximo %d apostadores: ", vaga);
			scanf("%d", &n);
			if(n==0)
				return;
		}
		while(n > vaga || n < 0);
		break;
	case 'v':
		if(bolao[0].bolaoV.finalizado == 1)
		{
			printf("Bolao finalizado, nao pode alterar\n");
			return;
		}
		if(bolao[0].bolaoV.quant == 0)
		{
			printf("Nao tem apostadores para alterar, por favor cadastre\n");
			return;
		}
		if(bolao[0].bolaoV.quant == MAX_APOSTADORES)
		{
			printf("Impossivel cadastrar, esta lotado!\n");
		}
		vaga = MAX_APOSTADORES - bolao[0].bolaoU.quant;
		
		do
		{
			printf("voce pode adicionar no maximo %d apostadores: ", vaga);
			scanf("%d", &n);
			if(n==0)
				return;
		}while(n > vaga || n < 0);
		
	}



	return;
}
//
//
//
void bolao_finalizar()
{

	return;
}
//
//
//
void bolao_ganhador()
{

	return;
}
//
// Menu das apostas
// Menu dos boloes que cadastra, altera e finaliza um bolao alem de falar o o cpf do ganhador
int menu_apostas(tapostadores apost[MAX_APOSTADORES], int *contador_apost, tbolao bolao[0])
{
	int opcao;
	/*
	1- Novo
	2- Alterar
	3- Finalizar (faz o campo finalizado do bolão desejado igual a 1)
	4- Imprimir
	5- Verificar Ganhador (Insira os 6 números sorteados na Mega-Sena. Não permita duplicidade.)
	0- Sair
	*/
	do
	{
		printf("-MENU DE APOSTAS-\n");
		printf("1- NOVO BOLAO\n");
		printf("2- ALTERAR BOLAO NAO FINALIZADO\n");
		printf("3- FINALIZAR BOLAO\n");
		printf("4- VERIFICAR GANHADOR\n");
		printf("0- SAIR\n");
		scanf("%d", &opcao);


		switch(opcao)
		{
		case 1:
			bolao_cadastrar(bolao, apost);
			break;
		case 2:
			bolao_alterar(bolao, apost);
			break;
		case 3:
			bolao_finalizar();
			break;
		case 4:
			bolao_ganhador();
			break;
		}

	}
	while(opcao != 0);


	return 0;
}

//
// Sera exibido no comeco do programa
//
/*
int menu_pincipal(int opcao)
{
	do
	{
		printf("1- MENU DOS APOSTADORES\n");
		printf("2- MENU DE APOSTAS\n");
		printf("0- SAIR DO PROGRAMA\n");
		scanf("%d", &opcao);
	}
	while(opcao != 1 && opcao != 2 && opcao != 0);
	return opcao;
}
*/

int main()
{
	int i;
	int opcao;
	int contador_apost = 0;
	tapostadores apost[MAX_APOSTADORES];
	tbolao bolao[1];
	bolao[0].data.dia = 0;
	bolao[0].data.mes = 0;
	bolao[0].data.ano = 0;
	bolao[0].bolaoU.quant = 0;
	bolao[0].bolaoV.quant = 0;


	//limpar o vetor dos indices
	for(i = 0; i < MAX_APOSTADORES; i++)
	{
		bolao[0].bolaoU.apostador[i] = '\n';
		bolao[0].bolaoV.apostador[i] = '\n';
	}
	do
	{
		//opcao = menu_pincipal(opcao);

		do
		{
			printf("1- MENU DOS APOSTADORES\n");
			printf("2- MENU DE APOSTAS\n");
			printf("0- SAIR DO PROGRAMA\n");
			scanf("%d", &opcao);
		}
		while(opcao != 1 && opcao != 2 && opcao != 0);

		switch(opcao)
		{
		case 1:
			menu_apostador(apost, &contador_apost);

			break;
		case 2:
			menu_apostas(apost, &contador_apost, bolao);
			break;
		case 0:
			return 0;
			break;
		default:
			continue;
			//		break;
		}

	}
	while(1);


	return 0;
}
