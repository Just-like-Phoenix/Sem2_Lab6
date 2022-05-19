#include "Menu.h"
#include "Libs.h"
#include <stack>
#include <queue>

class Building {
	int fee = 15;
public:

	string name;
	double cost;
	double profit;

	Building(string _name, double _cost) : name(_name), cost(_cost) { profit = cost * 0.15; };

	friend bool operator<(Building obj1, Building obj2) {
		return obj1.profit < obj2.profit;
	}
	friend bool operator>(Building obj1, Building obj2) {
		return obj1.profit > obj2.profit;
	}
	friend ostream& operator<<(ostream& str, Building obj) {
		return str << "Название: " << obj.name << "\n   Затраты: " << obj.cost << "$\n   Прибыль: " << obj.profit << "$\n\n";
	}
};

priority_queue < Building, vector<Building>, less<vector<Building>::value_type>> que;
queue<Building> stk;

void Add() {
	string name;
	double cost;
	cout << "Введите название строительного объекта: ";
	cin >> name;
	cout << "Введите затраты на постройку: ";
	cin >> cost;
	que.push(Building(name, cost));
	system("cls");
	cout << "Добавлено!";
}

void Show() {
	int i = 1;
	if (que.empty()) {
		cout << "Очередь пуста!";
	}
	else {
		while (!que.empty()) {
			cout << i << ". " << que.top();
			stk.push(que.top());
			que.pop();
			i++;
		}
		while (!stk.empty()) {
			que.push(stk.front());
			stk.pop();
		}
	}
}

void EndPrior() {
	cout << "Завершена стройка " << "\"" + que.top().name + "\"";
	que.pop();
}

void Redact() {
	Show();

	cout << "\n\nВыберите объект: ";
	int choise;
	cin >> choise;
	if (choise < 0 || choise > que.size()) {
		cout << "Такой позиции нет!";
	}
	else {
		string _name;
		double _cost;
		system("cls");
		cout << "Введите название строительного объекта: ";
		cin >> _name;
		cout << "Введите затраты на постройку: ";
		cin >> _cost;
		int i = 1;
		while (!que.empty()) {
			if (choise == i) {
				que.pop();
				que.push(Building(_name, _cost));
			}
			stk.push(que.top());
			que.pop();
			i++;
		}
		while (!stk.empty()) {
			que.push(stk.front());
			stk.pop();
		}
		system("cls");
		cout << "Изменено!";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;

	menu.CreateMenu(4, "Добавить", "Просмотреть", "Редактировать", "Завершить приор.");
	{
		menu.function[0] = Add;
		menu.function[1] = Show;
		menu.function[2] = Redact;
		menu.function[3] = EndPrior;
	}

	menu.Start();
}