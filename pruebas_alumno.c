#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void *elemento_1, void *elemento_2)
{
	int *e1 = elemento_1;
	int *e2 = elemento_2;

	return (*e1) - (*e2);
}

void prueba_creacion_arbol()
{
	abb_t *arbol_NULL = abb_crear(NULL);
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(
		arbol_NULL == NULL,
		"No se puede crear un arbol con función nula (abb_crear devuelve NULL)");
	pa2m_afirmar(
		arbol != NULL,
		"El arbol creado no devuelve NULL, se pudo crear el arbol");
	pa2m_afirmar(
		arbol->comparador != NULL,
		"El arbol creado posee una funcion comparadora (el puntero comparador no devuelve NULL)");
	pa2m_afirmar(arbol->tamanio == 0,
		     "El arbol está vacío, su tamaño es 0");
	abb_destruir(arbol);
}

void prueba_insercion_en_arbol()
{
	pa2m_afirmar(abb_insertar(NULL, NULL) == NULL,
		     "Intentar insertar en arbol nulo devuelve NULL");
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 37;
	abb_insertar(abb, &elemento);
	pa2m_afirmar(abb->comparador(&elemento, abb->nodo_raiz->elemento) == 0,
		     "Se insertó un elemento en nodo raiz");
	pa2m_afirmar(abb->tamanio == 1, "El tamaño del arbol subió a 1");
	pa2m_afirmar(abb->nodo_raiz->derecha == NULL,
		     "Puntero al nodo derecha de la raíz devuelve NULL");
	pa2m_afirmar(abb->nodo_raiz->izquierda == NULL,
		     "Puntero al nodo izquierda de la raíz devuelve NULL");
	abb_insertar(abb, &elemento_2);
	pa2m_afirmar(
		abb->tamanio == 2,
		"Se insertó un elemento menor, el tamaño del arbol subió a 2");
	abb_insertar(abb, &elemento_3);
	pa2m_afirmar(
		abb->tamanio == 3,
		"Se insertó un elemento mayor, el tamaño del arbol subió a 3");
	pa2m_afirmar(
		abb->nodo_raiz->derecha != NULL,
		"Puntero al nodo derecha de la raíz no devuelve NULL, se insertó el nodo");
	pa2m_afirmar(
		abb->nodo_raiz->izquierda != NULL,
		"Puntero al nodo izquierda de la raíz no devuelve NULL, se insertó el nodo");
	abb_destruir(abb);
}

void prueba_busqueda_en_arbol()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	int elemento = 23;
	int elemento_b = 23;
	int elemento_2 = 15;
	int elemento_3 = 37;
	int elemento_4 = 40;
	int elemento_5 = 12;
	int elemento_6 = 16;
	int elemento_7 = 32;
	abb_insertar(abb, &elemento);
	void *elemento_encontrado = abb_buscar(NULL, &elemento_b);
	pa2m_afirmar(
		elemento_encontrado == NULL,
		"No se puede buscar un elemento en un arbol nulo, devuelve NULL");
	elemento_encontrado = abb_buscar(abb_vacio, &elemento_b);
	pa2m_afirmar(
		elemento_encontrado == NULL,
		"No se puede buscar un elemento en un arbol vacio, devuelve NULL");
	elemento_encontrado = abb_buscar(abb, &elemento_b);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_b) == 0,
		     "Se encontró el elemento en la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_2);
	pa2m_afirmar(elemento_encontrado == NULL,
		     "Si se busca un elemento inexistente se devuelve NULL");
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	elemento_encontrado = abb_buscar(abb, &elemento_2);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_2) == 0,
		     "Se encontró el elemento de la izquierda de la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_3);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_3) == 0,
		     "Se encontró el elemento de la derecha de la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_4);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_4) == 0,
		     "Se encontró el elemento del subarbol derecho");
	elemento_encontrado = abb_buscar(abb, &elemento_5);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_5) == 0,
		     "Se encontró el elemento del subarbol izquierdo");
	elemento_encontrado = abb_buscar(abb, &elemento_6);
	pa2m_afirmar(
		comparador(elemento_encontrado, &elemento_6) == 0,
		"Se encontró el elemento del subarbol izquierdo, predecesor inorden a raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_7);
	pa2m_afirmar(
		comparador(elemento_encontrado, &elemento_7) == 0,
		"Se encontró el elemento del subarbol derecho, sucesor inorden a raiz");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

void prueba_eliminacion_en_arbol()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	pa2m_afirmar(abb_quitar(NULL, &elemento) == NULL,
		     "No se puede quitar de un arbol nulo");
	pa2m_afirmar(abb_quitar(abb_vacio, &elemento) == NULL,
		     "No se puede quitar de un arbol sin elementos");
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	pa2m_afirmar(abb_tamanio(abb) == 4,
		     "Se insertan 4 elementos en el arbol");
	void *elemento_quitado = NULL;
	elemento_quitado = abb_quitar(abb, &elemento_3);
	pa2m_afirmar(
		abb->comparador(&elemento_3, elemento_quitado) == 0,
		"Se ha quitado un elemento en el nivel 2 con rama izquierda no nula");
	pa2m_afirmar(abb_tamanio(abb) == 3,
		     "Se ha reducido el tamaño del arbol (3)");
	elemento_quitado = abb_quitar(abb, &elemento_4);
	pa2m_afirmar(abb->comparador(&elemento_4, elemento_quitado) == 0,
		     "Se quitó un elemento con hijos nulos");
	pa2m_afirmar(abb_tamanio(abb) == 2,
		     "Se ha reducido el tamaño del arbol (2)");
	elemento_quitado = abb_quitar(abb, &elemento_2);
	pa2m_afirmar(abb->comparador(&elemento_2, elemento_quitado) == 0,
		     "Se ha quitado un elemento en el nivel 2");
	pa2m_afirmar(abb_tamanio(abb) == 1,
		     "Se ha reducido el tamaño del arbol (1)");
	elemento_quitado = abb_quitar(abb, &elemento);
	pa2m_afirmar(abb->comparador(&elemento, elemento_quitado) == 0,
		     "Se quitó el elemento raiz");
	pa2m_afirmar(abb->nodo_raiz == NULL,
		     "El arbol quedó vacío, el puntero al nodo raiz es NULL");
	pa2m_afirmar(abb_tamanio(abb) == 0,
		     "El arbol quedó vacío, el tamaño es 0");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

void prueba_eliminacion_con_2_hijos_raiz()
{
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	int elemento_7 = 30;
	int elemento_8 = 16;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	abb_insertar(abb, &elemento_8);
	pa2m_afirmar(
		abb_tamanio(abb) == 8,
		"Se agregaron 8 elementos a la lista, en los dos hijos de la raíz");
	void *elemento_quitado;
	elemento_quitado = abb_quitar(abb, &elemento);
	pa2m_afirmar(abb->comparador(&elemento, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (23)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_5) ==
			     0,
		     "Se reemplazó por el predecesor inorden (17)");
	elemento_quitado = abb_quitar(abb, &elemento_5);
	pa2m_afirmar(abb->comparador(&elemento_5, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (17)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_8) ==
			     0,
		     "Se reemplazó por el predecesor inorden (16)");
	elemento_quitado = abb_quitar(abb, &elemento_8);
	pa2m_afirmar(abb->comparador(&elemento_8, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (16)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_2) ==
			     0,
		     "Se reemplazó por el predecesor inorden (15)");
	abb_quitar(abb, &elemento_2);
	abb_quitar(abb, &elemento_3);
	abb_quitar(abb, &elemento_4);
	abb_quitar(abb, &elemento_6);
	abb_quitar(abb, &elemento_7);
	pa2m_afirmar(
		abb_vacio(abb) == true,
		"Se eliminaron los elementos restantes a través de la raíz, el arbol quedó vacío");
	abb_destruir(abb);
}

bool buscador_en_bool(void *e1, void *e2)
{
	if (e2 == NULL)
		return true;
	int *i1 = e1;
	int *i2 = e2;
	int resultado = (*i1) - (*i2);
	if (resultado == 0)
		return false;
	return true;
}

void pruebas_iterador_interno_inorder()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	int elemento_7 = 30;
	int elemento_8 = 16;
	int elemento_9 = 49;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	abb_insertar(abb, &elemento_8);
	abb_insertar(abb, &elemento_9);
	size_t veces_iterado = 0;
	veces_iterado = abb_con_cada_elemento(abb_vacio, INORDEN,
					      buscador_en_bool, &elemento_5);
	pa2m_afirmar(veces_iterado == 0, "No se puede iterar un arbol vacío");
	veces_iterado = abb_con_cada_elemento(NULL, INORDEN, buscador_en_bool,
					      &elemento_5);
	pa2m_afirmar(veces_iterado == 0, "No se puede iterar un arbol nulo");
	veces_iterado = abb_con_cada_elemento(abb, INORDEN, buscador_en_bool,
					      &elemento_5);
	pa2m_afirmar(abb_tamanio(abb) == 9,
		     "Se han insertado 9 elementos en el arbol");
	pa2m_afirmar(
		veces_iterado == 4,
		"Se han iterado correctamente 4 veces pasando como auxiliar un elemento con valor medio");
	veces_iterado = abb_con_cada_elemento(abb, INORDEN, buscador_en_bool,
					      &elemento_6);
	pa2m_afirmar(
		veces_iterado == 1,
		"Se ha iterado correctamente 1 pasando como auxiliar el elemento menor");
	veces_iterado = abb_con_cada_elemento(abb, INORDEN, buscador_en_bool,
					      &elemento_9);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar el elemento mayor");
	veces_iterado =
		abb_con_cada_elemento(abb, INORDEN, buscador_en_bool, NULL);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar NULL");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

void pruebas_iterador_interno_preorder()
{
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	int elemento_7 = 30;
	int elemento_8 = 16;
	int elemento_9 = 49;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	abb_insertar(abb, &elemento_8);
	abb_insertar(abb, &elemento_9);
	size_t veces_iterado = 0;
	veces_iterado = abb_con_cada_elemento(abb, PREORDEN, buscador_en_bool,
					      &elemento_3);
	pa2m_afirmar(abb_tamanio(abb) == 9,
		     "Se han insertado 9 elementos en el arbol");
	pa2m_afirmar(
		veces_iterado == 6,
		"Se han iterado correctamente 6 veces pasando como auxiliar un elemento con valor medio");
	veces_iterado = abb_con_cada_elemento(abb, PREORDEN, buscador_en_bool,
					      &elemento);
	pa2m_afirmar(
		veces_iterado == 1,
		"Se ha iterado correctamente 1 pasando como auxiliar el elemento raíz");
	veces_iterado = abb_con_cada_elemento(abb, PREORDEN, buscador_en_bool,
					      &elemento_9);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar el elemento mayor (posicionado mas a la derecha)");
	veces_iterado =
		abb_con_cada_elemento(abb, PREORDEN, buscador_en_bool, NULL);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar NULL");
	abb_destruir(abb);
}

void pruebas_iterador_interno_postorder()
{
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	int elemento_7 = 30;
	int elemento_8 = 16;
	int elemento_9 = 49;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	abb_insertar(abb, &elemento_8);
	abb_insertar(abb, &elemento_9);
	size_t veces_iterado = 0;
	veces_iterado = abb_con_cada_elemento(abb, POSTORDEN, buscador_en_bool,
					      &elemento_3);
	pa2m_afirmar(abb_tamanio(abb) == 9,
		     "Se han insertado 9 elementos en el arbol");
	pa2m_afirmar(
		veces_iterado == 8,
		"Se han iterado correctamente 8 veces pasando como auxiliar un elemento hijo derecho de la raiz");
	veces_iterado = abb_con_cada_elemento(abb, POSTORDEN, buscador_en_bool,
					      &elemento_6);
	pa2m_afirmar(
		veces_iterado == 1,
		"Se ha iterado correctamente 1 pasando como auxiliar el elemento menor (nodo con hijos nulos)");
	veces_iterado = abb_con_cada_elemento(abb, POSTORDEN, buscador_en_bool,
					      &elemento);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar el elemento de la raíz");
	veces_iterado =
		abb_con_cada_elemento(abb, POSTORDEN, buscador_en_bool, NULL);
	pa2m_afirmar(
		veces_iterado == 9,
		"Se ha iterado correctamente 9 pasando como auxiliar NULL");
	abb_destruir(abb);
}

void prueba_elemento_vector_inorder()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	void *enteros[4];
	void **numeros = enteros;

	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	size_t cantidad_elementos_en_vector =
		abb_recorrer(abb_vacio, INORDEN, numeros, (size_t)4);
	pa2m_afirmar(
		cantidad_elementos_en_vector == 0,
		"La cantidad de elementos en un arbol vacío es 0, no se pasaron elementos");
	cantidad_elementos_en_vector =
		abb_recorrer(NULL, INORDEN, numeros, (size_t)4);
	pa2m_afirmar(
		cantidad_elementos_en_vector == 0,
		"La cantidad de elementos en un arbol nulo es 0, no se pasaron elementos");
	cantidad_elementos_en_vector =
		abb_recorrer(abb, INORDEN, numeros, (size_t)4);
	pa2m_afirmar(cantidad_elementos_en_vector == 4,
		     "Se insertaron los 4 elementos en el vector");
	pa2m_afirmar(comparador(enteros[0], &elemento_2) == 0,
		     "El primer elemento es el minimo");
	pa2m_afirmar(comparador(enteros[1], &elemento) == 0,
		     "El segundo elemento es el segundo menor");
	pa2m_afirmar(comparador(enteros[2], &elemento_4) == 0,
		     "El tercer elemento es el tercer menor");
	pa2m_afirmar(comparador(enteros[3], &elemento_3) == 0,
		     "El cuarto elemento es el mayor");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

void prueba_elementos_vector_menos_lugares()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	void *enteros[4];
	void **numeros = enteros;

	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	size_t cantidad_elementos_en_vector =
		abb_recorrer(abb, INORDEN, numeros, (size_t)4);
	pa2m_afirmar(cantidad_elementos_en_vector == 4,
		     "Se insertaron los 4 elementos de 6 en el vector");
	pa2m_afirmar(comparador(enteros[0], &elemento_6) == 0,
		     "El primer elemento es el minimo");
	pa2m_afirmar(comparador(enteros[1], &elemento_2) == 0,
		     "El segundo elemento es el segundo menor");
	pa2m_afirmar(comparador(enteros[2], &elemento_5) == 0,
		     "El tercer elemento es el tercer menor");
	pa2m_afirmar(comparador(enteros[3], &elemento) == 0,
		     "El cuarto elemento es el mayor");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}
void prueba_elemento_vector_preorder()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	void *enteros[4];
	void **numeros = enteros;

	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	size_t cantidad_elementos_en_vector =
		abb_recorrer(abb, PREORDEN, numeros, (size_t)4);
	pa2m_afirmar(cantidad_elementos_en_vector == 4,
		     "Se insertaron los 4 elementos en el vector");
	pa2m_afirmar(comparador(enteros[0], &elemento) == 0,
		     "El primer elemento es la raíz");
	pa2m_afirmar(comparador(enteros[1], &elemento_2) == 0,
		     "El segundo elemento es el hijo izquierdo de la raiz");
	pa2m_afirmar(comparador(enteros[2], &elemento_3) == 0,
		     "El tercer elemento es el hijo derecho de la raiz");
	pa2m_afirmar(comparador(enteros[3], &elemento_4) == 0,
		     "El cuarto elemento es el correcto");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

void prueba_elemento_vector_postorder()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	void *enteros[4];
	void **numeros = enteros;

	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	size_t cantidad_elementos_en_vector =
		abb_recorrer(abb, POSTORDEN, numeros, (size_t)4);
	pa2m_afirmar(cantidad_elementos_en_vector == 4,
		     "Se insertaron los 4 elementos en el vector");
	pa2m_afirmar(
		comparador(enteros[0], &elemento_2) == 0,
		"El primer elemento es el correcto (hijo izquierdo de la raíz)");
	pa2m_afirmar(comparador(enteros[1], &elemento_4) == 0,
		     "El segundo elemento es el correcto");
	pa2m_afirmar(comparador(enteros[2], &elemento_3) == 0,
		     "El tercer elemento es el correcto");
	pa2m_afirmar(comparador(enteros[3], &elemento) == 0,
		     "El cuarto elemento es la raiz");
	abb_destruir(abb);
	abb_destruir(abb_vacio);
}

int main()
{
	pa2m_nuevo_grupo("\nPruebas creación de arbol");

	prueba_creacion_arbol();

	pa2m_nuevo_grupo("\nPruebas insercion en arbol");

	prueba_insercion_en_arbol();

	pa2m_nuevo_grupo("\nPruebas busqueda en arbol");

	prueba_busqueda_en_arbol();

	pa2m_nuevo_grupo("\n Pruebas eliminacion en arbol");

	prueba_eliminacion_en_arbol();

	pa2m_nuevo_grupo("\n Pruebas eliminacion con 2 hijos desde raíz");

	prueba_eliminacion_con_2_hijos_raiz();

	pa2m_nuevo_grupo("\nPruebas recorrido iterador interno INORDER");

	pruebas_iterador_interno_inorder();

	pa2m_nuevo_grupo("\nPruebas recorrido iterador interno PREORDER");

	pruebas_iterador_interno_preorder();

	pa2m_nuevo_grupo("\nPruebas recorrido iterador interno POSTORDER");

	pruebas_iterador_interno_postorder();

	pa2m_nuevo_grupo("\nPruebas insertar elementos en vector INORDEN");

	prueba_elemento_vector_inorder();

	prueba_elementos_vector_menos_lugares();

	pa2m_nuevo_grupo("\nPruebas insertar elementos en vector PREORDEN");

	prueba_elemento_vector_preorder();

	pa2m_nuevo_grupo("\nPruebas insertar elementos en vector POSTORDEN");

	prueba_elemento_vector_postorder();

	return pa2m_mostrar_reporte();
}
