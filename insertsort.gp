### InsertSort: tiempo medio vs tamaño de entrada (col 1:x, col 4:y)

# --- Salida principal (lineal) ---
set term pngcairo size 1200,700
set output 'insertsort_tiempo.png'
set title 'InsertSort: Tiempo medio vs tamaño de entrada'
set xlabel 'N (tamaño de entrada)'
set ylabel 'Tiempo medio (s)'    # cambia a (ms) si aplica
set grid
set key top left
set tics out nomirror
set format y '%.2s%c'            # formato SI: 1.2k, 3.4M, etc.

# Modelo esperado ~ O(n^2)
f(n) = a*n**2 + b*n + c
a=1e-9; b=0; c=0                 # valores semilla para el ajuste
fit f(x) 'time_table_insert.txt' using 1:3 via a,b,c

plot 'time_table_insert.txt' using 1:3 with linespoints pt 7 ps 0.8 lw 1 title 'Medición', \
     f(x) with lines lw 2 dt 2 title sprintf('Ajuste: t=%.3g n^2 %+ .3g n %+ .3g', a,b,c)

unset output

# --- Comprobación de orden (log-log) ---
set term pngcairo size 1200,700
set output 'insertsort_loglog.png'
unset title
set logscale xy
set xlabel 'N'
set ylabel 'Tiempo medio'
set grid
plot 'time_table_insert.txt' using 1:3 with points pt 7 ps 0.8 title 'Medición', \
     f(x) with lines lw 2 dt 2 title 'Ajuste cuadrático'
unset output

# --- (Opcional) Estimar exponente directamente: log(t) = m log(n) + k ---
# g(n) = m*log(n) + k
# fit g(x) 'time_table_insert.txt' using (log($1)):(log($4)) via m,k
# print sprintf("Exponente ~ %.3f (debería ~2 para InsertSort)", m)

# --- (Opcional) Si col 5 es desviación estándar: usar barras de error ---
# replot 'time_table_insert.txt' using 1:4:5 with yerrorbars lc rgb "black" notitle