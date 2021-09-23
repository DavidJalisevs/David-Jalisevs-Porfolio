#include <iostream>
#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int plumberHit; // global number for temperera hit
int rabbitHit; // global number for temperera hit
int weaponType; // weapon type

class GameCharacters{
public:
    virtual void attack() { std::cout << "Attack" << std::endl; } // empty attack 
    virtual void shield() { std::cout << "Sheild" << std::endl; } // empty shield
    virtual void miss() { std::cout << "Miss" << std::endl; }
    virtual void health() = 0;
};

class Plumber :public GameCharacters {
public:
    virtual void attack() { std::cout << "You attacked rabbit" << std::endl; }
    virtual void health() { std::cout << "Plumber health :" << m_health << std::endl;}
    virtual void points() { std::cout << "You have: " << m_totalPoints << " Points."<< std::endl; }
    void decreaseHealth(int& t_health) {
        t_health = t_health - rabbitHit;
        m_health = t_health;
    }

    void setHealth(int& t_health) {
        m_health = t_health;
    }
    void increasePoints(int t_points) {
  
        m_totalPoints = m_totalPoints + t_points;
    }
    void decreasePoints(int t_points) {
        m_totalPoints = m_totalPoints - t_points;
    }
    int m_health = 100;
    int m_points = 0;
    int m_totalPoints =40;
   
};

class Rabbit :public GameCharacters {
public:
    virtual void health() { std::cout << "Rabbit health :" << m_health << std::endl;}
    virtual void attack() { std::cout << "Rabbit attacked you" << std::endl; } // empty attack 
    virtual void shield() { std::cout << "Rabbit used shield and blocked your attack" << std::endl; } // empty shield
    virtual void miss() { std::cout << "Rabbit have missed" << std::endl; }

    void decreaseHealth(int& t_health) {
        t_health = t_health - plumberHit;
        m_health = t_health;
     }
    void increaseHealth(int& t_health) {
        t_health = t_health + t_health;
        m_health = t_health;
    }
    int  m_health = 100;

};


void welcome(Plumber* t_plumberOne, Rabbit* t_rabbitOne);//, int& t_points);
void hideout(Plumber* t_plumberOne, Rabbit* t_rabbitOne);//, int& t_points);
void battle(Plumber* t_plumberOne, Rabbit* t_rabbitOne);//, int& t_points);

int main(void) 
{
    srand(time(NULL));
    Plumber* plumberOne = new Plumber;
    Rabbit* rabbitOne = new Rabbit;
    welcome(plumberOne, rabbitOne);//, plumberOne->m_points);
    


    std::cin.get();

    return 0;

}

void welcome(Plumber* t_plumberOne, Rabbit* t_rabbitOne)//, int &t_points)
{
    system("CLS");
    int temp;
    std::cout << "==================================================================================================== " << std::endl;
    std::cout << "\t-Plumbers vs Rabbits" << std::endl;
    std::cout << "\t-In this game you will play as a plumber defending his castle from Rabbits" << std::endl;
    std::cout << "\t-Please press 1 to start or 0 to exit " << std::endl;
    std::cin >> temp;
    while (temp != 1 && temp!= 0)
    {
        std::cout << "\t-Please press 1 to start or 0 to exit " << std::endl;
        std::cin >> temp;
    }
    if (temp == 0)
    {
        return;
    }
    if (temp == 1)
    {
        hideout(t_plumberOne, t_rabbitOne);//, t_points);
    }
}
void hideout(Plumber* t_plumberOne, Rabbit* t_rabbitOne)//, int &t_points)
{
    system("CLS");
    int temp;

    std::cout << "==================================================================================================== " << std::endl;
    std::cout << "\t-This is your hideout" << std::endl;
    std::cout << "\t-Here you decide if you want to go to the battle or shop" << std::endl;
    std::cout << "\t-Please press 1 for the battle " << std::endl;
    std::cin >> temp;
    while (temp != 1 && temp != 2)
    {
        std::cout << "\t-Please press 1 for the battle " << std::endl;
        std::cin >> temp;
    }
    if (temp == 1)
    {
        battle(t_plumberOne, t_rabbitOne);//, t_points);
    }
}

void battle(Plumber* t_plumberOne, Rabbit* t_rabbitOne)//, int &t_points)
{
    int temp;
    int random;
    bool rabbitShield = false;
    bool plumberAttacked = false;
    system("CLS");
    std::cout << "==================================================================================================== " << std::endl;
    std::cout << "\t-Battle has begun" << std::endl;
    std::cout << "==================================================================================================== " << std::endl;
    std::cout << "\t-Player" << std::endl;
    std::cout << "\t-";
    t_plumberOne->health();
    std::cout << "==================================================================================================== " << std::endl;
    std::cout << "\t-Rabbit" << std::endl;
    std::cout << "\t-";
    t_rabbitOne->health();

    while (t_rabbitOne->m_health >= 0 && t_plumberOne->m_health >= 0)
    {
        std::cout << "==================================================================================================== " << std::endl;
        std::cout << "\t-Press 1 to attack or Press 0 to Defend" << std::endl;
        std::cin >> temp;
        system("CLS");

        // if player decided to attack
        random = rand() % 10 + 1; // random for rabbit 

        if (temp == 1)
        {
            std::cout << "\t-Player" << std::endl;
            std::cout << "\t-";
            t_plumberOne->health();
            std::cout << "==================================================================================================== " << std::endl;
            std::cout << "\t-Rabbit" << std::endl;
            std::cout << "\t-";
            t_rabbitOne->health();
            std::cout << "==================================================================================================== " << std::endl;
            std::cout << "\t-";
            t_plumberOne->points();
            std::cout << "==============================================" << std::endl;
            std::cout << "\t-Please select your weapon" << std::endl;
            std::cout << "\t-1)Throw pipes - 10 hp | cost: free" << std::endl;
            std::cout << "\t-2)Head kick - 15 hp | cost: 5 Points" << std::endl;
            std::cout << "\t-3)AK-47 - 20hp | cost: 10 points " << std::endl;
            std::cout << "\t-4)Lightsaber - 28 hp | cost:  15 points" << std::endl;
            std::cout << "\t-5)Gravity gun - 36 hp | cost: 25 points" << std::endl;
            std::cout << "\t-6)Hidden Blade - 50 hp | cost: 40 points" << std::endl;
            std::cout << "\t-7)BFG-9000 - 60 hp | cost: 50 points " << std::endl;
            std::cout << "\t-8)R.Y.N.O - 74 hp | cost: 80 points " << std::endl;
            std::cin >> weaponType;

            switch (weaponType)
            {
            case 1:  // throw pipes
                plumberHit = 10;
                std::cout << " " << std::endl;
                t_plumberOne->attack();
                plumberAttacked = true;
                break;
            case 2: // head kick
                if (t_plumberOne->m_totalPoints >= 5)
                {
                    t_plumberOne->decreasePoints(5);
                    plumberHit = 15;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 3: // ak47
                if (t_plumberOne->m_totalPoints >= 10)
                {
                    t_plumberOne->decreasePoints(10);
                    plumberHit = 20;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 4: // lightsaber
                if (t_plumberOne->m_totalPoints >= 15)
                {
                    t_plumberOne->decreasePoints(15);
                    plumberHit = 28;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 5: // gravity gun
                if (t_plumberOne->m_totalPoints >= 25)
                {
                    t_plumberOne->decreasePoints(25);
                    plumberHit = 36;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 6: // hidden blade
                if (t_plumberOne->m_totalPoints >= 40)
                {
                    t_plumberOne->decreasePoints(40);
                    plumberHit = 50;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 7: // BFG
                if (t_plumberOne->m_totalPoints >= 50)
                {
                    t_plumberOne->decreasePoints(50);
                    plumberHit = 60;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            case 8: // RYNO
                if (t_plumberOne->m_totalPoints >= 80)
                {
                    t_plumberOne->decreasePoints(80);
                    plumberHit = 74;
                    std::cout << " " << std::endl;
                    t_plumberOne->attack();
                    plumberAttacked = true;
                }
                else
                {
                    system("CLS");
                    std::cout << "\t-Not enough of points" << std::endl;
                    plumberAttacked = false;
                }
                break;
            }
            // Rabbit attack controlled by randomness oh yes


            if (random >= 0 && random <= 3 && plumberAttacked == true)
            {
                rabbitHit = rand() % 60 + 10;
                t_rabbitOne->attack();
                t_plumberOne->decreaseHealth(t_plumberOne->m_health);
            }

            else if (random >= 4 && random <= 7 && plumberAttacked == true)
            {
                t_rabbitOne->miss();
            }

            else if (random >= 8 && random <= 10 && plumberAttacked == true)
            {
                rabbitShield = true;
                t_rabbitOne->shield();
            }
            if (rabbitShield == true && plumberAttacked == true) // bool as a control
            {
                plumberHit = 0;
                rabbitShield = false;
                std::cout << "\t-Rabbit blocked your attack" << std::endl;
            }
            if (plumberAttacked)
            {
                t_rabbitOne->decreaseHealth(t_rabbitOne->m_health);
            }
        }

        if (temp == 0)
        {
            if (random >= 0 && random <= 3)
            {
                rabbitHit =0;
                t_rabbitOne->attack();
                t_plumberOne->decreaseHealth(t_plumberOne->m_health);
            }

            else if (random >= 4 && random <= 7 )
            {
                t_rabbitOne->miss();
            }

            else if (random >= 8 && random <= 10 )
            {
                rabbitShield = true;
                t_rabbitOne->shield();
            }
            if (rabbitShield == true )
            {
                plumberHit = 0;
                rabbitShield = false;
                std::cout << "\t-Rabbit blocked your attack" << std::endl;
            }
            t_plumberOne->shield();
            std::cout << "\t-You blocked rabbits attack" << std::endl;
        }

        std::cout << "==================================================================================================== " << std::endl;
        std::cout << "\t-Player" << std::endl;
        std::cout << "\t-";
        t_plumberOne->health();
        std::cout << "==================================================================================================== " << std::endl;
        std::cout << "\t-Rabbit" << std::endl;
        std::cout << "\t-";
        t_rabbitOne->health();
    }

    if (t_rabbitOne->m_health <= 0)
    {
        system("CLS");
        std::cout << "You have defeated the Rabbit" << std::endl;
        std::cout << "points were added" << std::endl;
        t_plumberOne->increasePoints(100);
        t_plumberOne->points();
        std::cout << "\t-Want to kill another rabbit?(will be harder)" << std::endl;
        std::cout << "\t-Pess 1 to try again, Press 0 to exit" << std::endl;
        std::cin >> temp;

        if (temp == 0)
        {
            return;
        }
        if (temp == 1)
        {
            t_rabbitOne->m_health = 100;
            t_rabbitOne->m_health = 150;
            t_rabbitOne->increaseHealth(t_rabbitOne->m_health);
            t_plumberOne->setHealth(t_plumberOne->m_health);
            welcome(t_plumberOne, t_rabbitOne);//, int& t_points);
        }

    }

    if (t_plumberOne->m_health <= 0)
    {
        system("CLS");
        std::cout << "==================================================================================================== " << std::endl;
        std::cout << "\t-You LOST" << std::endl;
        std::cout << "\t-Want to try again ?" << std::endl;
        std::cout << "\t-Pess 1 to try again, Press 0 to exit" << std::endl;
        std::cin >> temp;

        if (temp == 0)
        {
            return;
        }
        if (temp == 1)
        {
            welcome(t_plumberOne,t_rabbitOne);//, int& t_points);
        }
        
    }
}