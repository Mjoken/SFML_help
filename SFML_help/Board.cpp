#include <iostream>
#include <SFML/Graphics.hpp>
//#include "board.h"
#include "Checker.cpp"
#include <memory>
#include <vector>

struct pos {
    int current_x{};
    int current_y{};
    int next_x{};
    int next_y{};
    int mark{};
    pos* CheackerToPos(Cheacker* a, int x_next, int y_next) {
        if (this != nullptr) {
            current_x = a->x;
            current_y = a->y;
            next_x = x_next;
            next_y = y_next;
            return this;
        }
    }
};

class Board {
private:
   int size = 8;
   
public:
   int countCheakers = 16;

   void Draw(sf::RenderWindow& window) {
      sf::RectangleShape tile;
      tile.setSize(sf::Vector2f(100.f, 100.f));
      for (int i = 0; i < size; i++) {
         for (int j = 0; j < size; j++) {
            tile.setPosition(sf::Vector2f(100 * i, 100 * j));
            if ((i + j) % 2 == 0) {
               tile.setFillColor(sf::Color(255, 233, 201, 255));
            }
            else {
               tile.setFillColor(sf::Color(137, 53, 255, 255));
            }
            window.draw(tile);
         }
      }
   }

   void Highlight(sf::RenderWindow& window, int x, int y) {
      sf::RectangleShape tile;
      tile.setSize(sf::Vector2f(100.f, 100.f));
      tile.setFillColor(sf::Color(68, 162, 130, 255));
      tile.setPosition(sf::Vector2f(100 * x, 100 * y));
      window.draw(tile);
   }
};

int eqalFunction(const Cheacker* cheackers_1_color, const Cheacker* cheackers_2_color, int count_of_cheackers = 12) {
    int Red = 0, White = 0;
    for (int i{}; i < count_of_cheackers; ++i) {
        if (cheackers_1_color[i].color == sf::Color::Red && cheackers_1_color[i].isAlive == true) {
            Red++;
            //std::cout <<"Red:" << Red << std::endl;
        }
        if (cheackers_2_color[i].color == sf::Color::White && cheackers_2_color[i].isAlive == true) {
            White++;
            //std::cout <<"White"<< White << std::endl;
        }
    }
    return Red - White;
}

void Setup(sf::RenderWindow& window, Cheacker* RedCheacker, Cheacker* WhiteCheacker) {
   int m = 0;
   for (int i = 0; i < 3; i++) {
      for (int j = (int)!(i % 2 & 1); j < 8; j += 2) {
         WhiteCheacker[m].isAlive = true;
         WhiteCheacker[m].x = j;
         WhiteCheacker[m].y = i;
         m++;
      }

   }
   m = 0;
   for (int i = 0; i < 3; i++) {
      for (int j = (int)(i % 2 & 1); j < 8; j += 2) {
         RedCheacker[m].isAlive = true;
         RedCheacker[m].x = j;
         RedCheacker[m].y = 7 - i;
         m++;
      }

   }
}
/*
* ���������: ��������� �����, � ������������� ����������� x, y
* ���� ��� ����� �� ����
* �����: ���� ��� ����, ���������� ������ �� ��, ���� ���, ����
* p.s. ��� ��������� ������ ����� �������� ���� �������� �� ��, ��������� �� ����� � ������ ����
*/
Cheacker* FindChecker(int x, int y, Cheacker* RedChecker, Cheacker* WhiteChecker) {
   for (int i = 0; i < 12; i++) {
      if (RedChecker[i].x == x && RedChecker[i].y == y) {
         if (RedChecker[i].isAlive) {
            return &RedChecker[i];
         }
      }
      if (WhiteChecker[i].x == x && WhiteChecker[i].y == y) {
         if (WhiteChecker[i].isAlive) {
            return &WhiteChecker[i];
         }
      }
   }
   return NULL;
}
/*
* ���������: ��������� �����, � ������������� ����������� x, y
* ���� ��� ����� �� ����
* �����: ���� ��� ����, ���������� true, ���� ���, false
* p.s. ��� ��������� ������ ����� �������� ���� �������� �� ��, ��������� �� ����� � ������ ����
*/
bool boolFindChecker(int x, int y, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    for (int i = 0; i < 12; i++) {
        if (RedChecker[i].x == x && RedChecker[i].y == y) {
            if (RedChecker[i].isAlive) {
                return true;
            }
        }
        if (WhiteChecker[i].x == x && WhiteChecker[i].y == y) {
            if (WhiteChecker[i].isAlive) {
                return true;
            }
        }
    }
    return false;
}

//void ocenochnaya(std::string color) {
//   static int toWin_red = 0;
//   static int toWin_white = 0;
//   if (color == "white") {
//
//      toWin_red += 1;
//      std::cout << "White eat: " << toWin_red << std::endl;
//   }
//   else if (color == "red") {
//      toWin_white += 1;
//      std::cout << "Red eat: " << toWin_white << std::endl;
//   }
//}

/*--------------------��������, ������ � ����� ������---------------------------*/
/*
* ���������: ��������� �����, � ������������� ����������� x, y
* ������� � �����
* ����������: ������� ������ (void)
*/
void KillCheacker(int x, int y, Cheacker* RedChecker, Cheacker* WhiteChecker, int* turn) {
  if (FindChecker(x, y, RedChecker, WhiteChecker)->color == sf::Color::Red) {
      //std::cout << "red";
      std::cout<< eqalFunction(RedChecker, WhiteChecker);
   }
   else if (FindChecker(x, y, RedChecker, WhiteChecker)->color == sf::Color::White) {
     //std::cout << "white";
     std::cout<< eqalFunction(RedChecker, WhiteChecker);
   }
  FindChecker(x, y, RedChecker, WhiteChecker)->isAlive = false;
  *turn = ((*turn == 1) ? 2 : 1);
   return;
}
/*
* ��������� ��� ������ ����� ����
* ���������: ��������� �����, � ������������� ����������� x, y
* ������� � �����
* ����������: ������� ������ (void)
*/
void KillCheacker(int x, int y, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    FindChecker(x, y, RedChecker, WhiteChecker)->isAlive = false;
    return;
}
/*
* ��������� ��� ������ ����� ����
* ���������: ��������� �����, � ������������� ����������� x, y
* ������� � �����
* ����������: ������� ������ (void)
*/
void KillCheacker(Cheacker* toKill) {
    toKill->isAlive = false;
    return;
}
/*
* ���������: ��������� � ���������� ����� � � ����
* ���� ����� ����� ������� � ���������� �����
* ����������: ��������� �� ��
*/
Cheacker* FindMidleCheaker(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    int midX{ abs(posCur->current_x - posCur->next_x) }, midY{ abs(posCur->current_y - posCur->next_y) };
    if (midX > 1 && midY > 1 && boolFindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker) &&
        FindChecker(posCur->current_x, posCur->current_y, RedChecker, WhiteChecker)->color != FindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker)->color) {
        return(FindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker));
    }
    return nullptr;
}

// ��������� ������, ����� ����� ���� �������� eqalFunction, ����� ��� ��� �������, � ���� �� �������... ����� ��� �������?
/*--------------------����� �����---------------------------*/

/*
* ���������: ��������� � ���������� ����� � � ����, ������ ����, ���������� 8
* ���������� �� ����� � � ��� � ������ ����
* �����: ���������� ����������� ����, ������� ����������, ���������� �� ������� � ����������� ��� � ������ ����
*/
bool inField(pos* posCur, int sizeField=8) {
    return (posCur->current_x < sizeField && posCur->current_x >= 0 && posCur->current_y < sizeField && posCur->current_y >= 0
        && posCur->next_x < sizeField && posCur->next_x >= 0 && posCur->next_y < sizeField && posCur->next_y >= 0
        );
}
/*
* ���������: ��������� � ���������� ����� � � ����
* �������� �� ������ � ������� �� ����� ������� ���
* �����: ���������� ����������� ����, �������� ��� ���
*/
bool isFreeNextPos(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker, int sizeField = 8) {
    return !boolFindChecker(posCur->next_x, posCur->next_y, RedChecker, WhiteChecker);
}
/*
* ���������: ��������� � ���������� ����� � � ����, ��������� � ������������� ����� �� ���� � �� ���������
* ���������, �������� �� ���, ������� ��������� ������������
* �����: ����� �� ������� ���
*/
bool canMove(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    if (inField(posCur) && isFreeNextPos(posCur, RedChecker, WhiteChecker)) {
        if (abs(posCur->next_x - posCur->current_x) < 2 && abs(posCur->next_y - posCur->current_y) < 2) {
            return true;
        }
        else if (FindMidleCheaker(posCur, RedChecker, WhiteChecker) != nullptr) {
            return true;
        }
    }
     return false;
}
/*
* ���������: ��������� � ���������� ����� � � ����, ��������� � ������������� ����� �� ���� � �� ���������
* ������ ���
* �����: -
*/
void Move(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    Cheacker* cur;
    Cheacker* mid;
    mid = FindMidleCheaker(posCur, RedChecker, WhiteChecker);
    cur = FindChecker(posCur->current_x, posCur->current_y, RedChecker, WhiteChecker); // ������ ������� �����
    if (canMove(posCur, RedChecker, WhiteChecker)) {
        cur->x = posCur->next_x;
        cur->y = posCur->next_y;
        if (mid != nullptr) {
            KillCheacker(mid);
        }
    }
}

int MoveChecker(int x, int y, Cheacker* s_checker, Cheacker* RedChecker, Cheacker* WhiteChecker, int* turn) {
   if (s_checker->color == sf::Color::Red || s_checker->color == sf::Color::White && s_checker->queen) {
      if (x == s_checker->x - 1 && y == s_checker->y - 1) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
      if (x == s_checker->x + 1 && y == s_checker->y - 1) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
      if (x == s_checker->x - 2 && y == s_checker->y - 2) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x + 1, y + 1, RedChecker, WhiteChecker) != NULL && FindChecker(x + 1, y + 1, RedChecker, WhiteChecker)->color != s_checker->color) {
            *turn = ((*turn == 1) ? 2 : 1);
          
            KillCheacker(x + 1, y + 1, RedChecker, WhiteChecker, turn);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
      if (x == s_checker->x + 2 && y == s_checker->y - 2) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x - 1, y + 1, RedChecker, WhiteChecker) != NULL && FindChecker(x - 1, y + 1, RedChecker, WhiteChecker)->color != s_checker->color) {
            *turn = ((*turn == 1) ? 2 : 1);
           
            KillCheacker(x - 1, y + 1, RedChecker, WhiteChecker, turn);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
   }
   if (s_checker->color == sf::Color::White || s_checker->color == sf::Color::Red && s_checker->queen) {
      if (x == s_checker->x - 1 && y == s_checker->y + 1) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
      if (x == s_checker->x + 1 && y == s_checker->y + 1) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
            return 1;
         }
      }
      if (x == s_checker->x - 2 && y == s_checker->y + 2) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x + 1, y - 1, RedChecker, WhiteChecker) != NULL && FindChecker(x + 1, y - 1, RedChecker, WhiteChecker)->color != s_checker->color) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
          
            KillCheacker(x + 1, y - 1, RedChecker, WhiteChecker, turn);
            return 1;
         }
      }
      if (x == s_checker->x + 2 && y == s_checker->y + 2) {
         if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x - 1, y - 1, RedChecker, WhiteChecker) != NULL && FindChecker(x - 1, y - 1, RedChecker, WhiteChecker)->color != s_checker->color) {
            *turn = ((*turn == 1) ? 2 : 1);
            s_checker->x = x;
            s_checker->y = y;
       
            KillCheacker(x - 1, y - 1, RedChecker, WhiteChecker, turn);
            return 1;
         }
      }
   }
   return 0;
}
/*
* 
* 
*/
int MoveChecker(int x, int y, Cheacker* s_checker, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    if (s_checker->color == sf::Color::Red || s_checker->color == sf::Color::White && s_checker->queen) {
        if (x == s_checker->x - 1 && y == s_checker->y - 1) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker)) {               
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
        if (x == s_checker->x + 1 && y == s_checker->y - 1) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker)) {           
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
        if (x == s_checker->x - 2 && y == s_checker->y - 2) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x + 1, y + 1, RedChecker, WhiteChecker) != NULL && FindChecker(x + 1, y + 1, RedChecker, WhiteChecker)->color != s_checker->color) {
                KillCheacker(x + 1, y + 1, RedChecker, WhiteChecker);
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
        if (x == s_checker->x + 2 && y == s_checker->y - 2) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x - 1, y + 1, RedChecker, WhiteChecker) != NULL && FindChecker(x - 1, y + 1, RedChecker, WhiteChecker)->color != s_checker->color) {
                KillCheacker(x - 1, y + 1, RedChecker, WhiteChecker);
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
    }
    if (s_checker->color == sf::Color::White || s_checker->color == sf::Color::Red && s_checker->queen) {
        if (x == s_checker->x - 1 && y == s_checker->y + 1) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
        if (x == s_checker->x + 1 && y == s_checker->y + 1) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker)) {
                s_checker->x = x;
                s_checker->y = y;
                return 1;
            }
        }
        if (x == s_checker->x - 2 && y == s_checker->y + 2) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x + 1, y - 1, RedChecker, WhiteChecker) != NULL && FindChecker(x + 1, y - 1, RedChecker, WhiteChecker)->color != s_checker->color) {
                s_checker->x = x;
                s_checker->y = y;

                KillCheacker(x + 1, y - 1, RedChecker, WhiteChecker);
                return 1;
            }
        }
        if (x == s_checker->x + 2 && y == s_checker->y + 2) {
            if (!FindChecker(x, y, RedChecker, WhiteChecker) && FindChecker(x - 1, y - 1, RedChecker, WhiteChecker) != NULL && FindChecker(x - 1, y - 1, RedChecker, WhiteChecker)->color != s_checker->color) {
                s_checker->x = x;
                s_checker->y = y;

                KillCheacker(x - 1, y - 1, RedChecker, WhiteChecker);
                return 1;
            }
        }
    }
    return 0;
}


void Copy(const Cheacker* Red, Cheacker* RedCopy, const Cheacker* White, Cheacker* WhiteCopy) {
    for (int i{}; i < 12; i++) {
        RedCopy[i] = Red[i];
        WhiteCopy[i] = White[i];
    }
}
/*
* ���������: ��� ��������� ���� pos, ���������� ������� � ��������� ���, 
* ���������� ������ ���� ��������
* ����������: ��������� � ������� �������
*/
pos* min(pos* a1, pos* a2)
{
    if (a1 == nullptr) {
        return a2;
    }
    if (a2 == nullptr) {
        return a1;
    }
    if (a1->mark == a2->mark) {
        return a1;
    }
    return a1->mark < a2->mark ? a1 : a2;
}
/*
* ���������: ��� ��������� ���� pos, ���������� ������� � ��������� ���,
* ���������� ������ ���� ��������
* ����������: ��������� � ������� �������
*/
pos* max(pos* a1, pos* a2)
{
    if (a1 == nullptr) {
        return a2;
    }
    if (a2 == nullptr) {
        return a1;
    }
    if (a1->mark == a2->mark) {
        return a1;
    }
    return a1->mark > a2->mark ? a1 : a2;
}

/*
* ���������:
* ���������� �������� ���������
* ����������:
*/
int alphabeta(pos* cur, pos* back, bool turn) {
    if (turn == true) {		// ��� ��������
        cur = min(cur, back);
        return cur->mark;
    }
    else if (turn == false) { // ��� ����������
        cur = max(cur, back);
        return cur->mark;
    }
}
/*
* ���������: Red - ������ ����� �������� �����, White - ������ ����� ������ �����, alpha - ������ ����� �������, beta - ������� ���� �������, humanTurn - ��� �� ������ ��������, depth - ������� ������
* ������� ��������� ������������� ��� ��������� ���� ������� �� �������� ���� � �� ������� depth, �.�. �� depth ����� �����, ���� ����� ��� ������
* ����������: ��������� � ����������� ��� �����
*/
pos* minmax(const Cheacker* Red, const Cheacker* White, int alpha=-9999, int beta=9999, bool humanTurn=false, int depth = 0) {
    pos* back = new pos;
    pos* cur = nullptr;
    if (depth == 5) {
        cur = new pos;
        cur->mark = eqalFunction(Red, White);
    }
    else {
        Cheacker* RedCopy = new Cheacker[12];
        Cheacker* WhiteCopy = new Cheacker[12];
        Copy(Red, RedCopy, White, WhiteCopy);
        for (int i{0}; i < 12; i++) {
            if (humanTurn == true && RedCopy[i].isAlive == true) {
                for (int j{1}; j <=2; j++){
                    if (canMove(back->CheackerToPos(RedCopy + i, RedCopy[i].x - j, RedCopy[i].y - j), RedCopy, WhiteCopy))
                    {
                        MoveChecker(RedCopy[i].x - j, RedCopy[i].y - j, RedCopy + i, RedCopy, WhiteCopy);
                        //Move(back->CheackerToPos(RedCopy + i, RedCopy[i].x - j, RedCopy[i].y - j), RedCopy, WhiteCopy);
                        back = minmax(RedCopy, WhiteCopy, alpha, beta, !humanTurn, depth + 1);
                        cur = min(cur, back);
                        beta = alphabeta(cur, back, humanTurn);
                        if (alpha >= beta) { break; }
                        Copy(Red, RedCopy, White, WhiteCopy);
                    }
                    if (canMove(back->CheackerToPos(RedCopy + i, RedCopy[i].x + j, RedCopy[i].y - j), RedCopy, WhiteCopy)) {
                        MoveChecker(RedCopy[i].x + j, RedCopy[i].y - j, RedCopy + i, RedCopy, WhiteCopy);
                        //Move(back->CheackerToPos(RedCopy + i, RedCopy[i].x - j, RedCopy[i].y + j), RedCopy, WhiteCopy);
                        back = minmax(RedCopy, WhiteCopy, alpha, beta, !humanTurn, depth + 1);
                        cur = min(cur, back);
                        beta = alphabeta(cur, back, humanTurn);
                        if (alpha >= beta) { break; }
                        Copy(Red, RedCopy, White, WhiteCopy);
                    }
                }
            }
            else if (humanTurn == false && WhiteCopy[i].isAlive == true) {
                for (int j{ 1 }; j <= 2; j++) {
                    if (canMove(back->CheackerToPos(WhiteCopy + i, WhiteCopy[i].x - j, WhiteCopy[i].y + j), RedCopy, WhiteCopy)) {
                        MoveChecker(WhiteCopy[i].x - j, WhiteCopy[i].y + j, WhiteCopy + i, RedCopy, WhiteCopy);
                        //Move(back->CheackerToPos(WhiteCopy + i, WhiteCopy[i].x + j, WhiteCopy[i].y - j), RedCopy, WhiteCopy);
                        back = minmax(RedCopy, WhiteCopy, alpha, beta, !humanTurn, depth + 1);
                        cur = max(cur, back);
                        alpha = alphabeta(cur, back, humanTurn);
                        if (alpha >= beta) { break; }
                        Copy(Red, RedCopy, White, WhiteCopy);
                    }
                    if (canMove(back->CheackerToPos(WhiteCopy + i, WhiteCopy[i].x + j, WhiteCopy[i].y + j), RedCopy, WhiteCopy)) {
                        MoveChecker(WhiteCopy[i].x + j, WhiteCopy[i].y + j, WhiteCopy + i, RedCopy, WhiteCopy);
                        //Move(back->CheackerToPos(WhiteCopy + i, WhiteCopy[i].x + j, WhiteCopy[i].y + j), RedCopy, WhiteCopy);
                        back = minmax(RedCopy, WhiteCopy, alpha, beta, !humanTurn, depth + 1);
                        cur = max(cur, back);
                        alpha = alphabeta(cur, back, humanTurn);
                        if (alpha >= beta) { break; }
                        Copy(Red, RedCopy, White, WhiteCopy);
                    }
                }
            }
        }
    }
    return cur;
}

//void printField(int** field, int size) { // �������
//    for (int i{}; i < size; i++) {
//        for (int j{}; j < size; j++) {
//            std::cout << field[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}

int main()
{
  /* sf::ContextSettings settings;
   settings.antialiasingLevel = 16.0;*/
   //std::vector<std::vector<int>[8]> field[8];
   sf::RenderWindow window(sf::VideoMode(800, 800), "Poddavki"/*, sf::Style::Default, settings*/);
   sf::Event event;
   Board board;
   int field[8][8];
   Cheacker RedCheacker[12];
   Cheacker WhiteCheacker[12];
   bool selected = false;
   Cheacker* SelectedPiece = NULL;
   int turn = 1;

   for (int i = 0; i < 12; i++) {
      WhiteCheacker[i].color = sf::Color::White;
      RedCheacker[i].color = sf::Color::Red;
   }


   Setup(window, RedCheacker, WhiteCheacker);

   while (window.isOpen()) {
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
            window.close();
         }

         if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
               selected = !selected;
            }
         }
         /*
         * ���������� ���������� � ���������� �����
         */
         if (event.type == sf::Event::KeyPressed) {
             if (event.key.code == sf::Keyboard::F2) {
                 std::cout << "RedCheackers:" << ":" << std::endl;
                 for (size_t i{}; i < 12; i++) {
                     std::cout << i << " = (" << RedCheacker[i].x+1 << ":" << RedCheacker[i].y+1 << "), isAlive:" << RedCheacker[i].isAlive<< std::endl;
                 }
                 std::cout << "WhiteCheackers:" << ":" << std::endl;
                 for (size_t i{}; i < 12; i++) {
                     std::cout << i << " = (" << WhiteCheacker[i].x+1 << ":" << WhiteCheacker[i].y+1 << "), isAlive:" << WhiteCheacker[i].isAlive << std::endl;
                 }
            }
         }
      }

      window.clear();

      board.Draw(window);

      if (SelectedPiece != NULL) {
         board.Highlight(window, SelectedPiece->x, SelectedPiece->y);
      }

      for (int i = 0; i < 12; i++) {
         WhiteCheacker[i].Draw(window);
         RedCheacker[i].Draw(window);
      }

      if (selected) {
         // printField(field, 8);
         std::cout << eqalFunction(RedCheacker, WhiteCheacker) << std::endl;
         int x = sf::Mouse::getPosition(window).x / 100;
         int y = sf::Mouse::getPosition(window).y / 100;
         if (FindChecker(x, y, RedCheacker, WhiteCheacker) && (FindChecker(x, y, RedCheacker, WhiteCheacker)->color == sf::Color::Red && turn == 1 || FindChecker(x, y, RedCheacker, WhiteCheacker)->color == sf::Color::White && turn == 2)) {
            if (FindChecker(x, y, RedCheacker, WhiteCheacker) == SelectedPiece) {
               SelectedPiece = NULL;
            }
            else {
               SelectedPiece = FindChecker(x, y, RedCheacker, WhiteCheacker);
            }

            selected = false;
         }
         else if (SelectedPiece != NULL && MoveChecker(x, y, SelectedPiece, RedCheacker, WhiteCheacker, &turn)) {
             if (turn == 2) { 
                 pos* temp = minmax(RedCheacker, WhiteCheacker); //������ �� �������, �� �� ����� ����� ���, ��� ��� ����.
                 std::cout <<"Current:("<< temp->current_x+1 <<":" << temp->current_y+1 <<")" <<"Next:(" << temp->next_x+1 <<":" << temp->next_y+1 <<")" << std::endl;
             }
            selected = false;
            SelectedPiece = NULL;
         }
         selected = false;
      }
      for (int i = 0; i < 12; i++) {
         if (RedCheacker[i].y == 0) {
            RedCheacker[i].queen = true;
         }
         if (WhiteCheacker[i].y == 7) {
            WhiteCheacker[i].queen = true;
         }
      }


      window.display();
   }
   return 0;
}