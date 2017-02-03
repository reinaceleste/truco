#Makefile del TPO - - TrucoC - Servidor
#Los comandos que empiezan con @ no se muestran al ejecutar su correspondiente regla make

CC=gcc -Wall
CFLAGS=-c
LDFLAGS=
ARCHIVO=server
PARTE=servidor
LOGFILE=$(LOGPATH)$(shell date +'%d/%m')
MODIF=
HEADERS=*.h
OBJS=main.o datos_server.o handlers.o manejoarchivos.o recibir.o

run: $(ARCHIVO)
	@echo "\nEjecutando archivo ..."
	./$(ARCHIVO)
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