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

void SourceLine::delComments() //�R����
{
	for (int n = 0; n < sourceLine.size(); n++)
	{
		if (sourceLine[n] == '/' && sourceLine[n + 1] == '/') //�Y��e�M�U�@�泣�O'/'
		{
			sourceLine.erase(n); //�h�qn�}�l�᭱���R
			break; //�R�������A���X�j��
		}
	}
}

void SourceLine::delStrConst() //�R�r��
{
	int begin = 0, end = 0; //�]�w�_�I�B���I
	while ((begin = sourceLine.find('"', begin)) != npos) //�Y�b�Ӧr�ꤺ�����Ĥ@�����޸�(�C���qbegin�}�l��A�]�Cerase�@���Abegin��C�檺�ȳ��|��)
	{
		end = sourceLine.find('"', begin + 1); //�h�M��ĤG�����޸�(�q�Ĥ@�����޸����U�@��}�l��)
		sourceLine.erase(begin, end - begin + 1); //�qn�}�l�R���@�q����(end - begin + 1 == length)
	}
}

void SourceLine::delCharConst() //�R�r��
{
	int begin = 0, end = 0; //�]�w�_�I�B���I
	while ((begin = sourceLine.find('\'', begin)) != npos) //�Y�b�Ӧr�ꤺ�����Ĥ@�ӳ�޸�(�C���qbegin�}�l��A�]�Cerase�@���Abegin��C�檺�ȳ��|��)
	{
		end = sourceLine.find('\'', begin + 1); //�h�M��ĤG�ӳ�޸�(�q�Ĥ@�ӳ�޸����U�@��}�l��)
		sourceLine.erase(begin, end - begin + 1); //�qn�}�l�R���@�q����(end - begin + 1 == length)
	}
}

void SourceLine::extractIdentifiers(vector< Identifier >& identifiers) //����Identifiers
{
	int begin = 0, end = 0; //�]�w�_�I�B���I
	for (int n = 0; n < sourceLine.size(); n++)
	{
		if (isalpha(sourceLine[n])) //�Y�Ӯ�O�^��r��
		{
			begin = n; //�N�Ӯ檺��m��begin
			while (++n) //n�� + 1��A����while���P�_����(�Y�ϥ�n++�A�bn == 0�����p�U�|���Q�P�w��false�An�A + 1)
			{
				if (!(isalnum(sourceLine[n]) || sourceLine[n] == '_')) //�Y�Ӯ椣�O�^��r���B�Ʀr�Ω��u
				{
					end = n; //�h�N�Ӯ檺��m��end
					break; //���end����m��Y���X�j��
				}
			}
			identifiers.push_back(sourceLine.substr(begin, end - begin)); //identifiers�W�[1��ñN�����X���l�r��[�J�䤤(end - begin == �l�r�����)
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