# Trim btrace result and plot

```shell
#!/bin/bash

files=`ls *.btrace`
plotting=1

if [ ! -d plot_timestamp ]
then
	mkdir plot_timestamp
fi

for file in $files
do
	echo $file
	grep -E "C   R|C  R|C   W|C  W" $file > ${file}_RW;

	cat ${file}_RW | awk '$4 < 1000 {printf "%.5f, %5d, %2s, %2s, %d, %d\n", $4, $5, $6, $7, $8, $10}' > ${file}_RW_csv

	grep R ${file}_RW_csv > ${file}_R_csv
	grep W ${file}_RW_csv > ${file}_W_csv

	gnuplot << EOF

#set terminal postscript enhanced color
set terminal postscript eps enhanced color font 'Helvetica,20'

set xlabel "Timestamp (second)";
set ylabel "Logical Sector Number";

set autoscale
#set xrange [1:1.1]
#set yrange [0:50000000]

set style line 1 pt 7 lc rgb "green";
set style line 2 pt 7 lc rgb "red";

set pointsize 0.2;
set datafile separator ",";

set output "${file}.eps";
plot "< grep R ${file}_RW_csv" u 1:5 ls 1 ti "Read", "< grep W ${file}_RW_csv" u 1:5 ls 2 ti "Write";

set output "${file}_R.eps";
plot "< grep R ${file}_RW_csv" u 1:5 ls 1 ti "Read";

set output "${file}_W.eps";
plot "< grep W ${file}_RW_csv" u 1:5 ls 2 ti "Write";

EOF

	mv *.eps plot_timestamp;
	rm *_csv *_RW
done
```

