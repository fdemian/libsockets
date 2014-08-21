
# Flags de compilacion.
# Convierte todos los warnings en errores.
FLAGS = -Werror -Wall 

PROGRAM_NAME = ejemplo_servidor.c 

EXECUTABLE_NAME = serv


# Agregar las dependencias de compilacion aca.
#DEPENDS = 

main:
	$(CC) $(FLAGS) $(PROGRAM_NAME) -o $(EXECUTABLE_NAME)

clean:
	rm $(EXECUTABLE_NAME)