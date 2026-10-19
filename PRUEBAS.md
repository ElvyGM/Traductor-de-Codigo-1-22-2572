# Pruebas del Traductor

## Variables y condicional

```python
nombre = "Elvy"
edad = 22
if edad >= 18:
    print(nombre)
else:
    print("Menor")
```

Debe generar variables `string` e `int`, un bloque `if/else` y llamadas a `Console.WriteLine`.

## Ciclo for

```python
for i in range(0, 5):
    print(i)
```

Debe generar un `for` de C# desde cero hasta cuatro.

## Ciclo while

```python
contador = 0
while contador < 3:
    print(contador)
    contador = contador + 1
```

Debe generar un `while`, conservar la asignacion y cerrar el bloque con llave.

## Funcion

```python
def sumar(a, b):
    return a + b
```

Debe generar un metodo estatico con parametros `dynamic` y una sentencia `return`.

## Error de indentacion

```python
if True:
  print("mal indentado")
```

Debe reportar que la linea 2 no utiliza grupos de cuatro espacios.
