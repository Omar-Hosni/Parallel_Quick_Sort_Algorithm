#include <iostream>
#include <algorithm>
#include <list>
#include <future>

using namespace std;

//Normal Sequential Quick Sort
template<typename T>
list<T> s_quickSort(list<T> input) {

	//recursively return condition 
	if (input.size() < 2) {
		return input;
	}

	//select the pivot
	list<T> results;
	results.splice(results.begin(), input, input.begin());
	T pivot = *results.begin();

	//arrang the input array
	auto divide_point = partition(input.begin(), input.end(), [&](T const& t) {return t < pivot; });

	//call the sequential_quick_sort recursively
	list<T> lower_list;
	lower_list.splice(lower_list.end(), input, input.begin(), divide_point);

	auto new_lower(s_quickSort(move(lower_list)));
	auto new_upper(s_quickSort(move(input)));

	//arranging the result list
	results.splice(results.begin(), new_lower);
	results.splice(results.end(), new_upper);

	return results;

}

//Parallel Quick Sort using Multithreading
template<typename T> 
list<T> parallel_quick_sort(list<T>input) {

	//conditional return
	if (input.size() < 2) {
		return input;
	}

	//move first element in the list and select it as pivot
	list<T> results;
	results.splice(input.begin(), input, input.end());
	T pivot = *results.begin();

	//determing the dividing point
	auto dividing_point = partition(input.begin(), input.end(), [&](T const& t) {return pivot < t; });
	
	//move lower part of the list to seperate list so that we can make recursive call
	list<T> lower_list;
	lower_list.splice(lower_list.end(), input, input.begin(), dividing_point);

	auto new_lower(parallel_quick_sort(move(lower_list)));
	
	future<list<T>> new_upper_future(async(&parallel_quick_sort<T>, move(input)));

	results.splice(results.begin(), new_lower);
	results.splice(results.end(), new_upper_future.get());
	
	return results;

}

int main() {

}
