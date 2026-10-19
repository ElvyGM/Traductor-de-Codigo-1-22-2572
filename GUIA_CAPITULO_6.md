# Guia de trabajo del Capitulo 6

Libro de referencia: Compiladores principios tecnicas y herramientas, segunda edicion. El capitulo 6 trata la generacion de codigo intermedio.

Esta guia organiza los ejercicios detectados en el capitulo para resolverlos en manuscrito. Los ejercicios que dependen de figuras deben copiarse junto con la figura correspondiente antes de desarrollar tablas, grafos o listas.

## 6.1 Variantes de arboles sintacticos

- **6.1.1:** construir el GDA creando una sola hoja por identificador y reutilizando los nodos de `x+y` y `x-y`. La segunda aparicion del producto debe apuntar al mismo nodo producto. La raiz suma el nodo de la resta exterior con ese producto compartido.
- **6.1.2:** numerar primero las hojas y despues cada suma nueva. Solo se reutiliza un numero de valor cuando coinciden operador, hijo izquierdo e hijo derecho; la asociatividad izquierda hace diferentes a expresiones con el mismo texto parcial pero distinta estructura.

## 6.2 Codigo de tres direcciones

- **6.2.1:** descomponer cada expresion para que cada instruccion tenga como maximo un operador; usar temporales `t1`, `t2`, etc.
- **6.2.2:** convertir el codigo de tres direcciones en cuadruplos `(op, arg1, arg2, resultado)`.
- **6.2.3:** sustituir temporales por referencias a posiciones para obtener tripletas; en tripletas indirectas crear una lista separada de apuntadores.

## 6.3 Tipos y declaraciones

- **6.3.1:** calcular tipos desde los constructores basicos hacia arreglos y apuntadores; registrar tipo y ancho en la tabla de simbolos.
- **6.3.2:** acumular desplazamientos sumando el ancho de cada declaracion y restaurar el desplazamiento al salir de un ambito.

## 6.4 Traduccion de expresiones

- **6.4.1 a 6.4.3:** aplicar precedencia y asociatividad, generar temporales para cada nodo interior y emitir una copia final al destino.
- **6.4.4 a 6.4.6:** para arreglos, calcular el desplazamiento multiplicando cada indice por el ancho de su dimension y del elemento.
- **6.4.7 a 6.4.9:** distinguir l-value y r-value; generar carga para leer un elemento y almacenamiento indexado para escribirlo.

## 6.5 Comprobacion y conversion de tipos

- **6.5.1:** construir expresiones de tipo y unificar solo tipos compatibles.
- **6.5.2:** insertar conversiones explicitas cuando el operando de menor rango debe promoverse; la conversion insegura en sentido contrario debe marcar error o requerir cast.

## 6.6 Flujo de control

- **6.6.1 a 6.6.4:** generar etiquetas para verdadero, falso y siguiente; traducir `and`, `or` y `not` mediante evaluacion de cortocircuito.
- **6.6.5 a 6.6.8:** traducir `if`, `if-else` y ciclos colocando saltos condicionales al bloque correcto y un salto de retorno a la prueba del ciclo.

## 6.7 Parcheo de retroceso

- **6.7.1:** iniciar en la instruccion 100, crear `truelist` y `falselist` para cada comparacion y combinar listas segun `and`, `or` y `not`.
- **6.7.2:** sustituir cada hueco por la etiqueta `i1` a `i8` que corresponde al inicio del bloque alcanzado en la figura 6.47.
- **6.7.3:** formar `S4.siguiente` desde la lista falsa de `E3`; combinar para bloques; parchear las listas verdaderas hacia el cuerpo y las falsas hacia la alternativa o salida.

## 6.8 Instrucciones switch

- **6.8.1:** la definicion orientada por sintaxis debe sintetizar una lista de pares `(valor, etiqueta)`. Cada `case` crea una etiqueta, agrega el par, emite la etiqueta y traduce su instruccion. Al final se emiten las comparaciones y el salto a `default`.

## Formato recomendado para el manuscrito

1. Escribir numero y enunciado resumido.
2. Dibujar el arbol, GDA o diagrama solicitado con regla y lapiz.
3. Numerar temporales, nodos o instrucciones en orden.
4. Presentar codigo de tres direcciones en una columna.
5. Colocar cuadruplos, tripletas o listas en tabla cuando corresponda.
6. Terminar con una frase que explique por que se reutiliza un nodo, se inserta una conversion o se parchea un salto.

## Lista de control

`6.1.1`, `6.1.2`, `6.2.1`, `6.2.2`, `6.2.3`, `6.3.1`, `6.3.2`, `6.4.1`, `6.4.2`, `6.4.3`, `6.4.4`, `6.4.5`, `6.4.6`, `6.4.7`, `6.4.8`, `6.4.9`, `6.5.1`, `6.5.2`, `6.6.1`, `6.6.2`, `6.6.3`, `6.6.4`, `6.6.5`, `6.6.6`, `6.6.7`, `6.6.8`, `6.7.1`, `6.7.2`, `6.7.3`, `6.8.1`.
