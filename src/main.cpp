#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "mainmenu.hpp"
#include "settings.hpp"
#include "rules.hpp"
#include "gamewindow.hpp"
#include "leaderboard.hpp"

using namespace sf;

bool debug = false;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    if (argc > 1) // включить дебаг режим
        if (strcmp(argv[1], "-d") == 0)
            debug = true;

    RenderWindow window(VideoMode(600, 600), "Hello, world!", Style::Close);
    window.setFramerateLimit(30);

    Mainmenu* mainmenu;
    Settings* settingsmenu;
    Rules* rulesmenu;
    Gamewindow* game;
    Leaderboard* leaderboard;
    int currentGameDifficulty = 2;
    int currentGameImage = 1;

    int programCode = 0;
    // меньше нуля: завершить программу
    // 0: главное меню
    // 1: начать игру
    // 2: настройки
    // 3: правила игры
    // 4: таблица лидеров

    while (programCode >= 0)
    {
        switch (programCode)
        {
        case 0:
            mainmenu = new Mainmenu;
            programCode = mainmenu->draw(window);
            delete mainmenu;
            mainmenu = NULL;
            break;
        case 1:
            game = new Gamewindow(currentGameDifficulty, currentGameImage);
            programCode = game->draw(window);
            delete game;
            game = NULL;
            break;
        case 2:
            settingsmenu = new Settings;
            programCode = settingsmenu->draw(window);
            currentGameDifficulty = settingsmenu->getGameDiffuculty();
            currentGameImage = settingsmenu->getGameImage();
            delete settingsmenu;
            settingsmenu = NULL;
            break;
        case 3:
            rulesmenu = new Rules;
            programCode = rulesmenu->draw(window);
            delete rulesmenu;
            rulesmenu = NULL;
            break;
        case 4:
            leaderboard = new Leaderboard;
            programCode = leaderboard->draw(window);
            delete leaderboard;
            leaderboard = NULL;
            break;
        default:
            programCode = -1;
            break;
        }
    }

    if (window.isOpen()) // лишняя проверка
    {
        window.close();
    }

    return 0;
}
