void ordenarListaSequencial_Shellsort (int *tam, Dados* node, int *contMovimentos, int *contComparacoes){
    int i,k, h, posicao;
    Dados rg;

    h = *tam;
    h = h/2;
    while (h>0){
        for (k=0; k < *tam; k++){
            for (i = k+h; i < *tam; i+=h){
                rg = node[i];
                posicao = i;
                while (posicao > k && node[posicao - h].rg > rg.rg){
                    *contComparacoes = *contComparacoes + 1;
                    *contMovimentos = *contMovimentos + 1;
                    node[posicao]=node[posicao - h];
                    posicao = posicao - h;
                }
                *contComparacoes = *contComparacoes + 1;//comparacao incrementa se comparou e nao
                                                    //executou o while
                node[posicao] = rg;//nao conta como movimento pois o espaço ja foi aberto na execução do while
            }
        }
        h = h/2;
    }
    foiOrdenado=1;
}
