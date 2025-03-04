// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

SourceLine::SourceLine()
	: sourceLine()
{
}

SourceLine& SourceLine::operator=(const char* const ptr)
{
	sourceLine = ptr;
	return *this;
}

void SourceLine::delComments() //刪註解
{
	for (int n = 0; n < sourceLine.size(); n++)
	{
		if (sourceLine[n] == '/' && sourceLine[n + 1] == '/') //若當前和下一格都是'/'
		{
			sourceLine.erase(n); //則從n開始後面全刪
			break; //刪除完畢，跳出迴圈
		}
	}
}

void SourceLine::delStrConst() //刪字串
{
	int begin = 0, end = 0; //設定起點、終點
	while ((begin = sourceLine.find('"', begin)) != npos) //若在該字串內有找到第一個雙引號(每次從begin開始找，因每erase一次，begin後每格的值都會改)
	{
		end = sourceLine.find('"', begin + 1); //則尋找第二個雙引號(從第一個雙引號的下一格開始找)
		sourceLine.erase(begin, end - begin + 1); //從n開始刪除一段長度(end - begin + 1 == length)
	}
}

void SourceLine::delCharConst() //刪字元
{
	int begin = 0, end = 0; //設定起點、終點
	while ((begin = sourceLine.find('\'', begin)) != npos) //若在該字串內有找到第一個單引號(每次從begin開始找，因每erase一次，begin後每格的值都會改)
	{
		end = sourceLine.find('\'', begin + 1); //則尋找第二個單引號(從第一個單引號的下一格開始找)
		sourceLine.erase(begin, end - begin + 1); //從n開始刪除一段長度(end - begin + 1 == length)
	}
}

void SourceLine::extractIdentifiers(vector< Identifier >& identifiers) //提取Identifiers
{
	int begin = 0, end = 0; //設定起點、終點
	for (int n = 0; n < sourceLine.size(); n++)
	{
		if (isalpha(sourceLine[n])) //若該格是英文字母
		{
			begin = n; //將該格的位置給begin
			while (++n) //n先 + 1後再成為while的判斷條件(若使用n++，在n == 0的情況下會先被判定為false，n再 + 1)
			{
				if (!(isalnum(sourceLine[n]) || sourceLine[n] == '_')) //若該格不是英文字母、數字或底線
				{
					end = n; //則將該格的位置給end
					break; //找到end的位置後即跳出迴圈
				}
			}
			identifiers.push_back(sourceLine.substr(begin, end - begin)); //identifiers增加1格並將提取出的子字串加入其中(end - begin == 子字串長度)
		}
	}
}

bool operator==(const SourceLine& lhs, const SourceLine& rhs)
{
	return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=(const SourceLine& lhs, const SourceLine& rhs)
{
	return !(lhs == rhs);
}