from matplotlib import pyplot as plt 
from random import randint,random,uniform
import math
import numpy as np 

def f(x: float) -> float:
    return math.exp(x)

def g(x: float,bias: float) -> float:
    return x+bias

def f_inv(x:float ) -> float:
    return math.log(max(0.1,x))

def h(x: float,bias: float) -> float:
    return f_inv(g(f(x),bias=bias))


def main():
    N = 1000
    seeds = []
    results = []
    biases = []
    for _ in range(100):
        bias = uniform(-100, 100)
        biases.append(bias)
        seed = uniform(-100, 100)
        seeds.append(seeds)
        next_val = h(seed,bias=bias)
        result = [seed, next_val]
        for _ in range(N-2):
            next_val = h(next_val,bias=bias)
            result.append(next_val)
        results.append(result[-1])
        print(f'Seed: {round(seed,2)} | Final: {round(result[-1],5)}')
    plt.plot(seeds,results)
    plt.savefig(f"{randint(10000,99999)}.png")

if __name__=='__main__':
    main()