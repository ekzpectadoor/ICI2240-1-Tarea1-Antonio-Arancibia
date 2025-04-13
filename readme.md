# Sistema de Gestión de Tickets de Soporte Técnico

## Descripción

Este sistema permite gestionar tickets de soporte técnico en una empresa mediante un sistema de colas con prioridades. Los tickets se organizan por urgencia (**Alto**, **Medio**, **Bajo**) y hora de registro, priorizando los casos más urgentes. La aplicación facilita el registro, modificación de prioridades, atención ordenada y consulta de tickets pendientes.

---

## Cómo compilar y ejecutar

El programa está desarrollado en **C** y puede compilarse fácilmente utilizando **Visual Studio Code** con las siguientes configuraciones:

### Requisitos previos:
- **Visual Studio Code**
- Extensión **C/C++ Extension Pack**.
- Compilador **gcc**.

### Pasos para compilar y ejecutar:
1. **Descargar** los archivos del repositorio y guardarlos en una carpeta.
2. **Abrir el proyecto en VS Code**:
   - `Archivo > Abrir carpeta...` → Seleccionar la carpeta del proyecto.
3. **Editar tasks.json**:
   - Revisar el tasks.json proporcionado y configurarlo segun como tenga instalado MINGW (sino, asegurarse que su archivo propio use los mismos argumentos que el proporcionado)
4. **Compilar el código**:
   - Abrir la terminal integrada (`Terminal > Nueva terminal`).
   - Ejecutar:
     
     gcc main.c list.c extras.c -o gestion_tickets
     
5. **Ejecutar el programa**:
   - Ejecutar:
     gestion_tickets.exe
   
---

## Funcionalidades

### Funcionando correctamente:
- **Registrar Tickets**:  
  Solicita ID único y descripción. Asigna hora actual y prioridad "Bajo" automáticamente.
- **Mostrar Tickets Pendientes**:  
  Lista ordenada por prioridad (Alto > Medio > Bajo) y hora de registro (más antiguo primero).
- **Procesar Siguiente Ticket**:  
  Atiende el ticket de mayor prioridad y más antiguo, eliminándolo de la lista.
- **Buscar Ticket por ID**:  
  Muestra detalles completos si el ticket existe.

### Problemas conocidos:
- **Limpieza de pantalla**:  
  - *Comportamiento inesperado*: Al terminar una operacion, la pantalla no se limpia completamente.  
  - *Causa probable*: Desconocida.
- **Registrar Ticket**:
  - *Comportamiento inesperado*: Si en la ID se le ingresa un string, el programa falla y muestra valores no validos en la ID.  
  - *Causa probable*: No hay un filtro en codigo para aquello, solo un texto.

### A mejorar:
  - Implementar una interfaz más bonita
  - Resolver el problema de no limpiar la pantalla correctamente
  - Implementar una solucion en codigo si la entrada es un string en la ID (para no depender del aviso que ya se da)
---

## Ejemplo de uso

**Paso 1: Registrar un nuevo ticket**  
Un usuario reporta un error crítico en el sistema de facturación.
Opción seleccionada: 1. Registrar Tickets
Ingrese la ID del ticket (solo números): 205
Ingrese el problema (máximo 500 caracteres): El sistema no genera facturas.
El sistema registra el ticket con prioridad "Bajo" y hora actual.
---

**Paso 2: Elevar prioridad del ticket**  
Un técnico determina que el error es crítico y actualiza la prioridad.
Opción seleccionada: 2 Asignar prioridad a Ticket
Ingrese la ID del Ticket y luego su prioridad (Alto, Medio, Bajo): 205 
Alto
Prioridad actualizada con éxito.
---

**Paso 3: Ver tickets pendientes**  
Se revisa la lista para confirmar la prioridad actualizada.
Opción seleccionada: 3 Mostrar Tickets pendientes
#1
ID: 205
Descripción: El sistema no genera facturas.
Prioridad: Alto
Hora: 15:22:10 //de ejemplo, en realidad es la hora en la que registro el ticket
#2
ID: 204
Descripción: Una pantalla tiene una linea negra.
Prioridad: Bajo
Hora: 15:01:03
---

**Paso 4: Atender el ticket prioritario**  
El equipo de soporte procesa el ticket urgente.
Opción seleccionada: 4 Procesar siguiente Ticket
ID: 205
Descripción: El sistema no genera facturas.
Prioridad: Alto
Hora: 15:22:10
El ticket se elimina de la lista, y el equipo inicia la solución del problema.
--- 

**Paso 5: Buscar un Ticket**
Una persona habla con soporte tecnico y le menciona su ticket a estos
Opción seleccionada: 5 Buscar Ticket por ID
Ingrese el Ticket a Buscar: 204
ID: 204
Descripción: Una pantalla tiene una linea negra.
Prioridad: Bajo
Hora: 15:01:03
El ticket es mostrado en pantalla y se tiene una idea el problema y el momento en que sucedio.

**Paso 6: Salir del sistema**
El dia se da por terminado y se deja de recibir tickets.
Saliendo del sistema de gestión de Tickets...

**Nota**: Al salir, se libera la memoria utilizada por los tickets.





