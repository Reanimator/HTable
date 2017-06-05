#ifndef _HT_H_
#define _HT_H_

#include <iostream>
#include "node.h"

template <class KEY, class DATA>
class Table
{
protected:
	int size; //общий размер
	int count;//текущее число записей
	int p; // смещение
	Node<KEY,DATA>* mas; // данные
	int Hash(KEY K);//хэш функция
public:
Table(int size_ = 1,int p_ =11); // конструктор принимающий размер и смещение
Table(Table& ht);//конструктор копирование
~Table();//деструктор
DATA& operator[](KEY k_);//доступ по ключу
Table& operator=(Table& ht);//оператор копирования
void Add(DATA val_,KEY k_);//добавление элемена
void Del(KEY k_);//удаление элемента
void resize(int newSize);//ресайз
void input()
{
	KEY k;
	DATA d;
	std::cout << "input key:";
	std::cin >> k;
	std::cout << "input data:";
	std::cin >> d;
	Add(d, k);
}
};

template <class KEY, class DATA>
Table<KEY, DATA>::Table(int size_, int p_)
{
	size = size_;
	count = 0;
	p = p_;
	mas = new Node<KEY,DATA>[size];//массив из узлов (ключ-значение)
}

template <class KEY, class DATA>
Table<KEY, DATA>::Table(Table& ht)
{
	size=ht.size;
	count=ht.count;
	p=ht.p;
	mas=new Node<KEY,DATA>[ht.size];
	for(int i=0; i<ht.size;++i)
		mas[i]=ht.mas[i];

}

template <class KEY, class DATA>
Table<KEY, DATA>::~Table()
{
	delete[] mas;
	size=0;
	count=0;
}

template <class KEY, class DATA>
int Table<KEY, DATA>:: Hash(KEY K)//функция выщитывающая хэш
{
	return ((int)K*17)% size;

}
template <class KEY, class DATA>
DATA& Table<KEY, DATA>::operator[](KEY K)
{
	int index=Hash(K);//получаем индекс
	int HashIndex=index;//запоминаем индекс
	do
	{
		if (mas[index].isUse() == false)//если элемент не используется выходим
			break;
	if(mas[index].GetKey()==K)//если ключ совпал в таблице 
		return mas[index].GetData();//возвращаем его
	else//
		index= (index + p) % size;//смещаемся
	} while (index != HashIndex);//если ключа равен запомненнуму индексу значит прошли по всему массиву
	throw 5;//ничего не вернули значит такого ключа нету, выкидываем ошибку
}

template<class KEY, class DATA>
Table<KEY,DATA> & Table<KEY, DATA>::operator=(Table & ht)
{
	size = ht.size;
	count = ht.count;
	p = ht.p;
	mas = new Node[ht.size];
	for (int i = 0; i<ht.size; ++i)
		mas[i] = ht.mas[i];
}

template <class KEY, class DATA>
void Table<KEY, DATA>::Add(DATA val_, KEY k_)
{
	int index=Hash(k_);//выщитали индекс
	int HashIndex=index;//запомнили
	do
	{

	if(mas[index].isUse() ==false || mas[index].GetKey() == k_)//если индекс не используется или ключи совпали
	{
		mas[index].SetKey(k_);//меняем ключ(на случай если не используется)
		mas[index].SetVal(val_);//значение
		mas[index].setUse(true);//gjvtxftv xnj bcgjkmpetncz
		return;//выходим

	}
	else
		index= (index+p)%size;//смещаемся
	} while (index != HashIndex);//пока не смистились до туда откуда начали
	throw 22;//выкидываем ошибку
}

template<class KEY, class DATA>
void Table<KEY, DATA>::Del(KEY k_)//удаляем так же
{
	int index = Hash(k_);//выщитываем индекс
	int HashIndex = index;//запоминаем индекс
	do
	{
		if (mas[index].isUse() == false)//если элемент не используется выходим
			break;
		if (mas[index].GetKey() == k_)//если ключ совпал в таблице 
		{
			mas[index].setUse(false);//помечаем что он не используется
			return;
	    }
		else//
			index = (index + p) % size;//смещаемся
	} while (index != HashIndex);//если ключа равен запомненнуму индексу значит прошли по всему массиву

}

template<class KEY, class DATA>
void Table<KEY, DATA>::resize(int newSize)//ресайз
{
	LinkedList<Node<KEY, DATA>>* tmp = mas;//делаем 2 указателя на один и тот же массив
	if (count > newSize)//проверяем что новый размер меньше количества элементов
		throw 112;
	mas = new LinkedList<Node<KEY, DATA>>[newSize];//меняем основной указатель класса на новый участок памяти
	count = 0;//обозначаем что в новом участке нет элементов
	int oldSize = size;//запоминаем старый размер что бы пройти по стараму массиву
	size = newSize;//устанавливаем новый участок памяти
	for (int i = 0; i < oldSize; i++)//проходим по стараму массиву
	{
		for (size_t x = 0; x<tmp[i].size(); x++)//и по списку в массиве
			Add(tmp[i].get(x).GetData(), tmp[i].get(x).GetKey());//добавляем каждый элемент через уже готовый метод Add
	}
	delete[] tmp;//удаляем старую память
}

#endif