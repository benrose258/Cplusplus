/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Ben Rose
 * Date        : March 15, 2019
 * Description : Solves the water jug puzzle for any given input of three jug
 * 				       capacities and the goal for how much you want each jug to contain.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Version	   : 2.0
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct State {
	int a, b, c;
	vector<string> directions;
	State* parent = nullptr;

	State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		for (unsigned int i=0; i<directions.size(); i++){
			oss << directions[i];
		}
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
	bool equalStates(int goalA, int goalB, int goalC) {
		if (a == goalA && b == goalB && c == goalC) {
			return true;
		}
		return false;
	}
};

bool isPourPossible(State *change, State *caps, string from, string to) {
	if ((from == "a" && change->a == 0)||(from == "b" && change->b==0)||(from == "c" && change->c==0)) {
		return false;
	}
	else if ((to == "a" && change->a == caps->a)||(to == "b" && change->b==caps->b)){
		return false;
	}
	else { // Do not worry about c being full, as a+b should equal c in the water jug problem
		return true;
	}
}
State* pour(State *tochange, State *caps, string from, string to) { // Assumes it is possible to pour
	int newA = tochange -> a;
	int newB = tochange -> b;
	int newC = tochange -> c;
	int change = 0;
	if (from == "c" && to == "a"){ // C to A
		while(newA != caps -> a && newC != 0) {
			newC--;
			newA++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState -> directions.push_back("Pour ");
		newState -> directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from C to A. ");
		}
		else {
			newState -> directions.push_back(" gallons from C to A. ");
		}
		newState -> parent = tochange;
		return newState;
	}
	else if (from == "b" && to == "a"){ // B to A
		while(newA != caps -> a && newB != 0) {
			newB--;
			newA++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState->directions.push_back("Pour ");
		newState->directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from B to A. ");
		}
		else {
			newState -> directions.push_back(" gallons from B to A. ");
		}
		newState -> parent = tochange;
		return newState;
	}
	else if (from == "c" && to == "b"){ // C to B
		while(newB != caps -> b && newC != 0) {
			newC--;
			newB++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState -> directions.push_back("Pour ");
		newState -> directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from C to B. ");
		}
		else {
			newState -> directions.push_back(" gallons from C to B. ");
		}
		newState -> parent=tochange;
		return newState;
	}
	else if (from == "a" && to== "b"){ // A to B
		while(newB != caps -> b && newA != 0) {
			newA--;
			newB++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState -> directions.push_back("Pour ");
		newState -> directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from A to B. ");
		}
		else {
			newState -> directions.push_back(" gallons from A to B. ");
		}
		newState -> parent=tochange;
		return newState;
	}
	else if (from == "b" && to == "c") { // B to C
		while(newC != caps -> c && newB != 0) {
			newB--;
			newC++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState -> directions.push_back("Pour ");
		newState -> directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from B to C. ");
		}
		else {
			newState -> directions.push_back(" gallons from B to C. ");
		}
		newState -> parent = tochange;
		return newState;
	}
	else { // A to C
		while(newC!=caps->c && newA!=0) {
			newA--;
			newC++;
			change++;
		}
		State *newState = new State(newA, newB, newC);
		string gallonsPoured = to_string(change);
		newState -> directions.push_back("Pour ");
		newState -> directions.push_back(gallonsPoured);
		if (change == 1){
			newState -> directions.push_back(" gallon from A to C. ");
		}
		else {
			newState -> directions.push_back(" gallons from A to C. ");
		}
		newState -> parent = tochange;
		return newState;
	}
}
bool** isSeenMatrix(int capA, int capB) { // Checks if the jug size combinations of a and b are already seen
	bool** seen = new bool*[capA+1];
	for (int i = 0; i <= capA; i++) {
		seen[i] = new bool[capB + 1];
		for (int j = 0 ; j <= capB; j++) {
			seen[i][j] = false;
		}
	}
	return seen;
}
void traversal(int capA, int capB, int capC, State *target, State *caps) {
	queue <State*> q;
	// Vector in C++ is the arraylist equivalent
	bool** seenList = isSeenMatrix(capA, capB); // jugsizea + 1 for row size, column size jugsizeb+1
	State *initial = new State(0, 0, capC);
	bool found=false;
	q.push(initial);
	State *current = initial;
	State *CtoA;
	State *BtoA;
	State *CtoB;
	State *AtoB;
	State *BtoC;
	State *AtoC;
	State *working;
	while(!q.empty()) {
		current = q.front();
		if (current -> equalStates(target -> a, target -> b, target -> c)) {
			found = true;
			break;
		}
		else {
			if (isPourPossible(current, caps, "c", "a")){
				CtoA = pour(current, caps, "c", "a");
				if (!(seenList[CtoA -> a][CtoA -> b])) {
					q.push(CtoA);
					seenList[CtoA->a] [CtoA->b] = true;
				}
			}
			if (isPourPossible(current, caps, "b", "a")){
				BtoA = pour(current, caps, "b", "a");
				if (!(seenList[BtoA -> a][BtoA -> b])){
					q.push(BtoA);
					seenList[BtoA -> a][BtoA -> b] = true;
				}
			}
			if (isPourPossible(current, caps, "c", "b")){
				CtoB = pour(current, caps, "c", "b");
				if (!(seenList[CtoB->a][CtoB->b])){
					q.push(CtoB);
					seenList[CtoB -> a][CtoB -> b] = true;
				}
			}
			if (isPourPossible(current, caps, "a", "b")){
				AtoB = pour(current, caps, "a", "b");
				if (!(seenList[AtoB -> a][AtoB -> b])) {
					q.push(AtoB);
					seenList[AtoB -> a][AtoB -> b] = true;
				}
			}
			if (isPourPossible(current, caps, "b", "c")){
				BtoC = pour(current, caps, "b", "c");
				if (!(seenList[BtoC -> a][BtoC -> b])) {
					q.push(BtoC);
					seenList[BtoC -> a][BtoC -> b] = true;
				}
			}
			if (isPourPossible(current, caps, "a", "c")){
				AtoC = pour(current, caps, "a", "c");
				if (!(seenList[AtoC -> a][AtoC -> b])) {
					q.push(AtoC);
					seenList[AtoC -> a][AtoC -> b] = true;
				}
			}
		}
		q.pop();
	}
	if (found == false) {
		cout << "No solution." << endl;
	}
	else {
		if (current -> equalStates(initial -> a, initial -> b, initial -> c)) { // If the initial is the target
			cout << "Initial state. " << current -> to_string() << endl;
			delete [] seenList;
			while (!q.empty()) {
				State *toDelete = q.front();
				q.pop();
				delete toDelete;
			}
			return;
		}
		vector<string> path;
		working = current -> parent;
		path.push_back(current -> to_string());
		while (!(working -> equalStates(initial -> a, initial -> b, initial -> c))) { // Traverses back through using the parent connections. This will get the path in reverse order.
			path.insert(path.begin(), working -> to_string());
			working = working -> parent;
		}
		path.insert(path.begin(), initial -> to_string());
		cout << "Initial state. " << path[0] << endl; // Prints the initial state
		for (unsigned int i=1; i < path.size(); i++){ // Prints it in correct order
			cout << path[i] << endl;
		}
		delete working;
	}
	for (int i = 0; seenList[i] != 0; i++) {
		delete [] seenList[i];
	}
	delete [] seenList;
	while (!q.empty()) {
		State *toDelete = q.front();
		q.pop();
		delete toDelete;
	}
}

int main(int argc, char * const argv[]) {

	int capAint, capBint, capCint, goalAint, goalBint, goalCint;
	if (argc != 7) { // We have too many arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	istringstream issCAPA(argv[1]), issCAPB(argv[2]), issCAPC(argv[3]), issGOALA(argv[4]), issGOALB(argv[5]), issGOALC(argv[6]);

	if ((!(issCAPA >> capAint)) || (capAint < 0)) { // If the capacity of A is not an integer less than zero
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}
	if ((!(issCAPB >> capBint)) || (capBint < 0)) { // If the capacity of B is not an integer less than zero
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;
	}
	if ((!(issCAPC >> capCint)) || (capCint <= 0)) { // If the capacity of C is not an integer less than or equal to zero
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;
	}
	if (!(issGOALA >> goalAint) || (goalAint < 0)) { // If the goal of A is not an integer less than zero
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
	}
	if (!(issGOALB >> goalBint) || goalBint < 0) { // If the goal of B is not an integer less than zero
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}
	if (!(issGOALC >> goalCint) || goalCint < 0) { // If the goal of C is not an integer less than zero
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}
	if (capAint < goalAint) { // If the goal of A exceeds the capacity of A
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
	if (capBint < goalBint) { // If the goal of B exceeds the capacity of B
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if (capCint < goalCint) { // If the goal of C exceeds the capacity of C
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
	if ((goalAint + goalBint + goalCint) != capCint) { // If the total gallons of water are not able to fit perfectly in jug C
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	else {
		State *goal = new State(goalAint, goalBint, goalCint);
		State *cap = new State(capAint, capBint, capCint);
		traversal(capAint, capBint, capCint, goal, cap);
		delete goal;
		delete cap;
		return 0;
	}

}
