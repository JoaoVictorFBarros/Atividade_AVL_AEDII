#include <iostream>
#include "avl.hpp"
using namespace std;

int main (){
	setlocale(LC_ALL,"portuguese");
	avl* t = NULL;
	short op=0;
	
	while(op != 4){
		
		data input;
		system("cls");
		cout<<"Digite:\n1: Inserir valor\n2: Remover valor\n3: Imprimir árvore AVL\n4: Sair\n\nOperação: ";
		cin>>op;
		
		switch (op){
			case 1:{
				cout<<"Digite o valor a ser inserido: ";
				cin>>input.value;
				insert(&t,input);
				cout<<"\nValor adicionado.\n";
				break;
			}
			
			case 2:{
				cout<<"Digite o valor a ser removido: ";
				cin>>input.value;
				remove(&t,NULL,'N',input);
				cout<<"\nValor removido.\n";
				break;
			}
			case 3:{
				cout<<"\nImprimindo em pré ordem\n";
				printAvl(t);
				cout<<"\n\n";
				break;
			}
		}
		if (op != 4){
			system("pause");	
		}
	}
	
	return 0;
}
