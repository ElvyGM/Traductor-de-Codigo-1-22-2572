# Traductor Python a C Sharp

Aplicacion grafica desarrollada con C++ 17 y Qt 6 Widgets. Convierte un subconjunto didactico de Python a codigo C# legible y muestra errores con numero de linea.

## Construcciones compatibles

- Variables enteras, reales, cadenas y booleanas.
- Asignaciones y expresiones aritmeticas.
- `print()` a `Console.WriteLine()`.
- Condicionales `if`, `elif` y `else`.
- Ciclos `while`.
- Ciclos `for` con `range(inicio, fin, paso)`.
- Funciones sencillas con `def` y `return`.
- Comentarios iniciados con `#`.
- Operadores `and`, `or`, `not`, `True`, `False` y `None`.
- Conversion de la indentacion de Python en llaves de C#.

## Reglas de traduccion

| Python | C# |
|---|---|
| `print(x)` | `Console.WriteLine(x);` |
| `True` y `False` | `true` y `false` |
| `and`, `or`, `not` | `&&`, `||`, `!` |
| `if condicion:` | `if (condicion) { ... }` |
| `elif condicion:` | `else if (condicion) { ... }` |
| `while condicion:` | `while (condicion) { ... }` |
| `for i in range(0, 5):` | `for (int i = 0; i < 5; i += 1) { ... }` |
| `def suma(a, b):` | `public static dynamic suma(dynamic a, dynamic b) { ... }` |
| `# comentario` | `// comentario` |

Los tipos se infieren en la primera asignacion: numeros enteros se convierten en `int`, decimales en `double`, textos en `string` y booleanos en `bool`. Cuando no puede inferirse un tipo seguro se utiliza `var`.

## Estructura

- `translator.cpp` y `translator.h`: motor de traduccion.
- `mainwindow.cpp`, `mainwindow.h` y `mainwindow.ui`: interfaz grafica.
- `main.cpp`: inicio de la aplicacion.
- `PRUEBAS.md`: casos de demostracion.
- `CMakeLists.txt`: configuracion para Qt Creator.

## Compilacion

1. Abra `CMakeLists.txt` en Qt Creator.
2. Seleccione `Desktop Qt 6.11.2 MinGW 64-bit`.
3. Active Debug o Release.
4. Pulse `Configure Project`.
5. Compile con `Ctrl + B` y ejecute con `Ctrl + R`.

## Uso

1. Escriba Python en el panel izquierdo o pulse **Cargar ejemplo**.
2. Pulse **Traducir**.
3. Revise C# en el panel derecho.
4. Pulse **Copiar C#** para llevar el resultado al portapapeles.

## Limitaciones

No implementa todo Python. No traduce clases, comprensiones, decoradores, excepciones, importaciones ni tipado complejo. La indentacion debe utilizar grupos de cuatro espacios. El resultado es didactico y puede requerir ajustes para compilar programas avanzados.
