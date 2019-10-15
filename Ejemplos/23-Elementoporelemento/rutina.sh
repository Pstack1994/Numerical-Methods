for core in {1..4}; do
    for size in 10 100 1000 10000 100000 1000000 10000000 25000000; do
        echo "Tamaño: $size Nucleos: $core"
        time ./multiplica $size $core
    done;
done;
