### Comparativa de tiempo medio: InsertSort vs BubbleSort
# Archivos y columnas
fileI = 'time_table_insert.txt'          # InsertSort: col1=N, col4=tiempo
fileB = 'time_table_buble.txt'          # BubbleSort: col1=N, col4=tiempo
colx  = 1
coly  = 4                     # <-- si quieres OBs, pon aquí la columna de OBs

set datafile separator whitespace
set grid; set tics out nomirror
set key top left
set xlabel 'N (tamaño de entrada)'
set ylabel 'OBs'
set format y '%.2s%c'

# --- Reescalado para evitar mala condición en el fit ---
stats fileI using colx name 'SI' nooutput
stats fileB using colx name 'SB' nooutput
sx = (SI_max>SB_max ? SI_max : SB_max)/1000.0
if (sx<=0) sx = 1.0

# Modelos ~ O(n^2) con solo el término cuadrático
fI(x) = aI*(x/sx)**2
fB(x) = aB*(x/sx)**2
aI = 1; aB = 1

fit fI(x) fileI using colx:coly via aI
fit fB(x) fileB using colx:coly via aB

# --- Gráfica principal (lineal) ---
set term pngcairo size 1200,700
set output 'comparativa_tiempo_obs.png'
plot fileI using colx:coly with linespoints pt 7 ps 0.8 lw 1 title 'InsertSort', \
     fileB using colx:coly with linespoints pt 5 ps 0.8 lw 1 title 'BubbleSort', \
     fI(x) with lines lw 2 dt 2 title sprintf('fit I: %.3g·(n/s)^2', aI), \
     fB(x) with lines lw 2 dt 3 title sprintf('fit B: %.3g·(n/s)^2', aB)
unset output

# --- Comprobación de orden en log–log (pendiente ≈2) ---
gI(x)=mI*log(x)+kI
gB(x)=mB*log(x)+kB
fit gI(x) fileI using (log(column(colx))):(log(column(coly))) via mI,kI
fit gB(x) fileB using (log(column(colx))):(log(column(coly))) via mB,kB

set term pngcairo size 1200,700
set output 'comparativa_loglog.png'
set logscale xy
set ylabel 'OBs'
plot fileI using colx:coly with points pt 7 ps 0.8 title sprintf('InsertSort (pend≈%.2f)', mI), \
     fileB using colx:coly with points pt 5 ps 0.8 title sprintf('BubbleSort (pend≈%.2f)', mB)
unset output

# Mensajes útiles en consola
print sprintf('Constantes cuadráticas: aI=%.3g, aB=%.3g  (mayor ⇒ más lento)', aI, aB)
print sprintf('Pendientes log-log:     mI=%.3f, mB=%.3f  (≈2 esperado)', mI, mB)