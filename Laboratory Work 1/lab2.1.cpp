//13. Создать абстрактный класс машина. Создать класс легковая машина(наследник абстрактного класса), имеющий марку, число цилиндров, мощность.
// Определить конструкторы, деструктор и функцию вывода. 
// Создать public-производный класс – автобус, имеющий вместимость пассажиров, объем багажника, наличие компьютера. 
// Определить конструкторы по умолчанию и с разным числом параметров, деструкторы, функцию вывода. 
// Определить функции переназначения мощности и грузоподъемности. 
// Использовать статическую переменную для хранения количества созданных объектов классов наследников и константы для хранения идентификационных номеров в 
// абстрактном классе, в классах наследниках. 

#include <iostream>

using namespace std;

class Car
{
protected:
	int power = 0;
	int capacity = 0;
	static int count;
	const int ID;

	public:

	virtual void PowerFoo(int newpow) = 0;
	virtual void LoadCapacity(int newcap) = 0;
	virtual void ShowInfo() = 0;
	
	Car() : ID(count + 1) {
		count++;
	}

	int getID() {
		return ID;
	}

	static int getCount() {
		return count;
	}

	virtual ~Car() {};
};
int Car::count = 0;

class PassengerCar : protected Car
{
private:

	string name;
	int cylinder;
	int power;

public:

	PassengerCar() {
		name = "Name";
		cylinder = 0;
		power = 0;
	}

	PassengerCar(string carname, int valuecylinder, int carpower) {
		name = carname;
		cylinder = valuecylinder;
		power = carpower;
	}

	~PassengerCar() {}

	void PowerFoo(int newpow) override {
		power = newpow;
		cout << "Мощность автомобиля изменена!" << endl;
	}

	void LoadCapacity(int newcap) override {
		capacity = newcap;
		cout << "Грузоподъемность легкового автомобиля изменена!";
	}

	void ShowInfo() override {
		cout << "Информация о легковом автомобиле:" << endl;
		cout << "1) Марка автомобиля: " << name << endl;
		cout << "2) Количество цилиндров: " << cylinder << endl;
		cout << "3) Мощность: " << power << endl;
		cout << "4) Грузоподъемность автомобиля: " << capacity << endl;
		cout << "5) Идентификационный номер: " << ID << endl;
	}
};

class Bus : public Car
{
private:
	int passengercapacity;
	int volume;
	bool computer;

public:

	Bus() {
		passengercapacity = 0;
		volume = 0;
		computer = false;
	}

	Bus(int pascap, int vol, bool comp) {
		passengercapacity = pascap;
		volume = vol;
		computer = comp;
	}

	~Bus() {}

	void LoadCapacity(int newcap) override {
		capacity = newcap;
		cout << "Грузоподъемность изменена!" << endl;
	}

	void PowerFoo(int newpow) override {
		power = newpow;
	}

	void ShowInfo() override {
		cout << "Информация об автобусе: " << endl;
		cout << "1) Вместимость пассажиров: " << passengercapacity << endl;
		cout << "2) Объем багажника: " << volume << endl;
		cout << "3) Наличие компьютера: " << (computer ? "Да":"Нет") << endl;
		cout << "4) Грузоподъемность автобуса: " << capacity << endl;
		cout << "5) Идентификационный номер: " << ID << endl;
 	}

};

int main() {
	setlocale(LC_ALL, "rus");

	PassengerCar volvo("Volvo", 5, 215);
	volvo.ShowInfo();
	volvo.PowerFoo(250);
	volvo.LoadCapacity(500);
	volvo.ShowInfo();

	cout << endl << endl;

	PassengerCar renault("Renault", 4, 160);
	renault.ShowInfo();
	renault.PowerFoo(200);
	renault.LoadCapacity(200);
	renault.ShowInfo();

	cout << endl << endl;

	Bus bus(50, 200, false);
	bus.ShowInfo();
	bus.PowerFoo(300);
	bus.LoadCapacity(1000);
	bus.ShowInfo();

	cout << "Всего автомобилей создано: " << Car::getCount() << endl;
	return 0;
}