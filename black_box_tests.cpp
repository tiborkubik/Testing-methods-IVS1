//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Tibor Kubik <xkubik34@stud.fit.vutbr.cz>
// $Date:       $2019-2-20
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Tibor Kubik
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test {
  protected:
    BinaryTree testedTree;

};

class NonEmptyTree : public ::testing::Test {
  protected:
    virtual void SetUp() {
      for (int i = 1; i < 15; i += 2) {
        testedTree.InsertNode(i);
      }
    }

    BinaryTree testedTree;
};

class TreeAxioms : public ::testing::Test {
    protected:
      virtual void SetUp() {
        for (int i = 0; i < 40; i += 4) {
          testedTree.InsertNode(i);
        }
      }

      BinaryTree testedTree;

};

TEST_F(EmptyTree, InsertNode) {

  ASSERT_TRUE(testedTree.GetRoot() == NULL) << "Koren prazdneho stromu musi mat hodnotu NULL.";

  std::pair<bool, BinaryTree::Node_t *> testedPair = testedTree.InsertNode(10);
  ASSERT_TRUE(testedPair.second != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(testedPair.first) << "Nespravne vlozeny prvok";
  EXPECT_EQ(testedPair.second->color, BinaryTree::BLACK)  << "Nespravne vlozeny prvok";

  EXPECT_TRUE(testedPair.second->pParent == NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(testedPair.second->pLeft != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(testedPair.second->pRight != NULL) << "Nespravne vlozeny prvok";

  EXPECT_TRUE(testedPair.second->pLeft->pParent != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(testedPair.second->pRight->pParent != NULL) << "Nespravne vlozeny prvok";

  EXPECT_EQ(testedPair.second->pLeft->color, BinaryTree::BLACK) << "Nespravne vlozeny prvok";
  EXPECT_EQ(testedPair.second->pRight->color, BinaryTree::BLACK) << "Nespravne vlozeny prvok";

  std::pair<bool, BinaryTree::Node_t *> tested2Pair = testedTree.InsertNode(10);
  ASSERT_TRUE(tested2Pair.second != NULL) << "Nespravne vlozeny prvok";
  EXPECT_FALSE(tested2Pair.first) << "Nespravne vlozeny prvok";

}

TEST_F(EmptyTree, DeleteNode) {
  EXPECT_FALSE(testedTree.DeleteNode(0)) << "Odstranenie prvku neprebieha spravne.";
  EXPECT_FALSE(testedTree.DeleteNode(42)) << "Odstranenie prvku neprebieha spravne.";
  EXPECT_FALSE(testedTree.DeleteNode(-3)) << "Odstranenie prvku neprebieha spravne.";

  std::pair<bool, BinaryTree::Node_t *> testedPair = testedTree.InsertNode(322);
  EXPECT_TRUE(testedTree.DeleteNode(322)) << "Odstranenie prvku neprebieha spravne.";
}

TEST_F(EmptyTree, FindNode) {
  EXPECT_FALSE(testedTree.FindNode(10)) << "Hladanie uzla neprebehlo v poriadku.";
  EXPECT_FALSE(testedTree.FindNode(-31)) << "Hladanie uzla neprebehlo v poriadku.";
  EXPECT_FALSE(testedTree.FindNode(0)) << "Hladanie uzla neprebehlo v poriadku.";

  std::pair<bool, BinaryTree::Node_t *> testedPair = testedTree.InsertNode(-2);
  EXPECT_TRUE(testedTree.FindNode(-2)) << "Hladanie uzla neprebehlo v poriadku.";
  EXPECT_FALSE(testedTree.FindNode(0)) << "Hladanie uzla neprebehlo v poriadku.";
}


TEST_F(NonEmptyTree, InsertNode) {
  ASSERT_FALSE(testedTree.GetRoot() == NULL) << "Koren prazdneho stromu musi mat hodnotu NULL.";


  std::pair<bool, BinaryTree::Node_t *> testedPair = testedTree.InsertNode(1);

  // vkladanie prvku, ktory uz existuje v liste
  ASSERT_FALSE(testedPair.first) << "Nespravne vlozeny prvok";

  std::pair<bool, BinaryTree::Node_t *> tested2Pair = testedTree.InsertNode(47);
  ASSERT_TRUE(tested2Pair.second != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(tested2Pair.first) << "Nespravne vlozeny prvok";

  EXPECT_TRUE(tested2Pair.second->pParent != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(tested2Pair.second->pLeft != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(tested2Pair.second->pRight != NULL) << "Nespravne vlozeny prvok";

  EXPECT_TRUE(tested2Pair.second->pLeft->pParent != NULL) << "Nespravne vlozeny prvok";
  EXPECT_TRUE(tested2Pair.second->pRight->pParent != NULL) << "Nespravne vlozeny prvok";

  EXPECT_EQ(testedPair.second->pLeft->color, BinaryTree::BLACK) << "Nespravne vlozeny prvok";
  EXPECT_EQ(testedPair.second->pRight->color, BinaryTree::BLACK) << "Nespravne vlozeny prvok";
}

TEST_F(NonEmptyTree, DeleteNode) {
  for (int i = 1; i < 15; i += 2) {
    EXPECT_TRUE(testedTree.DeleteNode(i)) << "Odstranenie prvku neprebieha spravne.";
  }

  for (int i = 2; i < 16; i += 2) {
    EXPECT_FALSE(testedTree.DeleteNode(i)) << "Odstranenie prvku neprebieha spravne.";
  }

  EXPECT_FALSE(testedTree.DeleteNode(80)) << "Odstranenie prvku neprebieha spravne.";

  std::pair<bool, BinaryTree::Node_t *> testedPair = testedTree.InsertNode(322);
  EXPECT_TRUE(testedTree.DeleteNode(322)) << "Odstranenie prvku neprebieha spravne.";
  EXPECT_FALSE(testedTree.DeleteNode(-231)) << "Odstranenie prvku neprebieha spravne.";
}


TEST_F(NonEmptyTree, FindNode) {
  for (int i = 1; i < 15; i += 2) {
    EXPECT_TRUE(testedTree.FindNode(i)) << "Hladanie uzla neprebehlo v poriadku.";
  }

  for (int i = 2; i < 16; i += 2) {
    EXPECT_FALSE(testedTree.FindNode(i)) << "Hladanie uzla neprebehlo v poriadku.";
  }
}

// vsechny listove uzly stromu jsou *VZDY* cerne
TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t *> leaves;
    testedTree.GetLeafNodes(leaves);

    // cyklus prejde vsetky nodes v poli listov a skontroluje ich farbu
    for (BinaryTree::Node_t *node : leaves) {
			EXPECT_EQ(node->color, BinaryTree::BLACK) << "Listove uzly musia mat ciernu farbu.";
		}
}

// Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
TEST_F(TreeAxioms, Axiom2) {
    // vytvorim pole, do ktoreho priradim vsetky uzly stromu, aby som mmohol nim iterovat
    std::vector<Node_t *> allNodes;

    testedTree.GetAllNodes(allNodes);

    // iteracia celym stromom, resp. polom obsahujucim vsetky uzly stromu
    for(BinaryTree::Node_t *node : allNodes) {
      if(node->color == BinaryTree::RED) {
        ASSERT_TRUE(node->pLeft->color == BinaryTree::BLACK) << "Cerveny uzol obsahuje cerveneho potomka !";
        ASSERT_TRUE(node->pRight->color == BinaryTree::BLACK) << "Cerveny uzol obsahuje cerveneho potomka !";
      }
    }
}

// vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
// *STEJNY* pocet cernych uzlu.
TEST_F(TreeAxioms, Axiom3) {
    std::vector<Node_t *> leaves;
    int prev_length = 0;
    int check = -1;

    testedTree.GetLeafNodes(leaves);  // pole obsahujuce vsetky listove uzly

    for(BinaryTree::Node_t *node : leaves) {
      int act_length = 0;
      BinaryTree::Node_t *actualNode = node;

      while(actualNode != NULL) {

        if(actualNode->color == BinaryTree::BLACK) {
          act_length++;
        }
        actualNode = actualNode->pParent;
      }

      //prva iteracia
      if(check == -1) {
        prev_length = act_length;
      }

      check = 0;
      ASSERT_TRUE(act_length == prev_length) << "Pocet ciernych uzlov medzi korenom a jednotlivymi listami nie je rovnaky!";
      prev_length = act_length;
    }
}

/*** Konec souboru black_box_tests.cpp ***/
