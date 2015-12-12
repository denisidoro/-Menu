#include <iostream>
#include <string>

#include "ucMenu/ucMenu.h"
#include "curtain/Alarm.h"
#include "curtain/Light.h"
#include "curtain/Sensor.h"

#include <vector>

// init LCD, menu system and sensors
ucMenu* menu = new ucMenu(16, 2);
Sensor* sensor = new Sensor();

// menu definition
MenuItem* mainMenu = new MenuItem(NULL);
MenuItem* triggerMenu = new MenuItem(mainMenu);
MenuItem* autoMenu = new MenuItem(mainMenu);
MenuItem* monitorMenu = new MenuItem(mainMenu);
MenuItem* configMenu = new MenuItem(mainMenu);
MenuItem* aboutMenu = new MenuItem(mainMenu);
MenuItem* newTriggerMenu;

// toggle definitions
ToggleOptions* stateTO = new ToggleOptions();
ToggleOptions* modeTO = new ToggleOptions();
ToggleOptions* triggerTO;

// init triggers
vector<Trigger*> triggers;
	
// menu helper variables
int option1, option2, option3, option4, option5;

// function definitions
void resetOptions();
void setup();
void loop();
void triggerCheck();

void setup() {
	
	// variable init
	resetOptions();
	
	triggerTO = new ToggleOptions(true);
	triggers.push_back(new Alarm(9, 45, true));
	triggers.push_back(new Alarm(20, 30, false));
	triggers.push_back(new Light(true, 90, false));

	// setup toggles
	stateTO->add("aberto", 0);
	stateTO->add("fechado", 1);
	modeTO->add("hora =", 0);
	modeTO->add("luz <", 1);
	modeTO->add("luz >", 2);
	
	// setup menu
	menu->setRoot(mainMenu);
	
	// main menu setup
	mainMenu->addRow(new MenuRowSubmenu("Triggers", triggerMenu));
	mainMenu->addRow(new MenuRowSubmenu("Monitor", monitorMenu));
	mainMenu->addRow(new MenuRowSubmenu("Config", configMenu));
	mainMenu->addRow(new MenuRow("Sobre"));
		
	// trigger menu setup
	newTriggerMenu = new MenuItem(triggerMenu);
	triggerMenu->addRow(new MenuRowSubmenu("Novo", newTriggerMenu));
	triggerMenu->addRow(new MenuRowToggle("Del", triggerTO, &option1));
	
	// new trigger menu setup
	newTriggerMenu->addRow(new MenuRowToggle("Acao", stateTO, &option1));
	newTriggerMenu->addRow(new MenuRowToggle("Modo", modeTO, &option5));
	newTriggerMenu->addRow(new MenuRowVar("Horas", &option2, "", 0, 23));
	newTriggerMenu->addRow(new MenuRowVar("Minutos", &option3, "", 0, 59));
	newTriggerMenu->addRow(new MenuRowVar("Luz", &option4, "", 0, 100));
	newTriggerMenu->addRow(new MenuRow("Confirmar"));
	
	// monitor menu setup
	monitorMenu->addRow(new MenuRowToggle("Estado", stateTO, &option1));
	monitorMenu->addRow(new MenuRowVar("Horas", &option2, "", 23, 23));
	monitorMenu->addRow(new MenuRowVar("Minutos", &option3, "", 59, 59));
	monitorMenu->addRow(new MenuRowVar("Luz", &option4, "", 100, 100));
	
	// config menu setup
	configMenu->addRow(new MenuRowVar("Horas", &option2, "", 0, 23));
	configMenu->addRow(new MenuRowVar("Minutos", &option3, "", 0, 59));
	configMenu->addRow(new MenuRow("Confirmar"));
	
	// display root menu and help
	menu->refresh();
	cout << endl << 
		" WASD: setas, K: cancel, L: select" << endl <<
		" aperte enter para confirmar sua escolha" <<
		endl << endl;

}

void loop() {

	// variable init
	string s;
	char ch;

	while (ch != 'x') {
		
		getline(cin, s);
		
		for (int i = 0; i < s.length(); i++) {
			
			ch = s[i];
			
			switch (ch) {
				case 'u': triggerCheck(); continue;	break; // UPDATE		
				case 'w': menu->up(); 				break;
				case 'a': menu->left();				break;
				case 's': menu->down(); 			break;
				case 'd': menu->right(); 			break;
				case 'k': menu->cancel(); 			break;
					break;
				case 'l': 
											
					// change new trigger menu content based on mode
					if (menu->nextMenu() == newTriggerMenu) {
						newTriggerMenu->getRow(2, true)->hidden = !(option5 == 0);
						newTriggerMenu->getRow(3, true)->hidden = !(option5 == 0);
						newTriggerMenu->getRow(4, true)->hidden = (option5 == 0);
					}		
					
					// trigger created message	
					if (menu->currentMenu == newTriggerMenu && menu->lastRow()) {
						if (option5 == 0)	// TIME
							triggers.push_back(new Alarm(option2, option3, triggerTO->getValue(option1)));
						else 				// LIGHT	
							triggers.push_back(new Light(triggerTO->getValue(option5) == 0, option4, triggerTO->getValue(option1)));
						menu->message("Trigger criado com sucesso!  ");
						resetOptions();
					}
					
					// delete trigger
					else if (menu->currentMenu == triggerMenu && menu->getCurrentRow() == 1 && menu->getCurrentMode() == TOGGLE) {
						menu->message("Tem certeza?", triggerMenu);
						menu->customMenuId = 1;
					}
						
					// populate trigger list toggle
					else if (menu->nextMenu() == triggerMenu) {
						triggerTO->clear();
						if (triggers.size() == 0)
							triggerMenu->getRow(1, true)->hidden = true;
						else {
							triggerMenu->getRow(1, true)->hidden = false;
							for (int i = 0; i < triggers.size(); i++)
								triggerTO->add(triggers[i]->text(), i);
						}
						menu->select(); 
						resetOptions();
					}
					
					// end message when removing trigger
					else if (menu->customMenuId == 1) {
						menu->customMenuId = 0;
						triggers.erase(triggers.begin() + option1);
						menu->message("Trigger remov. com sucesso!");
					}
					
					// about
					else if (menu->currentMenu == mainMenu && menu->lastRow())
						menu->message("Denis I F     Homero F S M  Teresa C      2015");
					
					// confirm new time
					else if (menu->currentMenu == configMenu && menu->lastRow()) {
						sensor->setTime(option2, option3);
						menu->message("Dados atual.  com sucesso!");
					}
						
					// refresh variables on monitor and config menus
					else if (menu->nextMenu() == monitorMenu || (menu->currentMenu != configMenu && menu->nextMenu() == configMenu)) {
						option2 = sensor->hours();
						option3 = sensor->minutes();
						option4 = sensor->ldrValue();
						menu->select(); 
					}
					
					// all other cases
					else
						menu->select(); 
						
					break;
			}
				
			menu->refresh();
			
			// debug
			// cout << "debug";
			
		}
		
	}

}

void triggerCheck() {

	for (int i = 0; i < triggers.size(); i++) {
		if (triggers[i]->check(sensor)) {
			// add motor action here
			if (triggers[i]->open) 	cout << "motor abrindo";
			else					cout << "motor fechando";
		}
	}

}

int main(int argc, char** argv) {
	setup();
	loop();
	return 0;
}

void resetOptions() {
	option1 = 0; option2 = 0; option3 = 0; option4 = 0;
}

