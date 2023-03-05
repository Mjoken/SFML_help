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
* Принимает: положение шашки, в целочисленных координатах x, y
* Ищет эту шашку на поле
* Выдаёт: если она есть, возвращает ссылку на неё, если нет, ноль
* p.s. для упрощения логики нужно добавить сюда проверку на то, находится ли шашка в рамках поля
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
* Принимает: положение шашки, в целочисленных координатах x, y
* Ищет эту шашку на поле
* Выдаёт: если она есть, возвращает true, если нет, false
* p.s. для упрощения логики нужно добавить сюда проверку на то, находится ли шашка в рамках поля
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

/*--------------------Убийство, матюки и голые сиськи---------------------------*/
/*
* Принимает: положение шашки, в целочисленных координатах x, y
* Убивает её нахуй
* Возврашает: светлую память (void)
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
* Прегрузка без ебучей смены хода
* Принимает: положение шашки, в целочисленных координатах x, y
* Убивает её нахуй
* Возврашает: светлую память (void)
*/
void KillCheacker(int x, int y, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    FindChecker(x, y, RedChecker, WhiteChecker)->isAlive = false;
    return;
}
/*
* Прегрузка без ебучей смены хода
* Принимает: положение шашки, в целочисленных координатах x, y
* Убивает её нахуй
* Возврашает: светлую память (void)
*/
void KillCheacker(Cheacker* toKill) {
    toKill->isAlive = false;
    return;
}
/*
* Принимает: структуру с положением шашки и её хода
* Ищет шашку между текушем и предыдушем ходом
* возвращает: Указатель на неё
*/
Cheacker* FindMidleCheaker(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    int midX{ abs(posCur->current_x - posCur->next_x) }, midY{ abs(posCur->current_y - posCur->next_y) };
    if (midX > 1 && midY > 1 && boolFindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker) &&
        FindChecker(posCur->current_x, posCur->current_y, RedChecker, WhiteChecker)->color != FindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker)->color) {
        return(FindChecker(midX / 2, midY / 2, RedChecker, WhiteChecker));
    }
    return nullptr;
}
// Возникает вопрос, зачем нужно было выводить eqalFunction, кроме как для отладки, а если их удалить... зачем эта функция?
/*--------------------конец блока---------------------------*/

/*
* Принимает: структуру с положением шашки и её хода, размер поля, стандартно 8
* Находиться ли шашка и её ход в рамках поля
* Выдаёт: переменную логического типа, которая показывает, находиться ли позиция и последующий ход в рамках поля
*/
bool inField(pos* posCur, int sizeField=8) {
    return (posCur->current_x < sizeField && posCur->current_x >= 0 && posCur->current_y < sizeField && posCur->current_y >= 0
        && posCur->next_x < sizeField && posCur->next_x >= 0 && posCur->next_y < sizeField && posCur->next_y >= 0
        );
}
/*
* Принимает: структуру с положением шашки и её хода
* Свободна ли клетка в которую мы хотим сделать ход
* Выдаёт: переменную логического типа, свободно или нет
*/
bool isFreeNextPos(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker, int sizeField = 8) {
    return boolFindChecker(posCur->next_x, posCur->next_y, RedChecker, WhiteChecker);
}
/*
* Принимает: структуру с положением шашки и её хода, струкутры с перечеслением шашек на поле и их атрибутов
* Проверяет, доступен ли ход, который совершает пользователь
* Выдаёт: можем ли сделать ход
*/
bool canMove(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    if (inField(posCur)&& isFreeNextPos(posCur, RedChecker, WhiteChecker) || FindMidleCheaker(posCur, RedChecker, WhiteChecker)!=nullptr) {
        return true;
    }
     return false;
}
/*
* Принимает: структуру с положением шашки и её хода, струкутры с перечеслением шашек на поле и их атрибутов
* Делает ход
* Выдаёт: -
*/
void Move(pos* posCur, Cheacker* RedChecker, Cheacker* WhiteChecker) {
    Cheacker* cur;
    Cheacker* mid;
    mid = FindMidleCheaker(posCur, RedChecker, WhiteChecker);
    cur = FindChecker(posCur->current_x, posCur->current_y, RedChecker, WhiteChecker); // делаем текущую шашку
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
* Принимает: Red - массив шашек красного цвета, White - массив шашек белого цвета, alpha - нижняя альфа граница, beta - верхняя бета граница, humanTurn - ход ли сейчас человека, depth - глубина дерева
* Функция минимакса рассматривает все возможные ходы начиная от текущего поля и до глубины depth, т.е. на depth ходов вперёд, ищёт среди них лучший
* Возвращает: структуру с оптимальным для ходом
*/
pos* minmax(const Cheacker* Red, const Cheacker* White, int alpha, int beta, bool humanTurn, int depth = 0) {
    pos* back=nullptr;
    pos* cur=nullptr;
    if (depth == 3) {
        cur = new pos();
        cur->mark = eqalFunction(Red, White);
    }
    else {
        Cheacker* RedCopy = new Cheacker[12];
        Cheacker* WhiteCopy = new Cheacker[12];
        for (int i{}; i < 12; i++) {
            RedCopy[i] = Red[i];
            WhiteCopy[i] = White[i];
        }
        for (int i{}; i < 12; i++) {
            if (humanTurn == true && RedCopy[i].isAlive == true) {

            }
            else if (humanTurn == false && WhiteCopy[i].isAlive == true) {
                
            }
        }
    }
    return cur;
}

//void printField(int** field, int size) { // Отладка
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