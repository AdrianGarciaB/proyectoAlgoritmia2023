# Compilador a utilizar
CXX = g++

# Flags de compilación
CXXFLAGS = -lgtest -lpthread -pedantic

# Archivos fuente
SOURCES = TestKdTree.cc kdTree.cc

# Nombre del archivo de salida
TARGET = TestKDTree

# Regla por defecto
all: $(TARGET)

# Regla para compilar el TARGET
$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(CXXFLAGS) -o $(TARGET)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET)
