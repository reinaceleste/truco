#Makefile del TPO - - TrucoC - Juego
#Los comandos que empiezan con @ no se muestran al ejecutar su correspondiente regla make

CC=gcc -Wall
CFLAGS=-c
LDFLAGS=
ARCHIVO=truco
PARTE=jugabilidad
LOGFILE=$(LOGPATH)$(shell date +'%d/%m')
MODIF=
HEADERS=*.h
OBJS=truco.o funciones.o

run: $(ARCHIVO)
	@while [ -z "$$mod" ]; do \
	read -r -p "Ingrese modo de juego (presione S para jugar con flor o N para jugar sin flor): " mod; \
	done ;  \
	[ $$mod = "S" ] || [ $$mod = "N" ] || (echo "Opción incorrecta\nBorrando archivos objeto ..."; rm -f *.o; echo "Archivos objeto eliminados\n"; killall make;); \
	while [ -z "$$jug" ]; do \
	read -r -p "Ingrese cantidad de jugadores por equipo (hasta 3): " jug; \
	done ; \
	[ $$jug = "1" ] || [ $$jug = "2" ] || [ $$jug = "3" ] || (echo "Cantidad de jugadores incorrecta\nBorrando archivos objeto ..."; rm -f *.o; echo "Archivos objeto eliminados\n"; killall make;); \
	echo "Puede jugar"; \
	./$(ARCHIVO) $$mod $$jug
	@echo "\nEjecución terminada. Presione cualquier tecla para continuar"
	@read tecla
	@echo "\nBorrando archivos objeto ..."
	rm -f *.o
	@echo "Archivos objeto eliminados\n"
	rm -f $(ARCHIVO)
	@echo "Archivo ejecutable eliminado"
	@echo "Para volver a obtenerlos, debe compilar los .c escribiendo make new o make $(ARCHIVO)\n"
	@echo "Para ejecutar archivo debe escribir make run o simplemente make\n"
	@echo "Puede escribir directamente make run o simplemente make para compilar, linkear y ejecutar en un paso\n"
	@echo "\nSi la ejecución fue satisfactoria, puede generar una página web con Doxygen escribiendo make html\n"
$(ARCHIVO): $(OBJS)
	@echo "\nSe crearon los archivos objeto $(OBJS)"
	@echo "Linkeando archivos objeto ..."
	$(CC) -o $@ $? $(LDFLAGS)
	@echo "\nSe creó el archivo ejecutable $(ARCHIVO)\n"
%.o: %.c $(HEADERS)
	@echo "\nCompilando archivos .c ..."
	$(CC) -o $@ $(CFLAGS) $<
new: $(ARCHIVO)
html:
	@echo "\nCreando página web ..."
	@doxygen
	@echo "\nPágina web creada"
	@echo "\nAbriendo página web ..."
	@firefox ./html/index.html
	@echo "\nEn caso de querer borrar página web escribir make no_html"
	@echo "\nSi está conforme con la página, puede añadir a su repositorio el Doxyfile, el Makefile, los .c y los .h del proyecto escribiendo make git\n"
no_html:
	@echo "\nBorrando página web ..."
	rm -rf html latex
	@echo "\nPagina web eliminada"
	@echo "Para volver a crearla, escribir make html\n"
git:
	git add .
	git commit -m "Avances en $(PARTE) al $(LOGFILE).$(MODIF)"
	git push