set -e

g++ g.cpp -o a
g++ gen.cpp -o gen
g++ ck.cpp -o ck
g++ ck2.cpp -o ck2

for((i=1; ; i++)); do
    echo $i
    ./gen $i > in

    ./a < in >> in

    ./ck < in
    ./ck2 < in
done