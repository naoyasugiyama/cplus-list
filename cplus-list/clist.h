#pragma once

#include <cstdint>
#include <assert.h>

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
		list_count--;

		//test
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
			p = this->Erase(top);//ƒŠƒXƒg‚©‚ç”‚ª‚·
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

	LinkNode* InserLast(const char* name, uint64_t playscore, uint64_t playtime)
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

	// æ“ª‚Ì—v‘f‚ðíœ
	void EraseFirst()
	{
		this->Erase(this->First());
	}

	// ––”ö‚Ì—v‘f‚ðíœ
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


// todo 
class Ranking
{
public:
	Ranking():
		LinkTable(nullptr)
	{
		if (this->LinkTable == nullptr)
		{
			this->LinkTable = new LinkList();
		}
	}

	~Ranking()
	{
		if (this->LinkTable != nullptr)
		{
			delete(this->LinkTable);
		}
		this->LinkTable = nullptr;
	}

private:
	LinkList* LinkTable;

};