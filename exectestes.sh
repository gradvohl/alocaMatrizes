#!/bin/bash
# Script para rodar testes em uma determinada aplicacao
#
# Prof. Andre Leon S. Gradvohl, Dr.
# gradvohl@ft.unicamp.br
# Ultima atualizacao: qui 23 mai 2019 14:53:36 -03
#
if [[ $# -ne 8 ]]; then
  echo "Numero de parametros invalidos."
  echo -e "Uso:\n\t $0 -p <programa> -n <#linhas> -m <#colunas> -i <quant_interacoes>"
  exit 1
fi
#
# Parsing dos parametros de entrada.
#
while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -p|--programa)
    PROG="$2"
    shift # past argument
    shift # past value
    ;;
    -n|--linhas)
    N="$2"
    shift # past argument
    shift # past value
    ;;
    -m|--colunas)
    M="$2"
    shift # past argument
    shift # past value
    ;;
    -i|--iter)
    ITERACOES="$2"
    shift # past argument
    shift # past value
    ;;
    *)    # unknown option
    echo -e "Opcao $1 invalida. Tente novamente.\n"
    echo -e "Uso:\n\t $0 -p <programa> -n <#linhas> -m <#colunas> -i <quant_interacoes>"
    exit 1
    ;;
  esac
done

for ((c=0; c<${ITERACOES}; c++)); do
# Executa o programa especificado, com os respectivos parametros.
 ${PROG} ${N} ${M}

# Se for a ultima iteracao, sai do laco.
 if [ ${c} -eq $((ITERACOES - 1)) ]; then
         break
 fi
# Senao, espera um tempo aleatorio (1, 2 ou 3s) antes da proxima iteracao.
 sleep $((1 + RANDOM % 3))
done

exit 0
