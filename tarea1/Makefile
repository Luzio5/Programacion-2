
# --------------------------------------------------------------------
#  Makefile de tarea 1.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega


# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

TESTDIR = test

MODULOS = pila mapping uso_tads # cola conjunto lista

# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.cpp)
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -I$(HDIR) -g
# -DNDEBUG
# se agrega esta opción para que las llamadas a assert no hagan nada.

$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# cada .o depende de su .cpp
# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE): $(ODIR)/$(PRINCIPAL).o $(OS)
	$(CC) $(CCFLAGS) $^ -o $@


# casos de prueba
CASOS = 00 01 02 03

# cadena de archivos, con directorio y extensión
INS=$(CASOS:%=$(TESTDIR)/%.in)
OUTS=$(CASOS:%=$(TESTDIR)/%.out)
SALS=$(CASOS:%=$(TESTDIR)/%.sal)
DIFFS=$(CASOS:%=$(TESTDIR)/%.diff)

$(SALS):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(TESTDIR)/%.sal:$(TESTDIR)/%.in
	./$(EJECUTABLE) < $< > $@


%.diff:Makefile
# cada .diff depende de su .out y de su .sal
%.diff: %.out %.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior.
# En el caso de `diff', si los dos archivos comparados no son iguales,
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.



# Test general. Las dependencias son los .diff.
# Con `find` se encuentran los .diff de tamaño > 0 que están en el directorio
# $(TESTDIR) y lo asigna a $(LST_ERR).
# Si el tamaño de $(LST_ERR) no es cero imprime los casos con error.
# Con `sed` se elimina el nombre de directorio y la extensión.
testing:$(DIFFS)
	@LST_ERR=$$(find $(TESTDIR) -name *.diff* -size +0c -print);             \
	if [ -n "$${LST_ERR}" ];                                                \
	then                                                                    \
		echo -- CASOS CON ERRORES --;                                   \
		echo "$${LST_ERR}" | sed -e 's/$(TESTDIR)\///g' -e 's/.diff//g';\
	fi


# Genera el entregable.
ENTREGA=Entrega1.tar.gz
CPPS_ENTREGA = $(MODULOS:%=%.cpp)
entrega:testing
	@rm -f $(ENTREGA)
	tar zcf $(ENTREGA) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)


# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS) ejemplos_letra

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(TESTDIR)/*.sal $(TESTDIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f *~ $(HDIR)/*~ $(CPPDIR)/*~














check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
