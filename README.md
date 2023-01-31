# VORSHA: Variable-sized, One-way and Randomized Secure Hash Algorithm

VORSHA is a secure hash algorithm that randomized the bits using generated pool of bits. It generates a set of bits, and later, it selects the generated bits to form
the randomized secure hash value.

## VORSHA-1D
It is a fast hash algorithm of VORSHA but it lacks randomization. Moreover, it does not features memory-hardness.

## VORSHA-2D
It is a slower hash algorithm than VORSHA-1D. VORSHA-2D hash three phases, namely, dimension, filling and retrieval. VORSHA-2D decides the dimensions of vector in the dimension phase,
and the dimensions are X and Y. VORSHA-2D generates set of pseudo-random bits and filled it in a bit vector in the filling phase. The retrieval phase selects n bits 
from bit vectors pseudo-randomly which forms the randomized secure hash value.

## VORSHA-3D
It is a slower hash algorithm than VORSHA-2D. It is similar except the bit vector. VORSHA-3D uses three dimensional bit vector, and the dimensions are X, Y, and Z.
It is more secure than VORSHA-1D and VORSHA-2D.

## Compilation

To compile VORSHA-1D, ```gcc vorsha-1D.c -o vorsha1D``` and run it as ```./vorsha1D```

To compile VORSHA-2D, ```gcc vorsha-2D.c -VORSHA2D -lm``` and run it as ```./vorsha2D```

To compile VORSHA-2D, ```gcc vorsha-3D.c -VORSHA2D -lm``` and run it as ```./vorsha3D```


## Citation

```
@misc{cryptoeprint:2023/110,
      author = {Ripon Patgiri and Laiphrakpam Dolendro Singh and Dalton Meitei Thounaojam},
      title = {VORSHA: A Variable-sized, One-way and Randomized Secure Hash Algorithm},
      howpublished = {Cryptology ePrint Archive, Paper 2023/110},
      year = {2023},
      note = {\url{https://eprint.iacr.org/2023/110}},
      url = {https://eprint.iacr.org/2023/110}
}
```


