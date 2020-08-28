/*******************************************************************************
 * Name        : knapsack.cpp
 * Author      : Ben Rose
 * Version     : 1.0
 * Date        : April 25, 2019
 * Description : Implementation of 0-1 Knapsack using Dynamic Programming.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
//#include <exception>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <string.h/strtok_r.c>
//#include <strtok_r.h>

using namespace std;

struct Item {
	unsigned int item_number, weight, value;
	string description;

	explicit Item(const unsigned int item_number,
			const unsigned int weight,
			const unsigned int value,
			const string &description) :
		item_number(item_number),
		weight(weight),
		value(value),
		description(description) { }

	inline const unsigned int get_item_number() const {
		return item_number;
	}

	inline const unsigned int get_weight() const {
		return weight;
	}

	inline const unsigned int get_value() const {
		return value;
	}

	inline const string& get_description() const {
		return description;
	}

	friend std::ostream& operator<<(std::ostream& os, const Item &item) {
		os << "Item " << item.item_number << ": " << item.description
			<< " (" << item.weight
			<< (item.weight == 1 ? " pound" : " pounds") << ", $"
			<< item.value << ")";
		os.flush();
		return os;
	}
};

// Upgraded Vector_to_String method, Version 2.0
// Altered for a vector of items
void vector_to_string(vector<Item> vec) { // to_string method to display vector content
	cout << "[";
//	printf("[");
//	const int vec_size = vec.size();
	int temp_calc = vec.size();
//	const int vector_size = vec.size();
	const unsigned int limiter = temp_calc - 1;
	for (unsigned int i = 0; i < vec.size(); i++) {
		cout << vec[i];
		(limiter != i) ? cout << ", " : cout << "";
//		if (limiter != i) {
//			cout << vec[i] << ", ";
//		} else {
//			cout << vec[i];
//		}
	}
	cout << "]";
}

//vector<string> item_parts(char *item) {
//	vector<string> parts;
//	char *token = (char *) malloc(1000);
//	token = strtok(item, ",");
//	while (token != NULL) {
//		string piece(token);
//		parts.push_back(piece);
//
//		token = strtok(NULL, ",");
//	}
//	free(token);
//	return parts;
//}

vector<Item> uniquify(vector<Item> items) { // Makes sure that all items are unique in a vector
	vector<Item> unique;
	if (!items.empty()) {
		if (unique.empty()) {
			unique.push_back(items[0]);
		}
		bool in_unique = false;
		for (auto &item : items) {
			for (auto &u_item : unique) {
				if (item.get_description().compare(u_item.get_description()) == 0) { // If we have seen the item
					in_unique = true;
					break;
				}
			}
			if (in_unique == false) { // If we have not seen the item
				unique.push_back(item); // Push it back to the unique vector
			}
			in_unique = false; // Reset in_unique
		}
	}
	return unique;
}

vector<Item> knapsack(vector<Item> items, int capacity) {
	vector<Item> used_items;
//	int selected_capacity = 0;
//	vector<vector<int>> lookup_table;
	int **lookup_table = new int*[items.size() + 1];
//	int lookup_table[capacity+1];
	for (unsigned int i = 0; i < items.size() + 1; i++) {
//		vector<int> vec;
//		lookup_table.push_back(vec);
		lookup_table[i] = new int[capacity + 1];
		for (unsigned int j = 0; j < (unsigned int) capacity + 1; j++) {
			if (i == 0 || j == 0) {
				lookup_table[i][j] = 0;
			}
			else { // the item isn't added if the weight of the item is greater than the capacity
				if (j < items[i - 1].get_weight()) {
					lookup_table[i][j] = lookup_table[i - 1][j];
				} else {
					// Use it or lose it!
					// Lookup_table[i][j] = the max of using the item or losing the item.

					if ((int) (items[i - 1].get_value() + lookup_table[i - 1][j - items[i - 1].get_weight()]) > (int) (lookup_table[i - 1][j])) { // Use it
						lookup_table[i][j] = (items[i - 1].get_value() + lookup_table[i - 1][j - items[i - 1].get_weight()]);
//						used_items.push_back(items[i - 1]); // Append the used item to the list of items
					} else { // Lose it
						lookup_table[i][j] = (lookup_table[i - 1][j]);
					}

//					((items[i - 1].get_value() + lookup_table[i - 1][j - items[i - 1].get_weight()]) > (lookup_table[i - 1][j])) ?
//							lookup_table[i][j] = (items[i - 1].get_value() + lookup_table[i - 1][j - items[i - 1].get_weight()]) :
//							lookup_table[i][j] = (lookup_table[i - 1][j]);
//					lookup_table[i][j] = max((items[i - 1].get_value() + lookup_table[i - 1][j - items[i - 1].get_weight()]), (lookup_table[i - 1][j]));
				}
			}
		}
//		delete [] lookup_table[i];

	}

	int items_size = items.size();
	int temp_capacity = capacity;

	while (items_size > 0 && temp_capacity > 0) { // While we haven't gone through all of the items and we are still not at capacity
		// If we used the item between the current and previous values in the lookup table
		if (lookup_table[items_size][temp_capacity] != lookup_table[items_size - 1][temp_capacity]) {
//			used_items.push_back(items[items_size - 1]); // Append the used item to the vector of used items
			used_items.insert(used_items.begin(), items[items_size - 1]);
			temp_capacity -= items[items_size - 1].get_weight(); // Decrease the remaining capacity by the weight of the used item
		}
		items_size--; // Decrement the remaining items
	}

	for (unsigned int i = 0; i < items.size() + 1; i++) {
		delete [] lookup_table[i];
	}

	delete [] lookup_table;
//	while (selected_capacity < capacity) { // While the weight of the items selected does not exceed the capacity
//
//	}

//	used_items = uniquify(used_items);

	return used_items;
}

void output_builder(vector<Item> items, int capacity) {
	cout << "Candidate items to place in knapsack:" << endl;
	for (unsigned int i = 0; i < items.size(); i++) {
		cout << "   " << items[i] << endl;
	}
	string plural;
	(capacity == 1) ? plural = "" : plural = "s"; // If the capacity is plural, add an "s" to the end. Otherwise, add nothing.
	cout << "Capacity: " << capacity << " pound" << plural << endl;
	vector<Item> used_items = knapsack(items, capacity);
//	(used_items.empty()) ? cout << "None";
	int total_weight = 0;
	int total_value = 0;
	cout << "Items to place in knapsack:";
	// if (used_items.empty()) {
	// 	cout << " None" << endl;
	// } else {
	// 	cout << endl;

	// (used_items.empty()) ? printf(" None\n") : printf("\n");
	(used_items.empty()) ? cout << " None" << endl : cout << endl;
//		cout << "In output elseeeeee" << endl;
		for (unsigned int i = 0; i < used_items.size(); i++) {
			cout << "   " << used_items[i] << endl;
			total_weight += used_items[i].get_weight();
			total_value += used_items[i].get_value();
		}
	// }


	(total_weight == 1) ? plural = "" : plural = "s"; // If the total weight is plural, add an "s" to the end. Otherwise, add nothing.
	cout << "Total weight: " << total_weight << " pound" << plural << endl;
	cout << "Total value : $" << total_value << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <capacity> <filename>";
		return 1;
	}
	int capacity;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> capacity) || capacity < 0) {
		cerr << "Error: Bad value \'" << argv[1] << "\' for capacity.";
		return 1;
	}
//	FILE *input_file = fopen(argv[2], "r"); // Open the input file for reading
	ifstream input_file(argv[2]);
	if (!input_file) { // If the input_file == NULL
		cerr << "Error: Cannot open file '" << argv[2] << "'.";
		return 1;
	}
//	fseek(input_file, 0, SEEK_END); // Set the file position for the input file to the end
//	int file_size = ftell(input_file); // Get the size of the input file
//	char *file_data = (char *) malloc(file_size); // Allocate memory to store the contents of the input file
//	rewind(input_file); // Set the file position to be at the beginning

	// Read the contents of the input file into file_data one byte at a time for file_size bytes. bytes_read = how many bytes were read
//	int bytes_read = fread(file_data, 1, file_size, input_file);
//	if (bytes_read != (int) (1 * file_size)) {
//		cerr << "An error has occurred reading all bytes from the file '" << argv[2] << "'.";
//		return 1;
//	}
//	rewind(input_file); // Since the position was moved to the end by reading from the file, we must rewind the file position again back to the beginning.

	vector<Item> items; // Initialize the vector to store the potential items

//	Item items[];


//	char *token = (char *) malloc(file_size); // Allocate file_size bytes for the token
//	token = strtok(file_data, "\n"); // Token equals the first item in the file
//	while (token != NULL) { // While there are items remaining in the file
	input_file.exceptions(ifstream::badbit);
	string line;
	unsigned int item_number = 1;
	try {

		while(getline(input_file, line)) {


	//		char *temp = token;

			vector<string> item_parts; // Create a vector of strings
//			vector<string> token_pieces;// = item_parts(token); // Create a vector of strings

	//		token_pieces = item_parts(token);
			char *line_data = new char[line.length() + 1];
			strcpy(line_data, line.c_str());
//			char *line_data = const_line_data;
			char *token = (char *) malloc(1000);
			token = strtok(line_data, ",");
//			while ((token = strtok(line_data, ","))) {
			while (token != NULL) {
				string part(token);
				item_parts.push_back(part);

				token = strtok(NULL, ",");
	//			item_parts = strtok_r(NULL, ",", NULL);
			}
			free(token);
			delete [] line_data;

			if (item_parts.size() != 3) {
				cerr << "Error: Line number " << item_number << " does not contain 3 fields.";
				return 1;
			}

			string description = item_parts[0];
			int weight;
			int value;

			stringstream iss;
			iss.str(item_parts[1]);

			if (!(iss >> weight) || weight <= 0) {
				cerr << "Error: Invalid weight '" << item_parts[1] << "' on line number " << item_number << ".";
				return 1;
			}

//			try {
//				weight = stoi(item_parts[1]);
//				if (weight < 0) {
//					cerr << "Error: Invalid weight '" << item_parts[1] << "' on line number " << item_number << ".";
//					return 1;
//				}
//			} catch (const invalid_argument &exception) {
//				cerr << "Error: Invalid weight '" << item_parts[1] << "' on line number " << item_number << ".";
//				return 1;
//			}

			iss.clear();
			iss.str(item_parts[2]);

//			cout << "Value: \"" << value << "\"" << endl;
//			cout << "Item_Parts[2]: \"" << item_parts[2] << "\"" << endl;

			if (!(iss >> value) || value < 0) {
				cerr << "Error: Invalid value '" << item_parts[2] << "' on line number " << item_number << ".";
				return 1;
			}

//			try {
//				cout << "Value: \"" << value << "\"" << endl;
////				value = stoi(item_parts[2]);
//				value = stoul(item_parts[2]);
////				cout << "Value: \"" << value << "\"" << endl;
//				if (value < 0) {
//					cerr << "Error: Invalid value '" << item_parts[2] << "' on line number " << item_number << ".";
//					return 1;
////					throw invalid_argument("Negative number!");
//				}
//			} catch (invalid_argument &exception) {
//				cerr << "Error: Invalid value '" << item_parts[2] << "' on line number " << item_number << ".";
//				return 1;
//			}

//			cout << "Value: \"" << value << "\"" << endl;

			// Work to push back item to items
	//		Item current_item = new Item(item_number, 1000, 9999, "test description");
			Item current_item(item_number, weight, value, description);
	//		current_item.description = "test_description";
	//		current_item.item_number = item_number;
	//		current_item.weight = 1000;
	//		current_item.value = 9999;

	//		cout << "Item Number: \"" << current_item.get_item_number() << "\", Weight: \"" << current_item.get_weight() << "\", Value: \"" << current_item.get_value() << "\", Description: \"" << current_item.get_description() << "\"." << endl;
	//		cout << "Item Number: \"" << current_item->get_item_number() << "\", Weight: \"" << current_item->get_weight() << "\", Value: \"" << current_item->get_value() << "\", Description: \"" << current_item->get_description() << "\"." << endl;
	//		cout << current_item << endl;

	//		items[item_number - 1] = &current_item;
	//		items.push_back(new const Item(item_number, 1000, 9999, "test description"));

			items.push_back(current_item);
//			items.insert(current_item);

			item_number++;


	//		delete current_item;
	//		free(token_pieces);
//			token = strtok(NULL, "\n"); // Reset token to look for the next item
	//		free(token_pieces);
//			cout << "Item Number: \"" << current_item.get_item_number() << "\", Weight: \"" << current_item.get_weight() << "\", Value: \"" << current_item.get_value() << "\", Description: \"" << current_item.get_description() << "\"." << endl;
		}
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}
	output_builder(items, capacity); // Build output
	// Note to self: I believe that we've cleaned most everything out.
	// Create the Dynamic Programming algorithm and produce output.
	// Well done.
//	vector_to_string(items);
//	free(token); // Free the memory allocated for the token
//	free(file_data); // Free the dynamically allocated memory
//	fclose(input_file); // Close the input file
	input_file.close();
	return 0;
}
