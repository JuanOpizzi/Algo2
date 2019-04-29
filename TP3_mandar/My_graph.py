class Grafo():
	def __init__(self, vertices={}, cant_vertices=0, cant_aristas=0):
		"""Crea el grafo no dirigido y no pesado"""
		self.vertices = {}
		self.cant_vertices = cant_vertices
		self.cant_aristas = cant_aristas

	def cantidad_vertices(self):
		"""Devuelve la cantidad de vertices del grafo"""
		return self.cant_vertices
		
	def cantidad_aristas(self):
		"""Devuelve la cantidad de aristas del grafo"""
		return self.cant_aristas
		
	def vertice_existe(self, vertice):
		"""Devuelve si existe el vertice en el grafo"""
		return (vertice in self.vertices)

	def __iter__(self):
		"""Devuelve un iterador de vertices"""
		return iter(self.vertices)

	# Yo creo que va con todo
	def son_adyacentes(self, vce1, vce2):
		"""verifica si son adyacentes 2 vertices"""
		if (vce2 in self.vertices.keys() and vce1 in self.vertices.keys()):
			return vce2 in self.vertices[vce1]

	def identificadores(self):
		"""Devuelve un arreglo de los vertices del grafo"""
		return (list(self.vertices.keys()))
		

	def agregar_vertice(self, vertice):
		"""Agrega un vértice al grafo"""
		if (vertice in self.vertices.keys()):
			raise KeyError("Ese vértice ya existe!")
		self.vertices[vertice] = []
		self.cant_vertices += 1;

	def borrar_vertice(self, vertice):
		"""Borra un vértice del grafo"""
		if (not vertice_existe(self, vertice)):
			raise KeyError("El vértice que quiere borrar no existe!")
		for v in self.vertices.keys():
			if v in self.vertices[vertice]:
				self.vertices[v].remove(vertice)
				self.cant_aristas -= 1
		self.vertices.pop( vertice )
		self.cant_vertices -= 1;

	def vertices_adyacentes(self, vertice):
		"""Devuelve una lista desordenda con los adyacentes al vertice.
		De lo contrario lanzo error de que el vertice no existe."""
		if ( vertice in self.vertices):	
			return list(self.vertices[vertice])
		else:
			raise KeyError("No existen esos vertices adyacentes")

	def agregar_arista(self, inicio, fin):
		"""Agrego una arista al grafo"""
		if ((fin or inicio) not in self.vertices.keys()):
			if(self.son_adyacentes(inicio, fin)):
				raise KeyError("No se puede agregar una arista!")
		self.vertices[inicio].append(fin)
		self.vertices[fin].append(inicio)
		self.cant_aristas += 1;

	def borrar_arista(self, inicio, fin):
		"""Borro una arista del grafo"""
		if ((fin or inicio) not in self.vertices.keys()):
			raise KeyError("No se puede borrar la arista entre ambos vertices porque al menos uno de ellos no existe")
		# Aca estoy asumiendo que existe una arista entre ambos vertices
		# Creo que deberia preguntar si hay una arista entre ambos vertices
		self.vertices[inicio].remove(fin)
		self.vertices[fin].remove(inicio)
		self.cant_aristas -= 1;

	def __str__(self):
		return ("{}".format(self.vertices))
		# si queres imprimir el grafo en tp3.py: print(grafo)

