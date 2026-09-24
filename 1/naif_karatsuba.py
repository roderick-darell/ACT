import matplotlib.pyplot as plt
import csv

n_vals = []
naive_vals = []
karatsuba_vals = []

with open("resultats.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        n_vals.append(int(row["n"]))
        naive_vals.append(int(row["naive"]))
        karatsuba_vals.append(int(row["karatsuba"]))

plt.figure(figsize=(8, 6))
plt.plot(n_vals, naive_vals, marker='o', label="Naïf (O(n²))")
plt.plot(n_vals, karatsuba_vals, marker='s', label="Karatsuba (O(n^log2(3)))")

plt.xlabel("Taille n du polynôme")
plt.ylabel("Nombre d'opérations arithmétiques")
plt.title("Comparaison naïf vs Karatsuba")
plt.legend()
plt.grid(True)

# Échelle log-log très utile ici, pour bien visualiser les deux
# pentes différentes (2 pour le naïf, log2(3)≈1.585 pour Karatsuba)
plt.xscale("log", base=2)
plt.yscale("log")

plt.savefig("comparaison.png", dpi=150)
plt.show()