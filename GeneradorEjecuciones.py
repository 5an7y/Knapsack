directorio = "/home/est_posgrado_jose.vales/OptEst/proyecto"
ejecuciones_file = open("ejecuciones", "w")

rseeds = [42, 635, 293, 472]

time = 60

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for seed in rseeds:
            ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_It_{seed}.out Iterativa {seed} {time}\n"
            )

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for seed in rseeds:
            ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_GA_Pen_{seed}.out Genetico {seed} {time}\n"
            )

for prefix in ["small", "medium", "big"]:
    for i in range(3):
        for seed in rseeds:
            ejecuciones_file.write(
f"{directorio}/Knapsack {directorio}/instancias/{prefix}_{i}.in " +
f"{directorio}/outputs/{prefix}_{i}_Mem_Pen_{seed}.out Memetico {seed} {time}\n"
            )

ejecuciones_file.close()