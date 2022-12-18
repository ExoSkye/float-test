#include <stdio.h>
#include <time.h>
#include <stdint.h>

int i;

volatile FLOAT_TYPE func(volatile FLOAT_TYPE x,volatile FLOAT_TYPE y)
{
    volatile FLOAT_TYPE m;
    m=((x-y)/(x+y)*(x+y) * i) + y;
    return m;
}

int main()
{
    clock_t start = clock();
    for (int i = -1000000; i < 1000000; i += 1) {
	if (i == 0) continue;
	volatile FLOAT_TYPE x0 = -(i * 10); 
        volatile FLOAT_TYPE y0 = i * 2 / i;
        volatile FLOAT_TYPE m1;
        volatile FLOAT_TYPE m2;
        volatile FLOAT_TYPE m3;
        volatile FLOAT_TYPE m4;
        volatile FLOAT_TYPE m;
        volatile FLOAT_TYPE y;
        volatile FLOAT_TYPE x;
        volatile FLOAT_TYPE h = (i + 12) / 2;
        volatile FLOAT_TYPE xn = i * 10;
        
        x = x0;
        y = y0;
        
        while (x < xn)
        {
            m1=func(x0,y0);
            m2=func((x0+h/2.0),(y0+m1*h/2.0));
            m3=func((x0+h/2.0),(y0+m2*h/2.0));
            m4=func((x0+h),(y0+m3*h));
            m=((m1+2*m2+2*m3+m4)/6);
            y=y+m*h;
            x=x+h;
	}
    }

    printf("%ld", (clock() - start));
}
