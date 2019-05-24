# Arquivo para compilar os programas para realizar os testes de alocação de matrizes. 
#
# Criado por Prof. Andre' Leon S. Gradvohl, Dr.
# e-mail: gradvohl@ft.unicamp.br
# Ultima versa: qui 23 mai 2019 22:31:02 -03

CC=gcc
DIRETIVAS=-lrt

#Arquivos
FONTES=matrizesDuploDinamicas.c matrizesSimplesDinamicas.c
OBJETOS=$(FONTES:.c=.o)

#Dependencias de Compilacao
all: $(OBJETOS)

# Compilando arquivo para alocacao dupla da matriz; primeiro as linhas, depois
# as colunas.
matrizesDuploDinamicas.o: matrizesDuploDinamicas.c
	@echo "Compilando arquivo: " $<
	$(CC)   matrizesDuploDinamicas.c $(DIRETIVAS) -o $@ 
	@echo "Arquivo " $@ "gerado"

#Compilando arquivo para alocacao simples da matriz.
matrizesSimplesDinamicas.o: matrizesSimplesDinamicas.c
	@echo "Compilando arquivo: " $<
	$(CC)   matrizesSimplesDinamicas.c $(DIRETIVAS) -o $@ 
	@echo "Arquivo " $@ "gerado"

#Limpeza
clean:
	rm -f $(OBJETOS)
