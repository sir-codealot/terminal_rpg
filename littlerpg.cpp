#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Enemy
{
public:
	string NAME;
	int HP;		// live points
	int HP_MAX;	// max life points
	int EXP;	// dropped expirience
	int ATP;	// attack strength
	int DEF;	// defense value
	int EVD;	// evade value




	Enemy(string new_NAME,int new_HP, int new_EXP,int new_ATP,int new_DEF,int new_IVD)
	{
		NAME   = new_NAME;
		HP     = new_HP;
		HP_MAX = HP;
		EXP    = new_EXP;
		ATP    = new_ATP;
		DEF    = new_DEF;
		EVD    = new_IVD;
	}
};

class Player
{
	public:
	string NAME;
	string INVENTORY[10];
	int HP_MAX;
	int HP;
	int EXP;
	int ATP;
	int DEF;
	int EVD;
	int LVL;
	int NEXTLVL;

	Player() {
		string defaultINV[10] = {	"Sword",
									"Mana potion",
									"Healing potion",
									"empty",
									"empty",
									"empty",
									"empty",
									"empty",
									"empty",
									"empty"
								};
		NAME = "Player1";
		
		for(int i=0;i<=9;i++) {
			INVENTORY[i]=defaultINV[i];
		}

		HP      = HP_MAX = 30;
		EXP     = 0;
		ATP     = 10;
		DEF     = 7;
		EVD     = 5;
		LVL     = 1;
		NEXTLVL = 100;
	}
};

char mDesc;
int hpPotion=3;
int mNumber=0;
int len = 0;

string loot[] = {	"heal",
					"nothing",
					"nothing",
				};

string mEnemy[] = {	"Dragon",
					"Black Knight",
					"Witch",
					"Goblin",
					"Troll",
					"Wolf",
					"Ghost"
				};

Player mPlayer;

void splashscreen();
void showInventory();
void showStats();
void enemyAttack(int number);
void use_healing_potion();
void check_exp();
void get_loot(Enemy En);
char input();
string string_input();
int fight(Enemy ENEMY);
bool PlayerBox();


int main()
{	
	//int k=0;
	splashscreen();

	while (true) {
		if(PlayerBox()==false)
			break;

		if(mPlayer.HP<=0)
		{
			cout << endl << "   ------   Game Over!   ------" << endl << endl;
			return 0;
		}
	}

	return 0;
}


void splashscreen() {
	cout << "\033[2J\033[1;1H"; // Diese Zeile lehrt das Terminal-Fenster!

	cout << endl 
			<< endl 
			<< "     +-------------------------+" << endl
			<< "     |     Little RPG Game     |" << endl
			<< "     +-------------------------+" << endl << endl;

	cout << "Current player name: " << mPlayer.NAME << endl
			<< "Change? (y/n) ";
	mDesc = input();

	if (mDesc == 'y' || mDesc == 'Y')
	{
		cout << endl << "New name: ";
		mPlayer.NAME = string_input();
		
		cout << endl << "You are now called " << mPlayer.NAME << "!" << endl;
	} else if (mDesc == 'n' || mDesc == 'N') {
		cout << endl << "Your name is still " << mPlayer.NAME << "!" << endl;
	} else {
		cout << endl << "Wrong input! Your name is still " << mPlayer.NAME << "!" << endl;
	}
	fflush(stdin);
	system("sleep 1.5");
}

void showInventory() {
	cout << "\033[2J\033[1;1H"; // clear terminal window!
	
	cout << endl 
			<< "   " << mPlayer.NAME << "'s Inventory" << endl
			<< "   ";
	for (int i=0; i < mPlayer.NAME.length(); i++) {
		cout << "-";
	}
	cout << "------------" << endl;

	for(int i=0 ; i < 10 ; i++)
	{
		if (mPlayer.INVENTORY[i] == "Healing potion") {
			cout << "- " << mPlayer.INVENTORY[i] << " ( " << hpPotion << "x )" << endl;
		}
		else {
			cout << "- " << mPlayer.INVENTORY[i] << endl;
		}
	}
	cout << endl << endl;
	system("read -p \"ENTER to proceed...\" dummy");
}

void showStats() {
	cout << "\033[2J\033[1;1H"; // clear terminal window!
	
	cout << endl 
			<< "   " << mPlayer.NAME << "'s status values" << endl
			<< "   ";
			for (int i=0; i < mPlayer.NAME.length(); i++) {
				cout << "-";
			}
			cout << "----------------" << endl << endl;

	cout << "   Health        : " << mPlayer.HP << " / " << mPlayer.HP_MAX << endl <<
			"   Attack points : " << mPlayer.ATP << endl <<
			"   Defense points: " << mPlayer.DEF << endl <<
			"   Evade points  : " << mPlayer.EVD << endl <<
			"   Expirience    : " << mPlayer.EXP << endl <<
			"   Next Level at : " << mPlayer.NEXTLVL << " Exp" << endl << endl;

	system("read -p \"ENTER to proceed...\" dummy");
}

bool PlayerBox() {
	cout << "\033[2J\033[1;1H"; // clear terminal window!
	cout << "+--------------------------------+" << endl <<
			"    Name            : " << mPlayer.NAME << endl <<
			"    Level           : " << mPlayer.LVL << endl <<
			"    Expirience      : " << mPlayer.EXP << endl <<
			"    Next Level at   : " << mPlayer.NEXTLVL << endl << 
			"    Health points   : " << mPlayer.HP << " / " << mPlayer.HP_MAX << endl << 
			"    Healing potions : " << hpPotion << endl <<
			"+--------------------------------+" << endl << endl;

	cout << "Commands:    (W)alk on   (H)ealing potion   (I)nventory   (S)tats   (Q)uit" << endl << endl << "Choice: ";
	mDesc = input();

	switch (mDesc)
	{	
		case 'W':
		case 'w':	len = ((sizeof(mEnemy)/sizeof(*mEnemy))-1);
					srand((unsigned) time(0));
					mNumber=rand() % len;

					enemyAttack(mNumber);
					break;
		
		case 'H':
		case 'h':	if (hpPotion>0)
					{
						hpPotion-=1;
						mPlayer.HP+=15;

						if (mPlayer.HP > mPlayer.HP_MAX)
							mPlayer.HP=mPlayer.HP_MAX;
					} else {
						cout << endl << "You are out of healing potions! go on? (y/n) ";
						mDesc = input();

						if (mDesc == 'n' || mDesc == 'N')
							return false;
					}
					cout << endl << "You're using a healing potion! New HP: " << mPlayer.HP << " / " << mPlayer.HP_MAX << endl << endl;
					system("sleep 1.5");
					PlayerBox();
					break;

		case 'I':
		case 'i':	showInventory();
					break;
		case 'S':
		case 's':	showStats();
					break;
		case 'Q':
		case 'q':	return false;

		default:	PlayerBox();
	}
	
	return true;
}

void enemyAttack(int number) {
	Enemy En(mEnemy[0], 20, 20, 15, 10, 5); // Dragon

	switch(number)
	{
		case 2:		En.NAME=mEnemy[1]; // Black Knight
					En.HP=15;
					En.ATP=12;
					En.EXP=10;
					En.DEF=10;
					En.EVD=7;
					break;
		case 3:		En.NAME=mEnemy[2]; // Witch
					En.HP=10;
					En.ATP=10;
					En.EXP=12;
					En.DEF=6;
					En.EVD=10;
					break;
		case 4:		En.NAME=mEnemy[3]; // Goblin
					En.HP=8;
					En.ATP=8;
					En.EXP=5;
					En.DEF=14;
					En.EVD=10;
					break;
		case 5:		En.NAME=mEnemy[4]; // Troll
					En.HP=20;
					En.ATP=18;
					En.EXP=5;
					En.DEF=15;
					En.EVD=5;
					break;
		case 6:		En.NAME=mEnemy[5]; // Wolf
					En.HP=7;
					En.ATP=8;
					En.EXP=6;
					En.DEF=8;
					En.EVD=12;
					break;
		case 7:		En.NAME=mEnemy[6]; // Ghost
					En.HP=10;
					En.ATP=8;
					En.EXP=14;
					En.DEF=15;
					En.EVD=8;
					break;
		default:	break;
	}

	cout << endl << "You are attacked by a " << En.NAME << " (" << En.HP << " HP) ! What will you do? (a)ttack / (f)lee" << endl << "Your choice: ";

	mDesc = input();

	switch (mDesc) {
		case 'a':	mPlayer.EXP+=fight(En);
					if (mPlayer.HP>0) {
						check_exp();
						get_loot(En);
					}
					break;

		case 'f':	cout << endl << "you fleed!" << endl;
					system("sleep 1.5");
					break;

		default:	enemyAttack(number);
	}
}

int fight(Enemy ENEMY) {
	while (mPlayer.HP > 0) {
		ENEMY.HP -= mPlayer.ATP;
		cout << "You attack and cause " << mPlayer.ATP << " points damage!" << endl;
		system("sleep 1");

		if (ENEMY.HP <= 0) {
			cout << "You're defeating the " << ENEMY.NAME << "! -> +" << ENEMY.EXP << " Exp" << endl;
			system("sleep 1.5");
			return ENEMY.EXP;
		}

		mPlayer.HP -= ENEMY.ATP;
		cout << "  " << ENEMY.NAME << " causes " << ENEMY.ATP << " points damage!" << endl;
		system("sleep 1");

		if (mPlayer.HP<=0) {
			cout << "You are defeated by a " << ENEMY.NAME << endl;
			return mPlayer.HP=0;
		}

		cout << endl
				<< ENEMY.NAME << "'s HP: " << ENEMY.HP << "/" << ENEMY.HP_MAX << endl
				<< mPlayer.NAME << "'s HP: " << mPlayer.HP << "/" << mPlayer.HP_MAX << endl
				<< endl;

		mDesc = ' ';
		while (mDesc != 'A' && mDesc != 'a') {
			cout << "What would you do? (A)ttack    (H)eal    (F)lee" << endl
					<< "Choice: ";

			mDesc = input();

			switch(mDesc) {
				case 'A':
				case 'a':	break;

				case 'H':
				case 'h':	use_healing_potion();
							system("sleep 1.5");
							break;
				case 'F':
				case 'f':	cout << "You fleed..." << endl;
							return 0;
			}
		}
	}
	return 0;
}

// using healing potion function
void use_healing_potion() {
	if (hpPotion > 0) {
		hpPotion--;
		mPlayer.HP += 10;
		if (mPlayer.HP > mPlayer.HP_MAX)
			mPlayer.HP = mPlayer.HP_MAX;

		for(int i=0 ; i < 10 ; i++) {
			if (mPlayer.INVENTORY[i] == "Healing potion" && hpPotion == 0)
				mPlayer.INVENTORY[i] = "empty";
		}
		cout << "You use a potion, HP restored ( " << mPlayer.HP << "/" << mPlayer.HP_MAX << ")" << endl;
	}
	else {
		cout << "You ran out of potions..." << endl;
		system("sleep 1.5"); 
	}
}

void check_exp() {
	if (mPlayer.EXP >= mPlayer.NEXTLVL) {
		int oldHP  = mPlayer.HP_MAX;
		int oldATP = mPlayer.ATP;
		int oldDEF = mPlayer.DEF;
		int oldEVD = mPlayer.EVD;

		mPlayer.NEXTLVL += mPlayer.NEXTLVL * 1.15 + 25;
		mPlayer.HP_MAX   = mPlayer.HP_MAX * 1.1;
		mPlayer.HP       = mPlayer.HP_MAX;
		mPlayer.ATP      = mPlayer.ATP * 1.1;
		mPlayer.DEF      = mPlayer.DEF * 1.2;
		mPlayer.EVD      = mPlayer.EVD * 1.3;
		mPlayer.LVL++;
		

		cout << endl << "!  LEVEL UP  !" << endl;

		cout << endl << "+--- New Stats: -----+" << endl <<
						"  Health  : " << oldHP << " -> " << mPlayer.HP_MAX << endl <<
						"  Attack  : " << oldATP << " -> " << mPlayer.ATP << endl <<
						"  Defense : " << oldDEF << " -> " << mPlayer.DEF << endl <<
						"  Evade   : " << oldEVD << " -> " << mPlayer.EVD << endl <<
						"+--------------------+" << endl << endl;
		system("read -p \"ENTER to proceed...\" dummy");
	}
}


void get_loot(Enemy En) {
	len = (sizeof(loot)/sizeof(*loot))-1;
	srand((unsigned) time(0));
	mNumber=rand() % len;

	if (mNumber == 0) {
		cout << En.NAME << " dropped a healing potion!" << endl;
		if (hpPotion < 10) {
			hpPotion++;
		}
		else {
			cout << "maximum potion reached (10)" << endl;
		}
	}
	else {
		cout << En.NAME << " dropped " << loot[mNumber] << endl;
	}
	system("sleep 1.5");
}

char input() {
	char buffer, input;

	cin >> input;
	while ((buffer = cin.get()) != '\n' && buffer != EOF);
	return input;
}

string string_input() {
	char buffer;
	string input;

	cin >> input;
	while ((buffer = cin.get()) != '\n' && buffer != EOF);
	return input;
}
