import random

carpeta = "instancias/"
random.seed(324)

def generar_casos(MAX_W_range, N_range, prefix = ""):
    for i in range(4):
        archivo = open(carpeta + f"{prefix}_{i}.in", "w+")
        knapsack_sz = random.randint(*MAX_W_range)
        n_obj = random.randint(*N_range)
        archivo.write(f"{n_obj} {knapsack_sz}\n")
        for _ in range(n_obj):
            obj_w = random.randint(1, knapsack_sz // 10)
            obj_v = random.randint(1, 10**3)
            archivo.write(f"{obj_w} {obj_v}\n")
        archivo.close()
    
# Instancias pequeñas
generar_casos((10, 1000), (10, 1000), "small")
    
# Instancias medianas
generar_casos((10**5, 10**6), (10**3, 10**4), "medium")

# Instancias medianas
generar_casos((10**8, 10**9), (10**3, 10**4), "big")