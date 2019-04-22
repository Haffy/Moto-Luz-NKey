/* Deuslirio Junior
 * 
 * O programa parte da ideia de que s�o duas motos competindo, ent�o nao tem como andar de "r�" e se tentar vai cair da moto.
 * As dificuldades do jogo s�o as paredes, o oponente, a velocidade e voc� mesmo.
 * para funcionar deve-se colocar -lncurses na op��o Construir/Definir_comandos_de_constru��o/construir.
*/

#include <stdio.h> //O programa funciona sem esta biblioteca, mas por padr�o, incluimos ela
#include <stdlib.h>//Para usar comandos como sleep() 1 segundo == 1;
#include <curses.h>//Usada para dar cor, e para que a "moto" continue andando clicando na tecla apenas uma vez
#include <time.h>//Usamos a time.h para pegar valores randomicos e tomar decis�es a partira da�
#include <unistd.h>//Necess�ria para usar o comando usleep() 1 segundo == 1000000
	int linhap1,colunap1,ud,cada27,linhap2,colunap2,finalizar=0,pontp1=0,pontp2=0,voltarmenu=0;
    char arena[23][79],cp1,cp2,menu[23][79]={{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ','@',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','@',' ',' ',' ',' ',' ',' ','@',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ','@',' ',' ',' ',' ',' ','@',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ','@',' ',' ',' ',' ','@',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ','@',' ',' ',' ','@',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@',' ',' ','@',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@',' ','@',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ','@','@',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ','@',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#','#','#','#','#','#','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','-','-','>','1',' ','P','L','A','Y','E','R','<','-','-',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','V','E','R','S','U','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','A','I','R',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
				};
/*	linhap1 e colunap1 s�o as coordenadas do player 1 na matriz arena
	linhap2 e colunap2 s�o as coordenadas do 2� player na matriz arena
	ud � a dire��o inicial do advers�rio virtual, ela s� � alterada quando ele deve virar para nao bater
	cada27: a cada "passo" do advers�rio virtual essa vari�vel recebe ela +1 e se esse valor for multiplo de 27 a dire��o a dire��o muda randomicamente
	finalizar: quando essa variavel tiver valor 1 o programa ir� fechar
	pontp1 e pontp2 s�o as pontua��es, se o 2� player bater em algo, pontp1 recebera +1, se o player 1 bater em algo, pontp2 recebera +1
	voltarmenu: se essa vari�vel tiver valor 1 terminar� o modo de jogo(1 player ou versus) e voltar� ao menu
	arena � a matriz onde o jogo acontece
	cp1 e cp2 s�o os pr�ximos caracteres para o player 1 e para o 2� player respectivamente, � usado para saber se o os jogadores bater�o em e no caso do virtual se ele deve virar
	menu � matriz exclusiva para o menu
	*/
void andar(int a);
void andarcpu(int a);
void print(char matriz[23][79]);
void campo();
void one();
void two();
void cima_baixo();
void direita_esquerda();
int escolher(int a);
int mostrarplacar();
void printplacar(char matriz[8][55]);

int main(){//Ir� iniciar a curses.h e as cores
	int escolha; //vai receber a teclar s� ira fazer algo se a tecla for W ou S ou enter
	initscr(); //INICIA A CURSES, SEM ESSE COMANDO NADA DA CERTO
	start_color();// Ativa cores
	init_pair(1,COLOR_RED, COLOR_RED);//inicia o par de cores 1 (fonte e fundo vermelho);
	init_pair(2,COLOR_BLUE, COLOR_BLUE);//inicia o par de cores 2 (fonte e fundo azul);
	init_pair(3,COLOR_GREEN, COLOR_GREEN);//inicia o par de cores 3 (fonte e fundo verde);
	init_pair(4,COLOR_WHITE, COLOR_BLACK);//inicia o par de cores 4 (fonte branca e fundo preto);
	print(menu); //imprime a matriz menu
	while(1){ //looping enfinito at� que seja "quebrado"
		escolha=getch();//escolha recebe a tecla clicada
		escolher(escolha);//chama a fun��o escolher com escolha como par�metro
		print(menu); //imprime a a matriz menu
		if (finalizar==1){ //Dentro da fun��o escolher esta variavel pode ter recebido 1 se isso ocorrer quer dizer que o programa deve ser finalizado
			break;
		}
	}
	endwin();	//FINALIZA A CURSES
	return 0;
}
void andar(int a){	//Essa fun��o ir� conferir se foi o player 1 ou o player 2 que clicou e fazer o que cada quis fazer.
	if(a==119){           //QUANDO "W" FOR PRESSIONADO, A lINHA IR� DIMINUIR PARA O PLAYER 1 IR PARA CIMA
		cp1=arena[linhap1-1][colunap1]; //A vari�vel cp1 recebe o caracter que estava naquela posi��o antes do jogador(vermelho)
		if (arena[linhap1-1][colunap1]== ' '){
			linhap1=linhap1-1; //A linhap1 diminuiu, assim a posi��o do jogador(vermelho) subiu em rela��o a anterior
		}
	}
	if(a==115){           //QUANDO "S" FOR PRESSIONADO, A LINHA IR� AUMENTAR PARA O PLAYER 1 PARA IR PARA BAIXO
		cp1=arena[linhap1+1][colunap1]; //A vari�vel cp1 recebe o caracter que estava naquela posi��o antes do jogador(vermelho)
		if (arena[linhap1+1][colunap1]== ' '){
			linhap1=linhap1+1; //A linhap1 aumentou, assim a posi��o do jogador(vermelho) desceu em rela��o a anterior
		}
	}
	if(a==97){            //QUANDO "A" FOR PRESSIONADO, A COLUNA IR� DIMINUIR PARA O PLAYER 1 IR PARA ESQUERDA
		cp1=arena[linhap1][colunap1-1]; //A vari�vel cp1 recebe o caracter que estava naquela posi��o antes do jogador(vermelho)
		if (arena[linhap1][colunap1-1]== ' '){
			colunap1=colunap1-1; //A colunap1 diminuiu, assim a posi��o do jogador(vermelho) virou a esquerda em rela��o a anterior
		}
	}
	if(a==100){           //QUANDO "D" FOR PRESSIONADO, A COLUNA IR� AUMENTAR PARA O PLAYER 1 IR PARA DIREITA
		cp1=arena[linhap1][colunap1+1]; //A vari�vel cp1 recebe o caracter que estava naquela posi��o antes do jogador(vermelho)
		if (arena[linhap1][colunap1+1]== ' '){
			colunap1=colunap1+1; //A colunap1 aumentou, assim a posi��o do jogador(vermelho) virou a direita em rela��o a anterior
		}
	}
	if(a==KEY_UP){        //QUANDO "CIMA" FOR PRESSIONADO,A lINHA IR� DIMINUIR PARA O PLAYER 2 IR PARA CIMA
		cp2=arena[linhap2-1][colunap2]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
		if (arena[linhap2-1][colunap2]== ' '){
			linhap2=linhap2-1; //A linhap2 diminuiu, assim a posi��o do jogador(azul) subiu em rela��o a anterior
		}
	}
	if(a==KEY_DOWN){      //QUANDO "BAIXO" FOR PRESSIONADO, A LINHA IR� AUMENTAR PARA O PLAYER 2 PARA IR PARA BAIXO
		cp2=arena[linhap2+1][colunap2]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
		if (arena[linhap2+1][colunap2]== ' '){
			linhap2=linhap2+1; //A linhap2 aumentou, assim a posi��o do jogador(azul) desceu em rela��o a anterior
		}
	}
	if(a==KEY_LEFT){      //QUANDO "ESQUERDA" FOR PRESSIONADO, A COLUNA IR� DIMINUIR PARA O PLAYER 2 IR PARA ESQUERDA
		cp2=arena[linhap2][colunap2-1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
		if (arena[linhap2][colunap2-1]== ' '){
			colunap2=colunap2-1; //A colunap2 diminuiu, assim a posi��o do jogador(azul) virou a esquerda em rela��o a anterior
		}
	}
	if(a==KEY_RIGHT){     //QUANDO "DIREITA" FOR PRESSIONADO, A COLUNA IR� AUMENTAR PARA O PLAYER 1 IR PARA DIREITA
		cp2=arena[linhap2][colunap2+1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
		if (arena[linhap2][colunap2+1]== ' '){
			colunap2=colunap2+1; //A colunap2 aumentou, assim a posi��o do jogador(azul) virou a direita em rela��o a anterior
		}
	}
	arena[linhap1][colunap1]='#'; //A arena na posi��o onde o jogador vermelho est� recebe # pois esse � o caracter que com a fun��o print fica vermelho
	arena[linhap2][colunap2]='@'; //A arena na posi��o onde o jogador azul est� recebe @ pois esse � o caracter que com a fun��o print fica azul
}
void andarcpu(int a){ //Essa fun��o � usada par ao advers�rio virtual andar
	int ran; 					//variavel que ira receber um valor randomico
	cada27=cada27+1; 			//cada 27 recebe ela +1
	srand(time(NULL));			//ativa a fun��o rand de acordo com o hor�rio
	ran=rand()%2; 				//ran recebe um valor randomico entre 2 possibilidades, 0 ou 1
	if((cada27%27)== 0){//Se o valor de cada27 for multiplo de 27 ent�o;
		if (ran==0){ //Se ran for 0 decida de vire para esquerda ou para direita
			direita_esquerda(); //Chama a fun��o direita_esquerda
		}
		else{ //se ran n�o for 0 decida de vire para cima ou para baixo
			cima_baixo(); 		//chama a fun��o cima_baixo
		}
	}
	else{ // se cada27 n�o for multiplo de 27 ent�o:
		if(a==KEY_UP){
			cp2=arena[linhap2-1][colunap2];     //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			if (arena[linhap2-1][colunap2]== ' '){ //Se o pr�ximo caracter for "espa�o" ent�o:
				linhap2=linhap2-1; //A linhap2 diminuiu, assim a posi��o do jogador(azul) subiu em rela��o a anterior
			}
			else{	//Se o pr�ximo caracter for diferente de "espa�o" ent�o:
				direita_esquerda(); //decida se vire a direita ou esquerda porque se continuar na mesma dire��o ir� bater
			}
		}
		if(a==KEY_DOWN){
			cp2=arena[linhap2+1][colunap2]; 	//A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			if (arena[linhap2+1][colunap2]== ' '){ //Se o pr�ximo caracter for "espa�o" ent�o:
				linhap2=linhap2+1; //A linhap2 aumentou, assim a posi��o do jogador(azul) desceu em rela��o a anterior
			}
			else{ 	//Se o pr�ximo caracter for diferente de "espa�o" ent�o:
				direita_esquerda(); //decida se vire a direita ou esquerda porque se continuar na mesma dire��o ir� bater
			}
		}
		if(a==KEY_LEFT){
			cp2=arena[linhap2][colunap2-1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			if (arena[linhap2][colunap2-1]== ' '){ //Se o pr�ximo caracter for "espa�o" ent�o:
				colunap2=colunap2-1; //A colunap2 diminuiu, assim a posi��o do jogador(azul) virou a esquerda em rela��o a anterior
			}
			else{	//Se o pr�ximo caracter for diferente de "espa�o" ent�o:
				cima_baixo(); //decida se para cima ou para baixo porque se continuar na mesma dire��o ir� bater
			}
		}
		if(a==KEY_RIGHT){
			cp2=arena[linhap2][colunap2+1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			if (arena[linhap2][colunap2+1]== ' '){ //Se o pr�ximo caracter for "espa�o" ent�o:
				colunap2=colunap2+1; //A colunap2 aumentou, assim a posi��o do jogador(azul) virou a direita em rela��o a anterior
			}
			else{ //Se o pr�ximo caracter for diferente de "espa�o" ent�o:
				cima_baixo();	//decida se para cima ou para baixo porque se continuar na mesma dire��o ir� bater
			}
		}
		arena[linhap2][colunap2]='@'; //A arena na posi��o onde o jogador azul est� recebe @ pois esse � o caracter que com a fun��o print fica azul
	}
}
void print(char matriz[23][79]){ //Recebe a matriz e imprime ela na tela com as cores
	int i,j;
	move(0,0);//Comando da curses.h faz o cursor "lugar onde ser� digitado ou escrito" ir para a coluna 0, linha 0 da tela
	for(i=0;i<23;i++){
		for(j=0;j<79;j++){
			switch(matriz[i][j]){
				case '#':attron(COLOR_PAIR(1)); //Caso o caracter que esteja na posi��o [i][j] seja # usa-se um Comando da curses:Liga o par de cores 1 definido na main(neste caso, fonte vermelha e fundo vermelho)
						printw("%c",matriz[i][j]); //Imprime usando printw, equivalente a printf na curses
						attroff(COLOR_PAIR(1)); //Desliga o par de cores 1
				break;
				case '@':attron(COLOR_PAIR(2)); //Caso o caracter que esteja na posi��o [i][j] seja @ usa-se um Comando da curses:Liga o par de cores 2 definido na main(neste caso, fonte azul e fundo azul)
						printw("%c",matriz[i][j]);//Imprime usando printw, equivalente a printf na curses
						attroff(COLOR_PAIR(2));//Desliga o par de cores 2
				break;
				case '|':attron(COLOR_PAIR(3)); //Caso o caracter que esteja na posi��o [i][j] seja | usa-se um Comando da curses:Liga o par de cores 3 definido na main(neste caso, fonte verde e fundo verde)
						printw("%c",matriz[i][j]);//Imprime usando printw, equivalente a printf na curses
						attroff(COLOR_PAIR(3));//Desliga o par de cores 3
				break;
				default:
						attron(COLOR_PAIR(4)); //se n�o for # ou @ ou | ent�o ligar o par de cores 4(neste caso fonte branca e fundo preto)
						printw("%c",matriz[i][j]); //Imprime usando printw, equivalente a printf na curses
						attroff(COLOR_PAIR(4));//desliga o par de cores 4
            }
		}
		printw("\n");
	}
	refresh(); //Comando da curses para atualizar a tela
}
void campo(){ //Essa fun��o coloca as paredes na fun��o e declara onde cada "moto" come�a o jogo
	int i,j;
	linhap1=11; //Declara em que linha o jogador(vermelho) come�a
	colunap1=18; //Declara em que coluna o jogador(vermelho) come�a
	linhap2=11; //Declara em que linha o jogador(azul) come�a
	colunap2=60; //Declara em que coluna o jogador(azul) come�a
	for(i=0;i<23;i++){
		for(j=0;j<79;j++){//DESENHAR AS BORDAS
			arena[i][j]=' '; //Todos os elementos da amtriz recebem "espa�o" assim a matriz fica limpa
			arena[0][j]='|'; //Todos os elementos da linha 0 recebem | onde ser� a parede de cima
			arena[22][j]='|'; //Todos os elementos da linha 22 recebem | onde ser� a parede de baixo
			arena[i][0]='|'; //Todos os elementos da coluna 0 recebem | onde ser� a parede da esquerda
			arena[i][78]= '|'; //Todos os elementos da coluna 78 recebem | onde ser� a parede da direita
		}
	}
}
void one(){ //Essa fun��o � o modo 1 player
	int  key,keyp1=100,keyp2=KEY_LEFT;
/*	key � a vari�vel que recebe o clique e v� se a tecla clicada � W ou A ou S ou D
	keyp1 � a tecla para o player 1 ela s� recebe um valor diferente do inicial quando W ou A ou S ou D for digitado
	keyp2 � a tecla para o player 2 ela n�o recebe um valor do teclado nessa op��o pois � apenas 1 jogador real
	 */
	ud=KEY_LEFT;// Para o 2� player come�ar o jogo indo para a esquerda come�ar
	noecho();//Comando da Curses para que a tecla digitada n�o seja exibida na tela
	curs_set(0); //Comando da Curses para que o cursor n�o fique piscando, desta forma ele fica invisivel
	nodelay(stdscr,true); //Comando da Curses, faz com que o programa nao fique parado esperando a entra pelo teclado, dentro do looping ele vai pedir uma tecla, se nada for digitado ele recome�a o looping
	keypad(stdscr,true); // Faz com que teclas especiais sejam aceitas utilizamos para que o programa aceite a entrada das "setas"
    campo(); //Chama a fun��o campo para desenhar as bordas
    while(1){ //Looping infinito at� que tenha um break
		keyp2=ud; //O jogador(azul) ira se movimentar dependendo do valor da ud
		usleep(35000); //Faz o looping ter um delay de 0.035 segundos
        key=getch();//RECEBER A TECLA CLICADA
        if (key==119||key==115||key==97||key==100){ //Se a tecla for W(119), S(115), A(97), D(100) a tecla de dire��o do player 1 recebe a tecla digitada se n�o for, nada acontece e o looping continua mesmo se nada for clicado
			keyp1=key;
		}
        andar(keyp1); //Chama a fun��o andar com a dire��o do player 1 como par�metro
        andarcpu(keyp2);//Chama a fun��o andarcpu com a dire��o do 2� player como par�metro
        move(0,0);//volta o cursor para a coluna 0 linha 0 da tela
        if (cp1== '|' ||cp1== '#'||cp1== '@'){//SE o player 1 BATER NAS BORDAS OU NO PROPRIO "CORPO" ENT�O:
			refresh(); //Atualiza a tela
			echo();//O que for digitado passa a ser visto
			nodelay(stdscr,false); //Sempre vai esperar algo ser digitado quando for pedido
			pontp2++; //Pontua��o do 2� player aumenta pois o player 1 bateu
			keyp1=100; //se a fun��o recome�ar o player 1 vai come�ar indo para a direita
			ud=KEY_LEFT; //se a fun��o recome�ar o 2� player vai come�ar indo para a esquerda
			mostrarplacar(); //chama a fun��o mostraplacar para que o placar seja exibido
			if (voltarmenu==1){ // se dentro da fun��o mostrarplacar o voltarmenu receber 1 ent�o
				voltarmenu=0; //voltarmenu recebe 0 novamente e
				break; //O modo 1 player � terminado
			}
		}
		if (cp2== '|' ||cp2== '#'||cp2== '@'){  //SE o player 2 BATER NAS BORDAS OU NO PROPRIO "CORPO" ENT�O:
			refresh(); //Atualiza a tela
			echo(); //O que for digitado passa a ser visto
			nodelay(stdscr,false); //Sempre vai esperar algo ser digitado quando for pedido
			pontp1++; //Pontua��o do player 1 aumenta pois o player 2 bateu
			keyp1=100; //se a fun��o recome�ar o player 1 vai come�ar indo para a direita
			ud=KEY_LEFT; //se a fun��o recome�ar o player 1 vai come�ar indo para a direita
			mostrarplacar(); //chama a fun��o mostraplacar para que o placar seja exibido
			if (voltarmenu==1){ // se dentro da fun��o mostrarplacar o voltarmenu receber 1 ent�o
				voltarmenu=0; //voltarmenu recebe 0 novamente e
				break; //O modo 1 player � terminado
			}
		}
		print(arena);	//Chama a fun��o print com a matriz arena como par�mentro para exibir a tela a cada final de looping
	}
}
void two(){ //Essa fun��o � o modo Versus
int  key,keyp1=100,keyp2=KEY_LEFT;
	noecho();//Comando da Curses para que a tecla digitada n�o seja exibida na tela
	curs_set(0); //Comando da Curses para que o cursor n�o fique piscando, desta forma ele fica invisivel
	nodelay(stdscr,true); //Comando da Curses, faz com que o programa nao fique parado esperando a entra pelo teclado, dentro do looping ele vai pedir uma tecla, se nada for digitado ele recome�a o looping
	keypad(stdscr,true); // Faz com que teclas especiais sejam aceitas utilizamos para que o programa aceite a entrada das "setas"
    campo(); //Chama a fun��o campo para desenhar as bordas
    while(1){
		usleep (35000);  //Faz o looping ter um delay de 0.035 segundos
        key=getch(); //RECEBER A TECLA CLICADA
        if (key==119||key==115||key==97||key==100){ //Se a tecla for W(119), S(115), A(97), D(100) a tecla de dire��o do player 1 recebe a tecla digitada se n�o for, nada acontece e o looping continua mesmo se nada for clicado
			keyp1=key;
		}
		if (key==KEY_UP||key==KEY_DOWN||key==KEY_LEFT||key==KEY_RIGHT){//Se a tecla for Cima(KEY_UP), Baixo(KEY__DOWN), Esquerda(KEY_LEFT), Direita(KEY_RIGHT) a tecla de dire��o do player 1 recebe a tecla digitada se n�o for, nada acontece e o looping continua mesmo se nada for clicado
			keyp2=key;
		}
        andar(keyp1); //Chama a fun��o andar com a dire��o do player 1 como par�metro
        andar(keyp2); //Chama a fun��o andar com a dire��o do player 2 como par�metro
        move(0,0); //volta o cursor para a coluna 0, linha 0 da tela
		 if (cp1== '|' ||cp1== '#'||cp1== '@'){//SE o player 1 BATER NAS BORDAS OU NO PROPRIO "CORPO" ENT�O:
			refresh(); //Atualiza a tela
			echo();//O que for digitado passa a ser visto
			nodelay(stdscr,false); //Sempre vai esperar algo ser digitado quando for pedido
			pontp2++; //Pontua��o do 2� player aumenta pois o player 1 bateu
			keyp1=100; //se a fun��o recome�ar o player 1 vai come�ar indo para a direita
			keyp2=KEY_LEFT; //se a fun��o recome�ar o 2� player vai come�ar indo para a esquerda
			mostrarplacar(); //chama a fun��o mostraplacar para que o placar seja exibido
			if (voltarmenu==1){ // se dentro da fun��o mostrarplacar o voltarmenu receber 1 ent�o
				voltarmenu=0; //voltarmenu recebe 0 novamente e
				break; //O modo versus � terminado
			}
		}
		else if (cp2== '|' ||cp2== '#'||cp2== '@'){//SE o player 1 BATER NAS BORDAS OU NO PROPRIO "CORPO" ENT�O:
			refresh(); //Atualiza a tela
			echo();//O que for digitado passa a ser visto
			nodelay(stdscr,false); //Sempre vai esperar algo ser digitado quando for pedido
			pontp1++; //Pontua��o do player 1 aumenta pois o 2 player bateu
			keyp1=100; //se a fun��o recome�ar o player 1 vai come�ar indo para a direita
			keyp2=KEY_LEFT; //se a fun��o recome�ar o 2� player vai come�ar indo para a esquerda
			mostrarplacar(); //chama a fun��o mostraplacar para que o placar seja exibido
			if (voltarmenu==1){ // se dentro da fun��o mostrarplacar o voltarmenu receber 1 ent�o
				voltarmenu=0; //voltarmenu recebe 0 novamente e
				break; //O modo versus � terminado
			}
		}
		print(arena); //Chama a fun��o print com a matriz arena como par�mentro para exibir a tela a cada final de looping
	}
}
void cima_baixo(){ //Essa fun��o ir� decidir randomicamente se o advers�rio virtual ir� subir ou descer
	int ran;			//variavel que ira receber um valor randomico
	srand(time(NULL));  //ativa a fun��o rand de acordo com o hor�rio
	ran=rand()%2;		//ran recebe um valor randomico entre 2 possibilidades, 0 ou 1
	if(ran==0){
		if ((arena[linhap2+2][colunap2] == ' ' && arena[linhap2+1][colunap2] == ' ')||arena[linhap2+1][colunap2] == ' '){
			cp2=arena[linhap2+1][colunap2];  //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			linhap2=linhap2+1; //Desce
			ud=KEY_DOWN;
		}
		else if ((arena[linhap2-2][colunap2] == ' ' && arena[linhap2-1][colunap2] == ' ')||arena[linhap2-1][colunap2] == ' '){
			cp2=arena[linhap2-1][colunap2]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			linhap2=linhap2-1;//Sobe
			ud=KEY_UP;
		}
	}
	else{
		if ((arena[linhap2-2][colunap2] == ' ' && arena[linhap2-1][colunap2] == ' ')||arena[linhap2-1][colunap2] == ' '){
			cp2=arena[linhap2-1][colunap2]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			linhap2=linhap2-1; //Sobe
			ud=KEY_UP;
		}
		else if ((arena[linhap2+2][colunap2] == ' ' && arena[linhap2+1][colunap2] == ' ')||arena[linhap2+1][colunap2] == ' '){
			cp2=arena[linhap2+1][colunap2]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			linhap2=linhap2+1; //Desce
			ud=KEY_DOWN;
		}
	}
}
void direita_esquerda(){ //Essa fun��o ir� decidir randomicamente se o advers�rio virtual ir� virar para a esquerda ou direita
	int ran;
	srand(time(NULL));
	ran=rand()%2;
	if(ran==0){
		if ((arena[linhap2][colunap2+2] == ' ' && arena[linhap2][colunap2+1] == ' ')||arena[linhap2][colunap2+1] == ' '){
			cp2=arena[linhap2][colunap2+1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			colunap2=colunap2+1;//Direita
			ud=KEY_RIGHT;
		}
		else if ((arena[linhap2][colunap2-2] == ' ' && arena[linhap2][colunap2-1] == ' ')||arena[linhap2][colunap2-1] == ' '){
			cp2=arena[linhap2][colunap2-1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			colunap2=colunap2-1;//Esquerda
			ud=KEY_LEFT;
		}
	}
	else{
		if ((arena[linhap2][colunap2-2] == ' ' && arena[linhap2][colunap2-1] == ' ')||arena[linhap2][colunap2-1] == ' '){
			cp2=arena[linhap2][colunap2-1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			colunap2=colunap2-1;//Esquerda
			ud=KEY_LEFT;
		}
		else if ((arena[linhap2][colunap2+2] == ' ' && arena[linhap2][colunap2+1] == ' ')||arena[linhap2][colunap2+1] == ' '){
			cp2=arena[linhap2][colunap2+1]; //A vari�vel cp2 recebe o caracter que estava naquela posi��o antes do jogador(azul)
			colunap2=colunap2+1; //Direita
			ud=KEY_RIGHT;
		}
	}
}
int escolher(int a){ //Essa fun��o permite a escolha do modo de jogo no menu
	int i,j;
	if (a==13 || a==10){ //se a tecla clicada for enter ent�o o programa ira ver em que linha da matriz menu est� o caracter ">" que faz parte da seta de escolha
				for(j=0;j<79;j++){
					if (menu[18][28]=='>'){ //se o caracter ">" estiver na linha 18 isso quer dizer que esta na linha "1 Player"
						one(); //Chama a fun��o do modo jogar sozinho
						break;
					}
					else if (menu[19][28]=='>'){  //se o caracter ">" estiver na linha 19 isso quer dizer que esta na linha "Versus"
						two(); //Chama a fun��o do modo jogar contra outra pessoa
						break;
					}
					else if (menu[20][28]=='>'){ //se o caracter ">" estiver na linha 20 isso quer dizer que esta na linha "Sair"
						finalizar=1; //Uma condi��o na main far� o programa acabar
						break;
					}
				}
		}
	else if 	(a==115){// se a tecla n�o for enter e for s
		for(i=19;i>=18;i--){ //esse for ir� percorrer a matriz de baixo para cima
			for(j=79;j>=1;j--){
				if (menu[i][j]== '-'||menu[i][j]== '>'||menu[i][j]== '<'){ //se o caracter na posi��o [i][j] for "-" ">" "<" ent�o
					menu[i+1][j] = menu[i][j]; //o caracter � copiado para a linha de baixo e
					menu[i][j]=' ';	//o caracter � removido de onde ele estava
					if(menu[i][j]=='-' && j<30){ //se o caracter na posi��o[][] for "-" ou seja o ultimo caracter que deve ser movido da linha ent�o:
						return 0;   //volte para o looping da main
					}
				}
			}
		}
	}
	else if 	(a==119){  // se a tecla n�o for enter e for W
		for(i=19;i<=20;i++){  //esse for ir� percorrer a matriz de cima para baixo
			for(j=0;j<79;j++){
				if (menu[i][j]== '-'||menu[i][j]== '>'||menu[i][j]== '<'){ //se o caracter na posi��o [i][j] for "-" ">" "<" ent�o
						menu[i-1][j] = menu[i][j]; //o caracter � copiado para a linha de cima e
						menu[i][j]=' ';		//o caracter � removido de onde ele estava
				}
			}
		}
	}
	return 0;
}
int mostrarplacar(){ //Essa fun��o desenha o placar
	char placar[8][55],sim;
	int i,j;
	sleep(1); //S� ir� mostrar o placar depois de 1 segundo
	for(i=0;i<8;i++){
		for(j=0;j<55;j++){//DESENHAR AS BORDAS
			placar[i][j]=' '; //Todos os elementos da matriz recebem "espa�o"
			if (j>=24 && j<=36){
				placar[0][j]='#'; //Todos elementos da matriz da posi��o [0][24] at� [0][36] recebem #
				placar[7][j]='#'; //Todos elementos da matriz da posi��o [7][24] at� [7][36] recebem #
			}
			if (i<8){
				placar[i][24]='#'; //elementos da matriz da posi��o [0][24] at� [7][24] recebem #
				placar[i][36]= '#'; //elementos da matriz da posi��o [0][36] at� [7][36] recebem #
				placar[i][42]='@'; //elementos da matriz da posi��o [0][42] at� [7][42] recebem @
				placar[i][54]= '@'; //elementos da matriz da posi��o [0][54] at� [7][54] recebem @
			}
			if (j>=42 && j<=54){
				placar[0][j]='@'; //Todos elementos da matriz da posi��o [0][42] at� [0][54] recebem @
				placar[7][j]='@'; //Todos elementos da matriz da posi��o [7][42] at� [7][54] recebem @
			}
		}
	}
	printplacar(placar); //Chama a fun��o printplacar com a matriz placar como par�metro
	printw("Digite ""s"" para jogar neste modo novamente: "); //Imprime a mensagem com printw que � equivalente a printf
	keypad(stdscr,false);//desativa a entrada de setas
	scanw("%c",&sim); //Escaneia o valor com scanw que � equivalente a scanf
	keypad(stdscr,true);//ativa a entrada de setas
	nodelay(stdscr,true); //N�o espera valores
	if (sim=='s'){// se o que foi digitado come�ar com "s" ent�o:
		campo(); //Reinicia o campo pois vai come�ar uma nova partida
	}
	else{ //se o que foi digitado come�ar com letra diferente de s ent�o:
		pontp1=pontp2=0; //A pontua��o � zerada pois o jogador vai trocar de modo de jogo, sair, ou recome�ar com o placar 0x0
		voltarmenu=1; //Com esse valor o menu � reaberto
	}
	return 0;
}
void printplacar(char matriz[8][55]){ //Essa fun��o ir� imprimir a matriz placar
	int i,j;
	char vermelho[9]="Vermelho",azul[5]="Azul"; // Essas variaveis ir�o ser impressas no meio da matriz no lugar onde seriam outros elementos
	clear(); //limpa a tela
	move(0,0); //move o cursor para a coluna 0 e linha 0 da tela
	for(i=0;i<8;i++){
		for(j=0;j<55;j++){
			if (i==1 && j==27){
				printw("%s",vermelho); //quando a posi��o da matriz for [1][27] ir� imprimir a palavra vermelho
				j=35;//E o valor da coluna ira pular para 35 para nao imprimir o as posi�oes [1][28],[1][29]...
			}
			if (i==1 && j==46){
				printw("%s",azul); //quando a posi��o da matriz for [1][46] ir� imprimir a palavra vermelho
				j=50;//E o valor da coluna ira pular para 50 para nao imprimir o as posi�oes [1][47],[1][48]...
			}
			if (i==5 && j==30){
				if (pontp1>9){ //na linha 5 se pontp1 for maior ou igual a 10 ou seja ir� ocupar dois espa�os na tela ent�o ter� que pular uma coluna
					j=31;
				}
				printw("%d",pontp1); //imprima pontp1 onde em [5][30]
			}
			else if (i==5 && j==48){
				if (pontp2>9){//na linha 5 se pontp2 for maior ou igual a 10 ou seja ir� ocupar dois espa�os na tela ent�o ter� que pular uma coluna
					j=49;
				}
				printw("%d",pontp2); //imprima pontp1 onde em [5][48]
			}
			else
			switch(matriz[i][j]){
			case '#':attron(COLOR_PAIR(1)); //Caso o caracter que esteja na posi��o [i][j] seja # usa-se um Comando da curses:Liga o par de cores 1 definido na main(neste caso, fonte vermelha e fundo vermelho)
				printw("%c",matriz[i][j]); //Imprime usando printw, equivalente a printf na curses
				attroff(COLOR_PAIR(1)); //Desliga o par de cores 1
			break;
			case '@':attron(COLOR_PAIR(2)); //Caso o caracter que esteja na posi��o [i][j] seja @ usa-se um Comando da curses:Liga o par de cores 2 definido na main(neste caso, fonte azul e fundo azul)
				printw("%c",matriz[i][j]);//Imprime usando printw, equivalente a printf na curses
						attroff(COLOR_PAIR(2));//Desliga o par de cores 2
			break;
			case '|':attron(COLOR_PAIR(3)); //Caso o caracter que esteja na posi��o [i][j] seja | usa-se um Comando da curses:Liga o par de cores 3 definido na main(neste caso, fonte verde e fundo verde)
				printw("%c",matriz[i][j]);//Imprime usando printw, equivalente a printf na curses
				attroff(COLOR_PAIR(3));//Desliga o par de cores 3
			break;
			default:
				attron(COLOR_PAIR(4)); //se n�o for # ou @ ou | ent�o ligar o par de cores 4(neste caso fonte branca e fundo preto)
				printw("%c",matriz[i][j]); //Imprime usando printw, equivalente a printf na curses
				attroff(COLOR_PAIR(4));//desliga o par de cores 4
            }
		}
		printw("\n");
	}
	refresh(); //atualiza a tela
}
