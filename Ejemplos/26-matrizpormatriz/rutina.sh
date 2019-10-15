#for core in {1..4}; do
    #for size in 10 100 1000 10000 100000 1000000 10000000 25000000; do
        #echo "Tamaño: $size Nucleos: $core"
        #time ./paralelo $size $core
    #done;
#done;

for core in {1..4}; do
    for size in 10 100 1000 5000; do
        echo "Tamaño: $size Nucleos: $core"
        time ./matrizmatriz $size $core
    done;
done;
