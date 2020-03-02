#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
int d;

struct book {
	int id;
	int score;
};

struct BookComparator{
	bool operator()(book const &b1,book const &b2) {
		return b1.score>b2.score;
	}
};

struct library {
	int id;
	int signup;
	int m;
	priority_queue<book,vector<book>,BookComparator> bookQ;

};

struct LibraryComparator {
	bool operator()(library const &l1,library const &l2) {
		return (d-l1.signup)>(d-l2.signup);
	}
};



unordered_map<int,bool> processed;
unordered_map<int,bool> processedLib;
unordered_map<int,vector<int> > output;
priority_queue<library,vector<library>, LibraryComparator> libraryQ;
priority_queue<library,vector<library>, LibraryComparator> outputOrder;

void processActiveLib(vector<library> &processList) {
	for(auto &lib:processList) {
		int count = 0;
		while(!lib.bookQ.empty()&&count<lib.m) {
			book temp = lib.bookQ.top();
			lib.bookQ.pop();
			output[lib.id].push_back(temp.id);
			count++;
		}
	}
}

int main() {
	unordered_map<int,int> bookScoreMap;
	long long int b,l;
	cin>>b>>l>>d;
	for(int i=0;i<b;i++) {
		int id,score;
		cin>>score;
		bookScoreMap[i] = score;
	}
	
	for(int i=0;i<l;i++) {
		int n,t,m;
		cin>>n>>t>>m;
		library temp;
		temp.m = m;
		temp.id = i;
		temp.signup = t;
		for(int i=0;i<n;i++) {
			int id;
			cin>>id;
			int score = bookScoreMap[id];
			book tempBook;
			tempBook.id = id;
			tempBook.score = score;
			if(processed[tempBook.id])
			temp.bookQ.push(tempBook);
		}
		libraryQ.push(temp);
	}
	outputOrder = libraryQ;
	int lastsignedup = 0;
	vector<library> processList;
	for(int i=0;i<d;i++) {
		if(libraryQ.empty())
			break;
		library cur = libraryQ.top();
		if(cur.bookQ.size()==0)
		{
			libraryQ.pop();
			continue;
		}
		if(lastsignedup<=i)
		{
			libraryQ.pop();
			processList.push_back(cur);
			processedLib[cur.id] = true;
			lastsignedup += cur.signup;
		}
		processActiveLib(processList);
	}
	for(auto &it:processedLib) {
		if(output[it.first].size()==0)
		{
			processedLib.erase(it.first);
		}
	}
	cout<<processedLib.size()<<endl;
	while(!outputOrder.empty())
	{
		library lib = outputOrder.top();
		outputOrder.pop();
		if(processedLib[lib.id]) {
			cout<<lib.id<<" "<<output[lib.id].size()<<endl;
			for(int i=0;i<output[lib.id].size();i++) {
				cout<<output[lib.id][i]<<" ";
			}
			cout<<endl;
		}
	}
	// your code goes here
	return 0;
}


