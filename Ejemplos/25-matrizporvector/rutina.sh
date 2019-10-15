for core in {1..4}; do
    for size in 10 100 1000 8000 9500; do
        echo "Tamaño: $size Nucleos: $core"
        time ./matrizvector $size $core
    done;
done;
