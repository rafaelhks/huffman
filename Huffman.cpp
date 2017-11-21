#include <bits/stdc++.h> //Importa todas as bibliotecas padrão do C++ que o código use.
using namespace std;
char palavra[2048]; //Armazena a palavra
int freq[2048]; //Armazena as frequencias
char plaux[2048]; //Salva uma copia da palavra
char binario[2048]; //Armazena a sequencia binaria informada pelo usuario
int tam; //Recebe o tamanho da palavra

//       Licensed to Rafael Francisco Ferreira under GNU General Public License v3.0        //

//					Rafael Francisco Ferreira - 3º ano C.C. Unespar
//Implementação do algorítimo de Huffman para a matéria de Organização e Estrutura de Dados.
//OBS: Aceita textos com espaços.

//Um nó da arvore de Huffman
struct NohHeapMin{
    char dados;                // um dos caracteres de entrada
    unsigned freq;             // frequência do caractere
    string bin;
    NohHeapMin *left, *right; // filho da esquerda e da direita

    NohHeapMin(char letra, int freq){
        left = right = NULL;
        this->dados = letra;
        this->freq = freq;
    }
};

// Para comparar os nós da heap min
struct compare{
    bool operator()(NohHeapMin* l, NohHeapMin* r){
        return (l->freq > r->freq);
    }
};

struct NohHeapMin *left, *right, *top, *no;
// Cria uma heap min
priority_queue<NohHeapMin*, vector<NohHeapMin*>, compare> minHeap; //HEAP MIN

void Codifica(struct NohHeapMin* raiz, string str){  //Desce a arvore codificando
	if (!raiz)
        return;
	raiz->bin = str;
    Codifica(raiz->left, str + "0");
    Codifica(raiz->right, str + "1");
}

void Decodifica(struct NohHeapMin* raiz){  //Desce a arvore seguindo a sequencia armazenada na variavel binario[]
	if(!raiz) return;
	cout<<"\nSequencia decodificada: ";
	int t = 0;
	inicio:
	struct NohHeapMin *no;
	no = raiz;

	for(int j=t; j<strlen(binario); j++){
		if(binario[j] == '0'){ //Se 0, desce para a esquerda
			no=no->left;
			if(no->dados != '§'){ //Se não for um nó interno, é um caractere (nó terminal)
				cout<<no->dados; //Printa o caractere na tela
				t++;
				goto inicio; //Volta à raiz para encontrar o proximo caractere
			}else t++;
		}else if(binario[j] == '1'){ //Se 1, desce para a direita
				no=no->right;
			if(no->dados != '§'){ //Se não for um nó interno, é um caractere (nó terminal)
				cout<<no->dados; //Printa o caractere na tela
				t++;
				goto inicio; //Volta à raiz para encontrar o proximo caractere
			}else t++;
		}
	}
}

// Printa os códigos da arvore de huffman partindo da raiz
void mostraCodigos(struct NohHeapMin* raiz){
	if (!raiz)
        return;
 	if (raiz->dados != '§')
 		cout<<raiz->dados<<" : "<< raiz->bin<<endl;
 	mostraCodigos(raiz->left);
 	mostraCodigos(raiz->right);
}

//Printa a sequencia binária da palavra ou texto, seguindo a sequencia da variavel plaux[]
void mostraBin(struct NohHeapMin* raiz, int k){
	if(!raiz)
		return;
	if(raiz->dados==plaux[k] && k<tam){
		cout<<raiz->bin;
		mostraBin(minHeap.top(), k+1);
	}else if(k<tam){
		mostraBin(raiz->left, k);
		mostraBin(raiz->right, k);
	}
}

//Conta e retorna a frequencia de cada caractere
int contaFreq(char c, char *s){
	int num_vezes=0;
	int i=0;
	while(*s!='\0'){
		if(*s==c)
		{
			num_vezes++;
		}
		s++;
	}
	return num_vezes;
}

//Auxiliar para a limpeza da Heap ao se digitar uma nova palavra
void limpaHeap(){
	while(minHeap.size() != 0)
    	minHeap.pop();
}

//Funcção que recebe os dados de entrada
void entrada(){
	limpaHeap();
	cout<<"\nInforme a palavra ou texto (Max: 2048): ";
	gets(palavra);
	gets(palavra);
	tam = strlen(palavra);
	cout<<"\nPalavra/Texto: "<<palavra<<endl;

	for(int i=0; i<tam; i++){
		freq[i] = contaFreq(palavra[i], palavra); //conta a frequência de cada caractere na palavra
		plaux[i] = palavra[i]; //salva os caracteres da palavra em uma var auxiliar
	}

	//Este for remove as letras repetidas e substitui por '\0'
	int i,j;
	for(i=0; i<tam; i++){
		int c=0;
		for(j=0; j<tam; j++){
			if (palavra[i] == palavra[j]) {//Se encontrar um caractere igual, incluindo ele mesmo
			    if (c == 0) {
			        //Muda o sentinela para 1 quando encontrar o primeiro igual, que, no caso, é o próprio caractere
			        c = 1;
			    }else{
			        palavra[i] = '\0'; //caso haja mais de uma ocorrencia, muda para '\0'
			        freq[i] = '\0';
				}
			}
		}
	}
}

// A função principal que constrói a arvore de Huffman e printa os codigos
void Huffman(){
	struct NohHeapMin *left, *right, *top;

	//Adiciona na Heap apenas os caracteres diferentes de '\0'
    for (int i = 0; i < tam; i++){
    	if(palavra[i] != '\0' && freq[i] != '\0')
    		minHeap.push(new NohHeapMin(palavra[i], freq[i]));
	}

	if(minHeap.size() == 1){
 		cout<<"A palavra precisa ter ao menos dois caracteres diferentes! (Ex: ab)"<<endl;
	}

    // Itera enquanto o tamanho da heap não chega a 1
    while (minHeap.size() != 1){
        // Extrai os dois nós de frequencia mínima da heap min
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Cria um novo nó interno com frequencia igual a da
        //soma das frequencias dos dois nós. Faz dos dois nós estraidos
        //os filhos da esquerda e da direita desse novo nó.
        //Adiciona este nó na heap min
        //'§' é um valor especial para nós internos, não usado
        top = new NohHeapMin('§', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
}

//main
int main(){
	char op;
	cout<<"\t\\Algoritimo de Huffman - Rafael Francisco Ferreira/"<<endl;

    do{
    	cout<<"\n-------------MENU------------"<<endl;
		cout<<"\n1 - Comprimir palavra ou texto."<<endl;
		cout<<"2 - Descomprimir palavra ou texto."<<endl;
		cout<<"3 - Sair."<<endl;
		cout<<"\nDigite a opcao desejada: ";
		cin>>op;

		switch(op){
			case '1':
				system("cls");
				entrada(); //Recebe a palavra e trata a entrada
				Huffman(); //Chamada do método principal
				cout<<"\nCaracteres codificados: "<<endl;
    			Codifica(minHeap.top(), "");
    			mostraCodigos(minHeap.top());
    			cout<<"\nCodigo binario da palavra/texto: ";
    			mostraBin(minHeap.top(), 0);
    			cout<<endl;
				break;
			case '2':
				system("cls");
				if(minHeap.size() == 0){ //Se nenhuma palavra foi codificada ainda, exibe aviso
					cout<<"Uma palavra deve ser comprimida antes de Descomprimir!";
					break;
				}
				cout<<"Tabela de codigos: "<<endl;
				mostraCodigos(minHeap.top());
				cout<<"\nInforme a sequencia binaria: ";
				gets(binario);
				gets(binario);
				Decodifica(minHeap.top());
				cout<<endl;
				break;
			case '3':
				cout<<"Finalizando..."<<endl;
				system("pause");
				return 0;
				break;
			default:
				system("cls");
				cout<<"Opcao invalida!"<<endl;
				break;
		}
 	}while(op!='3');
}
