import sys
from My_graph import  Grafo

def cargar_grafo(n_arch):
	try:
		with open(n_arch, "r") as arch:
			#ver como borrar
			for i in range(0,4):
				linea = arch.readline() #Para no leer los comentarios
			grafo = Grafo()
			for linea in arch:
				linea = (linea.rstrip('\n')).split('\t')
				if not grafo.vertice_existe(linea[0]):
					grafo.agregar_vertice(linea[0])
				if not grafo.vertice_existe(linea[1]):
					grafo.agregar_vertice(linea[1])
				if not grafo.son_adyacentes(linea[0], linea[1]):
					grafo.agregar_arista(linea[0], linea[1]) #sirve para ida y vuelta
			return grafo
	except FileNotFoundError:
		raise("El archivo no existe!")


def main(archivo):
	grafo = cargar_grafo(archivo)
	grafo.vertice_existe("11")
	grafo.vertice_existe("1991")
	print("\n\n\nseparacion\n\n\n")
	print( grafo.vertices_adyacentes("11") )
	print( grafo.vertices_adyacentes("1991") )

if __name__ == '__main__':
	main( sys.argv[1] ) 


