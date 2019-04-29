#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"
#define VACIO 0

/* *****************************************************************
 *           DEFINICION DE ESTRUCTURAS DEL ABB Y SU ITERADOR
 * *****************************************************************/
 
typedef struct nodo_abb{
	char* clave;
	void* dato;
	struct nodo_abb* izq;
	struct nodo_abb* der;
}nodo_abb_t;

struct abb{
	nodo_abb_t* raiz;
	abb_destruir_dato_t destructor;
	size_t cantidad;
	abb_comparar_clave_t cmp;
};

struct abb_iter{
	const abb_t* arbol;
	pila_t* pila_nodos;
};

/* *****************************************************************
 *           DEFINICION DE FUNCIONES AUXILIARES DEL ABB
 * *****************************************************************/
 
char* copy_key(const char* key);

nodo_abb_t* nodo_abb_crear(char* clave, void* dato);

bool esta_clave(nodo_abb_t* raiz,const char* clave,abb_comparar_clave_t cmp);

bool insertar_clave(nodo_abb_t* raiz,const char* clave,abb_comparar_clave_t cmp);

void destruir_nodos(nodo_abb_t* nodo,abb_destruir_dato_t destructor );

void* borrar_nodo(nodo_abb_t** dir_nodo,const char* clave,abb_comparar_clave_t cmp);

nodo_abb_t* buscar_min_der(nodo_abb_t* nodo);

void cambiar_nodo(nodo_abb_t* nodo1,nodo_abb_t* nodo2);

bool abb_iter_recur(nodo_abb_t* nodo,bool visitar(const char *, void *, void *), void *extra);

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/
 
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	if (!cmp)return NULL;
	abb_t* arbol = malloc(sizeof(abb_t));
	if(!arbol) return NULL;
	arbol->cantidad = VACIO;
	arbol->destructor = destruir_dato;
	arbol->cmp = cmp;
	arbol->raiz = NULL;
	return arbol;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if (arbol->cantidad == VACIO) return false;
	nodo_abb_t* raiz = arbol->raiz;
	return esta_clave(raiz,clave,arbol->cmp);
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_abb_t* nodo_actual = arbol->raiz;
	nodo_abb_t* nodo_anterior = NULL;
	while(nodo_actual){
		if(!arbol->cmp(nodo_actual->clave,clave)){
			if(arbol->destructor) arbol->destructor(nodo_actual->dato);
			nodo_actual->dato = dato;
			return true;
		}
		nodo_anterior = nodo_actual;
		if(arbol->cmp(nodo_actual->clave,clave)>0){
			nodo_actual = nodo_actual->izq;
			}
		else{
			nodo_actual = nodo_actual->der;
		}
	}
	char* key = copy_key (clave);
	if (key == NULL) return false;
	nodo_abb_t* nodo_agregar = nodo_abb_crear(key,dato);
	if (!nodo_agregar){
		free(key);
		return false;
	}
	if(!nodo_anterior){
		arbol->raiz= nodo_agregar;
		arbol->cantidad++;
		return true;
	}
	if(arbol->cmp(nodo_anterior->clave,clave)>0){
		nodo_anterior->izq = nodo_agregar;
		arbol->cantidad++;
		return true;
	}
	nodo_anterior->der = nodo_agregar;
	arbol->cantidad++;
	return true;
}
	
void *abb_obtener(const abb_t *arbol, const char *clave){
	if(!abb_pertenece(arbol,clave))return NULL;
	nodo_abb_t* nodo_actual = arbol->raiz;
	while(arbol->cmp(nodo_actual->clave,clave)){
		if(arbol->cmp(nodo_actual->clave,clave)>0){
				nodo_actual = nodo_actual->izq;
			}
		else{
			nodo_actual = nodo_actual->der;
		}
	}
	return nodo_actual->dato;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	if(!abb_pertenece(arbol,clave))return NULL;
	void* dato = borrar_nodo(&arbol->raiz,clave,arbol->cmp);
	arbol->cantidad--;
	return dato;
}
	
	
void abb_destruir(abb_t *arbol){
	nodo_abb_t* nodo_actual = arbol->raiz;
	destruir_nodos(nodo_actual,arbol->destructor);
	free(arbol);
}


/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR INORDER
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter) return NULL;
	iter->pila_nodos= pila_crear();
	if(!iter->pila_nodos){
		free(iter);
		return NULL;
	}
	nodo_abb_t* actual = arbol->raiz;
	while(actual){
		pila_apilar(iter->pila_nodos,actual);
		actual = actual->izq;
	}
	iter->arbol=arbol;
	return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	if(pila_esta_vacia(iter->pila_nodos))return true;
	return false;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(pila_esta_vacia(iter->pila_nodos))return false;
	nodo_abb_t* actual = pila_desapilar(iter->pila_nodos);
	if(actual->der){
		actual = actual->der;
		pila_apilar(iter->pila_nodos,actual);
		while(actual->izq){
			actual=actual->izq;
			pila_apilar(iter->pila_nodos,actual);
		}
	}
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if(pila_esta_vacia(iter->pila_nodos))return NULL;
	nodo_abb_t* actual = pila_ver_tope(iter->pila_nodos);
	return actual->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila_nodos);
	free(iter);
	return;
}
	
/* *****************************************************************
 *                    ITERADOR INTERNO INORDER
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	abb_iter_recur(arbol->raiz,visitar,extra);
	return;
}
	
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

char* copy_key(const char* key){
	char* clave = malloc((strlen(key)+1) * sizeof(char));
	if (clave==NULL) return NULL;
	strcpy(clave,key);
	return clave;
}

nodo_abb_t* nodo_abb_crear(char* clave, void* dato){
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	if (nodo == NULL) return NULL;
	nodo->dato = dato;
	nodo->der = NULL;
	nodo->izq = NULL;
	nodo->clave = clave;
	return nodo;
}	

bool esta_clave(nodo_abb_t* raiz,const char* clave,abb_comparar_clave_t cmp){
	if (!raiz)return false;
	if(!cmp(raiz->clave, clave)) return true;
	if(cmp(raiz->clave, clave) > 0){
		return esta_clave(raiz->izq,clave,cmp);
	} 
	return esta_clave(raiz->der,clave,cmp);
}

void destruir_nodos(nodo_abb_t* nodo,abb_destruir_dato_t destructor ){
	if(!nodo)return;
	destruir_nodos(nodo->izq,destructor);		
	destruir_nodos(nodo->der,destructor);
	if(destructor)destructor(nodo->dato);
	free(nodo->clave);
	free(nodo);
	return;
}
	
void* borrar_nodo(nodo_abb_t** dir_nodo,const char* clave,abb_comparar_clave_t cmp){
	nodo_abb_t* actual = *dir_nodo;
	if(!cmp(actual->clave,clave)){
		if(actual->der && actual->izq){
			nodo_abb_t* nodo_cambiar = buscar_min_der(actual->der);
			cambiar_nodo(actual,nodo_cambiar);
			return borrar_nodo(&actual->der,clave,cmp);
		}
		void* dato = actual->dato;
		free(actual->clave);
		if(!actual->der && !actual->izq){
			free(actual);
			*dir_nodo = NULL;
			return dato;
		}
		if(!actual->der){
			*dir_nodo = actual->izq;
			free(actual);
			return dato;
		}
		else{
			*dir_nodo = actual->der;
			free(actual);
			return dato;
		}
	}
	if(cmp(actual->clave,clave) >0){
		return borrar_nodo(&actual->izq,clave,cmp);
	}
	return borrar_nodo(&actual->der,clave,cmp);
}
		
		
void cambiar_nodo(nodo_abb_t* nodo1,nodo_abb_t* nodo2){
	char* clave1 = nodo1->clave;
	void* dato1 = nodo1->dato;
	nodo1->dato = nodo2->dato;
	nodo1->clave = nodo2->clave;
	nodo2->dato = dato1;
	nodo2->clave = clave1;
	
}
	
nodo_abb_t* buscar_min_der(nodo_abb_t* nodo){
	nodo_abb_t* actual = nodo;
	while(actual->izq){
		actual=actual->izq;
	}
	return actual;
}
	
bool abb_iter_recur(nodo_abb_t* nodo,bool visitar(const char *, void *, void *), void *extra){
	nodo_abb_t* actual = nodo;
	if(!actual) return true;
	bool estado_izq = abb_iter_recur(actual->izq,visitar,extra);
	if(!estado_izq) return false;
	bool estado_raiz = visitar(actual->clave,actual->dato,extra);
	if(!estado_raiz) return false;
	return abb_iter_recur(actual->der,visitar,extra);
}			
	

