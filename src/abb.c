#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;
	abb_t *arbol = calloc(1, sizeof(abb_t));
	arbol->comparador = comparador;
	return arbol;
}

nodo_abb_t *abb_insertar_recursivo(nodo_abb_t *raiz, void *elemento,
				   abb_comparador comparador, bool *error)
{
	if (raiz == NULL) {
		nodo_abb_t *nodo_insertar = malloc(sizeof(nodo_abb_t));
		if (nodo_insertar == NULL) {
			*error = true;
			return NULL;
		}
		nodo_insertar->elemento = elemento;
		nodo_insertar->derecha = NULL;
		nodo_insertar->izquierda = NULL;
		return nodo_insertar;
	}

	else if (comparador(raiz->elemento, elemento) >= 0)
		raiz->izquierda = abb_insertar_recursivo(
			raiz->izquierda, elemento, comparador, error);
	else if (comparador(raiz->elemento, elemento) < 0)
		raiz->derecha = abb_insertar_recursivo(raiz->derecha, elemento,
						       comparador, error);
	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	bool error = false;
	arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, elemento,
						  arbol->comparador, &error);
	if (error)
		return NULL;
	arbol->tamanio++;
	return arbol;
}

nodo_abb_t *extraigo_predecesor_inorden(nodo_abb_t *nodo,
					void **elemento_reemplazo)
{
	if (nodo->derecha == NULL) {
		*elemento_reemplazo = nodo->elemento;
		nodo_abb_t *nodo_izquierdo = nodo->izquierda;
		free(nodo);
		return nodo_izquierdo;
	}
	nodo->derecha =
		extraigo_predecesor_inorden(nodo->derecha, elemento_reemplazo);

	return nodo;
}

void *abb_quitar_recursivo(nodo_abb_t *raiz, void *elemento,
			   void **elemento_quitado, abb_comparador comparador,
			   bool *no_encontrado)
{
	if (raiz == NULL) {
		*no_encontrado = true;
		return NULL;
	}
	if (comparador(raiz->elemento, elemento) == 0) {
		*elemento_quitado = raiz->elemento;
		if (raiz->derecha != NULL && raiz->izquierda != NULL) {
			void *elemento_reemplazo;
			raiz->izquierda = extraigo_predecesor_inorden(
				raiz->izquierda, &elemento_reemplazo);
			raiz->elemento = elemento_reemplazo;
			return raiz;

		}

		else {
			nodo_abb_t *rama_izquierda = raiz->izquierda;
			nodo_abb_t *rama_derecha = raiz->derecha;
			free(raiz);
			if (rama_derecha == NULL)
				return rama_izquierda;
			return rama_derecha;
		}
	} else if (comparador(raiz->elemento, elemento) > 0)
		raiz->izquierda = abb_quitar_recursivo(
			raiz->izquierda, elemento, elemento_quitado, comparador,
			no_encontrado);
	else if (comparador(raiz->elemento, elemento) < 0)
		raiz->derecha = abb_quitar_recursivo(raiz->derecha, elemento,
						     elemento_quitado,
						     comparador, no_encontrado);
	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol))
		return NULL;
	void *elemento_quitado = NULL;
	bool no_encontrado = false;
	arbol->nodo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, elemento,
						&elemento_quitado,
						arbol->comparador,
						&no_encontrado);
	if (no_encontrado)
		return NULL;
	arbol->tamanio--;
	return elemento_quitado;
}

void *abb_buscar_recursivo(nodo_abb_t *raiz, void *elemento_buscado,
			   abb_comparador comparador)
{
	if (raiz == NULL)
		return NULL;
	if (comparador(raiz->elemento, elemento_buscado) > 0)
		return abb_buscar_recursivo(raiz->izquierda, elemento_buscado,
					    comparador);
	else if (comparador(raiz->elemento, elemento_buscado) < 0)
		return abb_buscar_recursivo(raiz->derecha, elemento_buscado,
					    comparador);
	return raiz->elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento_buscado)
{
	if (abb_vacio(arbol))
		return NULL;
	return abb_buscar_recursivo(arbol->nodo_raiz, elemento_buscado,
				    arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL || arbol->tamanio == 0)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo_recursivo(nodo_abb_t *nodo,
				 void (*destructor)(void *auxiliar),
				 abb_comparador comparador)
{
	if (nodo == NULL)
		return;

	abb_destruir_todo_recursivo(nodo->izquierda, destructor, comparador);

	abb_destruir_todo_recursivo(nodo->derecha, destructor, comparador);

	if (destructor != NULL)
		destructor(nodo->elemento);
	free(nodo);

	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol != NULL) {
		abb_destruir_todo_recursivo(arbol->nodo_raiz, destructor,
					    arbol->comparador);
		free(arbol);
	}
}

void abb_recorrido_inorder_recursivo(nodo_abb_t *nodo,
				     bool (*funcion)(void *, void *), void *aux,
				     size_t *veces_iterado,
				     bool *sigue_recorrido)
{
	if (nodo == NULL)
		return;
	abb_recorrido_inorder_recursivo(nodo->izquierda, funcion, aux,
					veces_iterado, sigue_recorrido);

	if (*sigue_recorrido == false)
		return;
	*sigue_recorrido = funcion(nodo->elemento, aux);
	(*veces_iterado)++;

	abb_recorrido_inorder_recursivo(nodo->derecha, funcion, aux,
					veces_iterado, sigue_recorrido);

	return;
}

void abb_recorrido_preorder_recursivo(nodo_abb_t *nodo,
				      bool (*funcion)(void *, void *),
				      void *aux, size_t *veces_iterado,
				      bool *sigue_recorrido)
{
	if (nodo == NULL)
		return;
	if (*sigue_recorrido == false)
		return;
	*sigue_recorrido = funcion(nodo->elemento, aux);
	(*veces_iterado)++;
	abb_recorrido_preorder_recursivo(nodo->izquierda, funcion, aux,
					 veces_iterado, sigue_recorrido);
	abb_recorrido_preorder_recursivo(nodo->derecha, funcion, aux,
					 veces_iterado, sigue_recorrido);
	return;
}

void abb_recorrido_postorder_recursivo(nodo_abb_t *nodo,
				       bool (*funcion)(void *, void *),
				       void *aux, size_t *veces_iterado,
				       bool *sigue_recorrido)
{
	if (nodo == NULL)
		return;

	abb_recorrido_postorder_recursivo(nodo->izquierda, funcion, aux,
					  veces_iterado, sigue_recorrido);
	abb_recorrido_postorder_recursivo(nodo->derecha, funcion, aux,
					  veces_iterado, sigue_recorrido);
	if (*sigue_recorrido == false)
		return;
	*sigue_recorrido = funcion(nodo->elemento, aux);
	(*veces_iterado)++;

	return;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (abb_vacio(arbol) || funcion == NULL)
		return 0;
	size_t i = 0;
	bool recorre = true;
	if (recorrido == INORDEN)
		abb_recorrido_inorder_recursivo(arbol->nodo_raiz, funcion, aux,
						&i, &recorre);
	else if (recorrido == PREORDEN)
		abb_recorrido_preorder_recursivo(arbol->nodo_raiz, funcion, aux,
						 &i, &recorre);
	else if (recorrido == POSTORDEN)
		abb_recorrido_postorder_recursivo(arbol->nodo_raiz, funcion,
						  aux, &i, &recorre);
	return i;
}

struct vector_y_tamanio {
	void **vector;
	size_t tamanio;
	size_t cantidad_elementos;
};

bool insertar_elementos_en_vector(void *elemento, void *aux)
{
	struct vector_y_tamanio *vector = aux;
	vector->vector[vector->cantidad_elementos] = elemento;
	vector->cantidad_elementos++;
	if (vector->cantidad_elementos >= vector->tamanio)
		return false;
	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	struct vector_y_tamanio vector;
	vector.vector = array;
	vector.tamanio = tamanio_array;
	vector.cantidad_elementos = 0;
	if (abb_vacio(arbol) == true)
		return 0;
	if (recorrido == INORDEN)
		return abb_con_cada_elemento(arbol, recorrido,
					     insertar_elementos_en_vector,
					     &vector);
	else if (recorrido == PREORDEN)
		return abb_con_cada_elemento(arbol, recorrido,
					     insertar_elementos_en_vector,
					     &vector);
	else if (recorrido == POSTORDEN)
		return abb_con_cada_elemento(arbol, recorrido,
					     insertar_elementos_en_vector,
					     &vector);
	return 0;
}
