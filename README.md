# Pokemon FR Follow me
Pokemon Fire Red Follow me.
Port del follow me hecho por Ghoulslash en pokeemerald:
        https://github.com/ghoulslash/pokeemerald/tree/follow_me

Adaptación hasta el commit:
        `3782cdfb4e8b06cab909e360b816ab730bbefae9`
        `fix setfollower for real`
        `ghoulslash committed Mar 28, 2022`

***Notas:***

- DevkitARM y ARMIPS son necesarios.

- Para compilar es necesario tener preproc.exe y gbagfx.exe dentro alguna ruta de la variable PATH

- Abrir el archivo config.mk, buscar y cambiar fa0000 de la siguiente línea por un offset alineado con suficiente espacio libre:
        `INSERT_INTO ?= 0x08fa0000`
- En el archivo config.mk, buscar la siguiente línea
        `ROM_CODE ?= BPRE`
    - mantener  BPRE para compilar usando Fire Red
    - cambiar a BPRS para compilar usando Rojo Fuego en español

- Compilan ejecutando make con su terminal, y una rom con la inyección aparecerá en una carpeta llamada build.

- Archivos dentro de la carpeta `include` fueron tomados de [**pokefirered**](https://github.com/pret/pokefirered).


## Script Follow me

- Los specials usados en esta inyección son:

        - 0x10 Setfollower (se configura poniendo antes 2 setvar: 0x8000 = local id, 0x8001 = flags)
        - 0x11 DestroyFollower
        - 0x12 PlayerFaceFollowerSprite
        - 0x13 CheckPlayerHasFollower
- Para que un NPC te siga, en advance map ponemos un script usando esta plantilla:

      setvar 0x8000 0x1 //NPC local id
      setvar 0x8001 0xBF //flags
      special 0x10 //Setfollower
- Si añades más cosas al script, asegúrate de poner un texto al final con `msgbox`

- Para que el NPC deje de seguirte, en otro script usa el `special 0x11`

- Las flags son las siguiente:

        - FOLLOWER_FLAG_HAS_RUNNING_FRAMES    0x1
        - FOLLOWER_FLAG_CAN_BIKE              0x2
        - FOLLOWER_FLAG_CAN_LEAVE_ROUTE       0x4     // teleport, dig, fly, etc
        - FOLLOWER_FLAG_CAN_SURF              0x8
        - FOLLOWER_FLAG_CAN_WATERFALL         0x10
        - FOLLOWER_FLAG_CAN_DIVE              0x20
        - FOLLOWER_FLAG_CAN_ROCK_CLIMB        0x40    // need rock climb implemented
        - FOLLOWER_FLAG_CLEAR_ON_WHITE_OUT    0x80
        - FOLLOWER_FLAG_CUSTOM_FOLLOW_SCRIPT  0x100   // follower has custom script while following (use loadword prior to setfollower)
- Sumas los valores en hexadecimal de las flags que quieras para tu NPC y la pones a la variable 0x8001 en tu script con setvar

***Advertencia:***
Este sistema todavía no es funcional con el sistema de escaleras laterales (SIDEWAYS STAIRS)
