#include "kdTree.hh"
#include <gtest/gtest.h>

class KDTreeTest : public ::testing::Test {
protected:
    kdTree* tree;

    // Esta función se ejecuta antes de cada prueba
    virtual void SetUp() {
        tree = new kdTree(2); // Creando un árbol de 2 dimensiones como ejemplo.
    }

    // Esta función se ejecuta después de cada prueba
    virtual void TearDown() {
        delete tree;
    }
};

TEST_F(KDTreeTest, TestConstructor) {
EXPECT_TRUE(tree);
EXPECT_TRUE(tree->empty());
EXPECT_EQ(tree->valori(0), -1); // Asumiendo que un árbol vacío retorna -1 para cualquier coordenada.
}

TEST_F(KDTreeTest, TestInsertAndInorder) {
EXPECT_TRUE(tree);
vector<double> point1 = {1.0, 2.0};
vector<double> point2 = {3.0, 4.0};

tree->insert(point1);
tree->insert(point2);

// No podemos verificar directamente la función inorder ya que solo imprime valores.
// Pero podemos verificar otros aspectos como el valor de la raíz después de las inserciones.
// Para un test más profundo, necesitaríamos acceso a más detalles internos o más funciones públicas.
EXPECT_EQ(tree->valori(0), 1.0);
EXPECT_FALSE(tree->empty());
}

// Puedes agregar más pruebas según lo necesites.

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}