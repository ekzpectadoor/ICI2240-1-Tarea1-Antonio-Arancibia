#include "list.h"
#include "extras.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Estructura del Ticket */
typedef struct {
  int ID;                     // Identificador único (numérico)
  char descripcion[501];      // Descripción del problema (máx 500 caracteres)
  time_t hora_tiempo;         // Tiempo en distinto formato para ordenamiento
  char hora[20];              // Hora legible (formato HH:MM:SS)
  unsigned short prioridad_num; // Prioridad numérica: 1 (Alto), 2 (Medio), 3 (Bajo)
} Ticket;

void mostrarMenuPrincipal() {
  puts("========================================");
  puts("     Sistema de Gestion Tickets");
  puts("========================================");
  puts("1) Registrar Tickets");
  puts("2) Asignar prioridad a Ticket");
  puts("3) Mostrar Tickets pendientes");
  puts("4) Procesar siguiente Ticket");
  puts("5) Buscar Ticket por ID");
  puts("6) Salir");
}
/**
 * Compara dos tickets para ordenamiento.
 * - Retorno: <0 si t1 va antes, >0 si t2 va antes, 0 si iguales.
 * - Orden: Primero por prioridad (menor número primero), luego por hora (más antiguo primero).
 */
int comparacion( void* piv1,  void* piv2)
{
  Ticket *t1 = (Ticket*) piv1;
  Ticket *t2 = (Ticket*) piv2;
  if(t1->prioridad_num != t2->prioridad_num)
  {
    return t1->prioridad_num - t2->prioridad_num;
  }
  double diferencia = difftime(t1->hora_tiempo, t2->hora_tiempo);
  if (diferencia > 0) 
  {
    return 1;
  } 
  else if (diferencia == 0) 
  {
    return 0;
  } 
  else 
  {
    return -1;
  }
}
/**
 * Registra un nuevo ticket en la lista.
 * - Valida si el ID es único.
 * - Obtiene el ID.
 * - Obtiene la descripción.
 * - Asigna la hora y prioridad inicial "Bajo".
 * - Inserta ordenadamente el ticket a la lista.
 */
void registrar_tickets(List *tickets) {
  Ticket *nuevo_ticket = (Ticket*) malloc(sizeof(Ticket));
  if(nuevo_ticket == NULL)
  {
    printf("Error al asignar memoria");
    return;
  }
  printf("Ingrese la ID del ticket (solo numeros)\n");
  scanf("%d", &nuevo_ticket->ID);
  Ticket *aux = (Ticket *)list_first(tickets);
  while (aux != NULL) // Se verifica si el ID ya existe o no
  {
    if (aux->ID == nuevo_ticket->ID) 
    {
      printf("ID ya registrado\n");
      free(nuevo_ticket);
      return;
    }
  aux = (Ticket *)list_next(tickets);
  }
  printf("Ingrese el problema (maximo 500 caracteres)\n");
  getchar();
  fgets(nuevo_ticket->descripcion, sizeof(nuevo_ticket->descripcion), stdin);
  nuevo_ticket->descripcion[strcspn(nuevo_ticket->descripcion, "\n")] = '\0';
  nuevo_ticket->prioridad_num = 3;  // Prioridad inicial: Bajo
  time_t hora = time(NULL);
  nuevo_ticket->hora_tiempo = hora;
  struct tm *tm_info = localtime(&hora);
  strftime(nuevo_ticket->hora, sizeof(nuevo_ticket->hora), "%H:%M:%S", tm_info);
  list_sortedInsert(tickets, nuevo_ticket, comparacion);
  printf("Ticket registrado con exito");
}

/**
 * Modifica la prioridad de un ticket existente.
 * - Busca por ID y revisa si es que existe o no.
 * - Actualiza prioridad y reordena la lista.
 */
void asignar_prioridad(List *tickets){
  int ID_buscar;
  int flag = 1;
  char prioridad[6];
  printf("Ingrese la ID del Ticket y luego su prioridad (Alto, Medio, Bajo):");
  scanf("%d", &ID_buscar);
  getchar();
  scanf(" %5s", prioridad);
  Ticket * auxiliar = (Ticket *)list_first(tickets);
  while (auxiliar != NULL)
  {
    if(ID_buscar == auxiliar->ID)
    {
      flag = 0;
      if(strcmp(prioridad, "Alto") == 0)
      {
        auxiliar->prioridad_num = 1;
        break;
      }
      else if(strcmp(prioridad, "Medio") == 0)
      {
        auxiliar->prioridad_num = 2;
        break;
      }
      else if(strcmp(prioridad, "Bajo") == 0)
      {
        auxiliar->prioridad_num = 3;
        break;
      }
      else
      {
        printf("Prioridad no valida");
        printf("\n");
        break;
      }
    }
    auxiliar = (Ticket *)list_next(tickets);
  }
  if(flag == 1)
  {
    printf("La ID ingresada no esta registrada");
    printf("\n");
    return;
  }
  Ticket *data = list_popCurrent(tickets);
  list_sortedInsert(tickets, data, comparacion);
  printf("Prioridad actualizada con éxito.\n");  
}

/**
 * Muesta la lista de Tickets ordenados por prioridad y hora
 * - Itera imprimiendo todos los datos hasta que no haya mas en la lista.
 * - Verifica si la lista esta vacia o no.
 */
void mostrar_lista_tickets(List *tickets) {
  if((Ticket *)list_first(tickets) == NULL)
  {
    printf("No hay tickets pendientes");
    return;
  }
  printf("Lista de Tickets pendientes: \n");
  Ticket *aux = (Ticket *)list_first(tickets);
  int cont = 1;
  while (aux != NULL)
  {
    printf("===========================================\n");
    printf("#%i\n", cont);
    printf("ID: %i\n", aux->ID);
    printf("Descripcion: %s\n", aux->descripcion);
    printf("Prioridad: ");
    switch (aux->prioridad_num)
    {
    case 1:
      printf("Alto");
      break;
    case 2:
      printf("Medio");
      break;
    case 3:
      printf("Bajo");
      break;
    }
    printf("\n");
    printf("Hora: %s", aux->hora);
    printf("\n");
    printf("===========================================\n");
    cont++;
    aux = list_next(tickets);
  }
}
/**
 * Atiende el ticket con mayor prioridad.
 * - Verifica si la lista esta vacia.
 * - Debido a que la lista ya esta ordenada, se toma el primer elemento de la lista y se imprime.
 * - Se elimina el primer elemento de la lista.
 */
void atender_siguiente_ticket(List* tickets)
{
  if((Ticket *)list_first(tickets) == NULL)
  {
    printf("No hay tickets pendientes\n");
    return;
  }
  Ticket *aux = (Ticket *)list_first(tickets);
  printf("===========================================\n");
  printf("ID: %i\n", aux->ID);
  printf("Descripcion: %s\n", aux->descripcion);
  printf("Prioridad: ");
  switch (aux->prioridad_num)
  {
  case 1:
    printf("Alto");
    break;
  case 2:
    printf("Medio");
    break;
   case 3:
    printf("Bajo");
    break;
  }
  printf("\n");
  printf("Hora: %s\n", aux->hora);
  printf("===========================================\n");
  list_popFront(tickets);
}
/**
 * Buscar Ticket por ID.
 * - Se verifica si la lista esta vacia.
 * - Se busca por ID en la lista y se revisa si es que existe o no.
 * - Imprime los datos correspondientes a esa ID y si no esta imprime un mensaje de error.
 */
void buscar_ticket_id (List *tickets){
  int ID_buscar;
  printf("Ingrese el Ticket a Buscar");
  getchar();
  scanf("%d", &ID_buscar);
  Ticket *aux = (Ticket *)list_first(tickets);
  while (aux != NULL)
  {
    if(aux->ID == ID_buscar)
    {
      printf("===========================================\n");
      printf("ID: %d\n", aux->ID);
      printf("Descripcion: %s\n", aux->descripcion);
      printf("Prioridad: ");
      if (aux->prioridad_num == 3)
      {
        printf("Bajo");
      }
      else if (aux->prioridad_num == 2)
      {
        printf("Medio");
      }
      else
      {
        printf("Alto");
      }
      printf("\n");
      printf("Hora: %s", aux->hora);
      printf("\n");
      printf("===========================================\n");
      return;
    }
    aux = (Ticket *)list_next(tickets);
  }
  printf("No hay un Ticket registrado con tal ID");
  printf("\n");
}

int main() {
  int opcion;
  List *tickets = list_create(); 

  do {
    limpiarPantalla();
    mostrarMenuPrincipal();
    printf("Ingrese su opcion (solo numeros): ");
    scanf("%i", &opcion); 
    switch (opcion) {  // cada caso es una opcion del menu
    case 1:
      registrar_tickets(tickets);
      
      break;
    case 2:
      asignar_prioridad(tickets);
     
      break;
    case 3:
      mostrar_lista_tickets(tickets);
    
      break;
    case 4:
      atender_siguiente_ticket(tickets);
     
      break;
    case 5:
      buscar_ticket_id(tickets);
      
      break;
    case 6:
      limpiarPantalla();
      list_clean(tickets);
      puts("Saliendo del sistema de gestion de Tickets...");
  
      break;
    default:
      puts("Opcion no valida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != 6);

  list_clean(tickets); // se libera memoria


  return 0;
}
