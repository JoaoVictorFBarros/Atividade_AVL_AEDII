#include <iostream>

struct data{
	int value;
};

struct avl{	
	avl *LChild;
	avl *RChild;
	data info;
	int weight=0;
};

int getWeight(avl** t){
	if (*t == NULL){
		return -1;
	}
	else{
		return (*t)->weight;
	}
}

int maxWeight(int a,int b){
	if (a>b){
		return a;
	}
	else{
		return b;
	}
}

void rotateRight(avl** t){
	avl* aux;
	aux = (*t)->LChild;
	(*t)->LChild = aux->RChild;
	aux->RChild = *t;
	
	*t = aux;	
}

void rotateLeft(avl** t){
	avl* aux;
	aux = (*t)->RChild;
	(*t)->RChild = aux->LChild;
	aux->LChild = *t;
	
	*t = aux;	
}

void DoubleRotationRight(avl** t){
	rotateLeft(&(*t)->LChild);
	rotateRight(t);
}

void DoubleRotationLeft(avl** t){
	rotateRight(&(*t)->RChild);
	rotateLeft(t);
}

void rebalance(avl** t){
	int balance, left=0,right=0;
	balance = getWeight(&(*t)->LChild) - getWeight(&(*t)->RChild);
	if((*t)->LChild){
		left = getWeight(&(*t)->LChild->LChild) - getWeight(&(*t)->LChild->RChild);
	}
		
	if((*t)->RChild){
		right = getWeight(&(*t)->RChild->LChild) - getWeight(&(*t)->RChild->RChild);	
	}
	
	if(balance == 2 and left >= 0){
		rotateRight(t);
	}
		
	if(balance == 2 and left < 0){
		DoubleRotationRight(t);
	}	

	if(balance == -2 and right >= 0){
		DoubleRotationLeft(t);
	}
		
	if(balance == -2 and right < 0){
		rotateLeft(t); 	
	}		
}

void insert(avl** t,data d){
	
	if (*t == NULL){
		*t = (avl*) malloc (sizeof(avl));
	
		(*t)->LChild = NULL;
		(*t)->RChild = NULL;
		(*t)->weight = 0;
		(*t)->info = d;
	}
			
	else if (d.value < (*t)->info.value){
			
		insert(&(*t)->LChild,d);
			
	}
	else if (d.value > (*t)->info.value){
		insert(&(*t)->RChild,d);
	}	
	(*t)->weight = maxWeight(getWeight(&(*t)->LChild),getWeight(&(*t)->RChild)) +1;			
	rebalance(t);
	return;
}

avl** search(avl** t,data d){
	if (*t == NULL){
		return NULL;
	}
	else if ((*t)->info.value == d.value){
		return t;
	}	
	else if (d.value < (*t)->info.value){
		search(&(*t)->LChild,d);
	}
	else if (d.value > (*t)->info.value){
		search(&(*t)->RChild,d);
	}	
}

avl* successor(avl* t){
	
	while (t->LChild != NULL){
		t = t->LChild;
	}
	
	return t;
}

void remove(avl** t,avl** parent,char direction,data d){
		
	if (*t == NULL){
		return;
	}	
	else if ((*t)->info.value == d.value){
		avl* aux;		
		aux = *t;
		
		if ((*t)->LChild == NULL and (*t)->RChild == NULL){
			free(aux);
			*t = NULL;
			if (direction == 'L' and (*parent) != NULL){
				(*parent)->LChild = NULL;
			}
			if (direction == 'R' and (*parent) != NULL){				
				(*parent)->RChild = NULL;
			}
		}
		else if ((*t)->RChild != NULL){	
			*t = successor((*t)->RChild);
			free(aux);
		}
		else{
			*t = (*t)->LChild;
			free(aux);
		}
	}	
	else if (d.value < (*t)->info.value){
		remove(&(*t)->LChild,t,'L',d);
		return;
	}
	else if (d.value > (*t)->info.value){
		remove(&(*t)->RChild,t,'R',d);
		return;
	}	
	if ( parent != NULL and (*parent) != NULL){		
		rebalance(parent);	
	}	
}

void printAvl(avl *t){
  if(!(t == NULL)){
    std::cout<<"["<<t->info.value<<"] ";
    printAvl(t->LChild); 
    printAvl(t->RChild); 
  }
}


