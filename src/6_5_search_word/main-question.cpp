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
//(1) your code ��ʵ��CQueryResult���вι��캯��


string makeAppend(int _n, const string& _original, const string& _append)
{
	return _n > 1 ? _original + _append : _original;
}
//(2) your code ��ʵ��CQueryResult����������������
ostream& operator<<(ostream& os, const CQueryResult& queryResult)
{




	return os;
}

class CTextQuery
{
public:
	//��ȡ�ļ����ݣ����ڴ������ɽṹ���ı��ڲ��ҵ����ݽṹ
	CTextQuery(ifstream& _fin);
	//�ṩ���û��Ĳ�ѯ�ӿ�
	CQueryResult query(const string& queryWord) const;
public:
	friend ostream& operator<<(ostream& os, const CTextQuery& _queryResult);

private:
	shared_ptr<vector<string> > m_allLineText;
	//���������ʱ������ϣ�������к�����������к�����Ӧ�����Դ������ܵ�
	map<string, shared_ptr<set<size_t> > > m_wordMap;
};
CTextQuery::CTextQuery(ifstream& _fin)
	:m_allLineText(new vector<string>)
{
	string lineText;
	int currentLine = 0;
	while (getline(_fin, lineText))
	{
		//cout<<currentLine+1<<" "<<lineText<<endl;//��ӡԭ�İ�������
		//(4) your code ����ȡ����һ�зŵ���Ա�����������


		istringstream iss(lineText);
		string word;
		while (iss >> word)
		{
			auto& lines = m_wordMap[word];//û�лᴴ���յ�shared_ptr,ע��������������ͣ��кκô�����
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
	//(3) your code ��ʵ�ֲ�ѯ�ӿ�
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
	//��ȡ�ļ����ݣ����ڴ������ɽṹ���ı��ڲ��ҵ����ݽṹ
	CTextQuery textQuery(fin);
	CQueryResult queryResult = textQuery.query("second");
	cout << queryResult << endl;

	return 0;
}