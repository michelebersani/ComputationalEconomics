for rule in VonNeumann Stochastic ; do
   for p_death in 0.0 0.2 0.5 0.8 1.0 ; do
     for p_birth in 0.0 0.2 0.5 0.8 1.0 ; do
        echo $rule $p_death $p_birth
        ./build/thread 100 100 500 8 8 $rule $p_death $p_birth
        python3 generate_movies.py --inputPath ./results/$rule/$rule\_$p_death\_$p_birth.txt --savePath ./videos/$rule\_$p_death\_$p_birth.mp4
     done
   done
done