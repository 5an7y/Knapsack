directorio = "/home/est_posgrado_jose.vales/OptEst/proyecto"
ejecuciones_file = open("ejecuciones", "w")

rseeds = [42, 635, 293, 472, 534]

time = 60
Memetic_test = [
    ("Lineal", "Lineal"), ("Fijo", "Fijo"),
    ("Fijo", "Lineal"), ("PesoInvertido", "Lineal"), 
    ("PesoInvertido", "Fijo"), ("PesoInvertido", "PesoInvertido"),
]

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for p_tor, p_bus in Memetic_test:
            for seed in rseeds:
                ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_Mem_{p_tor}_{p_bus}_{seed}.out Memetico {seed} {time} {p_tor} {p_bus} \n"
            )

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for p_cosa in ["PesoInvertido", "Lineal", "Fijo"]:
            for seed in rseeds:
                ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_Gen_{p_cosa}_{seed}.out Genetico {seed} {time} {p_cosa} \n"
            )

ejecuciones_file.close()