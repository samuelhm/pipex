# Pipex

![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)
![42 School](https://img.shields.io/badge/School-42_Barcelona-000000?style=flat-square&logo=42&logoColor=white)
![Unix](https://img.shields.io/badge/Platform-UNIX/Linux-4A4A4A?style=flat-square&logo=linux&logoColor=white)
![Processes](https://img.shields.io/badge/Concept-Process_Management-blue?style=flat-square)
![IPC](https://img.shields.io/badge/Concept-Inter_Process_Communication-orange?style=flat-square)
![System Calls](https://img.shields.io/badge/Concept-System_Calls-critical?style=flat-square)

---

## Descripción

**Pipex** es una implementación en C que replica el comportamiento del operador pipe (`|`) de la shell de UNIX. Simula la ejecución encadenada de comandos, donde la salida del primer comando se convierte en la entrada del segundo, tal como ocurre en ejecuciones como `cat file | grep pattern`.

El proyecto demuestra competencias en gestión de procesos, comunicación inter-proceso (IPC), manipulación de descriptores de archivo y llamadas al sistema de bajo nivel.

---

## Funcionalidades

- Replicación del comportamiento del pipe de shell (`|`)
- Lectura desde archivo de entrada (`infile`)
- Escritura hacia archivo de salida (`outfile`)
- Ejecución de dos comandos encadenados
- Manejo de errores robusto con mensajes descriptivos
- Limpieza correcta de recursos y descriptores

---

## Stack Tecnológico

| Categoría | Tecnología |
|-----------|------------|
| Lenguaje | C (GCC) |
| Compilación | Makefile con flags `-Wall -Wextra -Werror` |
| Librería personalizada | [Libft](https://github.com/samuelhm/libft) (submódulo) |
| System Calls | `fork()`, `pipe()`, `dup2()`, `execve()`, `waitpid()` |
| Headers estándar | `<unistd.h>`, `<fcntl.h>`, `<sys/wait.h>`, `<stdbool.h>` |

---

## Arquitectura y Decisiones Técnicas

El proyecto implementa un modelo de **dos procesos hijo spawned desde un proceso padre**, comunicados a través de un **pipe anónimo**. El primer proceso redirige su entrada estándar al archivo de entrada (`infile`) y su salida estándar al pipe mediante `dup2()`. El segundo proceso toma la salida del pipe como su entrada y redirige su salida al archivo final (`outfile`). Esta arquitectura resuelve el reto fundamental de sincronizar la ejecución paralela de comandos UNIX respetando la semántica del operador pipe.

El uso de `execve()` con `/bin/bash -c "comando"` permite procesar comandos complejos con argumentos, delegando el parsing a la shell. La estructura `t_pipedata` encapsula todos los recursos del proyecto (descriptores de archivo, PIDs), facilitando el manejo seguro de memoria y la liberación ordenada de recursos.

---

## Flujo de Ejecución

```mermaid
flowchart TD
    A[Inicio: main] --> B[Abrir infile y outfile]
    B --> C[Crear pipe pipefd_2_]
    C --> D[Fork: Crear proceso hijo 1]
    D --> E[Fork: Crear proceso hijo 2]
    
    E --> F[Proceso Hijo 1]
    E --> G[Proceso Hijo 2]
    
    F --> H[dup2: infile → STDIN]
    H --> I[dup2: pipe_1_ → STDOUT]
    I --> J[execve: ejecutar cmd1]
    
    G --> K[dup2: pipe_0_ → STDIN]
    K --> L[dup2: outfile → STDOUT]
    L --> M[execve: ejecutar cmd2]
    
    J --> N[Proceso Padre]
    M --> N
    N --> O[waitpid: esperar hijos]
    O --> P[Cerrar descriptores]
    P --> Q[Liberar memoria]
    Q --> R[Fin]

    style A fill:#e1f5fe
    style R fill:#e8f5e8
    style F fill:#fff3e0
    style G fill:#fff3e0
    style N fill:#f3e5f5
```

---

## Instalación

### Requisitos

- GCC (compilador C)
- Make
- Sistema operativo UNIX/Linux o macOS

### Pasos

```bash
# Clonar el repositorio con submódulos
git clone --recursive https://github.com/samuelhm/pipex.git

# Entrar al directorio
cd pipex

# Compilar el proyecto
make
```

### Uso

```bash
# Sintaxis
./pipex infile cmd1 cmd2 outfile

# Ejemplo: equivalente a 'cat infile | grep pattern > outfile'
./pipex infile "cat" "grep pattern" outfile

# Ejemplo con más comandos
./pipex input.txt "ls -la" "wc -l" output.txt
```

---

## Limpieza

```bash
# Limpiar objetos
make clean

# Limpiar todo (incluyendo binario)
make fclean

# Recompilar completamente
make re
```

---

## Estructura del Proyecto

```
pipex/
├── inc/
│   └── pipex.h          # Header con estructuras y prototipos
├── src/
│   ├── pipex.c          # Punto de entrada y lógica principal
│   └── process.c        # Funciones de ejecución de procesos
├── lib/
│   └── libft/           # Librería personalizada (submódulo)
├── Makefile             # Reglas de compilación
└── README.md
```

---

## Contacto

| Plataforma | Enlace |
|------------|--------|
| GitHub | [github.com/samuelhm](https://github.com/samuelhm/) |
| LinkedIn | [linkedin.com/in/shurtado-m](https://www.linkedin.com/in/shurtado-m/) |

---