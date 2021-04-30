#include "pch.h"
using namespace std;

static std::string roundAny(float r, int precision) {
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(precision) << r;
	return buffer.str();
}

class  Calculation {
public:
	int quantity;  //题目数量
	int maximum;   //最大数
	int elem_len;  //每个式子参与运算的个数
	bool brackets; //括号
	bool decimal;  //小数


	vector <string> opt{};
	vector <string> expression{};
	vector <string> answer{};
public:
	void Create();
	void SetQuantity(int q);
	void SetMaximum(int m);
	void SetBrackets(bool b);
	void SetDecimal(bool d);
	void SetElem_len(int len);
	void AddOpt(string op) {
		this->opt.push_back(op);
	}
	void SaveFile();

	Calculation(int q, int m, bool b, bool d);
};

Calculation::Calculation(int q, int m, bool b, bool d) {
	this->quantity = q;
	this->maximum = m;
	this->brackets = b;
	this->decimal = d;
	this->elem_len = 4;
	
}
void Calculation::SetElem_len(int len) {
	this->elem_len = len;
}
void Calculation::SetQuantity(int q) {
	this->quantity = q;
}
void Calculation::SetMaximum(int m) {
	this->maximum = m;
}
void Calculation::SetBrackets(bool b) {
	this->brackets = b;
}
void Calculation::SetDecimal(bool d) {
	this->decimal = d;
}
void Calculation::SaveFile() {
	ofstream outFile("exprssion.txt", ios::out | ios::binary);
	if (!outFile) {
		cout << "Faile!" << endl;
		return;
	}
	for (int i = 0; i < (this->expression.size()); i++) {
		outFile << this->expression[i] << endl;
	}
	outFile.close();
	return;
}
void Calculation::Create() {
	srand((unsigned int)(time(NULL)));

	for (int x = 0; x < quantity; x++) {
		string tmp;
		int left = rand() % (elem_len - 1);   // 括号左位置
		int right = rand() % (elem_len - left - 1) + left + 1; //括号右位置
		while (left == 0 && right == elem_len - 1) {
			left = rand() % (elem_len - 1);   // 括号左位置
			right = rand() % (elem_len - left - 1) + left + 1; //括号右位置
		}

		for (int i = 0; i < elem_len; i++) {

			string temp = "";
			float number = rand() % maximum + 1 + (float)(rand() % maximum) / maximum;
			if (this->decimal) {
				temp = roundAny(number, 2);
			}
			else {
				temp = roundAny(number, 0);
			}
			if (brackets) {
				if (i == left) {
					temp = "(" + temp + " ";
				}
				else if (i == right) {
					temp = temp + ")";
				}
				else {
					temp = temp + " ";
				}
			}
			else {
				temp = temp + " ";
			}
			if (temp.size() == 2) {
				temp = "  " + temp;
			}
			else if (temp.size() == 3) {
				temp = " " + temp;
			}
			tmp += temp;
			if (i < elem_len - 1)
				tmp += opt[rand() % (opt.size())] + " ";
			else
				tmp += " = ";
		}
		expression.push_back(tmp);
		//std::cout << expression[x] << endl;
	}
}


int main()
{
	int quantity;
	int maximum;
	char temp;
	bool brackets = false;
	bool decimal = false;
	int elem_len;
	cout << "请输入题目数量: "; cin >> quantity;
	cout << "请输入设置的最大数: "; cin >> maximum;
	cout << "请输入式子中的个数（大于3）: "; cin >> elem_len;
	cout << "是否有括号(Y or N): "; cin >> temp;
	if (temp == 'Y' || temp == 'y') {
		brackets = true;
	}
	cout << "是否用到小数(Y or N): "; cin >> temp;
	if (temp == 'Y' || temp == 'y') {
		decimal = true;
	} 
	
	cout << endl;
	Calculation clac(quantity, maximum, brackets, decimal);
	temp = ' ';
	cout << "请选择需要的运算符号: "; cin >> temp;
	while (cin.get() != '\n') {
		if(temp == '+') clac.AddOpt("＋");  //"＋", "－", "×", "÷"
		if(temp == '-') clac.AddOpt("－");
		if(temp == '*') clac.AddOpt("×");
		if(temp == '/') clac.AddOpt("÷");
		cin >> temp;
	}
	if (temp == '+') clac.AddOpt("＋");  //"＋", "－", "×", "÷"
	if (temp == '-') clac.AddOpt("－");
	if (temp == '*') clac.AddOpt("×");
	if (temp == '/') clac.AddOpt("÷");

	clac.SetElem_len(elem_len);
	clac.Create();
	clac.SaveFile();
	for (int i = 0; i < clac.expression.size(); i++) {
		cout << clac.expression[i] << endl;
	}

	return 0;
}
