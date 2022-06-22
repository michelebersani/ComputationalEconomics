for side in 100; do
  for ((iter = 0; iter <= 5; iter++)) do
     ./build/thread $side $side 5 $iter 8 ./results/${iter}.txt
  done
done
