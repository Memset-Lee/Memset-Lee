#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<chrono>
#define ll long long
#define llf LLONG_MAX
using namespace std;

ll questionNum = 100, maxRange = 100;//初始题目数量，初始自然数大小
ll parenthesesProbability = 5, denominatorRange = 100;//括号概率，分母范围
string exerciseFile, answerFile;//题目文件，答案文件
vector<string>allSymbol = { "+","-","*","/" };//运算符
static mt19937_64 randomNumberGenerator(chrono::steady_clock::now().time_since_epoch().count());//随机数生成器
uniform_int_distribution<ll>symbolNumRange(1, 3);//符号数量
uniform_int_distribution<ll>symbolRange(0, 3);//运算符种类
uniform_int_distribution<ll>parentheses(0, 100);//括号

ll gcd(ll a, ll b)//求最大公因数
{
	return b == 0 ? a : gcd(b, a % b);
}
struct Number//自然数结构体
{
	ll numerator, denominator;//numerator：分子，denominator：分母
	Number operator + (const Number& x) const
	{
		ll temp1 = numerator * x.denominator + x.numerator * denominator;
		ll temp2 = denominator * x.denominator;
		return { temp1 / gcd(abs(temp1),abs(temp2)),temp2 / gcd(abs(temp1),abs(temp2)) };
	}
	Number operator - (const Number& x) const
	{
		ll temp1 = numerator * x.denominator - x.numerator * denominator;
		ll temp2 = denominator * x.denominator;
		return { temp1 / gcd(abs(temp1),abs(temp2)),temp2 / gcd(abs(temp1),abs(temp2)) };
	}
	Number operator * (const Number& x) const
	{
		ll temp1 = numerator * x.numerator;
		ll temp2 = denominator * x.denominator;
		return { temp1 / gcd(abs(temp1),abs(temp2)),temp2 / gcd(abs(temp1),abs(temp2)) };
	}
	Number operator / (const Number& x) const
	{
		ll temp1 = numerator * x.denominator;
		ll temp2 = denominator * x.numerator;
		return { temp1 / gcd(abs(temp1),abs(temp2)),temp2 / gcd(abs(temp1),abs(temp2)) };
	}
};
string addParentheses(string s)//随机添加括号
{
	string temp = "";
	ll i, tempidx, cnt1 = 0, cnt2 = 0, idx = -1, idx1 = -1, idx2 = -1;
	for (i = 0; i < (ll)s.size(); i++)
	{
		if (s[i] == '+' || s[i] == '-') cnt1++, idx = i;
		else if (s[i] == '*' || (s[i] == '/' && s[i - 1] == ' ' && s[i + 1] == ' ')) cnt2++;
	}
	if (cnt1 != 0 && cnt2 != 0 && parentheses(randomNumberGenerator) % parenthesesProbability == 0)
	{
		tempidx = idx - 2;
		while (tempidx >= 0)
		{
			if (s[tempidx] == ' ')
			{
				idx1 = tempidx;
				break;
			}
			tempidx--;
		}
		tempidx = idx + 2;
		while (tempidx < (ll)s.size())
		{
			if (s[tempidx] == ' ')
			{
				idx2 = tempidx;
				break;
			}
			tempidx++;
		}
		if (idx1 == -1)
		{
			temp += "(";
			for (i = 0; i < idx2; i++) temp += s[i];
			temp += ")";
			for (; i < (ll)s.size(); i++) temp += s[i];
		}
		else if (idx2 == -1)
		{
			for (i = 0; i <= idx1; i++) temp += s[i];
			temp += "(";
			for (; i < (ll)s.size(); i++) temp += s[i];
			temp += ")";
		}
		else if (idx1 != -1 && idx2 != -1)
		{
			for (i = 0; i <= idx1; i++) temp += s[i];
			temp += "(";
			for (; i < idx2; i++) temp += s[i];
			temp += ")";
			for (; i < (ll)s.size(); i++) temp += s[i];
		}
		return temp;
	}
	else
	{
		return s;
	}
}
Number getNum(string s, ll idx)//获取表达式中的自然数
{
	ll num1 = 0, num2 = 0, num3 = 0, temp = 0;
	while (s[idx] != ' ' && idx < (ll)s.size())
	{
		if ('0' <= s[idx] && s[idx] <= '9') temp = temp * 10 + s[idx] - '0';
		if (s[idx] == '\'') num1 = temp, temp = 0;
		if (s[idx] == '/') num2 = temp, temp = 0;
		idx++;
	}
	if (num1 == 0 && num2 == 0 && num3 == 0) num2 = temp, num3 = 1;
	else num3 = temp;
	num2 += num3 * num1;
	ll g = gcd(num2, num3);
	num2 /= g; num3 /= g;
	return{ num2,num3 };
}
string getString(Number x)//将自然数化为正确形式
{
	string ans = "";
	if (x.numerator == 0)//0
	{
		ans += "0";
	}
	else if (x.numerator >= x.denominator)//带分数
	{
		ans += to_string(x.numerator / x.denominator);
		if (x.numerator % x.denominator != 0) ans += "'" + to_string(x.numerator % x.denominator) + "/" + to_string(x.denominator);
	}
	else//真分数
	{
		ans += to_string(x.numerator) + "/" + to_string(x.denominator);
	}
	return ans;
}
string getSimpleAns(string s)//计算无括号式子答案
{
	vector<Number>num;
	vector<char>sym;
	Number temp = { 0,0 };
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		if ('0' <= s[i] && s[i] <= '9')
		{
			temp = getNum(s, i);
			num.push_back(temp);
			while (s[i] != ' ' && i < (ll)s.size()) i++;
		}
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
		{
			sym.push_back(s[i]);
		}
	}
	vector<Number>newnum;
	vector<char>newsym;
	temp = num[0];
	for (ll i = 0; i < (ll)sym.size(); i++)
	{
		if (sym[i] == '+' || sym[i] == '-')
		{
			newnum.push_back(temp);
			newsym.push_back(sym[i]);
			temp = num[i + 1];
		}
		else if (sym[i] == '*')
		{
			temp = temp * num[i + 1];
		}
		else if (sym[i] == '/')
		{
			temp = temp / num[i + 1];
		}
	}
	newnum.push_back(temp);
	Number numans = newnum[0];
	for (ll i = 0; i < (ll)newsym.size(); i++)
	{
		if (newsym[i] == '+') numans = numans + newnum[i + 1];
		else if (newsym[i] == '-') numans = numans - newnum[i + 1];
		if (numans.numerator < 0 || numans.denominator < 0) return "F";
	}
	return getString(numans);
}
bool checkParentheses(string s)//查找括号
{
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		if (s[i] == '(' || s[i] == ')') return 1;
	}
	return 0;
}
string getAns(string s)//计算答案
{
	string ans = s;
	while (checkParentheses(ans) == 1)
	{
		ll l = -1, r = -1;
		for (ll i = 0; i < (ll)ans.size(); i++)
		{
			if (ans[i] == '(')
			{
				l = i;
			}
			else if (ans[i] == ')')
			{
				r = i;
				break;
			}
		}
		string sl = ans.substr(0, l);
		string sr = ans.substr(r + 1, (ll)ans.size() - r - 1);
		string sm = getSimpleAns(ans.substr(l + 1, r - l - 1));
		if (sm == "F") return "F";
		ans = sl + sm + sr;
	}
	return getSimpleAns(ans);
}
void generateQuestion()//生成问题
{
	ofstream exercises("Exercises.txt");
	ofstream answer("Answers.txt");
	if (!exercises.is_open())
	{
		cout << "Can not open the file: Exercises.txt" << endl;
		exit(0);
	}
	if (!answer.is_open())
	{
		cout << "Can not open the file: Answers.txt" << endl;
		exit(0);
	}
	for (ll i = 0; i < questionNum; i++)
	{
		ll symbolNum = symbolNumRange(randomNumberGenerator);//符号数量
		string question = "";
		for (ll j = 0; j <= symbolNum; j++)
		{
			ll denominator = uniform_int_distribution<ll>(1, denominatorRange)(randomNumberGenerator);//分母
			ll numerator = uniform_int_distribution<ll>(1, denominator * maxRange - 1)(randomNumberGenerator);//分子
			string symbol = allSymbol[symbolRange(randomNumberGenerator)];//符号
			string temp = getString({ numerator ,denominator });//化为正确形式
			question += temp;//加上数字
			if (j != symbolNum) question += " " + symbol + " ";//加上符号
		}
		question = addParentheses(question);//添加括号
		string ans = getAns(question);
		if (ans == "F")
		{
			i--;
		}
		else
		{
			exercises << i + 1 << "." << question << endl;
			answer << i + 1 << "." << ans << endl;
		}
	}
	exercises.close();
	answer.close();
}
string getTrue(string s)//去除标号
{
	ll idx = -1;
	for (ll i = 0; i < (ll)s.size(); i++)
	{
		if (s[i] == '.')
		{
			idx = i;
			break;
		}
	}
	return s.substr(idx + 1, (ll)s.size() - idx - 1);
}
void outputCheckAns(vector<ll>correct, vector<ll>wrong)//输出判断对错并进行数量统计的结果
{
	ofstream grade("Grade.txt");
	if (!grade.is_open())
	{
		cout << "Can not open the file: Grade.txt" << endl;
		exit(0);
	}
	grade << "Correct: " << correct.size() << " (";
	for (ll i = 0; i < (ll)correct.size(); i++)
	{
		grade << correct[i];
		if (i != (ll)correct.size() - 1) grade << ", ";
	}
	grade << ")" << endl;
	grade << "Wrong: " << wrong.size() << " (";
	for (ll i = 0; i < (ll)wrong.size(); i++)
	{
		grade << wrong[i];
		if (i != (ll)wrong.size() - 1) grade << ", ";
	}
	grade << ")" << endl;
	grade.close();
}
void checkAns()//判断答案对错并进行数量统计
{
	ifstream exercises(exerciseFile);
	ifstream answer(answerFile);
	if (!exercises.is_open())
	{
		cout << "Can not open the file: " << exerciseFile << endl;
		exit(0);
	}
	if (!answer.is_open())
	{
		cout << "Can not open the file: " << answerFile << endl;
		exit(0);
	}
	vector<string>question, ans;
	string s;
	while (getline(exercises, s)) question.push_back(s);
	while (getline(answer, s)) ans.push_back(s);
	vector<ll>correct, wrong;
	for (ll i = 0; i < (ll)question.size(); i++)
	{
		if (getAns(getTrue(question[i])) == getTrue(ans[i])) correct.push_back(i + 1);
		else wrong.push_back(i + 1);
	}
	outputCheckAns(correct, wrong);
	exercises.close();
	answer.close();
}

int main(int argc, char* argv[])
{
	if (argc == 5)
	{
		if (string(argv[1]) == "-n" && string(argv[3]) == "-r")
		{
			questionNum = atoi(argv[2]);
			maxRange = atoi(argv[4]);
			generateQuestion();
			cout << "Finish";
		}
		else if (string(argv[1]) == "-e" && string(argv[3]) == "-a")
		{
			exerciseFile = string(argv[2]);
			answerFile = string(argv[4]);
			checkAns();
			cout << "Finish";
		}
	}
	else
	{
		cout << "Input Error" << endl;
		exit(0);
	}
}
//cd C:\Users\26973\Desktop\Tools\C++ Code\SEPartnerProject\x64\Debug
//SEPartnerProject.exe -n 10 -r 10
//SEPartnerProject.exe -e exercisefile.txt -a answerfile.txt
