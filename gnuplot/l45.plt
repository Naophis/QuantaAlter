set xlabel "mm2"
set ylabel "mm" 
f(x)=a*x**6 + b*x**5 +c*x**4 +d*x**3 +e*x**2 +f*x +g 
fit f(x) 'data\l45.txt' via a,b,c,d,e,f,g
plot f(x) lt 1 lc rgb '#000000' title sprintf(a, b,c,d,e,f,g)