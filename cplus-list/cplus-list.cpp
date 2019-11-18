// cplus-list.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "clist.h"


void test()
{
	//!> test code 
	ListCheck check1;

		
	check1.Insert("AAAA", 200);
	check1.Insert("BBBB", 1500);
	check1.Insert("VVC", 100);
	check1.Insert("CteaA", 101);
	check1.Insert("AAAA", 150);
	check1.Insert("AAAA", 300);
	check1.Insert("AAAA", 10100);

	check1.PrintTop10();


	check1.PrintUser("AAAA");



	ListCheck check2;

	check2.Insert("Player1", 100);
	check2.Insert("Player2", 1000);
	check2.Insert("Player3", 300);
	check2.Insert("Player2", 900);
	check2.Insert("Player3", 10);
	check2.Insert("Player4", 150);
	check2.Insert("Player5", 1400);
	check2.Insert("Player6", 310);
	check2.Insert("Player7", 950);
	check2.Insert("Player8", 160);
	check2.Insert("Player9", 1500);
	check2.Insert("Player10", 310);
	check2.Insert("Player11", 910);
	check2.Insert("Player12", 910);
	check2.Insert("Player3", 910);
	check2.Insert("Player4", 910);

	check2.PrintTop10_Not_duplicate();


	ListCheck check3;
/*
	check3.Insert("user1", 201807181158ull, 10);
	check3.Insert("user2", 201807161158ull, 100);
	check3.Insert("user3", 201806100900ull, 1000);
	check3.Insert("user1", 201805032130ull, 300);
	check3.Insert("user2", 201808042013ull, 900);
	check3.Insert("user3", 201809141325ull, 10);
	*/
	check3.Insert("user1",  10, 201807181158ull);
	check3.Insert("user2", 100, 201807161158ull);
	check3.Insert("user3", 1000, 201806100900ull);
	check3.Insert("user1", 300, 201805032130ull);
	check3.Insert("user2", 9000, 201808042013ull);
	check3.Insert("user3", 25, 201809141325ull);
	check3.Insert("user4", 300, 201810141325ull);
	check3.Insert("user5", 90, 201801141325ull);
	check3.Insert("user6", 1213, 201812141325ull);
	check3.Insert("user7", 1502, 201811141325ull);
	check3.Insert("user8", 135, 201802141325ull);
	check3.Insert("user9", 188, 201803141325ull);
	check3.Insert("user10", 702, 201807141325ull);

	check3.PrintTop10_FilterTimeYM(201807000000ull);//todo


}

int main()
{

	test();


	getchar();

    return 0;
}

