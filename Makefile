# Compilador a utilizar
CXX = g++

# Flags de compilación
CXXFLAGS =  -std=c++11 -O2

# Archivos fuente
SOURCES = kdTree.cc nearestNeighbour.cc

# Nombre del archivo de salida
TARGET_TEST = TestKDTree

# Regla por defecto
all: $(TARGET_TEST) generadorKdTree queryKdTree

# Regla para compilar el TARGET
$(TARGET_TEST): $(SOURCES)
	$(CXX) TestKdTree.cc $(SOURCES) -lgtest -lpthread -pedantic $(CXXFLAGS) -o $(TARGET_TEST)

generadorKdTree: $(SOURCES) generadorKdTree.cc
	$(CXX) generadorKdTree.cc $(CXXFLAGS) -o generadorKdTree

queryKdTree: queryKdTree.cc $(SOURCES)
	$(CXX) queryKdTree.cc $(SOURCES) $(CXXFLAGS) -fopenmp -o queryKdTree

victor: victor_experimental.cc $(SOURCES)
	$(CXX) victor_experimental.cc $(SOURCES) $(CXXFLAGS) -o victor_experimental

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET_TEST) queryKdTree generadorKdTree victor_experimental
