# Teste de alocação de matrizes 
## Introdução
Esse relatório mostra alguns testes de alocação dinâmica de matrizes. A ideia é testar duas abordagens diferentes, no que se refere ao desempenho e à forma de utilização dessas estruturas de dados. Uma das abordagens é a alocação de matrizes em duas etapas: na primeira etapa ocorre a alocação das linhas (cada linha é um ponteiro para as colunas); e, na segunda etapa, a alocação de cada uma das colunas. A segunda abordagem é a alocação em uma única etapa, alocando toda a matriz em uma única dimensão, como se alocasse um vetor.

### Motivação
A motivação para estes testes e também para este repositório veio de uma observação a respeito da forma como os estudantes alocavam as matrizes em trabalhos com múltiplos _threads_, na disciplina de Sistemas Operacionais. Como o tamanho das matrizes deveria ser especificado pelo usuário no início da execução do programa, os estudantes tinham que alocar essas matrizes dinamicamente.

Sendo assim, notei que a maioria deles usava a abordagem em duas etapas. Isso me incomodava muito, pois a abordagem em uma única etapa me parecia muito mais prática e mais rápida. Por esse motivo, resolvi fazer alguns testes e apresentar os resultados para demonstrar que a segunda abordagem é, de fato, mais eficiente. Além disso, ao registrar os métodos e resultados, espero esclarecer as dúvidas dos estudantes e ajudá-los a escrever um código mais rápido.

## As abordagens
Conforme comentei na [Introdução](#introdução), há duas abordagens para alocação de matrizes em D dimensões. Vamos considerar _D_=2, por simplicidade, mas depois podemos generalizar. Consideraremos também que, para D=2, a matriz alocada terá _n_ linhas (_numLinhas_) e _m_ colunas (_numColunas_).

### Alocação em _D_ etapas
Uma das abordagens é a alocação de matrizes em _D_=2 etapas. Na primeira etapa será alocado espaço para _n_ ponteiros, um para cada linha da matriz. Na segunda etapa, para cada um dos _n_ ponteiros, será alocado um espaço para _m_ valores. 

Como exemplo, observe o código a seguir para alocar uma matriz de _n_ x _m_ números reais (_float_).
```c
  // Declaração da matriz
  float **matriz;
  
  // 1ª etapa de alocação 
  matriz = (float **) malloc(numLinhas * sizeof(float *));
  
  // 2ª etapa de alocação
  for (i=0; i<numLinhas; i++)
      matriz[i] = (float *) malloc(numColunas * sizeof(float));
```

Note que, na declaração da matriz, esta é do tipo "_float **_" ou, em outras palavras, a matriz é um "um ponteiro para ponteiros para números reais". Até aí, tudo bem em termos de ocupação de memória, pois um ponteiro ocupa poucos _bytes_.

Na 1ª etapa de alocação, utiliza-se o comando _malloc_ para alocar os ponteiros. Note que, nos parâmetros para este primeiro comando _malloc_, estamos calculando o tamanho de um ponteiro para _float_ e multiplicando pela quantidade de linhas. Note também que estamos fazendo uma conversão de tipos (_cast_) para o tipo _float **_.

A 2ª etapa inclui um laço em que, a cada iteração, chama-se o comando _malloc_ para alocar um conjunto de números reais, na quantidade de colunas que desejamos que a matriz tenha.

Daí, já se pode observar que o processo de alocação de matrizes tem ordem _M_, ou seja, _O_(_M_). Em outras palavras, a criação de uma matriz com _M_ colunas, vai gastar _M_ iterações.

Entretanto, vejo que há um pequeno aspecto positivo nessa abordagem. O acesso aos elementos de uma matriz alocada dessa forma é feito da mesma forma que uma matriz convencional (alocada estaticamente). Em suma, você acessaria o elemento da linha _i_ e coluna _j_ da _matriz_ utilizando `matriz[i][j]`.

Contudo, esse aspecto positivo some um pouco na hora da especificação de uma função que recebe uma matriz de alocação dinâmica como parâmetro. Nesse caso, uma função que recebe como parâmetro uma matriz de números reais alocada dinamicamente deve ter a seguinte assinatura: `funcao(float **matriz)`.

A generalização dessa abordagem para D dimensões é fácil de se obter. Basta adicionar mais laços, um para cada nova dimensão, e ajustar os limites e índices dos laços a cada nova dimensão a ser construída.

### Alocação em uma única etapa
A alocação em uma única etapa inclui uma única chamada à função _malloc_, independente da quantidade de dimensões que a matriz terá. Essa razão já é, em teoria, suficiente para contraindicar a alocação em _D_ etapas. Afinal, diferente da alocação em _D_ etapas, nesse caso a ordem para alocação de uma matriz é _O_(1).

Para a alocação em uma única etapa, vamos utilizar a função _malloc_ especificando o tamanho da matriz a partir da multiplicação da quantidade de linhas (_numLinhas_) pela quantidade de colunas (_numColunas_), multiplicado pelo tamanho do tipo de dados da matriz. Observe o código a seguir:

```c
  // Declaração da matriz
  float *matriz;

  matriz = (float *) malloc(numLinhas * numColunas * sizeof(float));
```

Note que, na declaração da matriz, esta é do tipo "_float *_" ou, em outras palavras, a matriz é um "um ponteiro para números reais". Isso porque, embora o _malloc_ aloque espaço suficiente para todos os elementos da _matriz_, precisamos apenas do endereço da primeira posição. As demais serão calculadas a partir desse primeiro endereço.

Neste momento aparece um aspecto um pouco negativo dessa abordagem: a forma de acesso aos elementos da matriz. Aqui, é preciso lembrar que as matrizes na linguagem C -- diferente da linguagem Fortran, por exemplo -- alocam as matrizes estáticas no formato "linha primeiro", ou seja, primeiro os elementos da primeira linha, depois os elementos da segunda linha, e assim por diante. Sendo assim, para acessar o elemento que está na linha _i_, coluna _j_, de uma matriz com _numColunas_, é preciso usar a seguinte fórmula `matriz[i*numColunas + j]`.

Pode parecer estranho e deixar o código pouco legível, mas pode acreditar, funciona. E funciona um pouco melhor se as variáveis _i_, _j_ e _numColunas_ forem registradores, ao invés de variáveis alocadas na memória. O programador mais experiente na linugagem C pode inclusive criar uma definição (`#define`) para tornar o código mais legível. Por exemplo:

```c
#define posicao(I, J, COLUNAS) ((I*COLUNAS) + J)
...
   // Acesso à matriz
  valor = matriz[posicao(i, j, numColunas)];
```

A passagem dessa matriz como parâmetro para uma função é muito simples e, mais uma vez, não depende da quantidade de dimensões. Veja o exemplo a seguir: `funcao(float *matriz)`.

