#pragma once
#include "Hashtable.h"

using namespace std;

class analyzer {
public:
	string str;
	string str2;
	string str3;
	int p;
	int sum = 0;
	int sum2 = 0;
	int sum3 = 0;
	bool proverka = true;

	analyzer(string& str) {
		this->str = str;
		p = 0;
	}

	void scan(HashTable&);
	void begin(HashTable&);
	bool type(HashTable&);
	void descriptions(HashTable&);
	void descr(HashTable&);
	void operators(HashTable&);
	void op(HashTable&);
	bool id(HashTable&);
	void expr(HashTable&);
	void SimpleExpr(HashTable&);
	bool FunctionName(HashTable&);
	bool Const(HashTable&);
	void end(HashTable&);
};

void analyzer::scan(HashTable& hassh) {
	Node k;
	k.Name = ";";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);

	k.Name = "}";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);

	k.Name = "{";
	k.Type = "DEVIDER";
	hassh.insertItem(k.Name, k);
	//ofst << "begin" << endl;
	begin(hassh);
	if (str[p] != '(' || str[p + 1] != ')' || str[p + 2] != ' ' || str[p + 3] != '{') {
		proverka = false;
		cerr << "Error begin" << endl;
		while (str[p] != ' ') p++;
	}
	else p += 5;
	ofst << "descriptions->Type id" << endl;
	descriptions(hassh);
	ofst << "operators" << endl;
	operators(hassh);
	ofst << "end->return id" << endl;
	end(hassh);
	if (proverka) cout << "True" << endl; else cout << "False" << endl;
	return;
}

void analyzer:: begin(HashTable& hassh) {
	ofst << "begin->type FunctionName" << endl;
	if (!type(hassh)) {
		proverka = false;
		cerr << "Not type" << endl;
	}
	if (!FunctionName(hassh)) {
		proverka = false;
		cerr << "Not FunctionName" << endl;
	}
	 return;
}

bool analyzer::type(HashTable& hassh) {
	string h;
	string q;
	while (str[p] != ' ' && str[p] != ' ') {
		h += str[p];
		p++;
	}
	Node y;
	y.Name = h;
	y.Type = "TYPE";
	hassh.insertItem(y.Name, y);
	q = h;
	ofst << "   Type->" << q << endl;
	q += str[p];
	if (q == "int ") {
		//cout << "int" << endl;
		return true;
	}
	else {
		//proverka = false;
		return false;
	}
}

bool analyzer::FunctionName(HashTable& hassh) {
	p++;
	string n;
	bool t = true;
	while (str[p] != '(') {
		if (isdigit(str[p])) {
			proverka = false;
			t = false;
		}
		n += str[p];
		p++;
	}
	ofst << "   FunctionName->" << n << endl;
	return t;
}

void analyzer::descriptions(HashTable& hassh) {
	while (p+1 != str.size()) {
		if (str[p] == 'g' && str[p + 1] == 'o' && str[p + 2] == 't' && str[p + 3] == 'o' && str[p + 4] == ' ') {
			Node k;
			k.Name = "goto";
			k.Type = "RESWORD";
			hassh.insertItem(k.Name, k);
			return;
		}
		else {
			if (str[p] == 'i' && str[p + 1] == 'n' && str[p + 2] == 't' && str[p + 3] == ' ') {
				descr(hassh);
			}
			else {
				int u = p;
				while (str[u] != ' ') {
					u++;
				}
				u++;
				if (str[u] == '=' || str[u] == ':') {
					return;
				}
				else {
					proverka = false;
					cerr << "ERROR in INT" << endl;
					descr(hassh);
				}
			}
		}
	}
}

void analyzer::descr(HashTable& hassh) {
	if (!type(hassh)) proverka = false;
	p++;
	while (str[p] != ';') {
		if (str[p] == ',') {
			Node k;
			k.Name = ",";
			k.Type = "DEVIDER";
			hassh.insertItem(k.Name, k);
			p += 2;
		}
		if (!id(hassh)) {
			proverka = false;
			cerr << "Not id" << endl;
		}
		if (str[p] != ',' && str[p] != ';') {
				proverka = false;
				cerr << "Not , or ;" << endl;
				break;
		}
	}
	p += 2;
	return;
}

bool analyzer::id(HashTable& hassh) {
	string h;
	bool t = true;
	while (str[p] != ',' && str[p] != ';' && str[p] != ' ') {
		if (!isalpha(str[p])) t = false;
		h += str[p];
		p++;
	}
	str2 = h;
	ofst << "   id->" << h << endl;
	Node y;
	y.Name = h;
	y.Type = "ID";
	hassh.insertItem(y.Name, y);
	//if (h==" ") proverka = false;
	return t;
}

void analyzer::operators(HashTable& hassh) {
	//cout << "STR: " <<str[p];str[p]!='r'&&str[p]!='e'&&str[p]!='t'
	string q;
	while (q+str[p]+str[p+1]+str[p+2] + str[p + 3] + str[p + 4] + str[p + 5] !="return"&&str[p]!=str.size()) {
		op(hassh);
	}
	if (str[p] == str.size()) {
		cerr << "Not return" << endl;
		proverka = false;
	}
	return;
}

void analyzer::op(HashTable& hassh) {
	Node k;
	if (str[p] == 'g' && str[p + 1] == 'o' && str[p + 2] == 't' && str[p + 3] == 'o'&& str[p+4]==' ') {
		k.Name = "goto";
		k.Type = "RESWORD";
		hassh.insertItem(k.Name, k);
		p += 5;

		if (sum >= 1) {
			ofst << "   operator->goto id" << endl;
			sum--;
		}
		else ofst << "   goto id" << endl;

		if (!id(hassh)) {
			cerr << "Not id" << endl;
			proverka = false;
		}

		if (str[p] == ' ') {
			proverka = false;
			cerr << "Not ;" << endl;
		}
		p += 2;


		return;
	}
	else {
		int u = p;
		while (str[u] != ' ') {
			u++;
		}
		u++;
		if (str[u] == '=') {
			k.Name = "=";
			k.Type = "OPERATOR";
			hassh.insertItem(k.Name, k);
			if (sum >= 1) {
				ofst << "   operator->id = SimpleExpr" << endl;
				sum--;
			}
			else ofst << "   id = SimpleExpr" << endl;
			id( hassh);
			p++;
			p += 2;
			expr(hassh);
			return;
		}
		else {
			if (str[u] == ':') {
				sum++;
				k.Name = ":";
				k.Type = "DEVIDER";
				hassh.insertItem(k.Name, k);
				
				if (sum > 1) {
					ofst << "   operator->id : operator" << endl;
					sum=0;
				}
				else ofst << "   id : operator" << endl;

				id(hassh);
				p++;
				p += 2;
				op(hassh);
				return;
			}
			else {
				//if (str.substr(p, p + 6) == "return") {
					//return;
				//}
				//else {
				proverka = false;
					cout << "ERROR not goto" << endl;
					while (str[p] != ' ') {
						//cout << str[p];
						p++;
					}
					p++;
					id(hassh);
					p += 2;
					return;
				//}
			}
		} 
	}
}

void analyzer::expr(HashTable& hassh) {
	sum2++;
	SimpleExpr(hassh);
	if (str[p] == '+' || str[p] == '-') {
		//ofst << "   Expr->SimpleExpr +||- Expr" << endl;
		sum2=1;
		Node r;
		r.Name = str[p];
		r.Type = "OPERATOR";
		hassh.insertItem(r.Name, r);
		p += 2;
		expr(hassh);
		return;
	}
	else {
		//ofst << "   Expr->SimpleExpr" << endl;
	}
	if (str[p] == ';') {
		sum2 = 0;
		p += 2;
		//cout << str[p];
		return;
	}
	return;
}

void analyzer::SimpleExpr(HashTable& hassh) {
	if (isdigit(str[p])) {
		//if (sum2 != 1) ofst << "   SimpleExpr->Const" << endl; else sum2 = 0;
		ofst << "   SimpleExpr->Const" << endl;
		Const(hassh);
		for (int i = 0; i < sum2; i++) {

		}

		p++;
		return;
	}
	else {
		if (str[p] == '(') {
			//if (sum2 != 1) ofst << "   SimpleExpr->( Expr )" << endl; else sum2 = 0;
			ofst << "   SimpleExpr->( Expr )" << endl;
			Node r;
			r.Name = "(";
			r.Type = "DEVIDER";
			hassh.insertItem(r.Name, r);
			p += 2;
			expr(hassh);
			if (str[p] != ')') {
				cerr << "ERROR )" << endl;
				while (str[p] != ';') p++;
			}
			else {
				r.Name = ")";
				r.Type = "DEVIDER";
				hassh.insertItem(r.Name, r);
			}
			p += 2;
			return;
		}
		else {
			ofst << "   SimpleExpr->id" << endl;
			if (id(hassh)) {
				//if (sum2 != 1) ofst << "   SimpleExpr->id" << endl; else sum2 = 0;
				p++;
				return;
			}
			else {
				cout << "Error: not const/not id" << endl;
				while (str[p] != ';') p++;
				return;
			}
		}
	}
}

bool analyzer::Const(HashTable& hassh) {
	string h;
	bool t = true;
	while (str[p] != ',' && str[p] != ';' && str[p] != ' ') {
		if (isalpha(str[p])) t = false;
		h += str[p];
		p++;
	}
	ofst << "   Const->"<< h << endl;
	Node y;
	y.Name = h;
	y.Type = "CONST";
	hassh.insertItem(y.Name, y);
	if (!t) {
		cerr << "Not Const" << endl;
		proverka = false;
	}
	return t;
}

void analyzer::end(HashTable& hassh) {
	p += 7;
	if (!id(hassh)) {
		cerr << "Not id" << endl;
		proverka = false;
	}
	return;
}