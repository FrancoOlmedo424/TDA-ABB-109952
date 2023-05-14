# TDA ABB

## Repositorio de Franco Daniel Olmedo - 109952 - francoolmedo424@gmail.com

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_alumno.c
```

- Para ejecutar:

```bash
make pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron
```
---
##  Funcionamiento

El programa solicitado hace uso de las funciones publicas y privadas para el manejo del arbol binario de busqueda. Estas son: creación, inserción, eliminación, busqueda, arbol vacío, recorrido y destruccion en conjunto con un iterador interno. A continuación se explicará el funcionamiento de las funciones mas importantes y del programa mismo. 

Creación del abb: se utiliza la función "abb_crear" que recibe la función comparadora. Esta funcion crea un puntero y reserva un bloque de memoria de tramaño "abb_t" mediante calloc. Este, al fallar, devuelve NULL. Se apunta el puntero comparador de la estructura del arbol a la función comparadora. En caso de éxito devuelve el arbol, en caso contrario devuelve NULL. 

Inserción de elementos: Se utiliza la función "abb_insertar" que recibe el arbol y un puntero al elemento a insertar. Los elementos se insertan de forma recursiva, mediante la función "abb_insertar_recursivo" que recibe un puntero a un nodo (la primera vez al nodo raíz), el elemento a insertar, el comparador (ya que no recibe el arbol, sino un nodo de él), y la direccion de memoria de una variable bool para verificar si hubo error en el malloc. Primero, en funcion abb_insertar, se comprueba si el puntero a arbol no apunta a null, en caso que si se devuelve NULL. Se declara y se inicializa la variable error en false y en la siguiente linea se apunta el puntero arbol->nodo_raiz a lo que devuelva la función recursiva (devuelve el nodo insertado si no había nada o el nodo que ya estaba como raíz) y se la invoca mandando el puntero al nodo raíz. En la función recursiva se comprueba primero si el puntero al nodo recibido apunta a NULL, en este caso es donde se tiene que insertar el elemento, se reserva el bloque de memoria necesario para el nodo mediante malloc (en caso de error se cambia el valor de la variable error a true y se devuelve NULL), se apunta el puntero elemento al elemento a insertar y se apuntan los punteros al hijo derecho e izquiero a NULL (ya que será un nodo hoja) y se devuelve el puntero al bloque de memoria del nodo donde se insertó  el elemento (de esta forma, el puntero a hijo derecho o izquierdo de la instancia anterior de la función recursiva es igualado a la direccion de memoria del nodo del elemento a insertar, se "engancha"). En caso que no sea NULL se compara el elemento en el nodo con el elemento a insertar (el comparador devuelve >0 si el elemento en nodo es mayor al que se debe insertar, 0 si son iguales o <0 si es mayor al elemento en el nodo) si devuelve >=0 se iguala el puntero a raiz izquierda a una nueva invocación de abb_insertar_recursivo que recibe el puntero al nodo izquierdo (como pasa con la raíz, si se debe insertar el nuevo nodo en esa posicion, el puntero se apunta el bloque de memoria del nodo insertado, en caso contrario se apunta al nodo que ya estaba ahí). Si devuelve <0 se iguala el puntero raiz derecha a una invocacion nueva de la función, pero esta vez recibiendo el puntero al nodo derecho. Cuando se haya terminado de insertar, esta función devuelve la direccion al nodo donde se estaba trabajando, de esta forma se "vuelve a armar" la rama del arbol donde se insertó el elemento mediante las instancias de la función recursiva. En la funcion abb_insertar, despues de que se insertó el elemento o no (hubo error en malloc, error es true) se comprueba si error es true, en este caso se devuelve NULL, en caso contrario se aumenta el tamaño del arbol y se devuelve el arbol. 

Inserción de elementos:
<div align="center">
<img width="70%" src="img/arbol insertar.png">
</div>

Eliminacion de elementos: para la eliminacion de elementos del arbol se utiliza la función "abb_quitar" que recibe un puntero al bloque de memoria del arbol y un puntero al elemento a eliminar. Se comprueba primero si el arbol está vacío mediante la función "abb_vacio" que recibe el arbol y devuelve true si el puntero apunta a NULL o si el tamaño es 0 o false en caso contrario (que no esté vacío), en caso de que esté vacío se devuelve NULL, en caso contrario se sigue ejecutando. De la misma forma que en abb_insertar se utiliza una funcion recursiva abb_quitar_recursivo a la que se iguala el puntero al nodo raíz, en caso de que no se tenga que eliminar este nodo, devuelve la direccion del nodo raíz (a la que ya estaba apuntando). Esta función recursiva recibe un puntero al nodo donde va a trabajar, un puntero al elemento que debe eliminar, un doble puntero que se apuntará al elemento eliminado, la función comparadora, y la direccion de memoria de una variable bool llamada no_encontrado en caso que no se encuentre el elemento a eliminar y no se deba quitar nada. En abb_quitar_recursivo, una vez se la invoca, en caso de que el puntero a nodo recibido apunte a NULL significa que no se encontró el elemento a eliminar, por lo tanto el valor de no_encontrado cambia a true y se devuelve NULL, en caso contrario se sigue ejecutando. Se compara el elemento en el nodo y el elemento a eliminar, si son iguales (devuelve 0) el doble puntero elemento_quitado se iguala al puntero del elemento del nodo que se debe quitar. Se comprueba despues si tiene dos hijos el nodo (sus punteros no apuntan a NULL simultaneamente) en caso de que no, se apuntan dos punteros (rama_izquierda, y el otro rama_derecha) a los hijos del nodo y se libera el bloque de memoria. Si el puntero a rama derecha apunta a NULL se devuelve el puntero a rama izquierda, en caso contrario se devuelve el puntero a rama derecha (en caso que los dos apunten a NULL se devuelve NULL ya que rama derecha apuntaría a NULL) de esta forma en la instancia anterior se apunta el puntero igualado (sea rama izquierda o rama derecha) a NULL, eliminando el nodo correspondiente. Si los dos punteros de las ramas no apuntan a NULL se iguala el puntero a la rama izquierda a la invocación de la función extraigo_predecesor_inorden, con esta función se quiere extraer el elemento menor con el valor mas cercano al elemento a eliminar (predecesor inorden) "recorriendo una vez por izquierda y después todo por derecha" hasta que se encuentre que el puntero a nodo derecha apunte a NULL. En extraigo_predecesor_inorden primero se comprueba si el puntero al hijo derecho es NULL, en caso de que no lo sea se iguala el puntero a nodo derecha a una nueva invocación de extraigo_predecesor_inorden enviando el puntero al nodo derecho. En caso contrario, el puntero doble recibido como parametro elemento_reemplazo (su valor) se iguala al puntero del elemento del nodo, se iguala un nuevo puntero al hijo izquierdo y se libera el nodo donde se está trabajando para devolver el puntero a la rama izquierda. Cuando se vuelve a abb_quitar_recursivo se iguala el puntero del elemento a eliminar por el puntero al elemento que lo va a reemplazar (extraído por extraigo_predecesor_inorden) y se devuelve el nodo donde se trabajó. En caso que el comparador no devuelve 0 se sigue ejecutando, si el comparador devuelve >0 se iguala el puntero al nodo izquierdo a una nueva invocacion de la función abb_quitar_recursivo enviando el puntero al nodo izquierdo. Si el comparador devuelve <0 se hace lo mismo pero con el puntero al nodo derecho. Al final de la función se devuelve el puntero al nodo donde se trabajó (de esta forma "vuelven a engancharse" los nodos en los que se trabajó de la misma forma). Una vez se termina de ejecutar la forma recursiva, en abb_quitar se comprueba si no_encontrado es true, en este caso se devuelve NULL (no se quitó ningún nodo), al contrario si es false se devuelve el puntero al elemento quitado. 

Quitar un nodo hoja:
<div align="center">
<img width="70%" src="img/arbol eliminar.png">
</div>

Quitar un nodo con un hijo:
<div align="center">
<img width="70%" src="img/arbol eliminar un hijo.png">
</div>

Quitar un nodo con dos hijos y reemplazar por predecesor inorden:
<div align="center">
<img width="70%" src="img/arbol eliminar dos hijos.png">
</div>

Busqueda de elementos en el arbol: para esta operación se utiliza la función abb_buscar que recibe un puntero al arbol y un puntero al elemento a buscar. Se devuelve el puntero devuelto por "abb_buscar_recursivo" que recibe el puntero al arbol, el puntero al elemento y la función comparadora (NOTA: anteriormente había implementado esta funcion igualando el una variable puntero elemento encontrado a las invocaciones de la funcion recursiva, pero la cambié a devolver el puntero a elemento que devuelve la invocación de la función recursiva hecha en clase, generalmente intento pensar mi propia implementación para la mayoría de las funciones pero en este caso me pareció mucho mejor, mas eficiente y mas entendible). En la función recursiva se comprueba si el puntero a raíz apunta a NULL, en ese caso no se encontró el elemento, por lo que se devuelve NULL en la función. En caso de que no, se compara el elemento del nodo con el elemento buscado. Si se devuelve mayor o menor a 0 se devuelve una nueva invocación de abb_buscar_recursivo mandando el puntero al hijo derecho o izquierdo segun corresponda y se sigue recorriendo hasta que se encuentra o hasta que se llega a NULL. Se devuelve el puntero al elemento en el nodo trabajado.

Para destruir el arbol se utiliza la función "abb_destruir_todo" que recibe el puntero al arbol y la función destructora. Utiliza la función recursiva abb_destruir_todo_recursivo, esta hace el tipo de recorrido "postorden" que recorre IDN (izquierda, derecha, nodo) ya es apropiado para destruir cada nodo sin perder referencias de los nodos anteriores. A cada elemento a eliminar se le aplica la función destructora en caso de que esta no sea NULL para después liberar el bloque de memoria de cada nodo.

Como funciones adicionales se solicitaron una para un iterador interno (abb_con_cada_elemento) que recibe el arbol, el recorrido a realizar, una función con dos parametros void* y un puntero a variable auxiliar y recorre de 3 formas diferentes el arbol (Preorden "NID", Inorden "IND", Postorden "IDN") para despues aplicar una función a cada elemento que devuelve true o false,en caso de que devuelva false se para de aplicar la funcion a cada elemento y se devuelve el numero de iteraciones realizadas, otra denominada "abb_recorrer" que, dependiendo del recorrido, utiliza el iterador interno para aplicar una función de extracción donde copia los elementos del arbol y los mete en un vector con un tamaño limitado. La función abb_recorrer utiliza una variable struct que contiene un puntero doble al vector, una variable para el tamaño maximo del vector y otra para la cantidad de elementos en vector (esto se hace para poder utilizar el iterador interno y poder pasar la estructura como un solo puntero void). Primero se comprueba si el arbol está vacío con abb_vacío, si devuelve true se devuelve 0, en caso contrario se comprueba cual es el recorrido solicitado. Si es INORDEN, PREORDEN o POSTORDEN se devuelve lo que devuelva la invocación del iterador interno (devuelve el número de iteraciones), esta recibe el arbol, el recorrido solicitado, la función insertar_elementos_en_vector y la direccion de memoria del struct vector. La función insertar_elementos_en_vector inserta el elemento recibido como primer parámetro en el puntero a struct vector recibido como segundo parámetro y devuelve true si queda espacio en el vector o false si no se pueden seguir insertando mas elementos (recordar que se deja de iterar cuando la función del iterador interno devuelve false). Se devuelve el numero de elementos insertados en el vector o 0 si el arbol está vacío o si el recorrido no corresponde a los pedidos. 

## Respuestas a las preguntas teóricas

Explique teóricamente qué es una árbol, árbol binario y árbol
    binario de búsqueda. Explique cómo funcionan, cuáles son sus operaciones básicas
    (incluyendo el análisis de complejidad de cada una de ellas) y por qué es
    importante la distinción de cada uno de estos diferentes tipos de
    árboles. Ayúdese con diagramas para explicar.

Un arbol es un tipo de dato abstracto (TDA) conformado por una colección de nodos con un elemento conectados a otros nodos con otros elementos. La característica principal es que el primer nodo se lo llama raíz, este puede estar conectado a un numero diferente de nodos (hijos), y estos nodos a otros nodos (creando subarboles) identificando así niveles dentro del arbol. Si nos paramos en un nodo, el nodo por encima de este se denomina padre, solo puede tener uno, los nodos a los que se conecta hacia abajo el mismo se denominan hijos. Un nodo sin hijos se denomina nodo hoja. Podemos tambien identificar subarboles en los nodos.

Representación gráfica: 
<div align="center">
<img width="70%" src="img/arbol diagrama.png">
</div>

Arbol binario: un arbol binario es un tipo de arbol caracterizado por el número máximo de hijos que puede tener cada nodo (2). Esto nos permite determinar la noción de izquierda y derecha. 

Arbol binario:
<div align="center">
<img width="70%" src="img/arbol binario.png">
</div>

El arbol binario de búsqueda es un tipo de arbol binario caracterizado por estar organizado dependiendo de un orden, por lo tanto tenemos una forma de comparar los elementos al realizar la función deseada aumentando la eficiencia de las mismas. En este caso, el hijo con la clave menor a la del padre está como hijo izquierdo del padre y el hijo con la clave mayor como hijo derecho. Los subarboles izquierdos y derechos también son arboles binarios de busqueda.

Arbol binario de búsqueda:
<div align="center">
<img width="70%" src="img/arbol binario de busqueda.png">
</div>

Es importante la distinción de cada tipo de arbol ya que cada uno tiene sus ventajas y desventajas, los arboles n-arios permiten que cada nodo tenga 2 o mas hijos, los arboles binarios facilitan el recorrido haciendo que cada nodo solo pueda tener 2 hijos, y el arbol binario de búsqueda facilita la búsqueda de los elementos haciendo que cada elemento se inserte con un orden en mente, aumentando la eficiencia de búsqueda de los elementos.

Funciones básicas:

Crear: complejidad O(1) ya que se debe reservar el bloque de memoria para el arbol y devolver el puntero.

Insertar: en el arbol binario de búsqueda esta operación en promedio es un O(log(n)) ya que se va tomando un camino de derecha o izquierda en cada nodo, dependiendo de si este es mayor o menor del elemento a insertar, en cada nivel dividiendo la n por 2 cada vez que se toma un camino, una vez se llega a la posición donde se debe insertar se reserva memoria para el nodo, y se inserta el elemento. En el peor de los casos (que cada nodo del arbol tenga un solo hijo) es un O(n) ya que se debe recorrer el arbol.

Quitar: en el caso del arbol y del arbol binario, en el peor de los casos es un O(n) ya que no tiene un tipo de organización y se debe recorrer todo el arbol para encontrar el elemento a quitar. En el caso del arbol binario de búsqueda sería un O(log(n)) en el caso promedio ya que, a medida que bajamos de nivel se toma un camino por izquierda o por derecha buscando el elemento a eliminar, por lo tanto se divide la n por 2 en cada nivel. Si el nodo es un nodo hoja solo se elimina el nodo del arbol y se libera la memoria. Si tiene un hijo, despues de liberar la memoria se "engancha" el hijo al padre del nodo eliminado. En el caso de tener dos hijos se debe reemplazar el elemento en el nodo con otro elemento en su lugar (en el caso de este trabajo se pidió el predecesor inorden por lo tanto se reemplazó por ese, puede ser también sucesor inorden), se libera la memoria del nodo del elemento por el cual se reemplazó y se "engancha" su hijo al nodo padre. En el peor de los casos, como se especificó en función quitar es un O(n). Se devuelve el elemento eliminado.

Destruir: Libera la memoria utilizada por cad nodo y por el arbol. En el arbol, el arbol binario, y el arbol binario de búsqueda esta operación en un O(n) ya que se debe recorrer cada elemento del arbol para destruirlos uno por uno.

Vacío: identifica si el arbol está vacío. Es un O(1) ya que se debe ver si el puntero a raíz apunta a NULL. En el caso de este trabajo se revisó si el contador de elementos en el arbol especificado en la estructura del mismo es 0 o si el puntero al arbol es nulo 

Buscar: en el arbol y del arbol binario, en el peor de los casos es un O(n) ya que no tiene un tipo de organización y se debe recorrer todo el arbol para encontrar el elemento. En el arbol binario de búsqueda es un O(log(n)) ya que se toma un camino de izquierda o derecha en cada nivel del arbol comparando los elementos hasta encontrar el mismo. Como se especificó puede ser un O(n) si cada nodo del arbol tiene un solo hijo.

Recorrer: para recorrer los arboles binarios de búsqueda se tienen 6 tipos de recorridos (NID IND IDN NDI DNI DIN), pero a nosotros nos sirven más 3 de esos: 

Preorden: (NID) se visita primero el nodo actual, después el izquierdo y por último el derecho. Este tipo de recorrido nos sirve mas que nada si necesitamos hacer una copia exacta del arbol y a medida que recorremos copiamos e insertamos en otro arbol.

Inorden: (IND) se visita primero el nodo izquierdo, después el actual y por último el derecho. Este recorrido, si a medida que lo ejecutamos vamos sacando los elementos y poniendolos en un vector, nos damos cuenta que los elementos quedan ordenados de menor a mayor.

Postorden: (IDN) se visita primero el nodo izquierdo, después el derecho y por último el actual. En el caso de este trabajo se utilizó para la función abb_destruir_todo ya que se puede aplicar un free a cada nodo actual cuando se recorre este y en ningún momento se pierde referencia a otros nodos, haciendo que no quede memoria sin liberar.

Decisiones de diseño:

Para las funciones que exigían un recorrido del arbol (inserción, eliminación, destrucción, búsqueda) se utilizaron funciones adicionales recursivas, más que nada para facilitar la programación y el entendimiento de la recursividad y del código. En mi caso intento hacer las funciones realizando implementaciones propias al principio, en el caso de búsqueda, destrucción y al realizar recorridos del iterador interno recorría el arbol de la misma forma que inserción y eliminación (haciendo que las funciones sean nodo_abb_t, igualando el nodo que se va recorrer a la invocación y devolviendo el nodo al final),  para después terminar cambiando por las que están implementadas ahora al saber que no era necesario, haciendo que el codigo sea mas corto y entendible. Para las variables booleanas y algún puntero a elemento que necesitaba devolver al final decidí pasar su dirección de memoria como parámetro y así cambiar su valor en las funciones recursivas para no tener que devolverlos (me pareció que se entiende más), tuve alguna que otra dificultad intentando que funcione de esta forma que se arreglaron después de búsquedas por internet. Para las pruebas decidí usar enteros como elementos para los nodos del arbol, teniendo así una sola función comparadora y para no complicar la programación. 