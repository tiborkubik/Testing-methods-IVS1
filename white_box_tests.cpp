//======== Copyright (c) 2019, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Tibor Kubik <xkubik34@stud.fit.vutbr.cz>
// $Date:       $2019-02-15
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Tibor Kubik
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"
#include <limits>

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//
class Matrix_1x1 : public ::testing::Test {
    protected:
      Matrix matrix = Matrix(); //matica 1x1 skonstruovana funkciou Matrix()
};

class Matrix_RxR : public ::testing::Test {
    protected:
      int row = 5;
      Matrix matrix = Matrix(row, row);
};

class Matrix_RxC : public ::testing::Test {
    protected:
      int row = 2;
      int column = 4;
      Matrix matrix = Matrix(row, column);
};

//testy pre matice velkosti 1x1
TEST_F(Matrix_1x1, Construction) {
    EXPECT_NO_THROW(Matrix()) << "Maticu nebolo mozne skonstruovat.";
}

TEST_F(Matrix_1x1, Set_Value) {
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Pociatocna hodnota nulovej matice ma byt 0.";
}

TEST_F(Matrix_1x1, Indeces_Set) {
    EXPECT_TRUE(matrix.set(0, 0, 5)) << "Nepovolena velkost matice.";
    EXPECT_TRUE(matrix.set(0, 0, std::numeric_limits<double>::max())) << "Nepovolena velkost matice.";
    EXPECT_TRUE(matrix.set(0, 0, std::numeric_limits<double>::min())) << "Nepovolena velkost matice.";
}

TEST_F(Matrix_1x1, Indeces_Get) {
    //funkcia get vracia double, mozeme porovnavat
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Matica bola nespravne nainicializovana.";

    EXPECT_ANY_THROW(matrix.get(-3, -2)) << "Matica bola nespravne nainicializovana.";
    EXPECT_ANY_THROW(matrix.get(0, 1)) << "Matica bola nespravne nainicializovana.";
    EXPECT_ANY_THROW(matrix.get(1, 1)) << "Matica bola nespravne nainicializovana.";
}

TEST_F(Matrix_1x1, Equals) {
    Matrix valid_matrix = Matrix();
    Matrix invalid_matrix = Matrix(20, 32);
    Matrix invalid2_matrix = Matrix(1, 2);
    //funkcia operator== vracia bool, mozeme pouzit EXPECT_TRUE
    EXPECT_TRUE(matrix == valid_matrix)  << "Ocakavana velkost matice bola 1x1.";

    EXPECT_ANY_THROW(matrix == invalid_matrix)  << "Neocakavany tvar matice.";
    EXPECT_ANY_THROW(matrix == invalid2_matrix) << "Neocakavany tvar matice.";

    //nastavenie hodnot oboch matic na rovnaku hodnotu, mali by sa rovnat
    matrix.set(0, 0, 5);
    valid_matrix.set(0, 0, 5);

    EXPECT_TRUE(matrix == valid_matrix)  << "Matice sa neocakavane nerovnaju.";

    //nastavenie rozdielnych hodnot
    //matrix[0][0] = 5;
    valid_matrix.set(0, 0, -32);

    EXPECT_FALSE(matrix == valid_matrix)  << "Matice sa rovnaju, i ked by sa nemali.";
}

TEST_F(Matrix_1x1, Sum) {
    Matrix valid_matrix = Matrix();
    //matice musia mat rovnaku velkost, ak ich chceme scitat
    EXPECT_TRUE(matrix == valid_matrix)  << "Nepovolena velkost matice.";
    Matrix invalid_matrix = Matrix(2, 10);
    EXPECT_ANY_THROW(valid_matrix + invalid_matrix);

    valid_matrix.set(0, 0, 3);
    matrix.set(0, 0, 10);

    Matrix valid_result = matrix + valid_matrix;
    Matrix compare_result = Matrix();
    compare_result.set(0, 0, 13);
    EXPECT_TRUE(valid_result == compare_result) << "Sucet matic 1x1 je nespravny.";

    compare_result.set(0, 0, -942);
    EXPECT_FALSE(valid_result == compare_result) << "Sucet matic 1x1 je nespravny.";
}

TEST_F(Matrix_1x1, Product) {
    Matrix valid_matrix = Matrix();
    //matice musia mat rovnaku velkost
    EXPECT_TRUE(matrix == valid_matrix) << "Nepovolena velkost matice.";

    valid_matrix.set(0, 0, 4);
    matrix.set(0, 0, 10);

    Matrix valid_result = valid_matrix * matrix;
    Matrix compare_result = Matrix();
    compare_result.set(0, 0, 40);
    EXPECT_TRUE(valid_result == compare_result) << "Sucin matic 1x1 je nespravny.";

    compare_result.set(0, 0, 13.238);
    EXPECT_FALSE(valid_result == compare_result) << "Sucin matic 1x1 je nespravny.";
}

TEST_F(Matrix_1x1, Scalar) {
    matrix.set(0, 0, 10);

    int constant = 5;
    Matrix valid_result = matrix * 5;
    Matrix compare_result = Matrix();
    compare_result.set(0, 0, 50);
    EXPECT_TRUE(valid_result == compare_result) << "Vysledok nasobenia matice 1x1 skalarom je nespravny.";

    compare_result.set(0, 0, -13);
    EXPECT_FALSE(valid_result == compare_result) << "Vysledok nasobenia matice 1x1 skalarom je nespravny.";
}

TEST_F(Matrix_1x1, Solve) {
      matrix.set(0, 0, 2);

      //2x = 10 -> x = 5
      EXPECT_TRUE(matrix.solveEquation(std::vector<double> {10}) ==
                  (std::vector<double> {5}));
}

TEST_F(Matrix_RxR, Construction) {
    EXPECT_NO_THROW(Matrix(6, 6)) << "Matica nevytvorena, avsak velkost je spravna.";
    EXPECT_NO_THROW(Matrix(2392, 2392)) << "Matica nevytvorena, avsak velkost je spravna.";
    EXPECT_NO_THROW(Matrix(13, 13)) << "Matica nevytvorena, avsak velkost je spravna.";

    EXPECT_ANY_THROW(Matrix(-3, -3)) << "Matica vytvorena napriek neplatnej velkosti.";
    EXPECT_ANY_THROW(Matrix(0, 0)) << "Matica vytvorena napriek neplatnej velkosti.";
    EXPECT_ANY_THROW(Matrix(-239, -239)) << "Matica vytvorena napriek neplatnej velkosti.";
}

TEST_F(Matrix_RxR, Set_Value) {
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Pociatocna hodnota nulovej matice ma byt 0.";
    matrix.set(0, 0, 10);
    EXPECT_EQ(10, matrix.get(0, 0))<< "Nastavenie hodnoty prvku matice nefunkcne.";


    EXPECT_FALSE(matrix.set(-1, -1, 5)) << "Pristup na neplatny index.";
    EXPECT_FALSE(matrix.set(-53, -53, 0)) << "Pristup na neplatny index.";
}

TEST_F(Matrix_RxR, Set_Values_By_Matrix) {
    //funkcia vracia true/false, vyuzijeme EXPECT_TRUE,resp FALSE

    EXPECT_TRUE(matrix.set(std::vector<std::vector< double > >
        {
          {1,  2,  3,  4,  5},
          {6,  7,  8,  9,  10},
          {11, 12, 13, 14, 15},
          {16, 17, 18, 19, 20},
          {21, 22, 23, 24, 25}
        }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > >
        {
          {1, 2, 3},
          {4, 5, 6}
        }
    ));
}

TEST_F(Matrix_RxR, Indeces_Get) {
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Matica bola nespravne nainicializovana.";

    matrix.set(3, 3, 420);
    EXPECT_EQ(420.0, matrix.get(3, 3)) << "Nastavenie hodnoty prvku matice nefunkcne.";

    EXPECT_ANY_THROW(matrix.get(-78, -78)) << "Matica bola nespravne nainicializovana.";
    EXPECT_ANY_THROW(matrix.get(-1, -1)) << "Matica bola nespravne nainicializovana.";
    EXPECT_ANY_THROW(matrix.get(42, 42)) << "Matica bola nespravne nainicializovana.";
}

TEST_F(Matrix_RxR, Equals) {
    Matrix valid_matrix = Matrix(5, 5);
    Matrix invalid_matrix = Matrix(6, 6);
    Matrix invalid2_matrix = Matrix(3, 8);

    //funkcia operator== vracia bool, mozeme pouzit EXPECT_TRUE
    EXPECT_TRUE(matrix == valid_matrix) << "Matice sa maju rovnat, maju rovnaku velkost.";

    EXPECT_ANY_THROW(matrix == invalid_matrix) << "Matice nie su rovnako velke.";
    EXPECT_ANY_THROW(matrix == invalid2_matrix) << "Matice nie su rovnako velke.";

    //nastavenie hodnot oboch matic na rovnaku hodnotu, mali by sa rovnat
    matrix.set(std::vector<std::vector< double > >
      {
        {1,  0,  0,  0,  0},
        {0,  1,  0,  0,  0},
        {0,  0,  1,  0,  0},
        {0,  0,  0,  1,  0},
        {0,  0,  0,  0,  1}
      });
    valid_matrix.set(std::vector<std::vector< double > >
      {
        {1,  0,  0,  0,  0},
        {0,  1,  0,  0,  0},
        {0,  0,  1,  0,  0},
        {0,  0,  0,  1,  0},
        {0,  0,  0,  0,  1}
      });

    EXPECT_TRUE(matrix == valid_matrix) << "Nastavenie hodnot polom je nefunkcne.";

    //nastavenie rozdielnych hodnot
    //matrix[0][0] = 5;
    valid_matrix.set(0, 0, -32);

    EXPECT_FALSE(matrix == valid_matrix) << "Nastavenie hodnot polom je nefunkcne.";
}

TEST_F(Matrix_RxR, Sum) {
    Matrix valid_matrix = Matrix(5, 5);
    //matice musia mat rovnaku velkost, ak ich chceme scitat
    EXPECT_TRUE(matrix == valid_matrix)  << "Pre sucet 2 matic je potrebna rovnaka velkost.";

    Matrix inv_matrix = Matrix(3, 8);
    EXPECT_ANY_THROW(valid_matrix == inv_matrix);

    valid_matrix.set(std::vector<std::vector< double > >
        {
          {5,  0,  0,  0,  0},
          {2,  1,  0,  0,  0},
          {4,  0,  0,  10, 5},
          {10, 7,  0,  0,  2},
          {1,  2,  0,  0,  0}
        });

    matrix.set(std::vector<std::vector< double > >
        {
          {5,  0,  0,  0,  0},
          {8,  9,  0,  0,  0},
          {6,  0,  0,  0,  5},
          {0,  3,  0,  0,  8},
          {9,  8,  0,  0,  0}
        });

    /*
      Ocakavany vysledok suctu matic:
      {10,  0,   0,  0,  0},
      {10,  10,  0,  0,  0},
      {10,  0,   0,  10, 10},
      {10,  10,  0,  0,  10},
      {10,  10,  0,  0,  0}
    */

    Matrix valid_result = matrix + valid_matrix;
    Matrix compare_result = Matrix(5, 5);
    compare_result.set(std::vector<std::vector< double > >
        {
          {10,  0,   0,  0,  0},
          {10,  10,  0,  0,  0},
          {10,  0,   0,  10, 10},
          {10,  10,  0,  0,  10},
          {10,  10,  0,  0,  0}
        });
    EXPECT_TRUE(valid_result == compare_result) << "Scitanie matic typu RxR je chybove.";

    compare_result.set(0, 0, -942);
    EXPECT_FALSE(valid_result == compare_result) << "Scitanie matic typu RxR je chybove.";
}

TEST_F(Matrix_RxR, Product) {
    Matrix valid_matrix = Matrix(5, 5);
    Matrix inv_matrix = Matrix(1, 123);

    EXPECT_ANY_THROW(valid_matrix * inv_matrix);
    EXPECT_TRUE(matrix == valid_matrix) << "Matice sa maju rovnat = maju rovnaku velkost.";

    valid_matrix.set(std::vector<std::vector< double > >
        {
          {2,  2,  2,  2,  2},
          {3,  3,  3,  3,  3},
          {4,  4,  4,  4,  4},
          {5,  5,  5,  5,  5},
          {6,  6,  6,  6,  6}
        });

    matrix.set(std::vector<std::vector< double > >
        {
          {1,  2,  3,  4,  5},
          {1,  2,  3,  4,  5},
          {1,  2,  3,  4,  5},
          {1,  2,  3,  4,  5},
          {1,  2,  3,  4,  5}
        });

    /*
        Ocakavany vysledok sucinu matic:
        {10, 20, 30, 40, 50},
        {15, 30, 45, 60, 75},
        {20, 40, 60, 80, 100},
        {25, 50, 75, 100, 125},
        {30, 60, 90, 120, 150}
    */

    Matrix valid_result = Matrix(5, 5);
    valid_result = valid_matrix * matrix;

    Matrix compare_result = Matrix(5, 5);
    compare_result.set(std::vector<std::vector< double > >
        {
          {10, 20, 30, 40, 50},
          {15, 30, 45, 60, 75},
          {20, 40, 60, 80, 100},
          {25, 50, 75, 100, 125},
          {30, 60, 90, 120, 150}
        });

    EXPECT_TRUE(valid_result == compare_result) << "Chyba pri nasobeni dvoch matic typu RxR.";

    compare_result.set(0, 0, 13.238);
    EXPECT_FALSE(valid_result == compare_result)  << "Chyba pri nasobeni dvoch matic typu RxR.";
}

TEST_F(Matrix_RxR, Scalar) {
    matrix.set(std::vector<std::vector< double > >
      {
        {10,  0,  0,  0,  0},
        {0,  20,  0,  0,  0},
        {0,   0, 30,  0,  0},
        {0,   0,  0, 40,  0},
        {0,   0,  0,  0, 50}
      });

    int constant = 2;
    Matrix valid_result = matrix * constant;
    Matrix compare_result = Matrix(5, 5);

    compare_result.set(std::vector<std::vector< double > >
      {
        {20,  0,  0,  0,  0},
        {0,  40,  0,  0,  0},
        {0,   0, 60,  0,  0},
        {0,   0,  0, 80,  0},
        {0,   0,  0,  0,100}
      });
    EXPECT_TRUE(valid_result == compare_result) << "Nasobenie matic RxR skalarom chybove.";

    compare_result.set(0, 3, -13);
    EXPECT_FALSE(valid_result == compare_result) << "Nasobenie matic RxR skalarom chybove.";
}

TEST_F(Matrix_RxR, Solve) {

      Matrix m = Matrix(3, 3);
      m.set(std::vector<std::vector< double > >
        {
          {1,  2,  1},
          {3,  2,  1},
          {4,  3, -2}
        });

      Matrix x2 = Matrix(2, 2);
      x2.set(std::vector<std::vector< double > >
        {
          {1,  2},
          {3,  2}
        });

      EXPECT_TRUE(m.solveEquation(std::vector<double> {8, 10, 4}) ==
      (std::vector<double> {1, 2, 3}));

      Matrix singular = Matrix(2, 2);
      singular.set(std::vector<std::vector< double > >
        {
          {1, 1},
          {3, 3}
        });
      EXPECT_ANY_THROW(singular.solveEquation(std::vector<double> {3, 4}));

      Matrix x4 = Matrix(4, 4);
      x4.set(std::vector<std::vector< double > >
        {
          {1,  2,  1, 1},
          {3,  2,  1, 1},
          {4,  3, -2, 1},
          {1,  1,  1, 1}
        });

        EXPECT_TRUE(x4.solveEquation(std::vector<double> {1, 1, 1, 1}) ==
        (std::vector<double> {0, 0, 0, 1}));

}

TEST_F(Matrix_RxC, Construction) {
    EXPECT_NO_THROW(Matrix(2, 10)) << "Neplatna velkost matice.";
    EXPECT_NO_THROW(Matrix(1, 4)) << "Neplatna velkost matice.";
    EXPECT_NO_THROW(Matrix(123, 13)) << "Neplatna velkost matice.";

    EXPECT_ANY_THROW(Matrix(-3, 0)) << "Neplatna velkost matice.";
    EXPECT_ANY_THROW(Matrix(0, 123)) << "Neplatna velkost matice.";
    EXPECT_ANY_THROW(Matrix(-239, -78)) << "Neplatna velkost matice.";
}

TEST_F(Matrix_RxC, Set_Value) {
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Pociatocna hodnota nulovej matice ma byt 0.";
    matrix.set(0, 0, 10);
    EXPECT_EQ(10, matrix.get(0, 0)) << "Chyba pri dosadeni hodnoty do nulovej matice.";


    EXPECT_FALSE(matrix.set(-1, -332, 5)) << "Nepovolena velkost matice.";
    EXPECT_FALSE(matrix.set(-53, 0, 0)) << "Nepovolena velkost matice.";
}

TEST_F(Matrix_RxC, Set_Values_By_Matrix) {
    //funkcia vracia true/false, vyuzijeme EXPECT_TRUE,resp FALSE

    EXPECT_TRUE(matrix.set(std::vector<std::vector< double > >
        {
          {1, 2, 3, 4},
          {5, 6, 7, 8}
        }
    ));

    EXPECT_FALSE(matrix.set(std::vector<std::vector< double > >
        {
          {1, 2, 3},
          {4, 5, 6}
        }
    ));
}

TEST_F(Matrix_RxC, Indeces_Get) {
    EXPECT_EQ(0.0, matrix.get(0, 0)) << "Nefunkcna funkcia .get()";

    matrix.set(1, 3, 420);
    EXPECT_EQ(420.0, matrix.get(1, 3)) << "Nefunkcna funkcia .get()";

    EXPECT_ANY_THROW(matrix.get(0, -78)) << "Nefunkcna funkcia .get()";
    EXPECT_ANY_THROW(matrix.get(-1, 0)) << "Nefunkcna funkcia .get()";
    EXPECT_ANY_THROW(matrix.get(420, 142)) << "Nefunkcna funkcia .get()";
}

TEST_F(Matrix_RxC, Equals) {
    Matrix valid_matrix = Matrix(2, 4);
    Matrix invalid_matrix = Matrix(10, 600);
    Matrix invalid2_matrix = Matrix(300, 81);

    //funkcia operator== vracia bool, mozeme pouzit EXPECT_TRUE
    EXPECT_TRUE(matrix == valid_matrix) << "Porovavanie matic hadze chybove vysledky";

    EXPECT_ANY_THROW(matrix == invalid_matrix) << "Porovavanie matic hadze chybove vysledky";
    EXPECT_ANY_THROW(matrix == invalid2_matrix) << "Porovavanie matic hadze chybove vysledky";

    //nastavenie hodnot oboch matic na rovnaku hodnotu, mali by sa rovnat
    matrix.set(std::vector<std::vector< double > >
      {
        {2,  0,  0,  0},
        {0,  1,  0,  0}
      });
    valid_matrix.set(std::vector<std::vector< double > >
      {
        {2,  0,  0,  0},
        {0,  1,  0,  0}
      });

    EXPECT_TRUE(matrix == valid_matrix) << "Porovavanie matic hadze chybove vysledky";

    //nastavenie rozdielnych hodnot
    valid_matrix.set(0, 0, -32);
    EXPECT_FALSE(matrix == valid_matrix) << "Porovavanie matic hadze chybove vysledky";
}

TEST_F(Matrix_RxC, Sum) {
    Matrix valid_matrix = Matrix(2, 4);
    //matice musia mat rovnaku velkost, ak ich chceme scitat
    EXPECT_TRUE(matrix == valid_matrix) << "Porovavanie matic hadze chybove vysledky";

    valid_matrix.set(std::vector<std::vector< double > >
        {
          {5,  8,  123,  10},
          {2,  1,  11,  0}
        });

    matrix.set(std::vector<std::vector< double > >
        {
          {5,  10,  2,  0},
          {8,  9,  110,  9}
        });

    /*
      Ocakavany vysledok suctu matic:
      {10,  18,   125,  10},
      {10,  10,  121,  9}
    */

    Matrix valid_result = matrix + valid_matrix;
    Matrix compare_result = Matrix(2, 4);
    compare_result.set(std::vector<std::vector< double > >
        {
          {10,  18,   125,  10},
          {10,  10,  121,  9}
        });
    EXPECT_TRUE(valid_result == compare_result) << "Scitanie matic nefunguje spravne.";

    compare_result.set(0, 0, -942);
    EXPECT_FALSE(valid_result == compare_result) << "Scitanie matic nefunguje spravne.";
}

TEST_F(Matrix_RxC, Product) {
    Matrix valid_matrix = Matrix(4, 2);

    valid_matrix.set(std::vector<std::vector< double > >
      {
        {2,  0},
        {2,  2},
        {2,  3},
        {0,  1}
      });

    matrix.set(std::vector<std::vector< double > >
      {
        {5,  10,  2,  0},
        {8,  9,  110,  9}
      });

    Matrix valid_result = valid_matrix * matrix;

    /*
      Ocakavany vysledok:

      {10,  20,  4,  0},
      {26,  38,  224,  18},
      {34,  47,  334,  27},
      {8,  9,  110,  9}
    */

    Matrix compare_result = Matrix(4, 4);
    compare_result.set(std::vector<std::vector< double > >
      {
        {10,  20,  4,  0},
        {26,  38,  224,  18},
        {34,  47,  334,  27},
        {8,  9,  110,  9}
      });

    EXPECT_TRUE(compare_result == valid_result) << "Nasobenie matic ma chybove vysledky.";

    compare_result.set(1, 1, 444);
    EXPECT_FALSE(valid_result == compare_result) << "Nasobenie matic ma chybove vysledky.";
}

TEST_F(Matrix_RxC, Scalar) {
    matrix.set(std::vector<std::vector< double > >
      {
        {1,  2,  3,  4},
        {4,  3,  2,  1}
      });

    int constant = 10;
    Matrix valid_result = matrix * constant;
    Matrix compare_result = Matrix(2, 4);

    compare_result.set(std::vector<std::vector< double > >
      {
        {10,  20,  30,  40},
        {40,  30,  20,  10}
      });
    EXPECT_TRUE(valid_result == compare_result) << "Nasobenie matic skalarom ma chybove vysledky.";

    compare_result.set(1, 1, 444);
    EXPECT_FALSE(valid_result == compare_result) << "Nasobenie matic skalarom ma chybove vysledky.";
}

TEST_F(Matrix_RxC, Solve) {
      matrix.set(std::vector<std::vector< double > >
      {
        {5,  10,  2,  0},
        {8,  9,  110,  9}
      });

    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {8, 18, 3, 1}));
    EXPECT_ANY_THROW(matrix.solveEquation(std::vector<double> {8}));
}
/*** Konec souboru white_box_tests.cpp ***/
