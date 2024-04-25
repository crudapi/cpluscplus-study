#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class CQueryResult
{
public:
	CQueryResult() {};
	CQueryResult(const string& queryWord, shared_ptr<set<size_t> > lines
		, shared_ptr<vector<string> > lineText);
	friend ostream& operator<<(ostream& os, const CQueryResult& queryResult);

private:
	string m_queryWord;
	shared_ptr<set<size_t> > m_linesFound;
	shared_ptr<vector<string> > m_allLineText;
};
//(1) your code 请实现CQueryResult的有参构造函数


string makeAppend(int _n, const string& _original, const string& _append)
{
	return _n > 1 ? _original + _append : _original;
}
//(2) your code 请实现CQueryResult类的输出操作符重载
ostream& operator<<(ostream& os, const CQueryResult& queryResult)
{




	return os;
}

class CTextQuery
{
public:
	//读取文件内容，在内存中生成结构化的便于查找的数据结构
	CTextQuery(ifstream& _fin);
	//提供给用户的查询接口
	CQueryResult query(const string& queryWord) const;
public:
	friend ostream& operator<<(ostream& os, const CTextQuery& _queryResult);

private:
	shared_ptr<vector<string> > m_allLineText;
	//按行输出的时候我们希望按照行号输出，所以行号容器应该是自带排序功能的
	map<string, shared_ptr<set<size_t> > > m_wordMap;
};
CTextQuery::CTextQuery(ifstream& _fin)
	:m_allLineText(new vector<string>)
{
	string lineText;
	int currentLine = 0;
	while (getline(_fin, lineText))
	{
		//cout<<currentLine+1<<" "<<lineText<<endl;//打印原文包括行数
		//(4) your code 将读取到的一行放到成员变量里存起来


		istringstream iss(lineText);
		string word;
		while (iss >> word)
		{
			auto& lines = m_wordMap[word];//没有会创建空的shared_ptr,注意这里的引用类型（有何好处？）
			if (!lines)
			{
				lines.reset(new set<size_t>);
			}
			lines->insert(currentLine);
		}
		++currentLine;
	}
}

CQueryResult CTextQuery::query(const string& word) const
{
	//(3) your code 请实现查询接口
	CQueryResult result;


	return result;
}
int main()
{
	string file("input_file.txt");
	ifstream fin(file);
	if (!fin)
	{
		cout << "can't open file " << file << endl;
		return -1;
	}
	//读取文件内容，在内存中生成结构化的便于查找的数据结构
	CTextQuery textQuery(fin);
	CQueryResult queryResult = textQuery.query("second");
	cout << queryResult << endl;

	return 0;
}