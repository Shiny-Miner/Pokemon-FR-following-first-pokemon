# Pokemon FR Follow me
 Pokémon FR follow me.


***Notas:***

- DevkitARM y ARMIPS son necesarios.

- Para compilar es necesario tener preproc.exe y gbagfx.exe dentro alguna ruta de la variable PATH

- Abrir el archivo config.mk, buscar y cambiar fa0000 de la siguiente línea por un offset alineado con suficiente espacio libre:
        `INSERT_INTO ?= 0x08ff0000`
- En el archivo config.mk, buscar la siguiente línea
        `ROM_CODE ?= BPRE`
        - mantener  BPRE para compilar usando Fire Red
        - cambiar a BPRS para compilar usando Rojo Fuego en español

- Compilan ejecutando make con su terminal, y una rom con la inyección aparecerá en una carpeta llamada build.

- Archivos dentro de la carpeta `include` fueron tomados de pokefirered.

