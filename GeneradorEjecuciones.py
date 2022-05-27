directorio = "/home/est_posgrado_jose.vales/OptEst/proyecto"
ejecuciones_file = open("ejecuciones", "w")

rseeds = [42, 635, 293, 472]

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for seed in rseeds:
            ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_It_{seed}.out Iterativa {seed}\n"
            )

ejecuciones_file.close()