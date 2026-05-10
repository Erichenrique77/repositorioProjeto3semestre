#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LIVROS "Livros.dat"
#define CLIENTES "Clientes.dat"
#define VENDAS "Vendas.dat"
#define AUTORES "Autores.dat"
#define RELACAO "Relacao_autor_livro.dat"

struct reg_livro{ 
  int codigo; 
  char titulo[30]; 
  float preco; 
};

struct reg_cliente{
  int codigo;
  char nome[40];
  char fone[15];
  char email[30];	
};

struct reg_venda{
  int codigo; //Código da Venda
  int codcli; //Código do Cliente
  int codliv; //Código do Livro a ser vendido
  int qtde; //Quantidade vendida
  float desconto; //Desconto 
};

struct reg_autor {
	int codigo; //código do autor
	char nome[30];
};

struct reg_RelAutorLivro{
	int codrelacao;
	int codautor; //código do Autor
	int codlivro; //código do Livro
};

void converteParaMaiusculo(char string[]){
  int i;
  
  for (i=0; i<strlen(string); i++){
  	string[i] = toupper(string[i]);
  }
	
}//Fim converteParaMaiusculo()

struct reg_cliente buscarClientePeloCodigo(int codbuscar){
  FILE *fpcliente;
  struct reg_cliente cliente;
  int achou; 	
  
  //Abrir o Arquivo para Leitura
  fpcliente = fopen(CLIENTES,"rb");
  
  //Localizar o cLIENTE
  achou=0; 
  while((achou==0)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1)){
  	if (cliente.codigo==codbuscar){ //Achei o cliente
	  achou=1;
	}
  }

  //Fechar o Arquivo
  fclose(fpcliente);

   if(achou!=1){//cliente NÃO Localizado
   	 cliente.codigo = -1;	
   } 
    
   return cliente;
 	
}//Fim buscarClientePeloCodigo()

struct reg_autor buscarAutorPeloCodigo(int codbuscar){
  FILE *fpautor;
  struct reg_autor autor;
  int achou; 	
  
  //Abrir o Arquivo para Leitura
  fpautor = fopen(AUTORES,"rb");
  
  //Localizar o autor
  achou=0; 
  while((achou==0)&&(fread(&autor,sizeof(autor),1,fpautor)==1)){
  	if (autor.codigo==codbuscar){ //Achei o autor
	  achou=1;
	}
  }

  //Fechar o Arquivo
  fclose(fpautor);

   if(achou!=1){//autor NÃO Localizado
   	 autor.codigo = -1;	
   } 
    
   return autor;
 	
}//Fim buscarAutorPeloCodigo()

struct reg_livro buscarLivroPeloCodigo(int codbuscar){
  FILE *fplivro;
  struct reg_livro livro;
  int achou; 	
  
  //Abrir o Arquivo para Leitura
  fplivro = fopen(LIVROS,"rb");
  
  //Localizar o Livro
  achou=0; 
  while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivro)==1)){
  	if (livro.codigo==codbuscar){ //Achei o Livro
	  achou=1;
	}
  }

  //Fechar o Arquivo
  fclose(fplivro);

  if(achou!=1){//lIVRO NÃO Localizado
   	 livro.codigo = -1;	
  } 
    
   return livro;
 	
}//Fim buscarlIVROPeloCodigo()

struct reg_venda buscarVendaPeloCodigo(int codbuscar){
  FILE *fpvenda;
  struct reg_venda venda;
  int achou; 	
  
  //Abrir o Arquivo para Leitura
  fpvenda = fopen(VENDAS,"rb");
  
  //Localizar a Venda
  achou=0; 
  while((achou==0)&&(fread(&venda,sizeof(venda),1,fpvenda)==1)){
  	if (venda.codigo==codbuscar){ //Achei a venda
	  achou=1;
	}
  }

  //Fechar o Arquivo
  fclose(fpvenda);

   if(achou!=1){//venda NÃO Localizada
   	 venda.codigo = -1;	
   } 
    
   return venda;
 	
}//Fim buscarVendaPeloCodigo()

void cadastrarLivro(){
  FILE *fplivro;
  struct reg_livro livro;
  char opc;
  
  //Entrada de Dados - Pedir os dados do Livro
  printf("\nDigite o Codigo:");
  fflush(stdin); scanf("%i",&livro.codigo);
  printf("Titulo: "); 
  fflush(stdin); gets(livro.titulo);
  printf("Preco: ");
  fflush(stdin); scanf("%f", &livro.preco);
  
  printf("\nGravar Livro?(S/N): ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s') && (opc!='S')){
  	printf("\nOperacao Cancelada!");
  	return; //Retorna ao menu principal
  }
  
  //Abrir o Arquivo
  fplivro = fopen(LIVROS,"ab");
  
  //Gravar o Registro
  fwrite(&livro,sizeof(livro),1,fplivro);
  
  //Fechar o Arquivo
  fclose(fplivro);
  
  printf("\nLivro gravado com sucesso.");
}//Fim cadastrarLivro()

void cadastrarCliente(){
  FILE *fpcliente;
  struct reg_cliente cliente;
  char opc;
  
  //Entrada de Dados - Pedir os dados do cliente
  printf("\nDigite o Codigo:");
  fflush(stdin); scanf("%i",&cliente.codigo);
  printf("Nome: "); 
  fflush(stdin); gets(cliente.nome);
  printf("Fone: "); 
  fflush(stdin); gets(cliente.fone);
  printf("Email: "); 
  fflush(stdin); gets(cliente.email);  
  
  printf("\nGravar Cliente?(S/N)");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s') && (opc!='S')){
  	printf("\nOperacao Cancelada!");
  	return; //Retorna ao menu principal
  }
  
  //Abrir o Arquivo
  fpcliente= fopen(CLIENTES,"ab");
  
  //Gravar o Registro
  fwrite(&cliente,sizeof(cliente),1,fpcliente);
  
  //Fechar o Arquivo
  fclose(fpcliente);
  
  printf("\nCliente gravado com sucesso.");
}//Fim cadastrarCliente()

void listarLivros(){
  FILE *fplivro;
  struct reg_livro livro;	
  	
  //Abrir o arquivo
  fplivro = fopen(LIVROS,"rb");
  
  printf("\nRelatorio Todos os Livros: ");
  //Ler registro por registro e mostar na tela
  while(fread(&livro,sizeof(livro),1,fplivro)==1){
	  printf("\nCodigo: %i",livro.codigo);
	  printf("\nTitulo: %s",livro.titulo);
	  printf("\npreco: %5.2f",livro.preco);
	  printf("\n--------------------------------------------");
  }
  //Fechar o Arquivo	
  fclose(fplivro);
	
}//Fim listarLivros()

void listarClientes(){
  FILE *fpcliente;
  struct reg_cliente cliente;
  	 	
  //Abrir o arquivo
  fpcliente = fopen(CLIENTES,"rb");
  
  printf("\nRelatorio Todos os Clientes: ");
  printf("\nCodigo Nome                           Fone            Email");
  //Ler registro por registro e mostar na tela
  while(fread(&cliente,sizeof(cliente),1,fpcliente)==1){
	  printf("\n%-6i %-30s %-15s %s",cliente.codigo,cliente.nome,cliente.fone,cliente.email);
  }
  //Fechar o Arquivo	
  fclose(fpcliente);
	
}//Fim listarClientes()

void consultarPeloCodigo(){
  FILE *fplivro;
  struct reg_livro livro;
  int codbuscar, achou; 	
  
  //Entrada de Dados - Pedir o Código do Livro
  printf("\nDigite o Codigo do Livro a ser Localizado: ");
  fflush(stdin); scanf("%i",&codbuscar);
  	
  //Abrir o Arquivo para Leitura
  fplivro = fopen(LIVROS,"rb");
  
  //Localizar e Mostrar o Livro
  achou=0; 
  while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivro)==1)){
  	//printf("\nEntrou");
  	if (livro.codigo==codbuscar){ //Achei o Livro
	  printf("\nCodigo: %i",livro.codigo);
	  printf("\nTitulo: %s",livro.titulo);
	  printf("\npreco: %5.2f",livro.preco);
	  printf("\n--------------------------------------------");
	  achou=1;
	}
  }

   if(achou==0){
   	 printf("\nLivro Nao Localizado!");
   }  
  //Fechar o Arquivo
  fclose(fplivro);
  	
}//Fim consultarPeloCodigo()

void consultarPeloTitulo(){
  FILE *fplivro;
  struct reg_livro livro;
  int achou; 
  char titbuscar[30];	
  
  //Entrada de Dados - Pedir o Título do Livro
  printf("\nDigite o Titulo do Livro a ser Localizado: ");
  fflush(stdin); gets(titbuscar);
  converteParaMaiusculo(titbuscar);
  	
  //Abrir o Arquivo para Leitura
  fplivro = fopen(LIVROS,"rb");
  
  //Localizar e Mostrar o Livro
  achou=0; 
  while((achou==0)&&(fread(&livro,sizeof(livro),1,fplivro)==1)){
  	converteParaMaiusculo(livro.titulo);
  	if (strcmp(livro.titulo,titbuscar)==0){ //Achei o Livro
	  printf("\nCodigo: %i",livro.codigo);
	  printf("\nTitulo: %s",livro.titulo);
	  printf("\npreco: %5.2f",livro.preco);
	  printf("\n--------------------------------------------");
	  achou=1;
	}
  }

   if(achou==0){
   	 printf("\nLivro Nao Localizado!");
   }  
  //Fechar o Arquivo
  fclose(fplivro);
  	
}//Fim consultarPeloTitulo()

void consultarPalavraChaveTitulo(){
  FILE *fplivro;
  struct reg_livro livro;
  int achou; 
  char palavra[30];	
  
  //Entrada de Dados - Pedir a Palavra-Chave
  printf("\nDigite a Palavra-Chave: ");
  fflush(stdin); gets(palavra);
  converteParaMaiusculo(palavra);
  	
  //Abrir o Arquivo para Leitura
  fplivro = fopen(LIVROS,"rb");
  
  //Localizar e Mostrar o Livro
  printf("\nRelatorio Livros com Palavra-Chave %s:",palavra);
  printf("\nCodigo Titulo                         Preco");
  achou=0; 
  while(fread(&livro,sizeof(livro),1,fplivro)==1){
  	converteParaMaiusculo(livro.titulo);
  	if (strstr(livro.titulo,palavra)!=NULL){ //Achei o Livro
	  printf("\n%-6i %-30s %-5.2f",livro.codigo,livro.titulo,livro.preco);
	  achou=1;
	}
  }

   if(achou==0){
   	 printf("\nNenhum Livro com esta Palavra-Chave no Titulo!");
   }  
  //Fechar o Arquivo
  fclose(fplivro);
  		
	
}//Fim consultarPalavraChaveTitulo()

void alterarLivro(){
  FILE *fplivro;
  struct reg_livro livro,liv;
  int cod,achou;
  char opc;
  
  printf("\nCodigo do Livro a ser Alterado: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o Livro e Mostrar os dados
  livro = buscarLivroPeloCodigo(cod);
  if (livro.codigo==-1){
  	printf("\nLivro NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do Livro Localizado
  printf("\nCodigo: %i",livro.codigo);
  printf("\nTitulo: %s",livro.titulo);
  printf("\npreco: %5.2f",livro.preco);  
  
  printf("\nConfirma Livro(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='n')||(opc=='N')){
  	printf("\n Livro NAO confirmado!");
  	return; //Volta para o menu principal
  }
  
  //Solicitar novos dados
  printf("\nDeseja alterar o Titulo(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo Titulo: ");
  	fflush(stdin); gets(livro.titulo);
  }

  printf("\nDeseja alterar o Preco(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo preco: ");
  	fflush(stdin); scanf("%f",&livro.preco);
  }  
  
  printf("\nGravar Livro(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='n')||(opc=='N')){
  	printf("\n Operacao Cancelada!");
  	return; //Volta para o menu principal
  }  
  
  fplivro = fopen(LIVROS,"rb+");
  
  //Posicionar o ponteiro do arquivo 
  //no registro a ser alterado
  achou=0;
  while ((achou==0)&&(fread(&liv,sizeof(liv),1,fplivro)==1)){
  	if (liv.codigo==cod){
  		achou=1;
	  }
  }
  
  //Preciso voltar o ponteiro para o regitro anterior
  fseek(fplivro,-sizeof(livro),1);
  
  fwrite(&livro,sizeof(livro),1,fplivro);

  fclose(fplivro);
  
  printf("\nLivro alterado com sucesso.");
}

void excluirLivro(){
  FILE *fplivro, *fplivronew;
  struct reg_livro livro;
  int cod;
  char opc;
  	
  printf("\nInforme Codigo do Livro: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o Livro e Mostrar os dados
  livro = buscarLivroPeloCodigo(cod);
  if (livro.codigo==-1){
  	printf("\nLivro NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do Livro Localizado
  printf("\nCodigo: %i",livro.codigo);
  printf("\nTitulo: %s",livro.titulo);
  printf("\npreco: %5.2f",livro.preco);  
  
  //Pedir Confirmação
  printf("\nConfirmar Exclusao do Livro(S/N)? ");
  fflush(stdin); scanf("%c",&opc);  

  if ((opc=='n')||(opc=='N')){
  	printf("\n Exlusao NAO confirmada!");
  	return; //Volta para o menu principal
  }  
  	
  //Criar um novo arquivo (livrosnew.dat) e copiar 
  //todos os livros menos o Livro sendo Excluído
  fplivro = fopen(LIVROS,"rb");
  fplivronew = fopen("livrosnew.dat","wb");
  while (fread(&livro,sizeof(livro),1,fplivro)==1){
  	if (livro.codigo!=cod){
  		fwrite(&livro,sizeof(livro),1,fplivronew);
	  }
  }
  fclose(fplivro);
  fclose(fplivronew);
  
  //Excluir o arquivo antigo livros.dat do sistema
  system("del livros.dat");
  
  //Renomear o novo arquivo 
  //(livrosnew.dat) para (livros.dat)
  system("ren livrosnew.dat livros.dat");
  
  printf("\nLivro excluido com sucesso.");
	
}//Fim excluirLivro()

void alterarCliente(){
  FILE *fpcliente;
  struct reg_cliente cliente,cli;
  int cod,achou;//Código do cliente a ser Alterado
  char opc;
  
  //Pedir o código do Cliente a ser alterado
  printf("\nDigite o Codigo do Cliente a ser Alterado: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o Cliente e Mostrar os dados
  cliente = buscarClientePeloCodigo(cod);
  if (cliente.codigo==-1){
  	printf("\nCliente NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do Cliente Localizado
  printf("\nCodigo: %i",cliente.codigo);
  printf("\nNome: %s",cliente.nome);
  printf("\nTelefone: %s",cliente.fone);
  printf("\nEmail: %s",cliente.email); 
  
  printf("\nConfirma Cliente(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='n')||(opc=='N')){
  	printf("\n Cliente NAO confirmado!");
  	return; //Volta para o menu principal
  }
  
  //Solicitar novos dados
  printf("\nDeseja alterar o Nome (S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo Nome: ");
  	fflush(stdin); gets(cliente.nome);
  }
  
  printf("\nDeseja alterar o Telefone (S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo Telefone: ");
  	fflush(stdin); gets(cliente.fone);
  }
  
  printf("\nDeseja alterar o E-mail (S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo E-mail: ");
  	fflush(stdin); gets(cliente.email);
  }

  fpcliente = fopen(CLIENTES,"rb+");
  
  //Posicionar o ponteiro do arquivo no registro a ser alterado
  achou=0;
  while ((achou==0)&&(fread(&cli,sizeof(cli),1,fpcliente)==1)){
  	if (cli.codigo==cod){
  		achou=1;
	  }
  }
  
  //Preciso voltar o ponteiro para o regitro anterior
  fseek(fpcliente,-sizeof(cliente),1);
  
  //Gravar livro alterado 
  fwrite(&cliente,sizeof(cliente),1,fpcliente);

  //Fechar o arquivo
  fclose(fpcliente);
  
  printf("\nCliente alterado com sucesso.");
}//Fim alterarCliente()

void alterarAutor(){
  FILE *fpautor;
  struct reg_autor autor,aut;
  int cod,achou;//Código do autor a ser Alterado
  char opc;
  
  //Pedir o código do autor a ser alterado
  printf("\nDigite o Codigo do Autor a ser Alterado: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o autor e Mostrar os dados
  autor = buscarAutorPeloCodigo(cod);
  if (autor.codigo==-1){
  	printf("\nAutor NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do autor Localizado
  printf("\nCodigo: %i",autor.codigo);
  printf("\nNome: %s",autor.nome);
 
  printf("\nConfirma Autor(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='n')||(opc=='N')){
  	printf("\n Autor NAO confirmado!");
  	return; //Volta para o menu principal
  }
  
  //Solicitar novos dados
  printf("\nDeseja alterar o Nome (S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc=='s')||(opc=='S')){
  	printf("\nDigite o novo Nome: ");
  	fflush(stdin); gets(autor.nome);
  }
  
  fpautor = fopen(AUTORES,"rb+");
  
  //Posicionar o ponteiro do arquivo no registro a ser alterado
  achou=0;
  while ((achou==0)&&(fread(&aut,sizeof(aut),1,fpautor)==1)){
  	if (aut.codigo==cod){
  		achou=1;
	  }
  }
  
  //Preciso voltar o ponteiro para o regitro anterior
  fseek(fpautor,-sizeof(autor),1);
  
  //Gravar autor alterado 
  fwrite(&autor,sizeof(autor),1,fpautor);

  //Fechar o arquivo
  fclose(fpautor);
  
  printf("\Autor alterado com sucesso.");
}//Fim alterarAutor()

void excluirCliente(){
  FILE *fpcliente, *fpclientenew;
  struct reg_cliente cliente;
  int cod;
  char opc;
  	
  //Solicitar o código do Cliente a ser excluído
  printf("\nDigite o Codigo do Cliente a ser Excluido: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o Cliente e Mostrar os dados
  cliente = buscarClientePeloCodigo(cod);
  if (cliente.codigo==-1){
  	printf("\nCliente NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do Cliente Localizado
  printf("\nCodigo: %i",cliente.codigo);
  printf("\nNome: %s",cliente.nome);
  printf("\nTelefone: %s",cliente.fone); 
  printf("\nE-mail: %s",cliente.email);
  
  //Pedir Confirmação
  printf("\nConfirna Exclusao do Cliente(S/N)? ");
  fflush(stdin); scanf("%c",&opc);  

  if ((opc=='n')||(opc=='N')){
  	printf("\n Exlusao NAO confirmada!");
  	return; //Volta para o menu principal
  }  
  
  //Se confirmado - Excluir o Cliente do Arquivo	
  //Criar um novo arquivo (Clientesnew.dat) e copiar todos os Clientes
  // menos o Cliente sendo Excluído
  fpcliente = fopen(CLIENTES,"rb");
  fpclientenew = fopen("Clientesnew.dat","wb");
  while (fread(&cliente,sizeof(cliente),1,fpcliente)==1){
  	if (cliente.codigo!=cod){
  		fwrite(&cliente,sizeof(cliente),1,fpclientenew);
	  }
  }
  fclose(fpcliente);
  fclose(fpclientenew);
  
  //Excluir o arquivo antigo Clientes.dat do sistema
  system("del Clientes.dat");
  
  //Renomear o novo arquivo (Clientesnew.dat) para (Clientes.dat)
  system("ren Clientesnew.dat Clientes.dat");
  
  printf("\nCliente excluido com sucesso.");
	
}//Fim excluirLivro()

void excluirAutor(){
  FILE *fpautor, *fpautornew;
  struct reg_autor autor;
  int cod;
  char opc;
  	
  //Solicitar o código do autor a ser excluído
  printf("\nDigite o Codigo do Autor a ser Excluido: ");
  fflush(stdin); scanf("%i",&cod);
  
  //Localizar o autor e mostrar os dados
  autor = buscarAutorPeloCodigo(cod);
  if (autor.codigo==-1){
  	printf("\nAutor NAO Localizado!");
  	return;  //Volta para o Menu Principal
  }
  
  //Mostrar dados do Autor Localizado
  printf("\nCodigo: %i",autor.codigo);
  printf("\nNome: %s",autor.nome);
  
  //Pedir Confirmação
  printf("\nConfirna Exclusao do Autor(S/N)? ");
  fflush(stdin); scanf("%c",&opc);  

  if ((opc=='n')||(opc=='N')){
  	printf("\n Exlusao NAO confirmada!");
  	return; //Volta para o menu principal
  }  
  
  //Se confirmado - Excluir o autor do Arquivo	
  //Criar um novo arquivo (Autornew.dat) e copiar todos os autores
  // menos o autor sendo Excluído
  fpautor = fopen(AUTORES,"rb");
  fpautornew = fopen("Autoresnew.dat","wb");
  while (fread(&autor,sizeof(autor),1,fpautor)==1){
  	if (autor.codigo!=cod){
  		fwrite(&autor,sizeof(autor),1,fpautornew);
	  }
  }
  fclose(fpautor);
  fclose(fpautornew);
  
  //Excluir o arquivo antigo Autores.dat do sistema
  system("del Autores.dat");
  
  //Renomear o novo arquivo (Autoresnew.dat) para (Autores.dat)
  system("ren Autoresnew.dat Autores.dat");
  
  printf("\nAutor excluido com sucesso.");
	
}//Fim excluirLivro()

void efetuarVenda(){
  FILE *fpvenda;
  struct reg_livro livro;
  struct reg_cliente cliente;
  struct reg_venda venda;
  int codcli, codliv;
  char opc;
   	
  printf("\nDigite o Codigo da Venda: ");
  fflush(stdin); scanf("%i",&venda.codigo);
  
  printf("\nDigite o Codigo do Cliente: ");
  fflush(stdin); scanf("%i",&codcli); 

  cliente = buscarClientePeloCodigo(codcli);
  
  if (cliente.codigo==-1){
  	printf("\nCliente Nao Localizado!");
  	return; //Retorna para o menu Principal
  }
  
  printf("\nCodigo: %i - Nome: %s",cliente.codigo,cliente.nome);
  
  printf("\nDigite o Codigo do Livro: ");
  fflush(stdin); scanf("%i",&codliv); 

  livro = buscarLivroPeloCodigo(codliv);
  
  if (livro.codigo==-1){
  	printf("\nLivro Nao Localizado!");
  	return; //Retorna para o menu Principal
  }
  
  printf("\nCodigo: %i - Titulo: %s",livro.codigo,livro.titulo);  
  
  printf("\nConfirma Cliente e Livro(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s')&&(opc!='S')){
  	printf("\nNao confirmado.");
  	return; //Retorna ao Menu principal
  }
  
  printf("\nDigite a Quantidade: ");
  fflush(stdin); scanf("%i",&venda.qtde);
  
  printf("\nDigite o Desconto: ");
  fflush(stdin); scanf("%f",&venda.desconto);
   
  printf("\nGravar Venda(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s')&&(opc!='S')){
  	printf("\nOperacao Cancelada!");
  	return; //Retorna ao Menu principal
  }  	

  venda.codcli = cliente.codigo;
  venda.codliv = livro.codigo;
  
  fpvenda = fopen(VENDAS,"ab");
  
  fwrite(&venda,sizeof(venda),1,fpvenda);	
  	
  fclose(fpvenda);
  
  printf("\nVenda registrada com sucesso.");
  	
}//Fim efetuarVenda()

void listarVendas(){
  FILE *fpvenda;
  struct reg_venda venda;
  
  //Abrir o Arquivo de Vendas
  fpvenda = fopen(VENDAS,"rb");
  
  //Ler registro por registro e mostrar na tela
  while (fread(&venda,sizeof(venda),1,fpvenda)==1){
  	printf("\nCodigo Venda: %i",venda.codigo);
	printf("\nCodigo Cliente: %i",venda.codcli);
	printf("\nCodigo Livro: %i",venda.codliv);
	printf("\nQuantidade: %i",venda.qtde);
	printf("\nDesconto: %5.2f",venda.desconto);
	printf("\n----------------------------------------");
  }
  //Fechar o Arquivo
  fclose(fpvenda);
	
}//Fim listarVendas()

void relatorioVendasDetalhado(){
  FILE *fpvenda;
  struct reg_venda venda;
  struct reg_cliente cliente;
  struct reg_livro livro;
  int vendaanterior;
  
  //Abrir o Arquivo de Vendas
  fpvenda = fopen(VENDAS,"rb");
  
  printf("\n         Relatorio de Vendas - Detalhado");
  printf("\nVenda Cliente                      Livro                        Preco  Desc  Qtde Cobrado");
  //Ler registro por registro e mostrar na tela
  vendaanterior = -1;
  while (fread(&venda,sizeof(venda),1,fpvenda)==1){
  	cliente = buscarClientePeloCodigo(venda.codcli);
  	livro = buscarLivroPeloCodigo(venda.codliv);
  	if (venda.codigo==vendaanterior){
		printf("\n                                   %-2i-%-25s %-6.2f %-6.2f %-4i %5.2f",livro.codigo,livro.titulo,livro.preco,venda.desconto,venda.qtde,(livro.preco*venda.qtde)-venda.desconto);
	}else{
  		printf("\n%-5i %-2i-%-25s %-2i-%-25s %-6.2f %-6.2f %-4i %5.2f",venda.codigo,cliente.codigo,cliente.nome,livro.codigo,livro.titulo,livro.preco,venda.desconto,venda.qtde,(livro.preco*venda.qtde)-venda.desconto);
  	}
  	vendaanterior = venda.codigo;
  }
  //Fechar o Arquivo
  fclose(fpvenda);
		
}//Fim relatorioVendasDetalhado()

void fecharVenda() {
  FILE *fpvenda;
  struct reg_venda venda;
  struct reg_cliente cliente;
  struct reg_livro livro;
  float precoAnterior = 0.0;  // Inicializando precoAnterior
  int vendaanterior;
  int codbuscar, achou = 0; 
  
  // Entrada de Dados - Pedir o Código da venda
  printf("\nDigite o Codigo da Venda p/ fechamento (caixa): ");
  fflush(stdin);
  scanf("%i", &codbuscar);
  
  // Abrir o Arquivo para Leitura
  fpvenda = fopen(VENDAS, "rb");
  
  if (fpvenda == NULL) {
    printf("\nErro ao abrir o arquivo de vendas.\n");
    return;
  }
  
  // Localizar e Mostrar a venda
  printf("\nFechamento da Venda: ");
  printf("\nVenda Cliente                      Livro                        Preco  Desc  Qtde Cobrado");
  vendaanterior = -1;
  
  while (fread(&venda, sizeof(venda), 1, fpvenda) == 1) {

    if (venda.codigo == codbuscar) {
      achou = 1;
      cliente = buscarClientePeloCodigo(venda.codcli);
      livro = buscarLivroPeloCodigo(venda.codliv);
      
      if (venda.codigo == vendaanterior) {  
		printf("\n                                   %-2i-%-25s %-6.2f %-6.2f %-4i %5.2f",livro.codigo,livro.titulo,livro.preco,venda.desconto,venda.qtde,(livro.preco*venda.qtde)-venda.desconto);
      } else {
    	printf("\n%-5i %-2i-%-25s %-2i-%-25s %-6.2f %-6.2f %-4i %5.2f",venda.codigo,cliente.codigo,cliente.nome,livro.codigo,livro.titulo,livro.preco,venda.desconto,venda.qtde,(livro.preco*venda.qtde)-venda.desconto);
      }
      
      vendaanterior = venda.codigo;
      precoAnterior += (livro.preco * venda.qtde) - venda.desconto;  // Soma ao total
    }
  }
  
  if (achou) {
    printf("\n\nTotal venda: R$ %.2f", precoAnterior);
  } else {
    printf("\nVenda Nao Localizada!");
  }
  
  // Fechar o Arquivo
  fclose(fpvenda);
}

void aplicarAumento() {
    FILE *fplivro;
    struct reg_livro livro;
    float porcentagemAumento;
    char opc;

    // Solicita a porcentagem de aumento
    printf("Informe a porcentagem de aumento para o preco dos livros: ");
    scanf("%f", &porcentagemAumento);

    // Limpa o buffer de entrada
    while ((getchar()) != '\n'); 

    // Confirma a operação
    printf("\nDeseja realmente alterar os precos dos livros? (S/N): ");
    scanf("%c", &opc);
  
    if (opc == 'n' || opc == 'N') {
        printf("\nOperação Cancelada.\n");
        return;
    }

    // Abre o arquivo para leitura e escrita
    fplivro = fopen(LIVROS, "rb+");
    if (fplivro == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê cada registro e aplica o aumento
    while (fread(&livro, sizeof(livro), 1, fplivro) == 1) {
        // Aplica o aumento no preço
        livro.preco += livro.preco * (porcentagemAumento / 100.0);

        // Volta o ponteiro do arquivo para o início do registro lido
        fseek(fplivro, -sizeof(livro), SEEK_CUR);

        // Escreve o registro atualizado com o novo preço
        fwrite(&livro, sizeof(livro), 1, fplivro);

        // Garante que os dados sejam gravados
        fflush(fplivro);
    }

    // Fecha o arquivo
    fclose(fplivro);

    printf("\nPrecos dos livros alterados com sucesso.\n");
}

void cadastrarAutor(){
  FILE *fpautor;
  struct reg_autor autor;
  char opc;
  
  //Entrada de Dados - Pedir os dados do Autor
  printf("\nDigite o Codigo:");
  fflush(stdin); scanf("%i",&autor.codigo);
  printf("Nome: "); 
  fflush(stdin); gets(autor.nome);  
  
  printf("\nGravar Autor?(S/N)");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s') && (opc!='S')){
  	printf("\nOperacao Cancelada!");
  	return; //Retorna ao menu principal
  }
  
  //Abrir o Arquivo
  fpautor = fopen(AUTORES,"ab");
  
  //Gravar o Registro
  fwrite(&autor,sizeof(autor),1,fpautor);
  
  //Fechar o Arquivo
  fclose(fpautor);
  
  printf("\nAutor gravado com sucesso.");
}

void listarAutores(){
  FILE *fpautor;
  struct reg_autor autor;
  	 	
  //Abrir o arquivo
  fpautor = fopen(AUTORES,"rb");
  
  printf("\nRelatorio Todos os Autores: ");
  printf("\nCodigo Nome                           ");
  //Ler registro por registro e mostar na tela
  while(fread(&autor,sizeof(autor),1,fpautor)==1){
	  printf("\n%-6i %-30s",autor.codigo,autor.nome);
  }
  //Fechar o Arquivo	
  fclose(fpautor);
}

void relacionarAutorLivro(){
  FILE *fprelacao;
  struct reg_livro livro;
  struct reg_autor autor;
  struct reg_RelAutorLivro relacao;
  int codautor, codliv;
  char opc;
   	
  //Entrada de Dados
  //Pedir o código da Operação - Relacionar Autor ao Livro
  printf("\nDigite o Codigo da relacao autor-livro: ");
  fflush(stdin); scanf("%i",&relacao.codrelacao);
  
  //Pedir o Codigo do Autor
  printf("\nDigite o Codigo do Autor: ");
  fflush(stdin); scanf("%i",&codautor); 
  //Localizar e Mostrar os dados do Autor e pedir confirmação
  autor = buscarAutorPeloCodigo(codautor);
  
  if (autor.codigo==-1){
  	printf("\nAutor Nao Localizado!");
  	return; //Retorna para o menu Principal
  }
  
  printf("\nCodigo: %i - Nome: %s",autor.codigo,autor.nome);
  
  //Pedir o Código do Livro
  printf("\nDigite o Codigo do Livro: ");
  fflush(stdin); scanf("%i",&codliv); 
  //Localizar e Mostrar os dados do Livro e pedir confirmação
  livro = buscarLivroPeloCodigo(codliv);
  
  if (livro.codigo==-1){
  	printf("\nLivro Nao Localizado!");
  	return; //Retorna para o menu Principal
  }
  
  printf("\nCodigo: %i - Titulo: %s",livro.codigo,livro.titulo);  
  
  printf("\nConfirma Autor e Livro(S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s')&&(opc!='S')){
  	printf("\nNao confirmado.");
  	return; //Retorna ao Menu principal
  }
  
  printf("\nGravar a relacao Autor-Livro (S/N)? ");
  fflush(stdin); scanf("%c",&opc);
  
  if ((opc!='s')&&(opc!='S')){
  	printf("\nOperacao Cancelada!");
  	return; //Retorna ao Menu principal
  }  	

  relacao.codautor = autor.codigo;
  relacao.codlivro = livro.codigo;
  
  fprelacao = fopen(RELACAO,"ab");
  
  fwrite(&relacao,sizeof(relacao),1,fprelacao);	
  	
  fclose(fprelacao);
  
  printf("\nOperacao registrada com sucesso.");
  	
}//Fim relacionarAutorLivro()

void relatorioAutoresLivros(){
  FILE *fprelacao, *fplivro;
  struct reg_autor autor;
  struct reg_livro livro;
  struct reg_RelAutorLivro relacao;
  int codlivanterior = -1;
 
  //Abrir o Arquivo
  fplivro = fopen(LIVROS, "rb");
  fprelacao = fopen(RELACAO,"rb");
  
  printf("\n         Relatorio de Livros com Autores            ");
  printf("\n\n Codigo Titulo                         Autor                                    Preco");
  
  while(fread(&livro, sizeof(livro), 1, fplivro) == 1) {
		while(fread(&relacao, sizeof(relacao), 1, fprelacao) == 1) {
			if(livro.codigo == relacao.codlivro) {
				autor = buscarAutorPeloCodigo(relacao.codautor);
				if(codlivanterior == livro.codigo) {
					printf("\n                                       %-40s", autor.nome);
				} 
				else {
					printf("\n %-6i %-30s %-40s %6.2f", livro.codigo, livro.titulo, autor.nome, livro.preco);
				}
				codlivanterior = livro.codigo;
			}
		}
		fseek(fprelacao, 0, 0); //voltando o ponteiro para o inicio do arquivo
	}
  //Fechar o Arquivo
  fclose(fprelacao);
  fclose(fplivro);
		
}//Fim relatorioAutoresLivros()

void consultarLivrosAutor() {
    FILE *fprelacao;
    struct reg_autor autor;
    struct reg_livro livro;
    struct reg_RelAutorLivro relacao;
    int codautor;
    int encontrouLivro = 0;

    // Solicitar o código do autor
    printf("\nDigite o Codigo do Autor: ");
    fflush(stdin); scanf("%i", &codautor);

    // Buscar e verificar se o autor existe
    autor = buscarAutorPeloCodigo(codautor);

    if (autor.codigo == -1) {
        printf("\nAutor Nao Localizado!\n");
        return; // Retorna ao menu principal
    }

    fprelacao = fopen(RELACAO, "rb");
    
    if (fprelacao == NULL) {
        printf("\nErro ao abrir o arquivo de relacao!\n");
        return;
    }

    // Exibir nome do autor

    //printf("\nLivros deste autor:");
	printf("\nAutor                         Livro(s)");
	printf("\n%-25s", autor.nome);
    // Ler cada relação do arquivo e exibir os livros do autor
    while (fread(&relacao, sizeof(relacao), 1, fprelacao) == 1) {
        if (relacao.codautor == codautor) {	
            // Buscar o livro correspondente ao codigo
            livro = buscarLivroPeloCodigo(relacao.codlivro);
            if (livro.codigo != -1) {
                //printf("\nCodigo: %i - Titulo: %s - Preco: %.2f", livro.codigo, livro.titulo, livro.preco);
                printf("                    %-8s",livro.titulo);
                encontrouLivro = 1;
            }
        }
    }

    // Verifica se encontrou algum livro
    if (!encontrouLivro) {
        printf("\nNenhum livro encontrado para este autor.");
    }
    fclose(fprelacao);

    printf("\nConsulta finalizada.\n");

}// Fim consultarLivrosAutor()

void relacionamentosLivrosAutores(){
	FILE *fprelacao;
    struct reg_autor autor;
    struct reg_livro livro;
    struct reg_RelAutorLivro relacao;
    
    
    //abrir arquivo de relação
    fprelacao = fopen(RELACAO, "rb");
    
    if (fprelacao == NULL) {
        printf("\nErro ao abrir o arquivo de relacao!\n");
        return;
    }
    
    //percorrer os registros do arquivo de relação e exibir os registros
    printf("\nCodigo Livro                       Autor                          Preco_Livro");
    while(fread(&relacao, sizeof(relacao), 1, fprelacao) == 1){
    	autor = buscarAutorPeloCodigo(relacao.codautor);
    	livro = buscarLivroPeloCodigo(relacao.codlivro);
    	printf("\n%-6i %-2i-%-25s %-2i-%-25s %-5.2f", relacao.codrelacao, livro.codigo, livro.titulo, autor.codigo, autor.nome, livro.preco);
	}
}

main(){
  int op;	
	
  do {
  	
	printf("\n\n\n");
  	printf("\n#############   Livraria Alma do Saber   #############");
  	printf("\n#                                                    #");
  	printf("\n# ------------- OPERACOES COM LIVROS ----------------#");
  	printf("\n# 1) Cadastrar Livro                                 #");
  	printf("\n# 2) Listar Todos os Livros                          #");
  	printf("\n#  221) Consultar Livro pelo Codigo                  #");
  	printf("\n#  222) Consultar Livro pelo Titulo                  #");
	printf("\n#  223) Consultar Livro por Palavra-Chave            #");
  	printf("\n# 3) Alterar Livro                                   #");
  	printf("\n# 4) Excluir Livro                                   #");
	printf("\n# 5) Aplicar Aumento nos Precos dos Livros           #");
	printf("\n#                                                    #");
	printf("\n# ----------- OPERACOES COM CLIENTES ----------------#");
  	printf("\n# 6) Cadastrar Cliente                               #");
  	printf("\n# 7) Listar Todos os Clientes                        #");
  	printf("\n# 8) Alterar Cliente                                 #");
	printf("\n# 9) Excluir Cliente                                 #");
	printf("\n#                                                    #");
	printf("\n# ------------ OPERACOES COM AUTORES ----------------#");
	printf("\n# 10) Cadastrar Autor                                #");
	printf("\n# 11) Listar Todos os Autores                        #");
	printf("\n# 12) Alterar Autor                                  #");
	printf("\n# 13) Excluir Autor                                  #");
	printf("\n# 14) Adicionar Autor ao Livro                       #");
	printf("\n# 15) Relatorio Autores-Livros                       #");
	printf("\n# 16) Exibir os Livros do Autor                      #");
	printf("\n# 17) Listar os relacionamentos de Livros e Autores  #");
	printf("\n#                                                    #");
	printf("\n# --------------------- VENDAS ----------------------#");
	printf("\n# 18) Registrar Venda                                #");
	printf("\n# 19) Fechar a venda                                 #");
	printf("\n# 20) Listar Vendas                                  #");
	printf("\n# 21) Relatorio de Vendas Detalhado                  #");
	printf("\n# 0) Sair                                            #");
  	printf("\n#                                                    #");
  	printf("\n# Opcao-> ");
	fflush(stdin); scanf("%i",&op);
	
	switch(op){
  	  case 1: //Cadastrar um novo Livro
		cadastrarLivro();
		break;
	  case 2: //Listar todos os Livros	
  		listarLivros();
  		break;	
  	  case 221: //Consultar Livro pelo Código
  	  	consultarPeloCodigo();
  	  	break;
  	  case 222: //Consultar Livro pelo Titulo
  	  	consultarPeloTitulo();
  	  	break;
  	  case 223: //Consultar Livro por Palavra-Chave no Titulo
  	  	consultarPalavraChaveTitulo();
  	  	break;  	  	
  	  case 3://Alterar dados de um Livro
  	  	alterarLivro();
  	  	break;
  	  case 4://Excluir um Livro
  	  	excluirLivro();
  	  	break; 
  	  case 5: //Aplicar Aumento - Preço dos Livros
  	    aplicarAumento();								  	  	
  	  case 6: //Cadastrar um novo Cliente
		cadastrarCliente();
		break;		
	  case 7: //Listar todos os Clientes	
  		listarClientes();
  		break;  		
  	  case 8: //Alterar Cliente
  	  	alterarCliente();
  	  	break;
  	 case 9: //Excluir Cliente
  	 	excluirCliente();
  		break;
  	  case 10: //Cadastrar Autor
  	  	cadastrarAutor();
  	  	break;  
  	  case 11: //Listar Autores
  	  	listarAutores();
  	  	break;		
  	 case 12: //Alterar Autor
  	  	alterarAutor();
  	  	break;
  	 case 13: //Excluir Autor
  	  	excluirAutor();
  	  	break;  	  	
  	  case 14: //Adicionar Autor(es) ao(s) Livro(s)
  	  	relacionarAutorLivro();
  	  	break;
  	  case 15: //Relatorio autores-livros
  	  	relatorioAutoresLivros();
  	  	break;
  	 case 16: //Consultar livros do autor
  	    consultarLivrosAutor();
  	  	break;
  	 case 17: //relacionamentosLivrosAutores
  	 	relacionamentosLivrosAutores();
  		break;				
  	  case 18: //Efetuar Venda
  	  	efetuarVenda();
  	  	break;
  	  case 19: //Fechar a venda (caixa)
  	  	fecharVenda();
  	  	break;
  	  case 20: //Listar Vendas
  	    listarVendas();
  	    break;
  	  case 21: //Relatorio de Vendas Detalhado
  	  	relatorioVendasDetalhado();
  	  	break;
	}
	
		
  }while (op!=0);
  
  
}//Fim main()