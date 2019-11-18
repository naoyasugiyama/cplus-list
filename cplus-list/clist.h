#pragma once

#include <cstdint>
#include <assert.h>

//todo Memory leakの対処


struct userData
{
	char* name;
	uint64_t score;
	uint64_t daytime;

public:

	userData(const char* name, uint64_t score) :
		name(nullptr),
		score(0),
		daytime(0)
	{

		this->copyname(name);
		this->score = score;
	}

	userData(const char* name, uint64_t score, uint64_t playtime) :
		name(nullptr),
		score(0),
		daytime(0)
	{
		this->copyname(name);
		this->score = score;
		this->daytime = playtime;
	}



	~userData()
	{
		if (name != nullptr)
		{
			delete(this->name);
			name = nullptr;
		}
		this->score = 0;
		this->daytime = 0;
	}

private:

	void copyname(const char* name)
	{
		if (this->name != nullptr)
		{
			assert(1);
		}
		size_t len = strlen(name) + 1;
		this->name = new char[len];
		memset(this->name, 0, len);
		memcpy_s(this->name, len, name, len);
	}

};

class LinkNode
{
public:
	LinkNode(const char* name, uint64_t score, LinkNode* prev, LinkNode* next) :
		user_score(nullptr),
		prev(nullptr),
		next(nullptr)
	{
		this->prev = prev;
		this->next = next;
	}

	LinkNode(userData* score, LinkNode* prev, LinkNode* next) :
		user_score(nullptr),
		prev(nullptr),
		next(nullptr)
	{
		this->user_score = score;
		this->prev = prev;
		this->next = next;
	}

	~LinkNode() {
	}

	void addList(LinkNode* prev, LinkNode* next)
	{
		this->prev = prev;
		this->next = next;
	}

	userData* GetScore()
	{
		return this->user_score;
	}

	

	// getter/setter
	LinkNode* GetNext()
	{
		return this->next;
	}

	void SetNext(LinkNode* next)
	{
		this->next = next;
	}


	LinkNode* GetPrev()
	{
		return this->prev;
	}

	void SetPrev(LinkNode* prev)
	{
		this->prev = prev;
	}

private:
	userData* user_score;
	LinkNode* next;
	LinkNode* prev;
};

class LinkList
{
public:

	LinkList() :
		Dummy(nullptr),
		list_count(0)
	{
		userData* score = new userData("dummy", 0);

		this->Dummy = new LinkNode(score, nullptr, nullptr);
		this->Dummy->SetNext(this->Dummy);
		this->Dummy->SetPrev(this->Dummy);
		list_count++;
	}

	~LinkList()
	{
		this->DeleteList();
		delete(this->Dummy);

		//check
		std::cout << "delete count:[" << list_count << "]" << std::endl;

	}


	LinkNode* First()
	{
		return this->Dummy->GetNext();
	}

	LinkNode* Last()
	{
		return this->Dummy->GetPrev();
	}

	LinkNode* End()
	{
		return this->Dummy;
	}


	void DeleteList()
	{
		LinkNode* p = nullptr;
		LinkNode* top = this->First();
		while (top != this->End())
		{
			p = this->Erase(top);//リストから剥がす
			userData* pscore = top->GetScore();
			if (pscore != nullptr)
			{
				delete(pscore);
				pscore = nullptr;
			}
			if (top != nullptr) {
				delete(top);//delete 
				top = nullptr;
			}
			top = p;//
		}

	}


	// insert
	LinkNode* InsertAfter(LinkNode* n, userData* score)
	{
		LinkNode* m = new LinkNode(score, n, n->GetNext());
		n->GetNext()->SetPrev(m);
		n->SetNext(m);
		list_count++;
		return m;
	}

	LinkNode* InsertBeforer(LinkNode* n, userData* score)
	{
		LinkNode* m = new LinkNode(score, n->GetPrev(), n);
		n->GetPrev()->SetNext(m);
		n->SetPrev(m);
		list_count++;
		return m;
	}

	LinkNode* InserFirst(userData* score)
	{
		return this->InsertAfter(this->Dummy, score);
	}

	LinkNode* InsertLast(userData* score)
	{
		return this->InsertBeforer(this->Dummy, score);
	}

	LinkNode* InsertLast(const char* name, uint64_t palyscore)
	{
		userData* score = new userData(name, palyscore);
		return this->InsertBeforer(this->Dummy, score);
	}

	LinkNode* InsertLast(const char* name, uint64_t playscore, uint64_t playtime)
	{
		userData* score = new userData(name, playscore, playtime);
		return this->InsertBeforer(this->Dummy, score);
	}


	LinkNode* Erase(LinkNode* n)
	{
		if (n == this->Dummy)
		{
			return this->Dummy;
		}
		n->GetPrev()->SetNext(n->GetNext());
		n->GetNext()->SetPrev(n->GetPrev());
		list_count--;
		return n->GetNext();
	}

	void EraseFirst()
	{
		this->Erase(this->First());
	}

	void EraseLast()
	{
		this->Erase(this->Last());
	}

	const int Count()
	{
		int count = 0;
		LinkNode* n = this->First();

		for (; n != Dummy; n = n->GetNext())
		{
			count++;
		}
		return count;
	}


	LinkNode* sort_score()
	{
		if (this->First()->GetNext() == this->Last())
		{
			return this->First();
		}

		LinkNode* itr = this->First()->GetNext();
		LinkNode* result = nullptr;
		LinkNode* bkNext = nullptr;

		for (; itr != Dummy; itr = bkNext)
		{
			bkNext = itr->GetNext();
			uint64_t score = itr->GetScore()->score;

			for (LinkNode* find = this->First(); find != itr; find = find->GetNext())
			{
				if (score < find->GetScore()->score)
				{
					this->Erase(itr);

					itr->SetPrev(find->GetPrev());
					itr->SetNext(find);

					find->GetPrev()->SetNext(itr);
					find->SetPrev(itr);
					break;
				}
			}
		}

		return result;
	}

private:
	LinkNode* Dummy;
	int       list_count;
};


// list check test
class ListCheck
{
public:
	ListCheck() :
		LinkTable(nullptr),
		print_counter(9)
	{
		if (this->LinkTable == nullptr)
		{
			this->LinkTable = new LinkList();
		}
	}

	~ListCheck()
	{
		if (this->LinkTable != nullptr)
		{
			delete(this->LinkTable);
		}
		this->LinkTable = nullptr;
	}


private:

	// userdata * 
	userData*  GetUserData(const char* username) 
	{
		userData* data = nullptr;
		LinkNode* top = this->LinkTable->First();

		while (top != LinkTable->End())
		{
			userData* var = top->GetScore();
			if (var != nullptr)
			{
				if( strcmp( username, var->name ) == 0 )
				{
					data = var;
					break;
				}
			}
			top = top->GetNext();
		}
		return data;
	}

	//!> get user node linklist
	LinkNode* GetUserNode(const char* username, LinkList* srcList )
	{
		LinkNode* result = nullptr;

		if (srcList == nullptr)
		{
			assert("assert srcNode Null");
		}
		LinkNode* top = srcList->First();

		while (top != srcList->End())
		{
			userData* var = top->GetScore();
			if (strcmp( var->name, username) == 0 )
			{
				result = top;
				break;
			}
			top = top->GetNext();
		}

		return result;
	}


public:

	void Insert(const char* name, uint64_t score)
	{
		this->LinkTable->InsertLast(name, score);
	}

	void   Insert(const char* name, uint64_t score, uint64_t daytime)
	{
		this->LinkTable->InsertLast(name, score, daytime);
	}


	//!> dummyが表示されるバグ
	void PinrtListTop10(LinkList* srclist)
	{
//		std::cout << "call print list top 10 " << std::endl;
		
		if (srclist == nullptr)
		{
			assert("src list null");
		}

		srclist->sort_score();
		uint16_t count = 0;

		LinkNode* itr = srclist->Last();
		for (; itr != LinkTable->End(); itr = itr->GetPrev())
		{
			userData* var = itr->GetScore();
			if (var != nullptr )
			{
				if (var->daytime != 0) 
				{
					std::cout << "name:[" << var->name << "] score:[" << var->score << "]" << "daytime:[" << var->daytime << "]" << std::endl;
				}
				else
				{
					std::cout << "name:[" << var->name << "] score:[" << var->score << "]" << std::endl;
				}
			}

			count++;
			if (count > print_counter) break;
		}

		std::cout << "----------------------------------------" << std::endl;

	}

	void PrintTop10()
	{
		std::cout << "call PrintTop10 :" << std::endl;
//		this->LinkTable->sort_score();

		this->PinrtListTop10(this->LinkTable);
	}


	//!>
	void PrintUser(const char* username ) 
	{
		std::cout << "call PrintUser :" << username << std::endl;
		
		LinkNode* top = LinkTable->First();

		while(top != LinkTable->End() )
		{
			userData* var = top->GetScore();
			
			if (var != nullptr)
			{
				if (strcmp(var->name , username) == 0)
				{
					std::cout << "score:[" << var->score << "]" << std::endl;
				}
			}
			top = top->GetNext();
		}

		std::cout << "----------------------------------------" << std::endl;
	}


	//!> 同じ名前のユーザーのスコアが高い方を優先して表示する
	void PrintTop10_Not_duplicate()
	{
		std::cout << "call PrintTop10 distinct" << std::endl;

		LinkList* notDuplicate = new LinkList();
		LinkNode* top = LinkTable->First();

		while (top != LinkTable->End())
		{
			userData* var = top->GetScore();
			if (var != nullptr)
			{
				//!> table内に同名ユーザーがいる場合
				LinkNode* checkNode = this->GetUserNode(var->name, notDuplicate);
				//!> usernameが登録されていないか元データから抽出する
				if (checkNode == nullptr)
				{
					notDuplicate->InsertLast(var->name, var->score);
				}
				else
				{
					//!> usernameのスコアが高い方を上書き登録する
					userData* duplicate = checkNode->GetScore();
					if (var->score > duplicate->score) 
					{
						duplicate->score = var->score;
					}
				}
			}
			top = top->GetNext();
		}

		//!> print top10 node
		this->PinrtListTop10(notDuplicate);
		delete notDuplicate;
	}

	//6桁固定されてるのを変更したい
	void PrintTop10_FilterTimeYM( const uint64_t daytime )
	{
		// WHERE=daytime
		std::cout << "call ProntTop 10 Filter" << std::endl;
		LinkList* filterlist = new LinkList();
		LinkNode* top = LinkTable->First();

		uint64_t ym = daytime / 1000000;

		while (top != LinkTable->End())
		{
			userData* var = top->GetScore();
			
			if(var != nullptr )
			{
				uint64_t ym2 = var->daytime / 1000000;// year , month 
				if ( ym == ym2)
				{
					filterlist->InsertLast( var->name, var->score,var->daytime);
				}
			}
			top = top->GetNext();
		}


		this->PinrtListTop10(filterlist);

		delete filterlist;

	}



private:
	LinkList* LinkTable;
	const uint16_t print_counter;// print count 
};