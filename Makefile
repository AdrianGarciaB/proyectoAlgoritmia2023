# Compilador a utilizar
CXX = g++

# Flags de compilación
CXXFLAGS = -lgtest -lpthread -pedantic

# Archivos fuente
SOURCES = kdTree.cc nearestNeighbour.cc

# Nombre del archivo de salida
TARGET_TEST = TestKDTree

# Regla por defecto
all: $(TARGET_TEST) generadorKdTree queryKdTree

# Regla para compilar el TARGET
$(TARGET_TEST): $(SOURCES)
	$(CXX) TestKdTree.cc $(SOURCES) $(CXXFLAGS) -o $(TARGET_TEST)

generadorKdTree: $(SOURCES)
	$(CXX) generadorKdTree.cc kdTree.cc $(CXXFLAGS) -o generadorKdTree

queryKdTree: queryKdTree.cc $(SOURCES)
	$(CXX) queryKdTree.cc $(SOURCES) $(CXXFLAGS) -o queryKdTree

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET_TEST) queryKdTree generadorKdTree
