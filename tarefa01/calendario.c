#include <stdio.h>

int potencia(int x, int k, int i){
    //Calcula de x*k^i, complexidade O(n);
    for (int j=1; j<=i; j++){
        x = x*k;
    }
    return x;
}

int base10(int x, int i, int n){
    //Transforma base 6 em base 10; complexidade length(x)
    if (x == 0){
        return n;
    }
    int k = x%10;
    x = x/10;
    n += potencia(k, 6, i);
    i++;
    return base10(x, i, n);
}

int main(){
    //Variaveis
    int d, m, a;
    int dM, mA;
    int dias;
    int i=0, n=0;

    //Leitura
    scanf("%d/%d/%d", &d, &m, &a);
    scanf("%d %d", &dM, &mA);
    scanf("%d", &dias);
    n = base10(dias, i, n);

    //Logica principal
    d += n;
    int meses = d/dM;
    d = d%dM;
    if(d==0){
        d+=dM;
        meses--;
    }
    m += meses;
    int anos = m/mA;
    if(anos>0){
        m = m%mA;
        if(m==0){
            m+=mA;
            anos--;
        }
    }
    a += anos;
    printf("%d/%d/%d", d, m, a);
    return 0;
}
