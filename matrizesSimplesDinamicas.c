/**
 * Programa para calculo do tempo de alocacao, leitura e acesso
 * de uma matriz dinamica, alocada de uma unica vez.
 *
 * Autor: Prof. Andre Leon S. Gradvohl, Dr.
 * Ultima modificacao: qui 23 mai 2019 20:38:28 -03
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Funcao para ler uma matriz com n linhas e m colunas.
 * @param matriz Matriz, previamente alocada, a ser preenchida.
 * @param nlinhas Quantidade de linhas da matriz.
 * @param mcolunas Quantidade de colunas da matriz.
 */ 
void leMatriz(float *matriz, unsigned int nlinhas, unsigned int mcolunas)
{
  register unsigned int i, j;

  for (i=0; i<nlinhas; i++)
    for (j=0; j<mcolunas; j++)
        matriz[i*mcolunas + j] = rand()%2;
}

/**
 * Funcao para acessar uma matriz com n linhas e m colunas.
 * @param matriz Matriz, previamente alocada, a ser preenchida.
 * @param nlinhas Quantidade de linhas da matriz.
 * @param mcolunas Quantidade de colunas da matriz.
 */
void acessaMatriz(float *matriz, unsigned int nlinhas, unsigned int mcolunas)
{
  register unsigned int i, j, k;

  for (i=0; i<nlinhas; i++)
    for (j=0; j<mcolunas; j++)
        k = matriz[i*mcolunas + j];
}

/**
 * Funcao para calcular o tempo decorrido entre duas marcacoes.
 * @param tstart Marcacao do inicio da contagem de tempo.
 * @param tend Marcacao do final da contagem de tempo.
 */
double calculaTempo(struct timespec tstart, struct timespec tend)
{
  return ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
         ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
}

int main(int argc, char *argv[])
{
  struct timespec tstart={0,0}, tend={0,0};
  register double tempoAlocacao;
  register double tempoLeitura;
  register double tempoAcesso;
  unsigned int numLinhas, numColunas;
  float *matriz;

  if (argc!=3)
  {
    fprintf(stderr,"Numero de parametros invalidos\n");
    fprintf(stderr,"Uso:\n\t %s #linhas #colunas\n",argv[0]);
    exit(1);
  }

  numLinhas = (unsigned int) atoi(argv[1]);
  numColunas = (unsigned int) atoi(argv[2]);

  /*Alocacao da matriz*/
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  matriz = (float *) malloc(sizeof(float)*numLinhas*numColunas);
  clock_gettime(CLOCK_MONOTONIC, &tend);
  tempoAlocacao = calculaTempo(tstart, tend);

  /*Leitura da Matriz*/
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  leMatriz(matriz, numLinhas, numColunas);
  clock_gettime(CLOCK_MONOTONIC, &tend);
  tempoLeitura = calculaTempo(tstart, tend);

  /*Acesso a Matriz*/
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  acessaMatriz(matriz, numLinhas, numColunas);
  clock_gettime(CLOCK_MONOTONIC, &tend);
  tempoAcesso = calculaTempo(tstart, tend);

#ifdef CABECA
  printf("Tempo de alocação: %.10f, tempo de leitura: %.10f, tempo de acesso: %.10f\n", 
          tempoAlocacao, tempoLeitura, tempoAcesso);
#else
  printf("%.10f %.10f %.10f\n",
          tempoAlocacao, tempoLeitura, tempoAcesso);
#endif
  return 0;
}
