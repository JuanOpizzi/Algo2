from My_graph import Grafo
import heapq
import random
import sys
from collections import deque

"""..........................AUXILIARES.............................."""
def random_walk(grafo, origen, largo):
	recorrido = []
	if not (origen):
		origen = random.choice(grafo.identificadores())
	actual = origen
	recorrido.append(actual)
	for i in range(largo):
		lista = grafo.identificadores()
		actual = random.choice(lista)
		recorrido.append(actual)
	return recorrido

def bfs(grafo, user, fin = None):
	visitados = {} #diccionario
	padre = {}
	orden = {}
	for v in grafo:
		if v not in visitados:
			padre[v] = None
			orden[v] = 0
			bfs_visitar(grafo, v, fin, visitados, padre, orden)
	return padre, orden	

def bfs_visitar(grafo, origen, destino, dic_visitados, dic_camino, dic_orden):
	cola = deque()
	cola.append(origen)
	dic_visitados[origen] = True
	while (len(cola) > 0):
		v = cola.popleft()
		for w in grafo.vertices_adyacentes(v):
			if not w in dic_visitados:
				dic_visitados[w] = True		
				dic_camino[w] = v
				dic_orden[w] = dic_orden[v] + 1
				cola.append(w)

	
def label_prog(grafo):
	label = {}
	for i,v in enumerate(grafo):
		label[v] = i
	vertices = grafo.identificadores()
	recorrer = grafo.cant_vertices // 3
	for i in range(recorrer):
		the_chosen_one = random.choice(vertices)
		adyacentes = grafo.vertices_adyacentes(the_chosen_one)
		max_freq = max(adyacentes, key = adyacentes.count)
		label[i] = max_freq
	return label
		 

def ordenar(dic, n):
	if n > len(dic):
		raise KeyError("Se quiere devolver mas vertices de los que hay")
	lista = []	
	heap  = []
	for clave,valor in dic.items(): #agrega los primeros k elems del dic
		tupla = (valor,clave)
		lista.append(tupla)
	for i in range(n):
		heap.append(lista[i])
	heapq.heapify(heap)
	for j in range (n,len(lista)):
		if lista[j] > heap[0]:
			tupla2 = (lista[j][0],lista[j][1])
			heapq.heappush(heap,tupla2)
			heapq.heappop(heap)
	lista_retorno = []
	for z in range(len(heap)):
		lista_retorno.append(heapq.heappop(heap))
	return lista_retorno 

	
"""..........................FUNCIONES..............................."""

# SIMILARES ---> OK
ITERACIONES = 10
PASOS = 25

def buscar_vertices_parecidos(grafo, vertice, n, es_recomendado = False ): #el si lo recibe por si llamo con recomendar para que filtre dentro de esta funcion y no afuera
	dic_ocurrencias = {}
	for i in range(0, ITERACIONES):
		lista_recorrido = random_walk(grafo, vertice, PASOS)
		for v in range(1,len(lista_recorrido)):
			if es_recomendado and grafo.son_adyacentes( vertice,lista_recorrido[v] ):
				continue
			#Si quiero recomendar se saltea los que son adyacentes al vertice. 
			if( lista_recorrido[v] in dic_ocurrencias ):
				dic_ocurrencias[lista_recorrido[v]] += 1		    	
			else:
				dic_ocurrencias[lista_recorrido[v]] = 1
	lista = ordenar(dic_ocurrencias, n) 
	return lista

def similares(grafo, vertice, cant):
	"""Recibe un usuario y una cantidad n. 
	Muestra por pantalla los n usuarios similares
	al usuario pasado por paramétro."""
	print("Usuarios similares: \n")
	lista = buscar_vertices_parecidos(grafo, vertice, cant)	
	sorted(lista, reverse = True)
	for i in range(0, cant):
		print("- {}".format(lista[i][1]))
		
# RECOMENDAR ---> OK
def recomendar(grafo, vertice, cant):
	"""Recibe un usuario y una cantidad n. 
	Muestra por pantalla los n usuarios recomendados
	para el usuario pasado por paramétro."""
	print("Recomendados: \n")
	lista = buscar_vertices_parecidos(grafo, vertice, cant,True )
	sorted(lista, reverse = True)
	for i in range(cant):
		if not lista[i] in grafo.identificadores(): #Para no recomendar los adyacentes del vertice
			print("{}".format(lista[i][1])) 
		
# CAMINOS ---> OK
def caminos(grafo, inicio, fin):
	"""Recibe un usuario inicial y uno final e imprime 
	por pantalla el camino mínimos entre ambos."""
	pa = { inicio:None }
	orden = { inicio:0 }
	visitados = {}
	if (not grafo.vertice_existe(inicio)):
		raise KeyError("No hay camino posible!")
	bfs_visitar(grafo,inicio,fin,visitados,pa,orden)
	if not fin in pa:
		print ("No hay camino posible! no es conexo!")
		return
	lista_camino = [fin] # lista de vertices
	while lista_camino[0] != inicio:
		lista_camino.insert(0, pa[lista_camino[0]])
	print (lista_camino)
				
# CENTRALIDAD ---> OK 
def centralidad(grafo, n):
	"""Recibe un número n e imprime los n usuarios centrales
	del grafo."""
	print("Los {} vértices más centrales: ".format(n))
	dic_ocurrencias = {}
	for i in range(20):
		vertice = random.choice(grafo.identificadores())
		recorrido = random_walk(grafo, vertice, n)
		for v in recorrido:
			if v in dic_ocurrencias:
				dic_ocurrencias[v] += 1
			else:
				dic_ocurrencias[v] = 0
	lista = ordenar(dic_ocurrencias, n)
	if lista != None:
		for cla, val in lista:
			print("- {}".format(val))
	else:
		raise KeyError("No hay un camino posible entre ambos vertices")

# DISTANCIA ---> OK
def distancia(grafo, vce): #es para distancia n 
	"""Recibe un usuario e imprime por pantalla
	los usuarios que se encuentran a cada una de las
	distancias posibles."""
	if not (grafo.vertice_existe(vce)):
		raise KeyError("El vertice es un punto aislado")
	padre, orden = bfs(grafo, vce)
	cant = len(orden)-1
	lista = list(orden.values())
	lista.sort()
	repetidos = {}
	repetidos[vce] = True
	for j in lista:
		if not j in repetidos:
			repetidos[j] = True
			veces = lista.count(j)
			print ("Distancia {}: {}".format(j, veces))		

# ESTADISTICAS----> OK
def estadisticas(grafo):
	"""Imprime las estadíticas del grafo"""
	print("Cantidad de vertices: {}".format(grafo.cant_vertices) )
	print("Cantidad de aristas:  {}".format(grafo.cant_aristas) )
	cant = 0
	for vertice in grafo.vertices:
		cant += len(grafo.vertices_adyacentes(vertice))
	prom = cant/grafo.cant_vertices
	print ("Promedio del grado de entrada de cada vertice: {:.3}".format(prom))
	print ("Promedio del grado de salida  de cada vertice: {:.3}".format(prom))
	print ("Densidad del grafo: {:.3}".format((2 * grafo.cant_aristas) / (grafo.cant_vertices * (grafo.cant_vertices - 1))))

# COMUNIDADES --> OK
MAX_COM = 2000 
MIN_COM = 30 # creo que 5 personas no son una comunidad

def comunidades(grafo):
	"""Recibe el grafo e imprime por pantalla una lista
	con la cantidad de integrantes de cada comunidad."""
	labels = label_prog(grafo)
	new = {}
	for v,l in labels.items():
		if not l in new:
			new[l] = [v]
		else:
			new[l].append(v)
	lista_items = list(new.items())
	for l, personitas in lista_items:
		if (MIN_COM < len(new[l]) < MAX_COM):
			print("{} - {}".format(l, len(personitas)))


opciones = {
			"similares": similares,
			"recomendar": recomendar,
			"caminos": caminos,
			"centralidad": centralidad,
			"distancia": distancia,
			"estadisticas": estadisticas,
			"comunidades": comunidades
			}
 
def cargar_grafo(n_arch):
	try:
		with open(n_arch, "r") as arch:
			#ver como borrar
			for i in range(0,4):
				linea = arch.readline() #Para no leer los comentarios
			grafo = Grafo()
			for linea in arch:
				linea = (linea.rstrip('\n')).split('\t')
				if not grafo.vertice_existe(int(linea[0])):
					grafo.agregar_vertice(int(linea[0]))
				if not grafo.vertice_existe(int(linea[1])):
					grafo.agregar_vertice(int(linea[1]))
				if not grafo.son_adyacentes(int(linea[0]), int(linea[1])):
					grafo.agregar_arista(int(linea[0]), int(linea[1])) #sirve para ida y vuelta
			return grafo
	except FileNotFoundError:
		raise("El archivo no existe!")


def main():
	archivo = sys.argv[1]
	print("Espere mientras se carga el grafo...")
	grafo = cargar_grafo(archivo)
	print("Grafo cargado")
	print("Utilize alguno de los 7 comandos que se listan a continuacion: ")
	print("similares")
	print("recomendar") 
	print("caminos") 
	print("centralidad")
	print("distancia") 
	print("estadisticas")
	print("comunidades")
	print(" ")
	print("Nota: El programa se dentendrá si se ingresa 'Exit'")
	while True:
		try:
			comand = input() #Aún confio un poco en el user, le pido lo que quiere ver
			if len(comand) == 0:
				raise ("Comandos inválidos")
		except:
			raise("Algo salio mal!")			
		accion = (comand.rstrip('\n')).split(" ")
		parameters = []
		for ac in accion[1:]:
			parameters.append(int(ac))
		if accion[0] in opciones.keys():
			opciones[accion[0]](grafo,*parameters)
		if (comand == "Exit"):
			print("Se detendrá el programa")
			break		
		else: 
			print("Se ingresó un comando no válido.") #Ver: esto se imprime siempre


main()    
    



